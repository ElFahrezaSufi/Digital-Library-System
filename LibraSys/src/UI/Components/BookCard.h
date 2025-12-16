#ifndef BOOKCARD_H
#define BOOKCARD_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

// Forward declaration
struct Book;

// ============================================================================
// BookCard: Modern UI Component for Book Display
// Design: Card-based layout with cover image, metadata, and action button
// Pattern: Reusable widget following Qt's composition model
// ============================================================================

class BookCard : public QWidget {
    Q_OBJECT
    
private:
    int bookId_;
    
    // UI Components
    QLabel* coverLabel;
    QLabel* titleLabel;
    QLabel* authorLabel;
    QLabel* genreLabel;
    QLabel* yearLabel;
    QPushButton* borrowButton;
    QPushButton* detailsButton;
    
    void setupUI();
    void applyStyles();
    
public:
    explicit BookCard(const Book* book, QWidget* parent = nullptr);
    
    void setBook(const Book* book);
    int getBookId() const { return bookId_; }
    void setAvailability(bool available);
    
signals:
    void borrowClicked(int bookId);
    void detailsClicked(int bookId);
    
private slots:
    void onBorrowClicked();
    void onDetailsClicked();
};

#endif // BOOKCARD_H
