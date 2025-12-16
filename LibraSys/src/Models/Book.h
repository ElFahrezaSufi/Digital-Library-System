#ifndef BOOK_H
#define BOOK_H

#include <QString>

// ============================================================================
// Book Data Structure
// Purpose: Core entity representing a book in the library system
// ============================================================================

struct Book {
    int id;
    QString title;
    QString author;
    QString genre;
    int year;
    QString isbn;
    QString description;
    bool isAvailable;
    int borrowCount; // Popularity metric
    
    // Default constructor
    Book() : id(0), year(0), isAvailable(true), borrowCount(0) {}
    
    // Parameterized constructor
    Book(int id_, QString title_, QString author_, QString genre_, int year_,
         QString isbn_ = "", QString desc_ = "")
        : id(id_), title(title_), author(author_), genre(genre_), 
          year(year_), isbn(isbn_), description(desc_), 
          isAvailable(true), borrowCount(0) {}
    
    // Equality operator (for LinkedList remove operation)
    bool operator==(const Book& other) const {
        return id == other.id;
    }
    
    // Comparison operators for sorting
    bool operator<(const Book& other) const {
        return title < other.title;
    }
};

// Helper struct for borrowing queue
struct BorrowRequest {
    int bookId;
    QString userName;
    QString requestDate;
    
    BorrowRequest() : bookId(0) {}
    BorrowRequest(int id, QString name, QString date)
        : bookId(id), userName(name), requestDate(date) {}
};

#endif // BOOK_H
