#include "LibraryEngine.h"
#include <algorithm>

// Initialize static instance
LibraryEngine* LibraryEngine::instance_ = nullptr;

LibraryEngine::LibraryEngine() : nextBookId(1) {
    initializeSampleData();
    buildRecommendationGraph();
}

LibraryEngine* LibraryEngine::getInstance() {
    if (!instance_) {
        instance_ = new LibraryEngine();
    }
    return instance_;
}

LibraryEngine::~LibraryEngine() {
    // Custom data structures handle their own cleanup
}

// ============================================================================
// DATA INITIALIZATION: 15 Diverse Books Across Multiple Genres
// ============================================================================

void LibraryEngine::initializeSampleData() {
    // Technology & Programming (5 books)
    catalog.append(Book(nextBookId++, 
        "The C++ Programming Language", 
        "Bjarne Stroustrup", 
        "Technology", 2013,
        "978-0321563842",
        "Comprehensive guide to C++ from its creator. Essential for mastering modern C++ techniques."));
    
    catalog.append(Book(nextBookId++, 
        "Introduction to Algorithms", 
        "Thomas H. Cormen", 
        "Technology", 2009,
        "978-0262033848",
        "The definitive guide to algorithm design and analysis. A must-have for computer science students."));
    
    catalog.append(Book(nextBookId++, 
        "Clean Code", 
        "Robert C. Martin", 
        "Technology", 2008,
        "978-0132350884",
        "A handbook of agile software craftsmanship teaching how to write readable, maintainable code."));
    
    catalog.append(Book(nextBookId++, 
        "Design Patterns", 
        "Erich Gamma", 
        "Technology", 1994,
        "978-0201633612",
        "Essential catalog of software design patterns for object-oriented programming."));
    
    catalog.append(Book(nextBookId++, 
        "Artificial Intelligence: A Modern Approach", 
        "Stuart Russell", 
        "Technology", 2020,
        "978-0134610993",
        "Comprehensive introduction to AI theory and practice, covering machine learning and neural networks."));
    
    // Fiction (4 books)
    catalog.append(Book(nextBookId++, 
        "1984", 
        "George Orwell", 
        "Fiction", 1949,
        "978-0451524935",
        "Dystopian social science fiction about totalitarian surveillance and thought control."));
    
    catalog.append(Book(nextBookId++, 
        "To Kill a Mockingbird", 
        "Harper Lee", 
        "Fiction", 1960,
        "978-0061120084",
        "Classic novel about racial injustice in the American South through a child's eyes."));
    
    catalog.append(Book(nextBookId++, 
        "The Great Gatsby", 
        "F. Scott Fitzgerald", 
        "Fiction", 1925,
        "978-0743273565",
        "A tale of wealth, love, and the American Dream in the Roaring Twenties."));
    
    catalog.append(Book(nextBookId++, 
        "Brave New World", 
        "Aldous Huxley", 
        "Fiction", 1932,
        "978-0060850524",
        "Dystopian novel about a futuristic society driven by technology and conditioning."));
    
    // History & Biography (3 books)
    catalog.append(Book(nextBookId++, 
        "Sapiens: A Brief History of Humankind", 
        "Yuval Noah Harari", 
        "History", 2011,
        "978-0062316097",
        "An exploration of human history from the Stone Age to the modern age."));
    
    catalog.append(Book(nextBookId++, 
        "The Diary of a Young Girl", 
        "Anne Frank", 
        "History", 1947,
        "978-0553296983",
        "Personal account of a Jewish girl hiding from Nazi persecution during WWII."));
    
    catalog.append(Book(nextBookId++, 
        "Steve Jobs", 
        "Walter Isaacson", 
        "History", 2011,
        "978-1451648539",
        "Authorized biography of Apple's visionary co-founder based on exclusive interviews."));
    
    // Science & Philosophy (3 books)
    catalog.append(Book(nextBookId++, 
        "A Brief History of Time", 
        "Stephen Hawking", 
        "Science", 1988,
        "978-0553380163",
        "Landmark volume on cosmology, black holes, and the nature of time and space."));
    
    catalog.append(Book(nextBookId++, 
        "Thinking, Fast and Slow", 
        "Daniel Kahneman", 
        "Science", 2011,
        "978-0374533557",
        "Nobel Prize winner's exploration of the two systems that drive human thinking."));
    
    catalog.append(Book(nextBookId++, 
        "The Art of War", 
        "Sun Tzu", 
        "Philosophy", -500,
        "978-1599869773",
        "Ancient Chinese military treatise on strategy and tactics applicable to modern life."));
}

// ============================================================================
// RECOMMENDATION GRAPH: Manual Genre Similarity Connections
// Edge Weight = Similarity Score (0.0 - 1.0)
// ============================================================================

void LibraryEngine::buildRecommendationGraph() {
    // Technology Books Cluster (High similarity)
    addBookRelation(1, 2, 0.95f);  // C++ <-> Algorithms
    addBookRelation(1, 3, 0.80f);  // C++ <-> Clean Code
    addBookRelation(1, 4, 0.85f);  // C++ <-> Design Patterns
    addBookRelation(2, 4, 0.90f);  // Algorithms <-> Design Patterns
    addBookRelation(3, 4, 0.92f);  // Clean Code <-> Design Patterns
    addBookRelation(2, 5, 0.75f);  // Algorithms <-> AI
    
    // Fiction Cluster (Dystopian theme)
    addBookRelation(6, 9, 0.88f);  // 1984 <-> Brave New World
    addBookRelation(6, 7, 0.60f);  // 1984 <-> Mockingbird (social themes)
    addBookRelation(7, 8, 0.70f);  // Mockingbird <-> Gatsby (American classics)
    
    // History/Biography Cluster
    addBookRelation(10, 11, 0.75f); // Sapiens <-> Anne Frank
    addBookRelation(10, 12, 0.65f); // Sapiens <-> Steve Jobs
    addBookRelation(11, 6, 0.55f);  // Anne Frank <-> 1984 (dystopian reality)
    
    // Science/Philosophy Bridge
    addBookRelation(13, 14, 0.70f); // Hawking <-> Kahneman
    addBookRelation(14, 15, 0.60f); // Kahneman <-> Art of War (strategy)
    addBookRelation(15, 4, 0.50f);  // Art of War <-> Design Patterns (strategic thinking)
    
    // Cross-genre connections (AI to other fields)
    addBookRelation(5, 13, 0.68f);  // AI <-> Hawking (scientific mind)
    addBookRelation(5, 14, 0.72f);  // AI <-> Thinking (cognitive science)
    addBookRelation(12, 5, 0.55f);  // Steve Jobs <-> AI (tech innovation)
}

// ============================================================================
// SEARCH IMPLEMENTATIONS
// ============================================================================

DoublyLinkedList<Book*> LibraryEngine::searchByTitle(const QString& query) {
    QString lowerQuery = query.toLower();
    return SearchAlgorithms::linearSearch<Book>(catalog, [&](const Book& book) {
        return book.title.toLower().contains(lowerQuery);
    });
}

DoublyLinkedList<Book*> LibraryEngine::searchByAuthor(const QString& query) {
    QString lowerQuery = query.toLower();
    return SearchAlgorithms::linearSearch<Book>(catalog, [&](const Book& book) {
        return book.author.toLower().contains(lowerQuery);
    });
}

DoublyLinkedList<Book*> LibraryEngine::searchByGenre(const QString& genre) {
    QString lowerGenre = genre.toLower();
    return SearchAlgorithms::linearSearch<Book>(catalog, [&](const Book& book) {
        return book.genre.toLower() == lowerGenre;
    });
}

DoublyLinkedList<Book*> LibraryEngine::searchGeneral(const QString& query) {
    QString lowerQuery = query.toLower();
    return SearchAlgorithms::linearSearch<Book>(catalog, [&](const Book& book) {
        return book.title.toLower().contains(lowerQuery) ||
               book.author.toLower().contains(lowerQuery) ||
               book.genre.toLower().contains(lowerQuery) ||
               book.description.toLower().contains(lowerQuery);
    });
}

// ============================================================================
// SORTING IMPLEMENTATIONS (Using Quick Sort - O(n log n))
// ============================================================================

void LibraryEngine::sortCatalog(SortCriteria criteria, bool ascending) {
    if (catalog.isEmpty()) return;
    
    Book** arr = catalog.toArray();
    int size = catalog.size();
    
    // Define comparison functions based on criteria
    std::function<bool(const Book*, const Book*)> compare;
    
    switch (criteria) {
        case BY_TITLE:
            compare = [ascending](const Book* a, const Book* b) {
                return ascending ? (a->title < b->title) : (a->title > b->title);
            };
            break;
        case BY_AUTHOR:
            compare = [ascending](const Book* a, const Book* b) {
                return ascending ? (a->author < b->author) : (a->author > b->author);
            };
            break;
        case BY_YEAR:
            compare = [ascending](const Book* a, const Book* b) {
                return ascending ? (a->year < b->year) : (a->year > b->year);
            };
            break;
        case BY_POPULARITY:
            compare = [ascending](const Book* a, const Book* b) {
                return ascending ? (a->borrowCount < b->borrowCount) : (a->borrowCount > b->borrowCount);
            };
            break;
    }
    
    // Apply Quick Sort algorithm
    SortAlgorithms::quickSort(arr, 0, size - 1, compare);
    
    // Rebuild catalog in sorted order
    DoublyLinkedList<Book> sortedCatalog;
    for (int i = 0; i < size; i++) {
        sortedCatalog.append(*arr[i]);
    }
    
    catalog = sortedCatalog;
    delete[] arr;
}

// ============================================================================
// RECOMMENDATION SYSTEM
// ============================================================================

DoublyLinkedList<Book*> LibraryEngine::getRelatedBooks(int bookId, int count) {
    DoublyLinkedList<Book*> related;
    
    // Get related book IDs from graph
    DoublyLinkedList<int> relatedIds = recommendationGraph.getRelatedBooks(bookId, count);
    
    // Convert IDs to Book pointers
    for (auto it = relatedIds.begin(); it != relatedIds.end(); ++it) {
        Book* book = findBookById(*it);
        if (book) {
            related.append(book);
        }
    }
    
    return related;
}

void LibraryEngine::addBookRelation(int bookId1, int bookId2, float similarity) {
    recommendationGraph.addBidirectionalEdge(bookId1, bookId2, similarity);
}

// ============================================================================
// USER HISTORY (Stack - LIFO)
// ============================================================================

void LibraryEngine::addToHistory(int bookId) {
    recentlyViewed.push(bookId);
}

DoublyLinkedList<Book*> LibraryEngine::getRecentlyViewed(int count) {
    DoublyLinkedList<Book*> history;
    int added = 0;
    
    for (auto it = recentlyViewed.begin(); it != recentlyViewed.end() && added < count; ++it) {
        Book* book = findBookById(*it);
        if (book) {
            history.append(book);
            added++;
        }
    }
    
    return history;
}

void LibraryEngine::clearHistory() {
    recentlyViewed.clear();
}

// ============================================================================
// BORROWING QUEUE (Queue - FIFO)
// ============================================================================

void LibraryEngine::addBorrowRequest(int bookId, const QString& userName) {
    BorrowRequest request;
    request.bookId = bookId;
    request.userName = userName;
    request.requestDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm");
    
    borrowQueue.enqueue(request);
}

BorrowRequest* LibraryEngine::getNextBorrowRequest() {
    return borrowQueue.peek();
}

bool LibraryEngine::processNextBorrow() {
    BorrowRequest* request = borrowQueue.peek();
    if (!request) return false;
    
    Book* book = findBookById(request->bookId);
    if (book) {
        book->isAvailable = false;
        book->borrowCount++;
    }
    
    return borrowQueue.dequeue();
}

DoublyLinkedList<BorrowRequest> LibraryEngine::getAllBorrowRequests() {
    DoublyLinkedList<BorrowRequest> requests;
    for (auto it = borrowQueue.begin(); it != borrowQueue.end(); ++it) {
        requests.append(*it);
    }
    return requests;
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

void LibraryEngine::addBook(const Book& book) {
    catalog.append(book);
    recommendationGraph.addNode(book.id);
}

bool LibraryEngine::removeBook(int bookId) {
    for (auto it = catalog.begin(); it != catalog.end(); ++it) {
        if (it->id == bookId) {
            catalog.remove(*it);
            return true;
        }
    }
    return false;
}

Book* LibraryEngine::findBookById(int bookId) {
    for (auto it = catalog.begin(); it != catalog.end(); ++it) {
        if (it->id == bookId) {
            return &(*it);
        }
    }
    return nullptr;
}

DoublyLinkedList<Book*> LibraryEngine::getMostPopular(int count) {
    DoublyLinkedList<Book*> popular;
    
    if (catalog.isEmpty()) return popular;
    
    // Get array and sort by popularity
    Book** arr = catalog.toArray();
    int size = catalog.size();
    
    std::function<bool(const Book*, const Book*)> compare = [](const Book* a, const Book* b) {
        return a->borrowCount > b->borrowCount;
    };
    SortAlgorithms::quickSort(arr, 0, size - 1, compare);
    
    int limit = (count < size) ? count : size;
    for (int i = 0; i < limit; i++) {
        popular.append(arr[i]);
    }
    
    delete[] arr;
    return popular;
}
