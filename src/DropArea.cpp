#include "DropArea.h"
#include <QPainter>
#include <QMimeData>
#include <QVBoxLayout>

DropArea::DropArea(QWidget *parent)
    : QWidget(parent)
    , m_highlight(false)
{
    setAcceptDrops(true);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    m_label = new QLabel("Drop Image Here", this);
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setStyleSheet("font-size: 16pt; color: #888;");
    
    layout->addWidget(m_label);
    
    setStyleSheet("DropArea { border: 2px dashed #aaa; border-radius: 5px; background-color: #f8f8f8; }");
}

DropArea::~DropArea()
{
}

void DropArea::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        if (urls.size() == 1 && isImageFile(urls.first().toLocalFile())) {
            event->acceptProposedAction();
            m_highlight = true;
            update();
        }
    }
}

void DropArea::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void DropArea::dragLeaveEvent(QDragLeaveEvent *event)
{
    m_highlight = false;
    update();
    event->accept();
}

void DropArea::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urls = event->mimeData()->urls();
        if (urls.size() == 1) {
            QString filePath = urls.first().toLocalFile();
            if (isImageFile(filePath)) {
                emit imageDropped(filePath);
            }
        }
    }
    
    m_highlight = false;
    update();
    event->acceptProposedAction();
}

void DropArea::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    
    if (m_highlight) {
        QPainter painter(this);
        painter.setPen(QPen(Qt::blue, 3, Qt::DashLine));
        painter.drawRect(rect().adjusted(2, 2, -2, -2));
    }
}

bool DropArea::isImageFile(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    QString extension = fileInfo.suffix().toLower();
    
    return (extension == "png" || extension == "jpg" || extension == "jpeg" || 
            extension == "bmp" || extension == "gif" || extension == "tif" || 
            extension == "tiff" || extension == "webp");
}
