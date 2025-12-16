LibraSys — Digital Library Management System

LibraSys adalah aplikasi desktop manajemen perpustakaan digital modern yang dibangun dengan C++ dan framework Qt 6.

Aplikasi ini dikembangkan sebagai Proyek Akhir Struktur Data, yang menampilkan implementasi struktur data manual (custom data structures) di balik antarmuka pengguna yang rapi dan responsif.
🚀 Fitur Utama
1. Custom backend engine (implementasi struktur data manual)

Sesuai ketentuan akademis, aplikasi ini tidak menggunakan container STL (std::vector, std::list, dsb.) untuk logika inti, melainkan implementasi manual:

    Catalog Management: Doubly linked list untuk penyimpanan data buku.
    Recommendation Engine: Graph (adjacency list) untuk menghubungkan buku berdasarkan kesamaan genre.
    Borrowing System: Queue (FIFO) untuk antrean peminjaman buku.
    Reading History: Stack (LIFO) untuk riwayat buku yang dilihat pengguna.

2. Algoritma efisien

    Searching: Binary search untuk pencarian buku berdasarkan judul (waktu logaritmik).
    Sorting: Merge sort / Quick sort untuk mengurutkan katalog berdasarkan tahun terbit atau judul.

3. Antarmuka Modern (UI)

    Component-based UI: Menggunakan custom widget BookCard untuk tampilan grid dinamis.
    Theme system: Menggunakan Qt Style Sheets (QSS) dengan tema "Dark Academia" (Deep Slate & Neon Blue).
    Responsive layout: Grid layout yang menyesuaikan dengan ukuran jendela.

📂 Struktur Proyek

Proyek ini menggunakan struktur modular berbasis CMake:
Code

LibraSys/
├── CMakeLists.txt          # Konfigurasi build utama
├── Resources/              # Asset (ikon, font, style)
├── src/
│   ├── main.cpp            # Entry point aplikasi
│   ├── Utils/              # Helper (mis. StyleLoader.h untuk QSS)
│   ├── Models/             # Logika struktur data (custom engine)
│   │   ├── Book.h          # Definisi struktur buku
│   │   ├── DataStore.h     # Implementasi manual (LinkedList, Stack, Queue, Graph)
│   │   └── LibraryEngine.h # Wrapper logika bisnis
│   └── UI/                 # Tampilan antarmuka (GUI)
│       ├── MainWindow.cpp  # Dashboard utama
│       └── Components/     # Widget yang dapat digunakan kembali
│           ├── BookCard.h  # Kartu buku (cover + judul + tombol)
│           └── NavBar.h    # Navigasi samping

🛠️ Prasyarat

Sebelum menjalankan aplikasi, pastikan sistem Anda memiliki:

    Qt 6 (atau minimal Qt 5.15) dengan komponen Qt Widgets.
    Qt Creator (direkomendasikan).
    Compiler C++ (MinGW untuk Windows, GCC untuk Linux, atau Clang untuk macOS).
    CMake (biasanya sudah termasuk dalam instalasi Qt).

▶️ Cara Menjalankan Aplikasi (via Qt Creator)

Karena proyek ini menggunakan CMakeLists.txt (bukan .pro), ikuti langkah berikut agar proyek terkonfigurasi dengan benar:

    Buka Qt Creator
        Klik File > Open File or Project...
        Arahkan ke folder LibraSys dan pilih file CMakeLists.txt, lalu klik Open.

    Konfigurasi Kit
        Pada jendela Configure Project, pilih Kit yang tersedia (mis. Desktop Qt 6.x.x MinGW 64-bit).
        Klik Configure.

    Build & Run
        Tunggu proses indexing dan parsing CMake selesai.
        Klik tombol Run (ikon Play) atau tekan Ctrl+R.
        Aplikasi akan dikompilasi dan jendela LibraSys akan terbuka.

(Alternatif: Anda dapat membangun dari command line menggunakan CMake/Make sesuai konfigurasi platform, jika diperlukan.)
📸 Panduan Penggunaan (User Manual)

    Katalog (Home):
        Saat awal dijalankan, terdapat daftar ~15 buku dummy yang dimuat otomatis.
        Gunakan bilah pencarian (Search Bar) untuk mencari buku berdasarkan judul.
        Gunakan tombol Sort untuk mengurutkan buku berdasarkan tahun terbit atau judul.

    Detail & Rekomendasi:
        Klik salah satu Book Card untuk membuka jendela detail yang menampilkan sinopsis.
        Di bagian bawah halaman detail, tampilkan "Related Books" yang merupakan hasil traversal graph rekomendasi.

    Peminjaman & Riwayat:
        Klik tombol "Borrow" pada buku untuk memasukkannya ke antrean peminjaman (queue).
        Setiap buku yang dibuka detailnya akan otomatis ditambahkan ke history (stack).
        Buka tab "My Queue" atau "History" di sidebar (jika tersedia di UI) untuk melihat daftar.

📝 Catatan Akademis

Proyek ini memenuhi kriteria penilaian:

    Integrasi C++ dan Qt GUI.
    Implementasi struktur data mandiri (tanpa STL untuk core logic).
    Penggunaan graph untuk fitur rekomendasi.
    Algoritma sorting (non-bubble sort) dan searching.
    Minimal 15 data dummy saat inisialisasi.

Dibuat oleh: Kelompok GPT Gaming
