#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QStatusBar>

#include "DropArea.h"
#include "ImageConverter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleImageDropped(const QString &filePath);
    void convertImage();
    void updateUI();

private:
    void setupUI();
    void createMenus();

    DropArea *m_dropArea;
    ImageConverter *m_imageConverter;
    
    QComboBox *m_formatComboBox;
    QPushButton *m_convertButton;
    QLabel *m_statusLabel;
    QLabel *m_imageInfoLabel;
    
    QString m_currentImagePath;
};

#endif // MAINWINDOW_H
