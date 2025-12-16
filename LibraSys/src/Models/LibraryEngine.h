#ifndef LIBRARYENGINE_H
#define LIBRARYENGINE_H

#include "DataStore.h"
#include "Book.h"
#include <QString>
#include <QDateTime>

// ============================================================================
// LibraryEngine: Core Business Logic Layer
// Purpose: Manages all book operations, search, sorting, and recommendations
// Architecture: Singleton pattern for global access
// ============================================================================

class LibraryEngine {
private:
    // Core Data Structures (Custom implementations)
    DoublyLinkedList<Book> catalog;           // Main book database
    Graph recommendationGraph;                 // Genre similarity network
    Stack<int> recentlyViewed;                // User browsing history (book IDs)
    Queue<BorrowRequest> borrowQueue;         // Pending borrow requests
    
    int nextBookId;
    
    // Singleton instance
    static LibraryEngine* instance_;
    
    // Private constructor for singleton
    LibraryEngine();
    
    // Initialize sample data
    void initializeSampleData();
    void buildRecommendationGraph();
    
public:
    // Singleton accessor
    static LibraryEngine* getInstance();
    
    // Book Management
    void addBook(const Book& book);
    bool removeBook(int bookId);
    Book* findBookById(int bookId);
    DoublyLinkedList<Book>& getCatalog() { return catalog; }
    
    // Search Operations
    DoublyLinkedList<Book*> searchByTitle(const QString& query);
    DoublyLinkedList<Book*> searchByAuthor(const QString& query);
    DoublyLinkedList<Book*> searchByGenre(const QString& genre);
    DoublyLinkedList<Book*> searchGeneral(const QString& query);
    
    // Sorting Operations
    enum SortCriteria { BY_TITLE, BY_AUTHOR, BY_YEAR, BY_POPULARITY };
    void sortCatalog(SortCriteria criteria, bool ascending = true);
    
    // Recommendation System
    DoublyLinkedList<Book*> getRelatedBooks(int bookId, int count = 5);
    void addBookRelation(int bookId1, int bookId2, float similarity = 1.0f);
    
    // User History
    void addToHistory(int bookId);
    DoublyLinkedList<Book*> getRecentlyViewed(int count = 10);
    void clearHistory();
    
    // Borrowing Queue
    void addBorrowRequest(int bookId, const QString& userName);
    BorrowRequest* getNextBorrowRequest();
    bool processNextBorrow();
    int getQueueSize() const { return borrowQueue.size(); }
    DoublyLinkedList<BorrowRequest> getAllBorrowRequests();
    
    // Statistics
    int getTotalBooks() const { return catalog.size(); }
    DoublyLinkedList<Book*> getMostPopular(int count = 5);
    
    // Destructor
    ~LibraryEngine();
};

#endif // LIBRARYENGINE_H
