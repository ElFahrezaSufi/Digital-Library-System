#include "NavBar.h"

NavBar::NavBar(QWidget* parent) : QWidget(parent) {
    setupUI();
    applyStyles();
    setActiveButton(catalogButton); // Default active
}

void NavBar::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(8);
    mainLayout->setContentsMargins(16, 20, 16, 20);
    
    // Set object name for QSS targeting
    setObjectName("NavBar");
    
    // Title
    titleLabel = new QLabel("LibraSys", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #7F5AF0; padding: 10px;");
    
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(30);
    
    // Navigation buttons with object names
    catalogButton = new QPushButton("📚  Catalog", this);
    queueButton = new QPushButton("📋  My Queue", this);
    historyButton = new QPushButton("🕒  History", this);
    statsButton = new QPushButton("📊  Statistics", this);
    
    // Set object names for QSS styling
    catalogButton->setObjectName("navButton");
    queueButton->setObjectName("navButton");
    historyButton->setObjectName("navButton");
    statsButton->setObjectName("navButton");
    
    catalogButton->setCursor(Qt::PointingHandCursor);
    queueButton->setCursor(Qt::PointingHandCursor);
    historyButton->setCursor(Qt::PointingHandCursor);
    statsButton->setCursor(Qt::PointingHandCursor);
    
    catalogButton->setCheckable(true);
    queueButton->setCheckable(true);
    historyButton->setCheckable(true);
    statsButton->setCheckable(true);
    
    connect(catalogButton, &QPushButton::clicked, this, &NavBar::onCatalogClicked);
    connect(queueButton, &QPushButton::clicked, this, &NavBar::onQueueClicked);
    connect(historyButton, &QPushButton::clicked, this, &NavBar::onHistoryClicked);
    connect(statsButton, &QPushButton::clicked, this, &NavBar::onStatsClicked);
    
    mainLayout->addWidget(catalogButton);
    mainLayout->addWidget(queueButton);
    mainLayout->addWidget(historyButton);
    mainLayout->addWidget(statsButton);
    mainLayout->addStretch();
    
    setLayout(mainLayout);
}

void NavBar::applyStyles() {
    // Styles are now handled by global stylesheet in StyleLoader
    // No local styles needed - inherits from QSS
}

void NavBar::setActiveButton(QPushButton* button) {
    // Uncheck all buttons
    catalogButton->setChecked(false);
    queueButton->setChecked(false);
    historyButton->setChecked(false);
    statsButton->setChecked(false);
    
    // Check the active button (uses :checked state from QSS)
    button->setChecked(true);
}

void NavBar::onCatalogClicked() {
    setActiveButton(catalogButton);
    emit catalogRequested();
}

void NavBar::onQueueClicked() {
    setActiveButton(queueButton);
    emit queueRequested();
}

void NavBar::onHistoryClicked() {
    setActiveButton(historyButton);
    emit historyRequested();
}

void NavBar::onStatsClicked() {
    setActiveButton(statsButton);
    emit statsRequested();
}
