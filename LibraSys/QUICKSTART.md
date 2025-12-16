# LibraSys - Quick Start Guide

## ⚡ 5-Minute Setup

### Step 1: Prerequisites Check

**Required:**

- Qt6 (recommended) or Qt5 with Widgets module
- CMake 3.16+
- C++17 compiler (MSVC, MinGW, or GCC)

**Verify Qt Installation:**

```powershell
# Find qmake location
where qmake
# Example output: C:\Qt\6.5.0\mingw_64\bin\qmake.exe
```

### Step 2: Configure Qt Path (if needed)

If CMake can't find Qt automatically:

**Windows:**

```powershell
set CMAKE_PREFIX_PATH=C:\Qt\6.5.0\mingw_64
```

**Linux/macOS:**

```bash
export CMAKE_PREFIX_PATH=/opt/Qt/6.5.0/gcc_64
```

### Step 3: Build

**Option A: Automatic Build Script (Windows)**

```powershell
cd LibraSys
.\build.bat
```

**Option B: Manual Build**

```powershell
cd LibraSys
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Step 4: Run

```powershell
cd build
.\LibraSys.exe     # Windows
# OR
./LibraSys         # Linux/macOS
```

## 🎮 How to Use

### Catalog View (Default)

- **Browse**: Scroll through 15 pre-loaded books in card layout
- **Search**: Type in search bar (e.g., "C++", "Orwell", "Technology")
- **Sort**: Choose criteria from dropdown (Title/Author/Year/Popularity)
- **Toggle Order**: Click "↑ Ascending" / "↓ Descending"
- **View Details**: Click "View Details" on any book card
- **Borrow**: Click "Borrow" button and enter your name

### Book Details Modal

- **Description**: Full book information
- **Related Books**: Click any related book to open its details
- **Recommendation Logic**: Based on graph connections (genre similarity)

### My Queue View

- **See Requests**: All pending borrow requests in FIFO order
- **Process**: Click "Process" to handle the first request

### History View

- **Recently Viewed**: Books you've clicked "View Details" on
- **Order**: Most recent first (Stack LIFO)

### Statistics View

- **Metrics**: Total books, queue size, history count
- **Popular Books**: Top 5 most borrowed books

## 🔍 Testing Recommendations

### Test Case 1: Search & Sort

```
1. Type "C++" in search bar
2. Should show "The C++ Programming Language"
3. Select "Sort by Year"
4. Toggle to Descending
5. Verify oldest books appear first
```

### Test Case 2: Graph Recommendations

```
1. Click "View Details" on "Introduction to Algorithms"
2. Check related books: Should include "Design Patterns", "C++ Programming"
3. Click "Design Patterns" in related section
4. Verify it opens Design Patterns details
```

### Test Case 3: Queue System

```
1. Click "Borrow" on "1984"
2. Enter name: "John Doe"
3. Navigate to "My Queue"
4. Click "Process"
5. Verify book removed from queue
```

## 🐛 Common Issues

### Error: "Qt6_DIR not found"

**Solution:**

```powershell
cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.5.0/msvc2019_64"
```

### Error: "cannot find -lQt6Widgets"

**Solution:** Install Qt Widgets module via Qt Maintenance Tool

### Error: "MOC not found"

**Solution:** Ensure Qt bin directory is in PATH

### Runtime: "Qt6Core.dll missing"

**Solution (Windows):**

```powershell
cd build
windeployqt.exe LibraSys.exe
```

## 📊 Project Highlights for Demo

**Mention in Presentation:**

1. ✅ **NO STL containers used** (custom DoublyLinkedList, Stack, Queue, Graph)
2. ✅ **15 diverse books** pre-loaded with metadata
3. ✅ **Quick Sort O(n log n)** for sorting (NOT Bubble Sort)
4. ✅ **Graph-based recommendations** with weighted edges
5. ✅ **Modern UI** - card layout instead of tables
6. ✅ **Real-time search** across all book fields
7. ✅ **FIFO queue** for borrow management
8. ✅ **LIFO stack** for browsing history

## 📚 Code Files to Show

**For Code Review:**

- `src/Models/DataStore.h` - Custom data structures (450+ lines)
- `src/Models/LibraryEngine.cpp` - 15 book initialization + graph connections
- `src/UI/Components/BookCard.cpp` - Modern widget with genre colors
- `src/UI/MainWindow.cpp` - Grid layout + search/sort logic

## 🎯 Evaluation Checklist

- [x] Custom Linked List implementation
- [x] Stack (LIFO) usage
- [x] Queue (FIFO) usage
- [x] Graph with edges
- [x] Sorting algorithm (Quick Sort)
- [x] Search algorithm (Linear Search)
- [x] At least 15 data entries
- [x] Professional UI design
- [x] Complete project documentation

---

**Need Help?** Check README.md for detailed documentation.
