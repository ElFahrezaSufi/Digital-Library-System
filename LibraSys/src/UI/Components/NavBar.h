#ifndef NAVBAR_H
#define NAVBAR_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

// ============================================================================
// NavBar: Modern Sidebar Navigation Component
// Design: Vertical navigation with icon-based buttons
// ============================================================================

class NavBar : public QWidget {
    Q_OBJECT
    
private:
    QPushButton* catalogButton;
    QPushButton* queueButton;
    QPushButton* historyButton;
    QPushButton* statsButton;
    
    QLabel* titleLabel;
    
    void setupUI();
    void applyStyles();
    void setActiveButton(QPushButton* button);
    
public:
    explicit NavBar(QWidget* parent = nullptr);
    
signals:
    void catalogRequested();
    void queueRequested();
    void historyRequested();
    void statsRequested();
    
private slots:
    void onCatalogClicked();
    void onQueueClicked();
    void onHistoryClicked();
    void onStatsClicked();
};

#endif // NAVBAR_H
