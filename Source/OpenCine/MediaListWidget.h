#ifndef MEDIALISTWIDGET_H
#define MEDIALISTWIDGET_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QListView>

namespace Ui {
class MediaListWidget;
}

class MediaListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MediaListWidget(QWidget *parent = 0);
    ~MediaListWidget();

    void setModel(QAbstractItemModel* model);
    QListView* getListView();

private:
    Ui::MediaListWidget *ui;
};

#endif // MEDIALISTWIDGET_H
