#include "BookCard.h"
#include "Book.h"
#include <QPixmap>
#include <QPainter>

// ============================================================================
// BookCard Implementation: Modern Card-Based Book Widget
// Visual Design: Inspired by modern e-commerce and streaming platforms
// ============================================================================

BookCard::BookCard(const Book* book, QWidget* parent)
    : QWidget(parent), bookId_(0) {
    setupUI();
    applyStyles();
    if (book) {
        setBook(book);
    }
}

void BookCard::setupUI() {
    // Set object name for QSS targeting
    setObjectName("BookCard");
    
    // Main vertical layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(8);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    
    // Cover image placeholder
    coverLabel = new QLabel(this);
    coverLabel->setFixedSize(150, 200);
    coverLabel->setAlignment(Qt::AlignCenter);
    coverLabel->setScaledContents(false);
    
    // Create placeholder cover
    QPixmap placeholder(150, 200);
    QPainter painter(&placeholder);
    painter.fillRect(placeholder.rect(), QColor(52, 73, 94));
    painter.setPen(QColor(189, 195, 199));
    painter.setFont(QFont("Segoe UI", 10));
    painter.drawText(placeholder.rect(), Qt::AlignCenter, "📚\nBook\nCover");
    coverLabel->setPixmap(placeholder);
    
    // Title label
    titleLabel = new QLabel(this);
    titleLabel->setObjectName("titleLabel");
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    titleLabel->setMaximumWidth(150);
    titleLabel->setMinimumHeight(40);
    
    // Author label
    authorLabel = new QLabel(this);
    authorLabel->setObjectName("authorLabel");
    authorLabel->setWordWrap(true);
    authorLabel->setAlignment(Qt::AlignLeft);
    authorLabel->setMaximumWidth(150);
    
    // Genre and Year container
    QHBoxLayout* metaLayout = new QHBoxLayout();
    genreLabel = new QLabel(this);
    genreLabel->setObjectName("metaLabel");
    yearLabel = new QLabel(this);
    yearLabel->setObjectName("metaLabel");
    metaLayout->addWidget(genreLabel);
    metaLayout->addWidget(yearLabel);
    metaLayout->addStretch();
    
    // Details button
    detailsButton = new QPushButton("View Details", this);
    detailsButton->setObjectName("secondaryButton");
    detailsButton->setCursor(Qt::PointingHandCursor);
    connect(detailsButton, &QPushButton::clicked, this, &BookCard::onDetailsClicked);
    
    // Borrow button (uses default primary button style)
    borrowButton = new QPushButton("Borrow", this);
    borrowButton->setCursor(Qt::PointingHandCursor);
    connect(borrowButton, &QPushButton::clicked, this, &BookCard::onBorrowClicked);
    
    // Add widgets to layout
    mainLayout->addWidget(coverLabel, 0, Qt::AlignHCenter);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(authorLabel);
    mainLayout->addLayout(metaLayout);
    mainLayout->addWidget(detailsButton);
    mainLayout->addWidget(borrowButton);
    mainLayout->addStretch();
    
    setLayout(mainLayout);
}

void BookCard::applyStyles() {
    // All styles now handled by global QSS (StyleLoader)
    // Card uses #BookCard, labels use #titleLabel, #authorLabel, #metaLabel
    // Buttons use #secondaryButton and default button styles
}

void BookCard::setBook(const Book* book) {
    if (!book) return;
    
    bookId_ = book->id;
    
    // Set text content
    titleLabel->setText(book->title);
    authorLabel->setText(book->author);
    genreLabel->setText(book->genre);
    yearLabel->setText(QString::number(book->year));
    
    // Set availability
    setAvailability(book->isAvailable);
    
    // Update cover with genre-specific color
    QPixmap cover(150, 200);
    QPainter painter(&cover);
    
    // Genre-based color scheme
    QColor bgColor;
    if (book->genre == "Technology") {
        bgColor = QColor(41, 128, 185);
    } else if (book->genre == "Fiction") {
        bgColor = QColor(142, 68, 173);
    } else if (book->genre == "History") {
        bgColor = QColor(211, 84, 0);
    } else if (book->genre == "Science") {
        bgColor = QColor(39, 174, 96);
    } else if (book->genre == "Philosophy") {
        bgColor = QColor(192, 57, 43);
    } else {
        bgColor = QColor(52, 73, 94);
    }
    
    painter.fillRect(cover.rect(), bgColor);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Segoe UI", 10, QFont::Bold));
    
    // Draw genre icon
    QString icon;
    if (book->genre == "Technology") icon = "💻";
    else if (book->genre == "Fiction") icon = "📖";
    else if (book->genre == "History") icon = "🏛️";
    else if (book->genre == "Science") icon = "🔬";
    else if (book->genre == "Philosophy") icon = "🤔";
    else icon = "📚";
    
    painter.setFont(QFont("Segoe UI", 32));
    painter.drawText(QRect(0, 60, 150, 60), Qt::AlignCenter, icon);
    
    painter.setFont(QFont("Segoe UI", 9, QFont::Bold));
    painter.drawText(QRect(10, 140, 130, 50), Qt::AlignCenter | Qt::TextWordWrap, 
                     book->title.left(40) + (book->title.length() > 40 ? "..." : ""));
    
    coverLabel->setPixmap(cover);
}

void BookCard::setAvailability(bool available) {
    borrowButton->setEnabled(available);
    borrowButton->setText(available ? "Borrow" : "Unavailable");
}

void BookCard::onBorrowClicked() {
    emit borrowClicked(bookId_);
}

void BookCard::onDetailsClicked() {
    emit detailsClicked(bookId_);
}
