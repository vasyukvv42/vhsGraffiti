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
#include <QFileDialog>
#include <QWebEngineView>
#include <QEventLoop>
#include <QUrlQuery>
#include <QStandardPaths>
#include <QTextStream>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void onGenerateTokenAction();
    void onUrlChanged(const QUrl &url);
    void onChooseFileAction();
    //TODO: upload button slot
private:
    void setupUi();
    QString createConfigDir();

    QWidget *m_centralWidget;
    QPushButton *m_uploadButton;
    QLineEdit *m_tokenEdit;
    QLineEdit *m_filePathEdit;
    QLineEdit *m_nameEdit;
    QAction *m_generateTokenAction;
    QAction *m_chooseFileAction;
    QWebEngineView *m_webView;
};

#endif // MAINWINDOW_H
