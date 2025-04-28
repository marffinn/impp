#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <QObject>
#include <QString>
#include <QImage>
#include <QMap>
#include <QStringList>

class ImageConverter : public QObject
{
    Q_OBJECT

public:
    explicit ImageConverter(QObject *parent = nullptr);
    ~ImageConverter();

    bool convert(const QString &inputPath, const QString &outputPath, const QString &format);
    QString getImageInfo(const QString &filePath);
    QString detectImageFormat(const QString &filePath);
    QStringList getSupportedFormats() const;
    QStringList getWritableFormats() const;

private:
    QMap<QString, QString> m_formatExtensions;
    QStringList m_supportedFormats;
    QStringList m_writableFormats;

    void initSupportedFormats();
};

#endif // IMAGECONVERTER_H
