#include "MediaListItemDelegate.h"
#include <QStylePainter>
#include <QApplication>
#include <QPushButton>
#include <QPixmap>

MediaListItemDelegate::MediaListItemDelegate(QObject* parent) : QAbstractItemDelegate(parent)
{
    this->view = view;
    _sizeHint = new QSize(0,0);
}

MediaListItemDelegate::~MediaListItemDelegate()
{

}

void MediaListItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QVariant data = index.model()->data(index,Qt::DisplayRole);
    MediaListItemWidget *listItem = new MediaListItemWidget((QWidget*)this->parent());
    listItem->GetLabelTop()->setText(data.toString());
    _sizeHint->setWidth(listItem->sizeHint().width());
    _sizeHint->setHeight(listItem->sizeHint().height());
    QString fullPath = index.model()->data(index,pathRole).toString() + "/" + index.model()->data(index,Qt::DisplayRole).toString();
    QImage* thumbnail = (QImage*)index.model()->data(index,Qt::DecorationRole).value<void*>();
    if(thumbnail){
        listItem->GetThumbnailView()->setPixmap(QPixmap::fromImage(*thumbnail));
        painter->translate(option.rect.topLeft());
        listItem->resize( option.rect.size() );
        listItem->render(painter,  QPoint(), QRegion(),QWidget::DrawChildren);
    }
    delete listItem;

    painter->restore();
}

QSize MediaListItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return *this->_sizeHint;
}
