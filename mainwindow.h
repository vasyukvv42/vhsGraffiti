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
#include "vkdocuploader.h"

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
    void onUploadButtonClicked();
    void onApiError(const QString &title, const QString &info);
    void onUploadFinished();
private:
    void setupUi();
    QString configFilePath();

    QWidget *m_centralWidget;
    QPushButton *m_uploadButton;
    QLineEdit *m_tokenEdit;
    QLineEdit *m_filePathEdit;
    QLineEdit *m_titleEdit;
    QAction *m_generateTokenAction;
    QAction *m_chooseFileAction;
    QWebEngineView *m_webView;
    VKDocUploader *m_uploader;
};

#endif // MAINWINDOW_H
