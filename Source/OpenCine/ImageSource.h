#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <QObject>
#include <QStringList>

struct FileStruct{
    int padding;
    int fileNumber;
    QString basename;
    QString path;
    QString extension;
    QString nameRoot;
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
    QString _name;
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
    QString getName();

signals:

public slots:
};

#endif // IMAGESOURCE_H
