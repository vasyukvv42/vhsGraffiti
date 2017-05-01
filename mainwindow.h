#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFormLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>
#include <QWidget>
#include <QAction>
#include <QIcon>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
private:
    void setupUi();

    QWidget *m_centralWidget;
    QPushButton *m_uploadButton;
    QLineEdit *m_tokenEdit;
    QLineEdit *m_filePathEdit;
    QLineEdit *m_nameEdit;
    QAction *m_generateTokenAction;
    QAction *m_openFileDialogAction;
};

#endif // MAINWINDOW_H
