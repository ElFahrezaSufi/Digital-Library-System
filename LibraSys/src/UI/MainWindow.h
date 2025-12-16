#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QScrollArea>
#include <QWidget>
#include <QGridLayout>
#include <QDialog>
#include <QTextEdit>
#include "Components/NavBar.h"

class LibraryEngine;
class BookCard;

// ============================================================================
// MainWindow: Primary Application Window with Dashboard
// Architecture: MVC pattern - View layer interacting with LibraryEngine
// Features: Search, Sort, Grid Layout, Navigation, Details Modal
// ============================================================================

class MainWindow : public QMainWindow {
    Q_OBJECT
    
private:
    // Core components
    LibraryEngine* engine;
    NavBar* navBar;
    
    // Top bar controls
    QLineEdit* searchBar;
    QComboBox* sortCombo;
    QPushButton* sortOrderButton;
    
    // Content area
    QScrollArea* scrollArea;
    QWidget* contentWidget;
    QGridLayout* gridLayout;
    
    // State
    bool sortAscending;
    int currentView; // 0=Catalog, 1=Queue, 2=History, 3=Stats
    
    void setupUI();
    void setupMenuBar();
    QWidget* createTopBarWidget();
    void createContentArea();
    void applyStyles();
    
    void displayCatalog();
    void displayQueue();
    void displayHistory();
    void displayStatistics();
    
    void refreshGrid();
    void clearGrid();
    void addBookCardToGrid(BookCard* card, int& row, int& col);
    
    void showBookDetails(int bookId);
    void processBorrowRequest(int bookId);
    
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    
private slots:
    void onSearchTextChanged(const QString& text);
    void onSortChanged(int index);
    void onSortOrderToggled();
    
    void onCatalogView();
    void onQueueView();
    void onHistoryView();
    void onStatsView();
    
    void onBookBorrow(int bookId);
    void onBookDetails(int bookId);
};

// ============================================================================
// BookDetailsDialog: Modal window for detailed book information
// ============================================================================

class BookDetailsDialog : public QDialog {
    Q_OBJECT
    
private:
    int bookId_;
    LibraryEngine* engine;
    
    QLabel* coverLabel;
    QLabel* titleLabel;
    QLabel* authorLabel;
    QTextEdit* descriptionText;
    QWidget* relatedBooksWidget;
    
    void setupUI();
    void loadBookData();
    
public:
    explicit BookDetailsDialog(int bookId, QWidget* parent = nullptr);
    
signals:
    void relatedBookClicked(int bookId);
};

#endif // MAINWINDOW_H
