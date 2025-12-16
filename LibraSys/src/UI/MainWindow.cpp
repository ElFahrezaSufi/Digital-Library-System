#include "MainWindow.h"
#include "Components/BookCard.h"
#include "LibraryEngine.h"
#include "Book.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QInputDialog>
#include <QPushButton>
#include <QGroupBox>
#include <QPainter>

// ============================================================================
// MainWindow Implementation: Dashboard with Modern Grid Layout
// ============================================================================

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), sortAscending(true), currentView(0) {
    
    // Get engine instance
    engine = LibraryEngine::getInstance();
    
    setupUI();
    setupMenuBar();
    applyStyles();
    
    // Display catalog by default
    displayCatalog();
}

MainWindow::~MainWindow() {
    // Engine is singleton, don't delete
}

void MainWindow::setupUI() {
    // Main widget
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    
    // Navigation sidebar
    navBar = new NavBar(this);
    navBar->setFixedWidth(200);
    connect(navBar, &NavBar::catalogRequested, this, &MainWindow::onCatalogView);
    connect(navBar, &NavBar::queueRequested, this, &MainWindow::onQueueView);
    connect(navBar, &NavBar::historyRequested, this, &MainWindow::onHistoryView);
    connect(navBar, &NavBar::statsRequested, this, &MainWindow::onStatsView);
    
    // Right side content area
    QWidget* rightPanel = new QWidget(this);
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setSpacing(0);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    
    createContentArea();
    
    QWidget* topBarWidget = createTopBarWidget();
    rightLayout->addWidget(topBarWidget);
    rightLayout->addWidget(scrollArea);
    
    mainLayout->addWidget(navBar);
    mainLayout->addWidget(rightPanel, 1);
    
    setCentralWidget(centralWidget);
    setWindowTitle("LibraSys - Digital Library Management System");
    resize(1280, 800);
}

QWidget* MainWindow::createTopBarWidget() {
    QWidget* topBar = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(topBar);
    layout->setContentsMargins(20, 15, 20, 15);
    
    // Search bar
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("🔍 Search books by title, author, or genre...");
    searchBar->setMinimumWidth(400);
    connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    
    // Sort combo
    sortCombo = new QComboBox(this);
    sortCombo->addItem("Sort by Title");
    sortCombo->addItem("Sort by Author");
    sortCombo->addItem("Sort by Year");
    sortCombo->addItem("Sort by Popularity");
    connect(sortCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &MainWindow::onSortChanged);
    
    // Sort order button
    sortOrderButton = new QPushButton("↑ Ascending", this);
    sortOrderButton->setCursor(Qt::PointingHandCursor);
    connect(sortOrderButton, &QPushButton::clicked, this, &MainWindow::onSortOrderToggled);
    
    layout->addWidget(searchBar, 1);
    layout->addWidget(sortCombo);
    layout->addWidget(sortOrderButton);
    
    // Set minimal custom styling for top bar (uses global theme)
    topBar->setStyleSheet(R"(
        QWidget {
            background-color: #252535;
            border-bottom: 2px solid #16161a;
        }
    )");
    
    return topBar;
}

void MainWindow::createContentArea() {
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    contentWidget = new QWidget();
    gridLayout = new QGridLayout(contentWidget);
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(20, 20, 20, 20);
    
    scrollArea->setWidget(contentWidget);
}

void MainWindow::setupMenuBar() {
    QMenuBar* menuBar = new QMenuBar(this);
    
    QMenu* fileMenu = menuBar->addMenu("&File");
    fileMenu->addAction("&Exit", this, &QWidget::close);
    
    QMenu* viewMenu = menuBar->addMenu("&View");
    viewMenu->addAction("&Catalog", this, &MainWindow::onCatalogView);
    viewMenu->addAction("&Queue", this, &MainWindow::onQueueView);
    viewMenu->addAction("&History", this, &MainWindow::onHistoryView);
    
    QMenu* helpMenu = menuBar->addMenu("&Help");
    helpMenu->addAction("&About", [this]() {
        QMessageBox::about(this, "About LibraSys",
            "<h3>LibraSys v1.0</h3>"
            "<p><b>Digital Library Management System</b></p>"
            "<p>Built with Qt and custom data structures:</p>"
            "<ul>"
            "<li>Doubly Linked List for catalog storage</li>"
            "<li>Graph for book recommendations</li>"
            "<li>Stack for browsing history (LIFO)</li>"
            "<li>Queue for borrow requests (FIFO)</li>"
            "<li>Quick Sort algorithm (O(n log n))</li>"
            "</ul>"
            "<p>© 2025 LibraSys Project</p>");
    });
    
    setMenuBar(menuBar);
}

void MainWindow::applyStyles() {
    // Styles now handled by global QSS (StyleLoader)
    // No local overrides needed
}

// ============================================================================
// VIEW SWITCHING
// ============================================================================

void MainWindow::onCatalogView() {
    currentView = 0;
    displayCatalog();
}

void MainWindow::onQueueView() {
    currentView = 1;
    displayQueue();
}

void MainWindow::onHistoryView() {
    currentView = 2;
    displayHistory();
}

void MainWindow::onStatsView() {
    currentView = 3;
    displayStatistics();
}

// ============================================================================
// DISPLAY FUNCTIONS
// ============================================================================

void MainWindow::displayCatalog() {
    clearGrid();
    
    DoublyLinkedList<Book>& catalog = engine->getCatalog();
    int row = 0, col = 0;
    
    for (auto it = catalog.begin(); it != catalog.end(); ++it) {
        BookCard* card = new BookCard(&(*it), contentWidget);
        connect(card, &BookCard::borrowClicked, this, &MainWindow::onBookBorrow);
        connect(card, &BookCard::detailsClicked, this, &MainWindow::onBookDetails);
        addBookCardToGrid(card, row, col);
    }
    
    // Update window title
    setWindowTitle(QString("LibraSys - Catalog (%1 books)").arg(catalog.size()));
}

void MainWindow::displayQueue() {
    clearGrid();
    
    QLabel* titleLabel = new QLabel("<h2>📋 Borrow Request Queue</h2>", contentWidget);
    gridLayout->addWidget(titleLabel, 0, 0, 1, 4);
    
    DoublyLinkedList<BorrowRequest> requests = engine->getAllBorrowRequests();
    
    if (requests.isEmpty()) {
        QLabel* emptyLabel = new QLabel("No pending borrow requests.", contentWidget);
        emptyLabel->setStyleSheet("font-size: 16px; color: #7f8c8d; padding: 40px;");
        gridLayout->addWidget(emptyLabel, 1, 0, 1, 4, Qt::AlignCenter);
        return;
    }
    
    int row = 1;
    for (auto it = requests.begin(); it != requests.end(); ++it) {
        Book* book = engine->findBookById(it->bookId);
        if (!book) continue;
        
        QGroupBox* requestBox = new QGroupBox(contentWidget);
        QHBoxLayout* layout = new QHBoxLayout(requestBox);
        
        QLabel* infoLabel = new QLabel(
            QString("<b>%1</b><br>By: %2<br>User: %3<br>Date: %4")
            .arg(book->title)
            .arg(book->author)
            .arg(it->userName)
            .arg(it->requestDate),
            requestBox
        );
        
        QPushButton* processBtn = new QPushButton("Process", requestBox);
        processBtn->setFixedWidth(100);
        connect(processBtn, &QPushButton::clicked, [this]() {
            if (engine->processNextBorrow()) {
                QMessageBox::information(this, "Success", "Borrow request processed!");
                displayQueue();
            }
        });
        
        layout->addWidget(infoLabel, 1);
        layout->addWidget(processBtn);
        
        gridLayout->addWidget(requestBox, row++, 0, 1, 4);
    }
    
    setWindowTitle(QString("LibraSys - Queue (%1 requests)").arg(requests.size()));
}

void MainWindow::displayHistory() {
    clearGrid();
    
    QLabel* titleLabel = new QLabel("<h2>🕒 Recently Viewed Books</h2>", contentWidget);
    gridLayout->addWidget(titleLabel, 0, 0, 1, 4);
    
    DoublyLinkedList<Book*> history = engine->getRecentlyViewed(20);
    
    if (history.isEmpty()) {
        QLabel* emptyLabel = new QLabel("No viewing history yet.", contentWidget);
        emptyLabel->setStyleSheet("font-size: 16px; color: #7f8c8d; padding: 40px;");
        gridLayout->addWidget(emptyLabel, 1, 0, 1, 4, Qt::AlignCenter);
        return;
    }
    
    int row = 1, col = 0;
    for (auto it = history.begin(); it != history.end(); ++it) {
        BookCard* card = new BookCard(*it, contentWidget);
        connect(card, &BookCard::detailsClicked, this, &MainWindow::onBookDetails);
        addBookCardToGrid(card, row, col);
    }
    
    setWindowTitle(QString("LibraSys - History (%1 books)").arg(history.size()));
}

void MainWindow::displayStatistics() {
    clearGrid();
    
    QLabel* titleLabel = new QLabel("<h2>📊 Library Statistics</h2>", contentWidget);
    gridLayout->addWidget(titleLabel, 0, 0, 1, 4);
    
    QLabel* statsLabel = new QLabel(
        QString("<h3>Total Books: %1</h3>"
                "<h3>Pending Requests: %2</h3>"
                "<h3>History Items: %3</h3>")
        .arg(engine->getTotalBooks())
        .arg(engine->getQueueSize())
        .arg(engine->getRecentlyViewed(100).size()),
        contentWidget
    );
    statsLabel->setStyleSheet("padding: 20px; font-size: 18px;");
    gridLayout->addWidget(statsLabel, 1, 0, 1, 4);
    
    QLabel* popularLabel = new QLabel("<h3>📈 Most Popular Books:</h3>", contentWidget);
    gridLayout->addWidget(popularLabel, 2, 0, 1, 4);
    
    DoublyLinkedList<Book*> popular = engine->getMostPopular(5);
    int row = 3, col = 0;
    for (auto it = popular.begin(); it != popular.end(); ++it) {
        BookCard* card = new BookCard(*it, contentWidget);
        connect(card, &BookCard::detailsClicked, this, &MainWindow::onBookDetails);
        addBookCardToGrid(card, row, col);
    }
    
    setWindowTitle("LibraSys - Statistics");
}

// ============================================================================
// GRID MANAGEMENT
// ============================================================================

void MainWindow::clearGrid() {
    QLayoutItem* item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

void MainWindow::addBookCardToGrid(BookCard* card, int& row, int& col) {
    gridLayout->addWidget(card, row, col);
    col++;
    if (col >= 4) { // 4 cards per row
        col = 0;
        row++;
    }
}

void MainWindow::refreshGrid() {
    switch (currentView) {
        case 0: displayCatalog(); break;
        case 1: displayQueue(); break;
        case 2: displayHistory(); break;
        case 3: displayStatistics(); break;
    }
}

// ============================================================================
// EVENT HANDLERS
// ============================================================================

void MainWindow::onSearchTextChanged(const QString& text) {
    if (currentView != 0) return; // Only search in catalog view
    
    clearGrid();
    
    if (text.isEmpty()) {
        displayCatalog();
        return;
    }
    
    DoublyLinkedList<Book*> results = engine->searchGeneral(text);
    
    if (results.isEmpty()) {
        QLabel* noResults = new QLabel("No books found matching your search.", contentWidget);
        noResults->setStyleSheet("font-size: 16px; color: #7f8c8d; padding: 40px;");
        gridLayout->addWidget(noResults, 0, 0, 1, 4, Qt::AlignCenter);
        return;
    }
    
    int row = 0, col = 0;
    for (auto it = results.begin(); it != results.end(); ++it) {
        BookCard* card = new BookCard(*it, contentWidget);
        connect(card, &BookCard::borrowClicked, this, &MainWindow::onBookBorrow);
        connect(card, &BookCard::detailsClicked, this, &MainWindow::onBookDetails);
        addBookCardToGrid(card, row, col);
    }
}

void MainWindow::onSortChanged(int index) {
    LibraryEngine::SortCriteria criteria;
    switch (index) {
        case 0: criteria = LibraryEngine::BY_TITLE; break;
        case 1: criteria = LibraryEngine::BY_AUTHOR; break;
        case 2: criteria = LibraryEngine::BY_YEAR; break;
        case 3: criteria = LibraryEngine::BY_POPULARITY; break;
        default: criteria = LibraryEngine::BY_TITLE;
    }
    
    engine->sortCatalog(criteria, sortAscending);
    refreshGrid();
}

void MainWindow::onSortOrderToggled() {
    sortAscending = !sortAscending;
    sortOrderButton->setText(sortAscending ? "↑ Ascending" : "↓ Descending");
    
    // Re-apply current sort
    onSortChanged(sortCombo->currentIndex());
}

void MainWindow::onBookBorrow(int bookId) {
    bool ok;
    QString userName = QInputDialog::getText(this, "Borrow Request",
        "Enter your name:", QLineEdit::Normal, "", &ok);
    
    if (ok && !userName.isEmpty()) {
        engine->addBorrowRequest(bookId, userName);
        QMessageBox::information(this, "Success", 
            "Your borrow request has been added to the queue!");
    }
}

void MainWindow::onBookDetails(int bookId) {
    engine->addToHistory(bookId);
    
    BookDetailsDialog* dialog = new BookDetailsDialog(bookId, this);
    connect(dialog, &BookDetailsDialog::relatedBookClicked, this, &MainWindow::onBookDetails);
    dialog->exec();
    delete dialog;
}

// ============================================================================
// BookDetailsDialog Implementation
// ============================================================================

BookDetailsDialog::BookDetailsDialog(int bookId, QWidget* parent)
    : QDialog(parent), bookId_(bookId) {
    
    engine = LibraryEngine::getInstance();
    setupUI();
    loadBookData();
}

void BookDetailsDialog::setupUI() {
    setWindowTitle("Book Details");
    setModal(true);
    resize(700, 600);
    setObjectName("bookDetailsDialog");
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(16);
    
    // Top section: Cover + Basic Info
    QHBoxLayout* topLayout = new QHBoxLayout();
    topLayout->setSpacing(20);
    
    coverLabel = new QLabel(this);
    coverLabel->setFixedSize(200, 280);
    coverLabel->setObjectName("dialogCover");
    
    QVBoxLayout* infoLayout = new QVBoxLayout();
    infoLayout->setSpacing(8);
    
    titleLabel = new QLabel(this);
    titleLabel->setWordWrap(true);
    titleLabel->setObjectName("dialogTitle");
    
    authorLabel = new QLabel(this);
    authorLabel->setObjectName("dialogAuthor");
    
    infoLayout->addWidget(titleLabel);
    infoLayout->addWidget(authorLabel);
    infoLayout->addStretch();
    
    topLayout->addWidget(coverLabel);
    topLayout->addLayout(infoLayout, 1);
    
    // Description
    QLabel* descLabel = new QLabel("📖 Description:", this);
    descLabel->setObjectName("sectionLabel");
    
    descriptionText = new QTextEdit(this);
    descriptionText->setReadOnly(true);
    descriptionText->setMaximumHeight(150);
    descriptionText->setObjectName("descriptionText");
    
    // Related books section
    QLabel* relatedLabel = new QLabel("🔗 Related Books You Might Like:", this);
    relatedLabel->setObjectName("sectionLabel");
    
    relatedBooksWidget = new QWidget(this);
    relatedBooksWidget->setObjectName("relatedBooksContainer");
    QHBoxLayout* relatedLayout = new QHBoxLayout(relatedBooksWidget);
    relatedLayout->setSpacing(10);
    relatedLayout->setContentsMargins(0, 0, 0, 0);
    
    // Close button
    QPushButton* closeBtn = new QPushButton("Close", this);
    closeBtn->setObjectName("closeButton");
    closeBtn->setCursor(Qt::PointingHandCursor);
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(descLabel);
    mainLayout->addWidget(descriptionText);
    mainLayout->addWidget(relatedLabel);
    mainLayout->addWidget(relatedBooksWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(closeBtn);
    
    // Dark Academia Theme for Dialog
    setStyleSheet(R"(
        QDialog#bookDetailsDialog {
            background-color: #1E1E2E;
        }
        
        QLabel#dialogTitle {
            font-size: 24px;
            font-weight: 700;
            color: #FFFFFE;
            padding: 8px 0px;
        }
        
        QLabel#dialogAuthor {
            font-size: 16px;
            font-style: italic;
            color: #94A1B2;
        }
        
        QLabel#sectionLabel {
            font-size: 14px;
            font-weight: 600;
            color: #7F5AF0;
            padding: 8px 0px;
        }
        
        QTextEdit#descriptionText {
            background-color: #252535;
            color: #FFFFFE;
            border: 2px solid #3a3a4a;
            border-radius: 8px;
            padding: 12px;
            font-size: 13px;
            line-height: 1.5;
        }
        
        QTextEdit#descriptionText:focus {
            border: 2px solid #7F5AF0;
        }
        
        QWidget#relatedBooksContainer {
            background-color: transparent;
        }
        
        QPushButton#closeButton {
            background-color: #7F5AF0;
            color: #FFFFFE;
            border: none;
            border-radius: 8px;
            padding: 12px 24px;
            font-size: 14px;
            font-weight: 600;
            min-height: 28px;
        }
        
        QPushButton#closeButton:hover {
            background-color: #9D7FF0;
            box-shadow: 0 4px 12px rgba(127, 90, 240, 0.3);
        }
        
        QPushButton#closeButton:pressed {
            background-color: #6B48D6;
        }
        
        QPushButton#relatedBookButton {
            background-color: #252535;
            color: #FFFFFE;
            border: 2px solid #7F5AF0;
            border-radius: 8px;
            padding: 10px 16px;
            font-size: 13px;
            font-weight: 600;
            min-height: 28px;
        }
        
        QPushButton#relatedBookButton:hover {
            background-color: rgba(127, 90, 240, 0.1);
            border-color: #9D7FF0;
        }
        
        QPushButton#relatedBookButton:pressed {
            background-color: rgba(127, 90, 240, 0.2);
        }
    )");
}

void BookDetailsDialog::loadBookData() {
    Book* book = engine->findBookById(bookId_);
    if (!book) return;
    
    // Set basic info
    titleLabel->setText(book->title);
    authorLabel->setText(QString("by %1 (%2)").arg(book->author).arg(book->year));
    descriptionText->setText(book->description);
    
    // Create cover (same logic as BookCard)
    QPixmap cover(200, 280);
    QPainter painter(&cover);
    
    QColor bgColor;
    if (book->genre == "Technology") bgColor = QColor(41, 128, 185);
    else if (book->genre == "Fiction") bgColor = QColor(142, 68, 173);
    else if (book->genre == "History") bgColor = QColor(211, 84, 0);
    else if (book->genre == "Science") bgColor = QColor(39, 174, 96);
    else if (book->genre == "Philosophy") bgColor = QColor(192, 57, 43);
    else bgColor = QColor(52, 73, 94);
    
    painter.fillRect(cover.rect(), bgColor);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Segoe UI", 48));
    
    QString icon;
    if (book->genre == "Technology") icon = "💻";
    else if (book->genre == "Fiction") icon = "📖";
    else if (book->genre == "History") icon = "🏛️";
    else if (book->genre == "Science") icon = "🔬";
    else if (book->genre == "Philosophy") icon = "🤔";
    else icon = "📚";
    
    painter.drawText(QRect(0, 80, 200, 80), Qt::AlignCenter, icon);
    coverLabel->setPixmap(cover);
    
    // Load related books from graph
    DoublyLinkedList<Book*> related = engine->getRelatedBooks(bookId_, 4);
    QHBoxLayout* relatedLayout = qobject_cast<QHBoxLayout*>(relatedBooksWidget->layout());
    
    for (auto it = related.begin(); it != related.end(); ++it) {
        QPushButton* relatedBtn = new QPushButton((*it)->title, relatedBooksWidget);
        relatedBtn->setObjectName("relatedBookButton");
        relatedBtn->setMaximumWidth(160);
        relatedBtn->setToolTip(QString("By %1").arg((*it)->author));
        relatedBtn->setCursor(Qt::PointingHandCursor);
        
        int relatedId = (*it)->id;
        connect(relatedBtn, &QPushButton::clicked, [this, relatedId]() {
            accept(); // Close current dialog
            emit relatedBookClicked(relatedId);
        });
        
        relatedLayout->addWidget(relatedBtn);
    }
    
    if (related.isEmpty()) {
        QLabel* noRelated = new QLabel("No related books found.", relatedBooksWidget);
        noRelated->setStyleSheet("color: #94A1B2; font-style: italic;");
        relatedLayout->addWidget(noRelated);
    }
}
