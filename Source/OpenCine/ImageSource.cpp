#include "ImageSource.h"
#include <QFileInfo>
#include <QDir>

ImageSource::ImageSource(QString path, QObject *parent) : QObject(parent)
{
    this->scanSequence(path);
}

ImageSource::~ImageSource()
{

}

FileStruct ImageSource::getFileStruct(QString filename)
{
    FileStruct result;
    QFileInfo fileInfo(filename);
    result.basename = fileInfo.completeBaseName();
    result.path = fileInfo.absolutePath();
    result.extension = fileInfo.suffix();
    if(isNumerical(result.basename.right(1))){
        result.padding = 1;
        while(result.padding < result.basename.count() && isNumerical(result.basename.right(result.padding + 1))){
            result.padding++;

        }
    }
    result.fileNumber = result.basename.right(result.padding).toInt();
    result.nameRoot = result.basename.left(result.basename.count() - result.padding);

    return result;
}

void ImageSource::scanSequence(QString path)
{
    fileList.clear();
    FileStruct fileInfo  = this->getFileStruct(path);
    this->path = fileInfo.path;
    QDir dir(fileInfo.path);

    QString curFilename = fileInfo.basename + "." + fileInfo.extension;
    int curFileNum = fileInfo.fileNumber;

    while(dir.exists(curFilename)){
        this->firstFrameNum = curFileNum;
        curFileNum--;
        curFilename = fileInfo.nameRoot + QString::number(curFileNum).rightJustified(fileInfo.padding,'0') + "." + fileInfo.extension;
    }

    curFileNum = this->firstFrameNum;
    curFilename = fileInfo.nameRoot + QString::number(curFileNum).rightJustified(fileInfo.padding,'0') + "." + fileInfo.extension;
    this->numFrames = 0;

    while(dir.exists(curFilename)){
        fileList << curFilename;
        this->numFrames++;
        curFileNum++;
        curFilename = fileInfo.nameRoot + QString::number(curFileNum).rightJustified(fileInfo.padding,'0') + "." + fileInfo.extension;
    }
    this->_name = fileInfo.nameRoot + "[" + QString().number(this->firstFrameNum).rightJustified(fileInfo.padding,'0') + "-" + QString().number(this->firstFrameNum + this->numFrames - 1).rightJustified(fileInfo.padding,'0') + "]." + fileInfo.extension;
}

bool ImageSource::isNumerical(QString str)
{
    bool ok;
    str.toInt(&ok);
    return ok;
}

QString ImageSource::getName(){
    return this->_name;
}
