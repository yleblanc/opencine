#ifndef MEDIALISTITEMDELEGATE_H
#define MEDIALISTITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include "MediaListItemWidget.h"
#include "MediaListFileSystemModel.h"

class MediaListItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    MediaListItemDelegate(QObject* parent = 0);
    ~MediaListItemDelegate();


    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QAbstractItemView *view;
    QSize *_sizeHint;
};

#endif // MEDIALISTITEMDELEGATE_H
