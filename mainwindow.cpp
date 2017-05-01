#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
    connect(m_chooseFileAction, SIGNAL(triggered(bool)),
                      this, SLOT(onChooseFileAction()));
    //TODO: other slots
    //TODO: save/read settings
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

    m_nameEdit = new QLineEdit(m_centralWidget);
    formLayout->addRow("Graffiti name: ", m_nameEdit);

    gridLayout->addLayout(formLayout, 0, 0, 3, 3);

    m_uploadButton = new QPushButton(m_centralWidget);
    m_uploadButton->setText("Upload");
    gridLayout->addWidget(m_uploadButton, 3, 1);

    setCentralWidget(m_centralWidget);
}

void MainWindow::onGenerateTokenAction()
{
    //TODO: implement getting new VK token
}

void MainWindow::onChooseFileAction()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose input file",
                                                    QDir::homePath(),
                /* Only those types were tested*/   "Images (*.gif *.png *.jpg)");
    m_filePathEdit->setText(filename);
}
