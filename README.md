# LibraSys - Digital Library Management System

![LibraSys Banner](https://via.placeholder.com/1000x300/1E1E2E/7F5AF0?text=LibraSys+Digital+Library)

**LibraSys** adalah aplikasi desktop manajemen perpustakaan digital modern yang dibangun menggunakan **C++** dan framework **Qt 6**.

Aplikasi ini dirancang sebagai **Projek Akhir Struktur Data**, yang menampilkan implementasi struktur data manual (Custom Data Structures) di balik antarmuka pengguna yang bersih dan responsif.

## 🚀 Fitur Utama

### 1. Custom Backend Engine (Manual Data Structures)
Sesuai ketentuan akademis, aplikasi ini tidak menggunakan STL container (`std::vector`, `std::list`) untuk logika inti, melainkan menggunakan implementasi manual:
- **Catalog Management:** Doubly Linked List untuk penyimpanan data buku.
- **Recommendation Engine:** Struktur **Graph** (Adjacency List) untuk menghubungkan buku berdasarkan kesamaan genre.
- **Borrowing System:** Implementasi **Queue** (FIFO) untuk antrean peminjaman buku.
- **Reading History:** Implementasi **Stack** (LIFO) untuk riwayat buku yang dilihat pengguna.

### 2. Algoritma Efisien
- **Searching:** Binary Search untuk pencarian buku berdasarkan judul (Logarithmic Time).
- **Sorting:** Merge Sort / Quick Sort untuk pengurutan katalog berdasarkan Tahun atau Judul.

### 3. Modern User Interface (UI)
- **Component-Based UI:** Menggunakan custom widget `BookCard` untuk tampilan grid yang dinamis.
- **Theme System:** Menggunakan Qt Style Sheets (QSS) dengan tema "Dark Academia" (Deep Slate & Neon Blue).
- **Responsive Layout:** Grid layout yang menyesuaikan dengan ukuran window.

---

## 📂 Struktur Project

Project ini menggunakan struktur modular berbasis **CMake**:

```text
LibraSys/
├── CMakeLists.txt          # Konfigurasi Build Utama
├── Resources/              # Asset (Icon, Fonts, Styles)
├── src/
│   ├── main.cpp            # Entry Point Aplikasi
│   ├── Utils/              # Helper (StyleLoader.h untuk QSS)
│   ├── Models/             # LOGIKA STRUKTUR DATA (Custom Engine)
│   │   ├── Book.h          # Definisi Struct Buku
│   │   ├── DataStore.h     # Implementasi Manual (LinkedList, Stack, Queue, Graph)
│   │   └── LibraryEngine.h # Wrapper logika bisnis
│   └── UI/                 # Tampilan Antarmuka (GUI)
│       ├── MainWindow.cpp  # Dashboard Utama
│       └── Components/     # Widget yang dapat digunakan kembali
│           ├── BookCard.h  # Kartu Buku (Cover + Judul + Tombol)
│           └── NavBar.h    # Navigasi Samping
```
🛠️ Prasyarat (Prerequisites)

Sebelum menjalankan aplikasi, pastikan komputer Anda telah terinstal:

    Qt 6 (atau minimal Qt 5.15) dengan komponen Qt Widgets.

    Qt Creator (IDE resmi Qt).

    C++ Compiler (MinGW untuk Windows, GCC untuk Linux, atau Clang untuk macOS).

    CMake (biasanya sudah termasuk dalam instalasi Qt).

▶️ Cara Menjalankan Aplikasi (via Qt Creator)

Karena project ini menggunakan CMakeLists.txt (bukan .pro), ikuti langkah berikut agar project terkonfigurasi dengan benar:
Langkah 1: Buka Project

    Buka Qt Creator.

    Klik File > Open File or Project...

    Arahkan ke folder LibraSys dan pilih file CMakeLists.txt.

    Klik Open.

Langkah 2: Konfigurasi Kit

    Qt Creator akan membuka jendela Configure Project.

    Pilih Kit yang tersedia (contoh: Desktop Qt 6.x.x MinGW 64-bit).

    Klik tombol Configure.

Langkah 3: Build & Run

    Tunggu hingga proses Indexing dan Parsing CMake selesai (lihat bar hijau di pojok kiri bawah/kanan bawah).

    Klik tombol Run (ikon Play segitiga hijau) di pojok kiri bawah, atau tekan Ctrl+R.

    Aplikasi akan mengompilasi kode dan jendela LibraSys akan muncul.

📸 Panduan Penggunaan (User Manual)

    Katalog (Home):

        Anda akan melihat daftar 15 buku dummy yang sudah dimuat otomatis.

        Gunakan Search Bar di atas untuk mencari buku berdasarkan judul.

        Gunakan tombol Sort untuk mengurutkan buku berdasarkan Tahun Terbit.

    Detail & Rekomendasi:

        Klik pada salah satu Book Card.

        Jendela detail akan muncul menampilkan Sinopsis.

        Di bagian bawah, lihat bagian "Related Books" (Hasil traversal Graph).

    Peminjaman & History:

        Klik tombol "Borrow" pada buku untuk memasukkannya ke dalam Queue.

        Setiap buku yang Anda klik detailnya akan otomatis masuk ke History Stack.

        Buka Tab "My Queue" atau "History" di sidebar (jika sudah diimplementasikan di UI) untuk melihat datanya.

📝 Catatan Akademis

Project ini memenuhi kriteria penilaian sebagai berikut:

    [x] Integrasi C++ dan Qt GUI.

    [x] Implementasi Struktur Data Mandiri (Tanpa STL untuk core logic).

    [x] Penggunaan Graph untuk fitur Rekomendasi.

    [x] Algoritma Sorting (Non-Bubble Sort) dan Searching.

    [x] Minimal 15 data dummy saat inisialisasi.

Dibuat oleh:

    Kelompok GPT Gaming
