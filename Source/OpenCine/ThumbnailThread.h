#ifndef THUMBNAILTHREAD_H
#define THUMBNAILTHREAD_H

#include <QObject>
#include <QThread>
#include "MediaListFileSystemModel.h"
#include <libraw/libraw.h>

class ThumbnailThread : public QThread
{
    Q_OBJECT

    QString path;
    int index;
    QSemaphore* semaphore;

public:
    ThumbnailThread(QString path, int index, QSemaphore* semaphore);
    ~ThumbnailThread();

    void run();

signals:
    void thumbnailReady(QImage* thumbnail, int index);

};

#endif // THUMBNAILTHREAD_H
