#include "MediaListItemDelegate.h"
#include <QStylePainter>
#include <QApplication>
#include <QPushButton>
#include <QPixmap>

MediaListItemDelegate::MediaListItemDelegate(QObject* parent) : QAbstractItemDelegate(parent)
{
    this->view = view;
}

MediaListItemDelegate::~MediaListItemDelegate()
{

}

void MediaListItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QVariant data = index.model()->data(index,Qt::DisplayRole);
    MediaListItemWidget *listItem = new MediaListItemWidget((QWidget*)this->parent());
    listItem->getLabelTop()->setText(data.toString());
    QString fullPath = index.model()->data(index,pathRole).toString() + "/" + index.model()->data(index,Qt::DisplayRole).toString();
    QImage thumbnail = index.model()->data(index,Qt::DecorationRole).value<QImage>();
    listItem->getThumbnailView()->setPixmap(QPixmap::fromImage(thumbnail));
    painter->translate(option.rect.topLeft());
    listItem->resize( option.rect.size() );
    listItem->render(painter,  QPoint(), QRegion(),QWidget::DrawChildren);
    delete listItem;

    painter->restore();
}

QSize MediaListItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(100,75);
}
