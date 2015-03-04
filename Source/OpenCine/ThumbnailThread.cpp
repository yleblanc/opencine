#include "thumbnailthread.h"
#include <QImage>

ThumbnailThread::ThumbnailThread(QString path, int index, QSemaphore* semaphore)
{
    this->index = index;
    this->path = path;
    this->semaphore = semaphore;
}

ThumbnailThread::~ThumbnailThread()
{

}

void ThumbnailThread::run()
{
    semaphore->acquire();
    LibRaw* libRawProcessor = new LibRaw();
    libRawProcessor->open_file(path.toStdString().c_str());
    libRawProcessor->unpack();
    libRawProcessor->imgdata.params.half_size = 1;
    libRawProcessor->imgdata.params.user_qual = 0;
    libRawProcessor->imgdata.params.use_rawspeed = 1;
    libRawProcessor->dcraw_process();
    int ret;
    libraw_processed_image_t *image = libRawProcessor->dcraw_make_mem_image(&ret);
    QImage* thumbnail = new QImage(image->data,image->width,image->height,QImage::Format_RGB888);
    QImage* thumbnailScaled = new QImage(thumbnail->scaledToHeight(100));
    LibRaw::dcraw_clear_mem(image);
    libRawProcessor->recycle();
    delete thumbnail;
    semaphore->release();
    emit thumbnailReady(thumbnailScaled, index);
}
