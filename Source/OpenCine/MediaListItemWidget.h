#ifndef MEDIALISTITEMWIDGET_H
#define MEDIALISTITEMWIDGET_H

#include <QWidget>
#include <QObject>
#include <QLabel>

namespace Ui {
class MediaListItemWidget;
}

class MediaListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MediaListItemWidget(QWidget *parent = 0);
    ~MediaListItemWidget();

    QLabel* getLabelTop();
    QLabel* getLabelMiddle();
    QLabel* getLabelBottom();
    QLabel* getThumbnailView();

private:
    Ui::MediaListItemWidget *ui;
};

#endif // MEDIALISTITEMWIDGET_H
