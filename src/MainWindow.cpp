#include "MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileInfo>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_currentImagePath("")
{
    m_imageConverter = new ImageConverter(this);
    setupUI();
    createMenus();
    updateUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // Central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // Drop area
    m_dropArea = new DropArea(this);
    m_dropArea->setMinimumSize(400, 300);
    connect(m_dropArea, &DropArea::imageDropped, this, &MainWindow::handleImageDropped);
    
    // Image info label
    m_imageInfoLabel = new QLabel("Drop an image here", this);
    m_imageInfoLabel->setAlignment(Qt::AlignCenter);
    
    // Format selection
    QGroupBox *formatGroupBox = new QGroupBox("Output Format", this);
    QVBoxLayout *formatLayout = new QVBoxLayout(formatGroupBox);
    
    m_formatComboBox = new QComboBox(this);
    m_formatComboBox->addItems(m_imageConverter->getWritableFormats());
    
    formatLayout->addWidget(m_formatComboBox);
    
    // Convert button
    m_convertButton = new QPushButton("Convert", this);
    m_convertButton->setEnabled(false);
    connect(m_convertButton, &QPushButton::clicked, this, &MainWindow::convertImage);
    
    // Status label
    m_statusLabel = new QLabel(this);
    m_statusLabel->setAlignment(Qt::AlignCenter);
    
    // Add widgets to main layout
    mainLayout->addWidget(m_dropArea);
    mainLayout->addWidget(m_imageInfoLabel);
    mainLayout->addWidget(formatGroupBox);
    mainLayout->addWidget(m_convertButton);
    mainLayout->addWidget(m_statusLabel);
    
    // Status bar
    statusBar()->showMessage("Ready");
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu("&File");
    
    QAction *openAction = fileMenu->addAction("&Open Image...");
    connect(openAction, &QAction::triggered, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Open Image", 
            QDir::homePath(), "Image Files (*.png *.jpg *.jpeg *.bmp *.gif *.tif *.tiff *.webp)");
        
        if (!filePath.isEmpty()) {
            handleImageDropped(filePath);
        }
    });
    
    fileMenu->addSeparator();
    
    QAction *exitAction = fileMenu->addAction("E&xit");
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    
    QAction *aboutAction = helpMenu->addAction("&About");
    connect(aboutAction, &QAction::triggered, [this]() {
        QMessageBox::about(this, "About IMPP", 
            "IMPP - Image Format Converter\n\n"
            "A simple application to convert images between different formats.\n"
            "Drag and drop images to convert them.");
    });
}

void MainWindow::handleImageDropped(const QString &filePath)
{
    m_currentImagePath = filePath;
    
    QFileInfo fileInfo(filePath);
    QString format = m_imageConverter->detectImageFormat(filePath);
    
    m_imageInfoLabel->setText(m_imageConverter->getImageInfo(filePath));
    
    // Remove the current format from the combo box options
    m_formatComboBox->clear();
    QStringList formats = m_imageConverter->getWritableFormats();
    formats.removeAll(format.toLower());
    m_formatComboBox->addItems(formats);
    
    updateUI();
    
    statusBar()->showMessage("Image loaded: " + fileInfo.fileName());
}

void MainWindow::convertImage()
{
    if (m_currentImagePath.isEmpty()) {
        return;
    }
    
    QFileInfo fileInfo(m_currentImagePath);
    QString selectedFormat = m_formatComboBox->currentText();
    
    QString outputPath = QFileDialog::getSaveFileName(this, "Save Converted Image",
        fileInfo.dir().filePath(fileInfo.baseName() + "." + selectedFormat.toLower()),
        selectedFormat + " Files (*." + selectedFormat.toLower() + ")");
    
    if (outputPath.isEmpty()) {
        return;
    }
    
    if (m_imageConverter->convert(m_currentImagePath, outputPath, selectedFormat)) {
        m_statusLabel->setText("Conversion successful: " + QFileInfo(outputPath).fileName());
        statusBar()->showMessage("Image converted successfully");
    } else {
        m_statusLabel->setText("Conversion failed");
        statusBar()->showMessage("Conversion failed");
    }
}

void MainWindow::updateUI()
{
    m_convertButton->setEnabled(!m_currentImagePath.isEmpty());
}
