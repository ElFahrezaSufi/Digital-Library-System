#ifndef DATASTORE_H
#define DATASTORE_H

#include "Book.h"
#include <QString>
#include <functional>

// ============================================================================
// CUSTOM DATA STRUCTURES IMPLEMENTATION
// Purpose: Manual memory management and algorithm implementation for 
//          educational analysis and performance optimization
// Note: STL containers (std::vector, std::list, std::map) are intentionally
//       avoided to demonstrate low-level data structure understanding
// ============================================================================

// ============================= DOUBLY LINKED LIST ===========================
// Used for: Main Book Catalog Storage
// Complexity: O(1) insertion/deletion at ends, O(n) search
// ============================================================================

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int size_;
    
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size_(0) {}
    
    ~DoublyLinkedList() {
        clear();
    }
    
    // Copy operations
    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), size_(0) {
        Node* current = other.head;
        while (current) {
            append(current->data);
            current = current->next;
        }
    }
    
    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this != &other) {
            clear();
            Node* current = other.head;
            while (current) {
                append(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    void append(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size_++;
    }
    
    void prepend(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size_++;
    }
    
    bool remove(const T& value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }
                
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }
                
                delete current;
                size_--;
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size_ = 0;
    }
    
    int size() const { return size_; }
    bool isEmpty() const { return size_ == 0; }
    
    // Iterator support for range-based loops
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}
        T& operator*() { return current->data; }
        T* operator->() { return &(current->data); }
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };
    
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    
    // For const iteration
    class ConstIterator {
    private:
        const Node* current;
    public:
        ConstIterator(const Node* node) : current(node) {}
        const T& operator*() const { return current->data; }
        const T* operator->() const { return &(current->data); }
        ConstIterator& operator++() { current = current->next; return *this; }
        bool operator!=(const ConstIterator& other) const { return current != other.current; }
    };
    
    ConstIterator begin() const { return ConstIterator(head); }
    ConstIterator end() const { return ConstIterator(nullptr); }
    
    // Access by index (O(n) operation)
    T* at(int index) {
        if (index < 0 || index >= size_) return nullptr;
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return &(current->data);
    }
    
    const T* at(int index) const {
        if (index < 0 || index >= size_) return nullptr;
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return &(current->data);
    }
    
    // Convert to array for sorting (returns pointer array)
    T** toArray() {
        if (size_ == 0) return nullptr;
        T** arr = new T*[size_];
        Node* current = head;
        for (int i = 0; i < size_; i++) {
            arr[i] = &(current->data);
            current = current->next;
        }
        return arr;
    }
};

// ================================= STACK ====================================
// Used for: Recently Viewed Books (User History)
// Complexity: O(1) push/pop/peek
// Principle: LIFO (Last In, First Out)
// ============================================================================

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* top_;
    int size_;
    int maxSize_;
    
public:
    Stack(int maxSize = 50) : top_(nullptr), size_(0), maxSize_(maxSize) {}
    
    ~Stack() {
        clear();
    }
    
    void push(const T& value) {
        // Limit stack size for history
        if (size_ >= maxSize_) {
            // Remove bottom element
            if (top_) {
                Node* current = top_;
                Node* prev = nullptr;
                while (current->next) {
                    prev = current;
                    current = current->next;
                }
                if (prev) {
                    prev->next = nullptr;
                    delete current;
                    size_--;
                }
            }
        }
        
        Node* newNode = new Node(value);
        newNode->next = top_;
        top_ = newNode;
        size_++;
    }
    
    bool pop() {
        if (!top_) return false;
        Node* temp = top_;
        top_ = top_->next;
        delete temp;
        size_--;
        return true;
    }
    
    T* peek() {
        if (!top_) return nullptr;
        return &(top_->data);
    }
    
    const T* peek() const {
        if (!top_) return nullptr;
        return &(top_->data);
    }
    
    bool isEmpty() const { return size_ == 0; }
    int size() const { return size_; }
    
    void clear() {
        while (top_) {
            pop();
        }
    }
    
    // Iterator for traversing stack (top to bottom)
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}
        T& operator*() { return current->data; }
        T* operator->() { return &(current->data); }
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };
    
    Iterator begin() { return Iterator(top_); }
    Iterator end() { return Iterator(nullptr); }
};

// ================================= QUEUE ====================================
// Used for: Book Borrowing Request Queue
// Complexity: O(1) enqueue/dequeue
// Principle: FIFO (First In, First Out)
// ============================================================================

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* front_;
    Node* rear_;
    int size_;
    
public:
    Queue() : front_(nullptr), rear_(nullptr), size_(0) {}
    
    ~Queue() {
        clear();
    }
    
    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (!rear_) {
            front_ = rear_ = newNode;
        } else {
            rear_->next = newNode;
            rear_ = newNode;
        }
        size_++;
    }
    
    bool dequeue() {
        if (!front_) return false;
        Node* temp = front_;
        front_ = front_->next;
        if (!front_) rear_ = nullptr;
        delete temp;
        size_--;
        return true;
    }
    
    T* peek() {
        if (!front_) return nullptr;
        return &(front_->data);
    }
    
    const T* peek() const {
        if (!front_) return nullptr;
        return &(front_->data);
    }
    
    bool isEmpty() const { return size_ == 0; }
    int size() const { return size_; }
    
    void clear() {
        while (front_) {
            dequeue();
        }
    }
    
    // Iterator for traversing queue (front to rear)
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}
        T& operator*() { return current->data; }
        T* operator->() { return &(current->data); }
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };
    
    Iterator begin() { return Iterator(front_); }
    Iterator end() { return Iterator(nullptr); }
};

// ================================= GRAPH ====================================
// Used for: Book Recommendation System (Genre Similarity)
// Structure: Adjacency List representation
// Nodes: Books, Edges: Genre/Topic Relationships
// ============================================================================

class Graph {
private:
    struct EdgeNode {
        int targetBookId;
        float weight; // Similarity score (0.0 - 1.0)
        EdgeNode* next;
        
        EdgeNode(int id, float w = 1.0f) : targetBookId(id), weight(w), next(nullptr) {}
    };
    
    struct GraphNode {
        int bookId;
        EdgeNode* edges;
        
        GraphNode(int id) : bookId(id), edges(nullptr) {}
        
        ~GraphNode() {
            EdgeNode* current = edges;
            while (current) {
                EdgeNode* next = current->next;
                delete current;
                current = next;
            }
        }
    };
    
    DoublyLinkedList<GraphNode*> nodes;
    
    GraphNode* findNode(int bookId) {
        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            if ((*it)->bookId == bookId) {
                return *it;
            }
        }
        return nullptr;
    }
    
public:
    Graph() {}
    
    ~Graph() {
        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            delete *it;
        }
    }
    
    void addNode(int bookId) {
        if (!findNode(bookId)) {
            nodes.append(new GraphNode(bookId));
        }
    }
    
    void addEdge(int fromBookId, int toBookId, float weight = 1.0f) {
        GraphNode* fromNode = findNode(fromBookId);
        if (!fromNode) {
            addNode(fromBookId);
            fromNode = findNode(fromBookId);
        }
        
        // Ensure target node exists
        if (!findNode(toBookId)) {
            addNode(toBookId);
        }
        
        // Check if edge already exists
        EdgeNode* current = fromNode->edges;
        while (current) {
            if (current->targetBookId == toBookId) {
                current->weight = weight; // Update weight
                return;
            }
            current = current->next;
        }
        
        // Add new edge
        EdgeNode* newEdge = new EdgeNode(toBookId, weight);
        newEdge->next = fromNode->edges;
        fromNode->edges = newEdge;
    }
    
    // Add bidirectional edge (for undirected graph)
    void addBidirectionalEdge(int bookId1, int bookId2, float weight = 1.0f) {
        addEdge(bookId1, bookId2, weight);
        addEdge(bookId2, bookId1, weight);
    }
    
    // Get related books sorted by similarity weight
    DoublyLinkedList<int> getRelatedBooks(int bookId, int maxResults = 5) {
        DoublyLinkedList<int> related;
        GraphNode* node = findNode(bookId);
        
        if (!node) return related;
        
        // Collect edges into array for sorting
        struct EdgeData {
            int bookId;
            float weight;
        };
        
        // Count edges
        int edgeCount = 0;
        EdgeNode* current = node->edges;
        while (current) {
            edgeCount++;
            current = current->next;
        }
        
        if (edgeCount == 0) return related;
        
        // Create array
        EdgeData* edges = new EdgeData[edgeCount];
        current = node->edges;
        for (int i = 0; i < edgeCount; i++) {
            edges[i].bookId = current->targetBookId;
            edges[i].weight = current->weight;
            current = current->next;
        }
        
        // Sort by weight (descending) using insertion sort (small dataset)
        for (int i = 1; i < edgeCount; i++) {
            EdgeData key = edges[i];
            int j = i - 1;
            while (j >= 0 && edges[j].weight < key.weight) {
                edges[j + 1] = edges[j];
                j--;
            }
            edges[j + 1] = key;
        }
        
        // Add top results
        int limit = (maxResults < edgeCount) ? maxResults : edgeCount;
        for (int i = 0; i < limit; i++) {
            related.append(edges[i].bookId);
        }
        
        delete[] edges;
        return related;
    }
    
    bool hasEdge(int fromBookId, int toBookId) const {
        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            if ((*it)->bookId == fromBookId) {
                EdgeNode* edge = (*it)->edges;
                while (edge) {
                    if (edge->targetBookId == toBookId) return true;
                    edge = edge->next;
                }
                return false;
            }
        }
        return false;
    }
};

// ========================= SEARCH ALGORITHMS ================================

namespace SearchAlgorithms {
    // Binary Search (assumes sorted list by ID or Title)
    // Complexity: O(log n)
    template <typename T>
    int binarySearch(T** arr, int size, const std::function<int(const T*)>& comparator) {
        int left = 0;
        int right = size - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int cmp = comparator(arr[mid]);
            
            if (cmp == 0) {
                return mid; // Found
            } else if (cmp < 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1; // Not found
    }
    
    // Linear Search (for unsorted data)
    // Complexity: O(n)
    template <typename T>
    DoublyLinkedList<T*> linearSearch(DoublyLinkedList<T>& list, 
                                       const std::function<bool(const T&)>& predicate) {
        DoublyLinkedList<T*> results;
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (predicate(*it)) {
                results.append(&(*it));
            }
        }
        return results;
    }
}

// ========================= SORTING ALGORITHMS ===============================

namespace SortAlgorithms {
    // Quick Sort Implementation
    // Complexity: Average O(n log n), Worst O(n²)
    // Note: Bubble Sort is avoided due to poor O(n²) performance
    template <typename T>
    void quickSort(T** arr, int low, int high, const std::function<bool(const T*, const T*)>& compare) {
        if (low < high) {
            // Partition
            T* pivot = arr[high];
            int i = low - 1;
            
            for (int j = low; j < high; j++) {
                if (compare(arr[j], pivot)) {
                    i++;
                    T* temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
            
            T* temp = arr[i + 1];
            arr[i + 1] = arr[high];
            arr[high] = temp;
            
            int pi = i + 1;
            
            // Recursively sort
            quickSort(arr, low, pi - 1, compare);
            quickSort(arr, pi + 1, high, compare);
        }
    }
    
    // Merge Sort Implementation (Stable sorting)
    // Complexity: O(n log n) in all cases
    template <typename T>
    void merge(T** arr, int left, int mid, int right, const std::function<bool(const T*, const T*)>& compare) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        T** L = new T*[n1];
        T** R = new T*[n2];
        
        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            if (compare(L[i], R[j])) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
        
        delete[] L;
        delete[] R;
    }
    
    template <typename T>
    void mergeSort(T** arr, int left, int right, const std::function<bool(const T*, const T*)>& compare) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid, compare);
            mergeSort(arr, mid + 1, right, compare);
            merge(arr, left, mid, right, compare);
        }
    }
}

#endif // DATASTORE_H
