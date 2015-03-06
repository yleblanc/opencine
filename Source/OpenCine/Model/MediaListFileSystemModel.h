#ifndef MEDIALISTFILESYSTEMMODEL_H
#define MEDIALISTFILESYSTEMMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QDir>
#include <QListView>
#include <QSemaphore>
#include <QImage>
#include "ImageSource.h"

#define pathRole 100

class MediaListFileSystemModel : public QAbstractListModel
{
    Q_OBJECT

    QString currentPath;
    QStringList fileList;
    QList<ImageSource*> imageSourceList;
    QList<QImage*> thumbnailList;
    QListView* listView;
    QSemaphore* thumbnailSemaphore;

    void loadThumbnail(QString path, int index);

public:
    MediaListFileSystemModel(QObject* parent = 0);
    ~MediaListFileSystemModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

    void clear(int numRows);

    void setCurrentPath(QString path);
    void scanCurrentPath();

public slots:
    void pathChanged();
    void thumbnailReady(QImage* thumbnail, int index);
};

#endif // MEDIALISTFILESYSTEMMODEL_H
