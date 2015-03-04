#include "MediaListWidget.h"
#include "ui_MediaListWidget.h"
#include "MediaListItemDelegate.h"

MediaListWidget::MediaListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaListWidget)
{
    ui->setupUi(this);
    ui->mediaFilesListView->setItemDelegate(new MediaListItemDelegate(ui->mediaFilesListView));
}

MediaListWidget::~MediaListWidget()
{
    delete ui;
}

void MediaListWidget::setModel(QAbstractItemModel* model)
{
    ui->mediaFilesListView->setModel(model);
}

QListView* MediaListWidget::getListView()
{
    return ui->mediaFilesListView;
}
