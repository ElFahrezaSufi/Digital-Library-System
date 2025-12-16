#ifndef STYLELOADER_H
#define STYLELOADER_H

#include <QString>
#include <QFile>
#include <QTextStream>

// ============================================================================
// StyleLoader: Modern Dark Academia Tech Theme
// Design Philosophy: Professional dark UI with neon accents
// Color Palette:
//   - Background (Deep Slate): #1E1E2E
//   - Surface (Gunmetal): #252535
//   - Primary Accent (Neon Purple): #7F5AF0
//   - Text Primary: #FFFFFE
//   - Text Secondary: #94A1B2
//   - Input Fields: #16161a
// ============================================================================

class StyleLoader {
public:
    // Legacy method for loading external files
    static QString loadStyleSheet(const QString& fileName) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream stream(&file);
            return stream.readAll();
        }
        return QString();
    }
    
    // Main stylesheet getter - Dark Academia Tech Theme
    static QString getAppStyleSheet() {
        return R"(
            /* ================================================================
               GLOBAL STYLES - Base Typography & Background
               ================================================================ */
            
            * {
                font-family: 'Segoe UI', 'Roboto', 'Helvetica Neue', Arial, sans-serif;
                outline: none;
            }
            
            QWidget {
                color: #FFFFFE;
                background-color: #1E1E2E;
            }
            
            QMainWindow {
                background-color: #1E1E2E;
            }
            
            /* ================================================================
               NAVIGATION BAR - Sidebar Styling
               ================================================================ */
            
            QFrame#NavBar {
                background-color: #252535;
                border-right: 2px solid #16161a;
            }
            
            /* ================================================================
               BUTTONS - Primary, Secondary, and Nav Buttons
               ================================================================ */
            
            /* Primary Action Buttons */
            QPushButton {
                background-color: #7F5AF0;
                color: #FFFFFE;
                border: none;
                border-radius: 8px;
                padding: 8px 16px;
                font-size: 13px;
                font-weight: 600;
                min-height: 28px;
            }
            
            QPushButton:hover {
                background-color: #9D7FF0;
                box-shadow: 0 4px 12px rgba(127, 90, 240, 0.3);
            }
            
            QPushButton:pressed {
                background-color: #6B48D6;
                padding-top: 9px;
                padding-bottom: 7px;
            }
            
            QPushButton:disabled {
                background-color: #3a3a4a;
                color: #5a5a6a;
            }
            
            /* Secondary/Ghost Buttons (for details, etc.) */
            QPushButton#secondaryButton {
                background-color: transparent;
                color: #7F5AF0;
                border: 2px solid #7F5AF0;
                border-radius: 8px;
                padding: 6px 14px;
            }
            
            QPushButton#secondaryButton:hover {
                background-color: rgba(127, 90, 240, 0.1);
                border-color: #9D7FF0;
                color: #9D7FF0;
            }
            
            QPushButton#secondaryButton:pressed {
                background-color: rgba(127, 90, 240, 0.2);
            }
            
            /* Navigation Buttons */
            QPushButton#navButton {
                background-color: transparent;
                color: #94A1B2;
                border: none;
                border-radius: 6px;
                padding: 12px 16px;
                text-align: left;
                font-size: 14px;
                font-weight: 500;
            }
            
            QPushButton#navButton:hover {
                background-color: #2f2f40;
                color: #FFFFFE;
            }
            
            QPushButton#navButton:checked,
            QPushButton#navButton:pressed {
                background-color: #7F5AF0;
                color: #FFFFFE;
                font-weight: 700;
            }
            
            /* ================================================================
               SEARCH BAR - Pill-Shaped Input
               ================================================================ */
            
            QLineEdit {
                background-color: #16161a;
                color: #FFFFFE;
                border: 2px solid #252535;
                border-radius: 15px;
                padding: 10px 16px;
                padding-left: 40px; /* Space for search icon */
                font-size: 14px;
                selection-background-color: #7F5AF0;
            }
            
            QLineEdit:focus {
                border: 2px solid #7F5AF0;
                background-color: #1a1a24;
            }
            
            QLineEdit::placeholder {
                color: #5a5a6a;
            }
            
            /* ================================================================
               COMBO BOX - Dropdown Selector
               ================================================================ */
            
            QComboBox {
                background-color: #252535;
                color: #FFFFFE;
                border: 2px solid #3a3a4a;
                border-radius: 8px;
                padding: 8px 12px;
                min-width: 150px;
                font-size: 13px;
            }
            
            QComboBox:hover {
                border-color: #7F5AF0;
            }
            
            QComboBox::drop-down {
                border: none;
                width: 30px;
            }
            
            QComboBox::down-arrow {
                image: none;
                border-left: 5px solid transparent;
                border-right: 5px solid transparent;
                border-top: 6px solid #94A1B2;
                margin-right: 8px;
            }
            
            QComboBox QAbstractItemView {
                background-color: #252535;
                color: #FFFFFE;
                border: 2px solid #7F5AF0;
                border-radius: 8px;
                selection-background-color: #7F5AF0;
                selection-color: #FFFFFE;
                padding: 4px;
            }
            
            QComboBox QAbstractItemView::item {
                padding: 8px;
                min-height: 30px;
            }
            
            QComboBox QAbstractItemView::item:hover {
                background-color: #3a3a4a;
            }
            
            /* ================================================================
               SCROLL AREA & BARS - Clean Touch-Like Scrolling
               ================================================================ */
            
            QScrollArea {
                background-color: transparent;
                border: none;
            }
            
            /* Vertical Scrollbar */
            QScrollBar:vertical {
                background-color: transparent;
                width: 8px;
                margin: 0px;
                border: none;
            }
            
            QScrollBar::handle:vertical {
                background-color: #3a3a4a;
                border-radius: 4px;
                min-height: 30px;
            }
            
            QScrollBar::handle:vertical:hover {
                background-color: #4a4a5a;
            }
            
            QScrollBar::handle:vertical:pressed {
                background-color: #7F5AF0;
            }
            
            /* Remove arrows */
            QScrollBar::add-line:vertical,
            QScrollBar::sub-line:vertical,
            QScrollBar::add-page:vertical,
            QScrollBar::sub-page:vertical {
                background: none;
                border: none;
            }
            
            /* Horizontal Scrollbar */
            QScrollBar:horizontal {
                background-color: transparent;
                height: 8px;
                margin: 0px;
                border: none;
            }
            
            QScrollBar::handle:horizontal {
                background-color: #3a3a4a;
                border-radius: 4px;
                min-width: 30px;
            }
            
            QScrollBar::handle:horizontal:hover {
                background-color: #4a4a5a;
            }
            
            QScrollBar::add-line:horizontal,
            QScrollBar::sub-line:horizontal,
            QScrollBar::add-page:horizontal,
            QScrollBar::sub-page:horizontal {
                background: none;
                border: none;
            }
            
            /* ================================================================
               BOOK CARDS - Modern Card Layout
               ================================================================ */
            
            QFrame#BookCard {
                background-color: #252535;
                border: 1px solid #2f2f40;
                border-radius: 12px;
                padding: 0px;
            }
            
            QFrame#BookCard:hover {
                background-color: #2f2f40;
                border-color: #7F5AF0;
                box-shadow: 0 8px 24px rgba(127, 90, 240, 0.2);
            }
            
            /* Card Labels */
            QFrame#BookCard QLabel {
                background: transparent;
                border: none;
            }
            
            /* ================================================================
               LABELS - Typography Hierarchy
               ================================================================ */
            
            QLabel {
                color: #FFFFFE;
                background: transparent;
            }
            
            QLabel#titleLabel {
                font-size: 16px;
                font-weight: 700;
                color: #FFFFFE;
            }
            
            QLabel#authorLabel {
                font-size: 13px;
                font-style: italic;
                color: #94A1B2;
            }
            
            QLabel#metaLabel {
                font-size: 11px;
                color: #6a6a7a;
            }
            
            /* ================================================================
               MENU BAR - Top Application Menu
               ================================================================ */
            
            QMenuBar {
                background-color: #252535;
                color: #FFFFFE;
                border-bottom: 1px solid #16161a;
                padding: 4px;
            }
            
            QMenuBar::item {
                background-color: transparent;
                padding: 6px 12px;
                border-radius: 4px;
            }
            
            QMenuBar::item:selected {
                background-color: #3a3a4a;
            }
            
            QMenuBar::item:pressed {
                background-color: #7F5AF0;
            }
            
            QMenu {
                background-color: #252535;
                color: #FFFFFE;
                border: 2px solid #3a3a4a;
                border-radius: 8px;
                padding: 8px;
            }
            
            QMenu::item {
                padding: 8px 24px;
                border-radius: 4px;
            }
            
            QMenu::item:selected {
                background-color: #7F5AF0;
                color: #FFFFFE;
            }
            
            QMenu::separator {
                height: 1px;
                background: #3a3a4a;
                margin: 4px 8px;
            }
            
            /* ================================================================
               DIALOG BOXES - Modal Windows
               ================================================================ */
            
            QDialog {
                background-color: #1E1E2E;
                color: #FFFFFE;
                border: 2px solid #7F5AF0;
                border-radius: 12px;
            }
            
            /* ================================================================
               TEXT EDIT - Multi-line Input
               ================================================================ */
            
            QTextEdit {
                background-color: #16161a;
                color: #FFFFFE;
                border: 2px solid #252535;
                border-radius: 8px;
                padding: 12px;
                font-size: 13px;
                selection-background-color: #7F5AF0;
            }
            
            QTextEdit:focus {
                border-color: #7F5AF0;
            }
            
            /* ================================================================
               GROUP BOX - Sectioned Content
               ================================================================ */
            
            QGroupBox {
                background-color: #252535;
                border: 2px solid #3a3a4a;
                border-radius: 8px;
                margin-top: 12px;
                padding: 16px;
                font-weight: 600;
            }
            
            QGroupBox::title {
                color: #FFFFFE;
                subcontrol-origin: margin;
                subcontrol-position: top left;
                padding: 4px 8px;
                background-color: #7F5AF0;
                border-radius: 4px;
            }
            
            /* ================================================================
               MESSAGE BOX - System Dialogs
               ================================================================ */
            
            QMessageBox {
                background-color: #1E1E2E;
            }
            
            QMessageBox QLabel {
                color: #FFFFFE;
                font-size: 13px;
            }
            
            QMessageBox QPushButton {
                min-width: 80px;
            }
        )";
    }
    
    // Legacy method name for compatibility
    static QString getDefaultTheme() {
        return getAppStyleSheet();
    }
};

#endif // STYLELOADER_H
