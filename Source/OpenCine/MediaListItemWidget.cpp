#include "MediaListItemWidget.h"
#include "ui_MediaListItemWidget.h"

MediaListItemWidget::MediaListItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaListItemWidget)
{
    ui->setupUi(this);

}

MediaListItemWidget::~MediaListItemWidget()
{
    delete ui;
}

QLabel* MediaListItemWidget::getLabelTop()
{
    return ui->labelTop;
}

QLabel* MediaListItemWidget::getLabelMiddle()
{
    return ui->labelCenter;
}

QLabel* MediaListItemWidget::getLabelBottom()
{
    return ui->labelBottom;
}

QLabel* MediaListItemWidget::getThumbnailView()
{
    return ui->thumbnailView;
}

