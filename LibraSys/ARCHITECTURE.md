# 🎨 LibraSys - Architecture Diagram

## System Overview

```
┌─────────────────────────────────────────────────────────────────┐
│                        LibraSys Application                      │
│                     (Qt6 Widgets Desktop App)                    │
└─────────────────────────────────────────────────────────────────┘
                                 │
                ┌────────────────┴────────────────┐
                │                                 │
        ┌───────▼────────┐                ┌──────▼──────┐
        │   UI Layer     │                │ Model Layer  │
        │   (View)       │◄───Signals────►│  (Engine)    │
        └───────┬────────┘                └──────┬───────┘
                │                                 │
                │                                 │
      ┌─────────┴──────────┐          ┌──────────┴──────────┐
      │                    │          │                     │
┌─────▼──────┐  ┌─────────▼──────┐  ┌▼────────────┐  ┌────▼─────┐
│ MainWindow │  │   Components   │  │ LibraryEngine│  │DataStore │
│            │  │                │  │  (Singleton) │  │ (Custom) │
│ - Search   │  │ - BookCard     │  │              │  │          │
│ - Sort     │  │ - NavBar       │  │ - Catalog    │  │ - List   │
│ - Grid     │  │ - Details      │  │ - Search     │  │ - Stack  │
│ - Events   │  │   Modal        │  │ - Sort       │  │ - Queue  │
└────────────┘  └────────────────┘  │ - Recommend  │  │ - Graph  │
                                    └──────────────┘  └──────────┘
```

## Data Flow: Search Operation

```
User Types "C++" in Search Bar
        │
        ▼
┌───────────────────┐
│ QLineEdit Signal  │
│ textChanged()     │
└────────┬──────────┘
         │
         ▼
┌────────────────────────────┐
│ MainWindow::              │
│ onSearchTextChanged()     │
│ - Clears current grid     │
└────────┬───────────────────┘
         │
         ▼
┌────────────────────────────┐
│ LibraryEngine::           │
│ searchGeneral("C++")      │
│ - Linear search O(n)      │
│ - Returns Book* list      │
└────────┬───────────────────┘
         │
         ▼
┌────────────────────────────┐
│ Iterate Results           │
│ - Create BookCard for each│
│ - Add to grid             │
└────────┬───────────────────┘
         │
         ▼
┌────────────────────────────┐
│ Display Results           │
│ - Update window title     │
│ - Show matching books     │
└───────────────────────────┘
```

## Data Structure Relationships

```
LibraryEngine (Core)
    │
    ├── DoublyLinkedList<Book>  ───────► [Book 1] ↔ [Book 2] ↔ ... ↔ [Book 15]
    │   (Main Catalog)                        │           │
    │                                         │           │
    ├── Graph                                 ▼           ▼
    │   (Recommendations)              Graph Node 1   Graph Node 2
    │       │                               │ \         / │
    │       └── Adjacency List:           │  Edge(0.95) │
    │           Node[1] → Edge[2,0.95]    │  /       \  │
    │           Node[1] → Edge[3,0.80]    ▼ ▼         ▼ ▼
    │           Node[2] → Edge[4,0.90]  Related Books Show
    │
    ├── Stack<int>                      [Book 15] ← Top
    │   (Recently Viewed)                   │
    │       Push/Pop O(1)                [Book 12]
    │       LIFO Order                      │
    │                                    [Book 5]
    │
    └── Queue<BorrowRequest>            Front → [Req 1] → [Req 2] → [Req 3] ← Rear
        (Borrow Requests)                       │
        Enqueue/Dequeue O(1)             Process (FIFO)
        FIFO Order
```

## UI Component Hierarchy

```
MainWindow (1280x800)
│
├── NavBar (Sidebar - 200px width)
│   ├── Title Label "LibraSys"
│   ├── Catalog Button [Active]
│   ├── Queue Button
│   ├── History Button
│   └── Stats Button
│
└── Right Panel (1080px width)
    ├── Top Bar (QWidget)
    │   ├── Search Bar (QLineEdit)
    │   ├── Sort Combo (QComboBox)
    │   └── Order Button (QPushButton)
    │
    └── Scroll Area (QScrollArea)
        └── Content Widget (QWidget)
            └── Grid Layout (4 columns)
                ├── BookCard 1
                │   ├── Cover Image (150x200)
                │   ├── Title Label (Bold)
                │   ├── Author Label (Italic)
                │   ├── Genre + Year
                │   ├── Details Button
                │   └── Borrow Button
                │
                ├── BookCard 2
                ├── BookCard 3
                ├── BookCard 4
                ├── [New Row]
                ├── BookCard 5
                └── ... (up to 15 cards)
```

## Sorting Algorithm Flow

```
User Selects "Sort by Year"
        │
        ▼
┌────────────────────────┐
│ MainWindow::          │
│ onSortChanged(2)      │
│ - Maps to BY_YEAR     │
└────────┬───────────────┘
         │
         ▼
┌────────────────────────────┐
│ LibraryEngine::           │
│ sortCatalog(BY_YEAR, ASC) │
└────────┬───────────────────┘
         │
         ▼
┌────────────────────────────┐
│ Convert List to Array     │
│ Book** arr = toArray()    │
└────────┬───────────────────┘
         │
         ▼
┌────────────────────────────┐
│ Quick Sort Algorithm      │
│ - Pivot selection         │
│ - Partition O(n)          │
│ - Recursive calls         │
│ - Total: O(n log n)       │
└────────┬───────────────────┘
         │
         ▼
┌────────────────────────────┐
│ Rebuild Linked List       │
│ - Clear old catalog       │
│ - Append sorted items     │
└────────┬───────────────────┘
         │
         ▼
┌────────────────────────────┐
│ Refresh Display           │
│ - Clear grid              │
│ - Re-create cards         │
└───────────────────────────┘
```

## Graph Recommendation Example

```
Book Network (Genre Similarity)

         [C++ Programming]
              /  |  \
         0.95/   |   \0.80
            /    |    \
           /     |0.85 \
          /      |      \
[Algorithms]    [D.P.]  [Clean Code]
     |  \         |         /
     |   \0.75    |0.92    /
     |    \       |       /
     |     \      |      /
     |      \     |     /
     |       [   AI   ]

When user clicks "Details" on [C++ Programming]:
1. Graph::getRelatedBooks(bookId=1, count=5)
2. Traverse edges from Node[1]
3. Sort by weight: 0.95, 0.85, 0.80
4. Return: [Algorithms, Design Patterns, Clean Code]
5. Display in modal dialog
```

## Memory Layout

```
Heap Memory (Manual Management)

DoublyLinkedList<Book>:
┌──────┐    ┌──────┐    ┌──────┐
│Node 1│←──→│Node 2│←──→│Node 3│
│ Book │    │ Book │    │ Book │
│ Data │    │ Data │    │ Data │
└──────┘    └──────┘    └──────┘
   ↑                         ↑
  head                     tail

Stack<int>:
┌──────┐
│ 15   │← top (last viewed)
├──────┤
│ 12   │
├──────┤
│ 5    │
└──────┘

Queue<BorrowRequest>:
┌──────────┐    ┌──────────┐    ┌──────────┐
│Request 1 │───→│Request 2 │───→│Request 3 │
└──────────┘    └──────────┘    └──────────┘
     ↑                                ↑
   front                            rear

Graph Adjacency List:
Node[1]
  ├─→ Edge(2, 0.95) ─→ null
  └─→ Edge(3, 0.80) ─→ Edge(4, 0.85) ─→ null

Node[2]
  ├─→ Edge(1, 0.95) ─→ null
  └─→ Edge(4, 0.90) ─→ null
```

## Build Process Flow

```
Developer Runs:
$ cmake ..

CMakeLists.txt
    │
    ├─→ Detect Qt6/Qt5
    ├─→ Enable AUTOMOC (Qt Meta-Object Compiler)
    ├─→ Enable AUTORCC (Qt Resource Compiler)
    ├─→ Enable AUTOUIC (Qt UI Compiler)
    │
    └─→ Generate Build Files

Developer Runs:
$ cmake --build .

    │
    ├─→ Compile .cpp files
    ├─→ Run MOC on QObject classes
    ├─→ Compile resources.qrc
    ├─→ Link Qt6::Widgets
    │
    └─→ Output: LibraSys.exe

User Runs:
$ ./LibraSys.exe

    │
    ├─→ main() entry point
    ├─→ Create QApplication
    ├─→ LibraryEngine::getInstance()
    │      └─→ Initialize 15 books
    │      └─→ Build graph connections
    ├─→ Create MainWindow
    │      └─→ Setup UI components
    │      └─→ Display catalog
    └─→ app.exec() (Event loop)
```

## Qt Signal-Slot Connections

```
BookCard (Widget)
    │
    │ borrowClicked(int bookId)
    └──────────────────────────► MainWindow::onBookBorrow(int)
                                        │
                                        ├─→ Show input dialog
                                        ├─→ Get user name
                                        └─→ engine->addBorrowRequest()
                                               │
                                               └─→ queue.enqueue()

NavBar (Widget)
    │
    │ catalogRequested()
    └──────────────────────────► MainWindow::onCatalogView()
                                        │
                                        └─→ displayCatalog()
                                               │
                                               └─→ Rebuild grid
```

## Performance Characteristics Summary

```
╔════════════════════╦═══════════════╦═══════════════╗
║ Operation          ║ Complexity    ║ Data Structure║
╠════════════════════╬═══════════════╬═══════════════╣
║ Add Book           ║ O(1)          ║ LinkedList    ║
║ Remove Book        ║ O(n)          ║ LinkedList    ║
║ Search Book        ║ O(n)          ║ Linear Scan   ║
║ Sort Catalog       ║ O(n log n)    ║ Quick Sort    ║
║ Get Related        ║ O(E)          ║ Graph Edges   ║
║ Push History       ║ O(1)          ║ Stack         ║
║ Pop History        ║ O(1)          ║ Stack         ║
║ Enqueue Borrow     ║ O(1)          ║ Queue         ║
║ Dequeue Borrow     ║ O(1)          ║ Queue         ║
║ Find by ID         ║ O(n)          ║ LinkedList    ║
╚════════════════════╩═══════════════╩═══════════════╝
```

---

**Architecture Notes:**

- **Separation of Concerns:** UI never directly manipulates data structures
- **Singleton Pattern:** One LibraryEngine instance for global state
- **Signal-Slot:** Loose coupling between components
- **Custom Structures:** Zero dependency on STL containers in core logic
- **Professional Design:** Industry-standard patterns and practices
