# LibraSys - Digital Library Management System

**A professional-grade library management application built with Qt6 and custom C++ data structures**

## 🎯 Project Overview

LibraSys is an academic project demonstrating advanced data structures and algorithms implementation alongside modern UI/UX design. The system avoids STL containers for core functionality to showcase low-level programming skills.

## 🏗️ Architecture

### Custom Data Structures (NO STL)

- **Doubly Linked List**: Book catalog storage
- **Graph (Adjacency List)**: Recommendation system based on genre similarity
- **Stack (LIFO)**: Recently viewed books history
- **Queue (FIFO)**: Book borrowing request management

### Algorithms Implemented

- **Quick Sort**: O(n log n) catalog sorting by title/author/year/popularity
- **Binary Search**: O(log n) search capability (header implementation)
- **Linear Search**: General text search across book metadata

### Modern UI Components

- **BookCard Widget**: Card-based book display with genre-specific colors
- **NavBar**: Sidebar navigation with 4 main views
- **MainWindow**: Responsive grid layout dashboard
- **Details Modal**: Pop-up with related books recommendations

## 📁 Project Structure

```
LibraSys/
├── CMakeLists.txt              # Modern CMake build configuration
├── README.md                   # This file
├── Resources/
│   └── resources.qrc           # Qt resource file
├── src/
│   ├── main.cpp                # Application entry point
│   ├── Models/                 # Backend Engine (Custom Data Structures)
│   │   ├── Book.h              # Book entity definition
│   │   ├── DataStore.h         # Manual LinkedList, Stack, Queue, Graph
│   │   ├── LibraryEngine.h     # Core business logic header
│   │   └── LibraryEngine.cpp   # Engine implementation with 15 sample books
│   ├── UI/                     # Frontend Layer
│   │   ├── MainWindow.h        # Main window header
│   │   ├── MainWindow.cpp      # Dashboard implementation
│   │   └── Components/
│   │       ├── BookCard.h/cpp  # Book display widget
│   │       └── NavBar.h/cpp    # Navigation sidebar
│   └── Utils/
│       ├── StyleLoader.h       # Style management utility
│       └── StyleLoader.cpp
```

## 🚀 Features

### 1. Catalog Management

- Display all 15 pre-loaded books in a responsive grid
- Genre-based color coding (Technology=Blue, Fiction=Purple, History=Orange, etc.)
- Real-time search across title, author, genre, and description
- Multi-criteria sorting (Title, Author, Year, Popularity)

### 2. Recommendation System

- Graph-based book relationships
- Click "View Details" to see related books
- Genre similarity connections (e.g., C++ → Algorithms → Design Patterns)

### 3. User History

- Stack-based "Recently Viewed" tracking
- LIFO principle: Latest viewed books appear first

### 4. Borrowing Queue

- FIFO queue for borrow requests
- User can add books to queue with their name
- Process requests in order

### 5. Statistics Dashboard

- Total books count
- Pending requests count
- Most popular books (by borrow count)

## 🛠️ Build Instructions

### Prerequisites

- **CMake** 3.16 or higher
- **Qt6** or **Qt5** (Widgets module)
- **C++17** compatible compiler (GCC, Clang, MSVC)

### Windows (Visual Studio)

```powershell
cd LibraSys
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

### Windows (MinGW)

```powershell
cd LibraSys
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

### Linux / macOS

```bash
cd LibraSys
mkdir build
cd build
cmake ..
make -j4
```

## ▶️ Running the Application

### Windows

```powershell
cd build/Release
./LibraSys.exe
```

### Linux / macOS

```bash
cd build
./LibraSys
```

## 📚 Sample Data

The system initializes with **15 diverse books**:

**Technology (5 books)**

1. The C++ Programming Language - Bjarne Stroustrup (2013)
2. Introduction to Algorithms - Thomas H. Cormen (2009)
3. Clean Code - Robert C. Martin (2008)
4. Design Patterns - Erich Gamma (1994)
5. Artificial Intelligence: A Modern Approach - Stuart Russell (2020)

**Fiction (4 books)** 6. 1984 - George Orwell (1949) 7. To Kill a Mockingbird - Harper Lee (1960) 8. The Great Gatsby - F. Scott Fitzgerald (1925) 9. Brave New World - Aldous Huxley (1932)

**History (3 books)** 10. Sapiens - Yuval Noah Harari (2011) 11. The Diary of a Young Girl - Anne Frank (1947) 12. Steve Jobs - Walter Isaacson (2011)

**Science & Philosophy (3 books)** 13. A Brief History of Time - Stephen Hawking (1988) 14. Thinking, Fast and Slow - Daniel Kahneman (2011) 15. The Art of War - Sun Tzu (500 BC)

## 🎨 UI/UX Highlights

- **Modern Card Layout**: No boring tables - Netflix-style grid design
- **Genre Visual Coding**: Each genre has unique colors and icons
- **Responsive Grid**: Automatically adjusts to 4 cards per row
- **Interactive Hover Effects**: Cards lift on hover with border highlight
- **Modal Details**: Book details open in centered dialog with related books
- **Clean Typography**: Segoe UI font with proper hierarchy

## 🧪 Testing the Features

### Search Functionality

1. Type "C++" in search bar → Returns C++ Programming Language
2. Type "Orwell" → Returns 1984
3. Type "History" → Returns all history books

### Sorting

1. Select "Sort by Year" → Oldest to newest
2. Click "↑ Ascending" → Toggle to "↓ Descending"
3. Books re-order in real-time

### Recommendation System

1. Click "View Details" on "C++ Programming Language"
2. See related books: Algorithms, Clean Code, Design Patterns
3. Click a related book → Opens that book's details

### Borrowing Queue

1. Click "Borrow" on any book
2. Enter your name → Book added to queue
3. Navigate to "My Queue" → See all pending requests
4. Click "Process" → Dequeues in FIFO order

## 📈 Performance Analysis

| Operation         | Complexity | Implementation    |
| ----------------- | ---------- | ----------------- |
| Add Book          | O(1)       | LinkedList append |
| Search            | O(n)       | Linear scan       |
| Sort              | O(n log n) | Quick Sort        |
| Get Related Books | O(E)       | Graph traversal   |
| Push History      | O(1)       | Stack push        |
| Enqueue Borrow    | O(1)       | Queue enqueue     |

## 🎓 Educational Value

This project demonstrates:

- **Memory Management**: Manual `new`/`delete` for linked structures
- **Algorithm Implementation**: Sorting without `std::sort`
- **Graph Theory**: Adjacency list for recommendations
- **OOP Design**: Separation of concerns (Model-View architecture)
- **Qt Framework**: Signal-slot mechanism, layouts, custom widgets

## 🐛 Troubleshooting

### Qt Not Found

```bash
# Set Qt path manually
cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.5.0/msvc2019_64"
```

### Build Errors

- Ensure C++17 is enabled: Check CMakeLists.txt `CMAKE_CXX_STANDARD`
- Missing MOC files: Clean and rebuild (`cmake --build . --clean-first`)

### Runtime Issues

- DLL not found (Windows): Copy Qt DLLs to build directory or use `windeployqt.exe`

## 📄 License

Academic project - Free to use for educational purposes.

## 👨‍💻 Author

Built as a Data Structures & Algorithms final project demonstrating professional C++ development practices.

---

**Note**: This implementation intentionally avoids STL containers (`std::vector`, `std::list`, `std::map`) for educational purposes. Production code should use standard library when appropriate.
