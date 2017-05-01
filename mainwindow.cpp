#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
    //TODO: connect everything
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
    m_openFileDialogAction = new QAction("Choose file...", this);
    m_openFileDialogAction->setToolTip("Choose input file");
    m_openFileDialogAction->setIcon(folderIcon);
    m_filePathEdit->addAction(m_openFileDialogAction, QLineEdit::TrailingPosition);
    formLayout->addRow("Input file: ", m_filePathEdit);

    m_nameEdit = new QLineEdit(m_centralWidget);
    formLayout->addRow("Graffiti name: ", m_nameEdit);

    gridLayout->addLayout(formLayout, 0, 0, 3, 3);

    m_uploadButton = new QPushButton(m_centralWidget);
    m_uploadButton->setText("Upload");
    gridLayout->addWidget(m_uploadButton, 3, 1);

    setCentralWidget(m_centralWidget);
}
