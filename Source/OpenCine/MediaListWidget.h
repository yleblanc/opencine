#ifndef MEDIALISTWIDGET_H
#define MEDIALISTWIDGET_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QListView>
#include "MediaListItemWidget.h"

namespace Ui {
class MediaListWidget;
}

class MediaListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MediaListWidget(QWidget *parent = 0);
    ~MediaListWidget();

    void SetModel(QAbstractItemModel* model);
    QWidget* GetListWidget();

public slots:
    void DataChanged(const QModelIndex& fromIndex,const QModelIndex& toIndex);
    void RowsRemoved(const QModelIndex & parent, int first, int last);
    void RowsInserted(const QModelIndex & parent, int first, int last);
    void ItemClickedEvent(QWidget *widget, bool control, bool shift);
    void SelectionChanged(const QItemSelection & selected, const QItemSelection & deselected);

private:
    Ui::MediaListWidget *_ui;
    QAbstractItemModel *_dataModel;
    QItemSelectionModel *_selectionModel;
};

#endif // MEDIALISTWIDGET_H
