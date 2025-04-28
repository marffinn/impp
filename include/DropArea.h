#ifndef DROPAREA_H
#define DROPAREA_H

#include <QWidget>
#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>

class DropArea : public QWidget
{
    Q_OBJECT

public:
    explicit DropArea(QWidget *parent = nullptr);
    ~DropArea();

signals:
    void imageDropped(const QString &filePath);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    bool isImageFile(const QString &filePath);
    QLabel *m_label;
    bool m_highlight;
};

#endif // DROPAREA_H
