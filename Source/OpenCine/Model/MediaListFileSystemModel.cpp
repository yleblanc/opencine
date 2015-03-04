#include "MediaListFileSystemModel.h"
#include "MediaListWidget.h"
#include <QPushButton>
#include "thumbnailthread.h"

MediaListFileSystemModel::MediaListFileSystemModel(QObject* parent)
{
    thumbnailSemaphore = new QSemaphore(3);
    currentPath = "/";
    listView = (QListView*)parent;
}

MediaListFileSystemModel::~MediaListFileSystemModel()
{
    delete thumbnailSemaphore;
}

void MediaListFileSystemModel::setCurrentPath(QString path)
{
    currentPath = path;
}

void MediaListFileSystemModel::scanCurrentPath()
{
    this->clear(0);

    QDir dir(currentPath);

    QStringList filters;
    filters << "*.dng";
    dir.setNameFilters(filters);

    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);

    QStringList curFileList = dir.entryList();
    int numFiles = curFileList.count();

    this->insertRows(0,numFiles);

    while(curFileList.count()){
        ImageSource* newSource = new ImageSource(currentPath + "/" + curFileList.at(0));
        this->imageSourceList.append(newSource);
    }

    for(int f = 0; f < numFiles; f++){

        this->setData(this->index(f),curFileList.at(f),Qt::DisplayRole);
        this->loadThumbnail(currentPath + "/" + curFileList.at(f),f);
    }

    return;
}

int MediaListFileSystemModel::rowCount(const QModelIndex &parent) const
{
    return fileList.count();
}

QVariant MediaListFileSystemModel::data(const QModelIndex &index, int role) const
{
    //listView->setIndexWidget(index,new QPushButton());
    if ( role == Qt::DisplayRole ) {
        //return QVariant();
        return QVariant(fileList.at(index.row()));
    }else if ( role == pathRole ) {
        //return QVariant();
        return QVariant(currentPath);
    }else if ( role == Qt::DecorationRole ) {
        //return QVariant();
        return QVariant(thumbnailList.at(index.row()));
    }
    return QVariant();
}

/*!
    Inserts a number of rows into the model at the specified position.
*/


bool MediaListFileSystemModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    if(!rows)return true;
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        fileList.insert(position, "");
        thumbnailList.insert(position,QImage());
        imageSourceList.insert(position,NULL);
    }

    endInsertRows();
    return true;

}


/*!
    Removes a number of rows from the model at the specified position.
*/


bool MediaListFileSystemModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    if(fileList.count() == 0) return true;
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        fileList.removeAt(position);
        //thumbnailList.at(row).detach();
        thumbnailList.removeAt(position);
    }

    endRemoveRows();
    return true;

}

/*!
    Changes an item in the string list, but only if the following conditions
    are met:

    * The index supplied is valid.
    * The index corresponds to an item to be shown in a view.
    * The role associated with editing text is specified.

    The dataChanged() signal is emitted if the item is changed.
*/


bool MediaListFileSystemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::DisplayRole) {
        fileList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }else if(index.isValid() && role == Qt::DecorationRole){
        thumbnailList.replace(index.row(), value.value<QImage>());
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

void MediaListFileSystemModel::clear(int numRows)
{
    if(this->rowCount() > 0){
        this->removeRows(0,this->rowCount());
    }
    this->insertRows(0,numRows);
}

void MediaListFileSystemModel::pathChanged()
{
    this->scanCurrentPath();
}

void MediaListFileSystemModel::loadThumbnail(QString path, int index)
{
    ThumbnailThread *workerThread = new ThumbnailThread(path,index,thumbnailSemaphore);
    connect(workerThread, SIGNAL(thumbnailReady(QImage*,int)), this, SLOT(thumbnailReady(QImage*,int)));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    workerThread->start();
}

void MediaListFileSystemModel::thumbnailReady(QImage* thumbnail, int index)
{
    this->setData(this->index(index),QVariant(*thumbnail),Qt::DecorationRole);
}
