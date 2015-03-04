#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <QObject>
#include <QStringList>

struct FileStruct{
    QString path;
    QString basename;
    QString extension;
    QString nameRoot;
    int padding;
    int fileNumber;
};

class ImageSource : public QObject
{
    Q_OBJECT

    enum ContainerType{
        fileSequence,
        MXF,
        MOV
    };

    QString path;
    int numFrames;
    int firstFrameNum;
    ContainerType containerType;
    QStringList fileList;

    bool isImageFile(QString filename);
    bool isNumerical(QString str);
    void scanSequence(QString path);
    FileStruct getFileStruct(QString filename);

public:
    explicit ImageSource(QString path, QObject *parent = 0);
    ~ImageSource();

    QStringList getFileList(){return this->fileList;}
    QString getPath(){return this->path;}

signals:

public slots:
};

#endif // IMAGESOURCE_H
