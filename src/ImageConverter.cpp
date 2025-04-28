#include "ImageConverter.h"
#include <QImageReader>
#include <QImageWriter>
#include <QFileInfo>
#include <QBuffer>

ImageConverter::ImageConverter(QObject *parent)
    : QObject(parent)
{
    initSupportedFormats();
    
    // Map format names to file extensions
    m_formatExtensions["PNG"] = "png";
    m_formatExtensions["JPEG"] = "jpg";
    m_formatExtensions["BMP"] = "bmp";
    m_formatExtensions["GIF"] = "gif";
    m_formatExtensions["TIFF"] = "tif";
    m_formatExtensions["WEBP"] = "webp";
}

ImageConverter::~ImageConverter()
{
}

void ImageConverter::initSupportedFormats()
{
    // Get supported read formats
    QList<QByteArray> readFormats = QImageReader::supportedImageFormats();
    for (const QByteArray &format : readFormats) {
        m_supportedFormats.append(QString(format).toUpper());
    }
    
    // Get supported write formats
    QList<QByteArray> writeFormats = QImageWriter::supportedImageFormats();
    for (const QByteArray &format : writeFormats) {
        m_writableFormats.append(QString(format).toUpper());
    }
}

bool ImageConverter::convert(const QString &inputPath, const QString &outputPath, const QString &format)
{
    QImage image;
    if (!image.load(inputPath)) {
        return false;
    }
    
    return image.save(outputPath, format.toUtf8().constData());
}

QString ImageConverter::getImageInfo(const QString &filePath)
{
    QImageReader reader(filePath);
    QImage image;
    
    if (!reader.read(&image)) {
        return "Invalid image or unsupported format";
    }
    
    QFileInfo fileInfo(filePath);
    QString format = reader.format();
    
    QString info = QString("File: %1\nFormat: %2\nDimensions: %3 x %4\nSize: %5 KB")
                    .arg(fileInfo.fileName())
                    .arg(QString(format).toUpper())
                    .arg(image.width())
                    .arg(image.height())
                    .arg(fileInfo.size() / 1024.0, 0, 'f', 2);
    
    return info;
}

QString ImageConverter::detectImageFormat(const QString &filePath)
{
    QImageReader reader(filePath);
    return QString(reader.format()).toUpper();
}

QStringList ImageConverter::getSupportedFormats() const
{
    return m_supportedFormats;
}

QStringList ImageConverter::getWritableFormats() const
{
    return m_writableFormats;
}
