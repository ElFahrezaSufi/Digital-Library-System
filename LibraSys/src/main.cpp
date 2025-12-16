#include "MainWindow.h"
#include "StyleLoader.h"
#include <QApplication>
#include <QIcon>

// ============================================================================
// Main Entry Point: Application Initialization
// ============================================================================

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Set application metadata
    app.setApplicationName("LibraSys");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("LibraSys Project");
    
    // Apply Dark Academia Tech Theme
    app.setStyleSheet(StyleLoader::getAppStyleSheet());
    
    // Create and show main window
    MainWindow window;
    window.show();
    
    return app.exec();
}
