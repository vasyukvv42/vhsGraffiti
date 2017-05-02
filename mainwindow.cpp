#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
    connect(m_chooseFileAction, SIGNAL(triggered(bool)),
                      this, SLOT(onChooseFileAction()));
    connect(m_generateTokenAction, SIGNAL(triggered(bool)),
                      this, SLOT(onGenerateTokenAction()));
    connect(m_uploadButton, SIGNAL(clicked(bool)),
            this, SLOT(onUploadButtonClicked()));

    QFile tokenFile(configFilePath());
    tokenFile.open(QIODevice::Text | QIODevice::ReadOnly);
    QTextStream in(&tokenFile);
    QString token;
    in >> token;
    m_tokenEdit->setText(token);
}

MainWindow::~MainWindow()
{
    delete m_webView;
}

void MainWindow::setupUi()
{
    setWindowTitle("/vhs/ grafFittities extra MaKeEr 123");
    setFixedSize(450, 150);
    m_centralWidget = new QWidget(this);

    QGridLayout *gridLayout = new QGridLayout(m_centralWidget);
    QFormLayout *formLayout = new QFormLayout;

    QIcon vkIcon(":/icons/vk.svg");
    m_tokenEdit = new QLineEdit(m_centralWidget);
    m_generateTokenAction = new QAction("Generate token...", this);
    m_generateTokenAction->setToolTip("Generate new VK access token");
    m_generateTokenAction->setIcon(vkIcon);
    m_tokenEdit->addAction(m_generateTokenAction, QLineEdit::TrailingPosition);
    formLayout->addRow("Access token: ", m_tokenEdit);

    QIcon folderIcon(":/icons/folder.svg");
    m_filePathEdit = new QLineEdit(m_centralWidget);
    m_chooseFileAction = new QAction("Choose file...", this);
    m_chooseFileAction->setToolTip("Choose input file");
    m_chooseFileAction->setIcon(folderIcon);
    m_filePathEdit->addAction(m_chooseFileAction, QLineEdit::TrailingPosition);
    formLayout->addRow("Input file: ", m_filePathEdit);

    m_titleEdit = new QLineEdit(m_centralWidget);
    formLayout->addRow("Graffiti title: ", m_titleEdit);

    gridLayout->addLayout(formLayout, 0, 0, 3, 3);

    m_uploadButton = new QPushButton(m_centralWidget);
    m_uploadButton->setText("Upload");
    gridLayout->addWidget(m_uploadButton, 3, 1);

    setCentralWidget(m_centralWidget);
}

void MainWindow::onGenerateTokenAction()
{
    m_webView = new QWebEngineView;
    QUrl url("https://oauth.vk.com/authorize?client_id=6012433"
             "&display=page"
             "&redirect_uri=https://oauth.vk.com/blank.html"
             "&scope=offline,docs"
             "&response_type=token");
    m_webView->load(url);
    m_webView->show();
    connect(m_webView, SIGNAL(urlChanged(QUrl)), this, SLOT(onUrlChanged(QUrl)));
}

void MainWindow::onUrlChanged(const QUrl &url)
{
    QString fixedUrl = url.toString();
    fixedUrl.replace("#", "?");
    QUrlQuery query(fixedUrl);
    QString queryKey = "https://oauth.vk.com/blank.html?access_token";
    if (query.hasQueryItem(queryKey)) {
        m_tokenEdit->setText(query.queryItemValue(queryKey));
        m_webView->close();
        QFile tokenFile(configFilePath());
        tokenFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate);
        QTextStream out(&tokenFile);
        out << m_tokenEdit->text();
    }
}

void MainWindow::onChooseFileAction()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose input file",
                                                    QDir::homePath(),
                /*Only gif and png work*/           "Images (*.gif *.png)");
    m_filePathEdit->setText(filename);
}

QString MainWindow::configFilePath()
{
    QString configPath;
    configPath = QStandardPaths::locate(QStandardPaths::ConfigLocation,
                                        QString(),
                                        QStandardPaths::LocateDirectory);
    QDir().mkpath(configPath + "vhsGraffiti");
    return QDir::cleanPath(configPath + QDir::separator() +
                           "vhsGraffiti" + QDir::separator() +
                           "token.txt");
}

void MainWindow::onUploadButtonClicked()
{
    m_uploader = new VKDocUploader(m_tokenEdit->text(),
                                   m_filePathEdit->text(),
                                   m_titleEdit->text());
    m_uploader->deleteLater();
    connect(m_uploader, SIGNAL(errorOccurred(QString,QString)),
                      this, SLOT(onApiError(QString,QString)));
    connect(m_uploader, SIGNAL(uploadFinished()),
                 this, SLOT(onUploadFinished()));
    m_uploader->uploadGraffiti();
}

void MainWindow::onApiError(const QString &title, const QString &info)
{
    QMessageBox::critical(this, title, info);
}

void MainWindow::onUploadFinished()
{
    QMessageBox::information(this, "Upload Finished",
                             "Graffiti successfully uploaded!");
}
