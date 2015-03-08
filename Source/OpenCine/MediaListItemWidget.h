#ifndef MEDIALISTITEMWIDGET_H
#define MEDIALISTITEMWIDGET_H

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>

namespace Ui {
class MediaListItemWidget;
}

class MediaListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MediaListItemWidget(QWidget *parent = 0);
    ~MediaListItemWidget();

    QLabel* GetLabelTop();
    QLabel* GetLabelMiddle();
    QLabel* GetLabelBottom();
    QLabel* GetThumbnailView();
    void SetHighlighted(bool highlight);

private:
    Ui::MediaListItemWidget *_ui;
    QPoint _lastPoint;
    bool _mouseClick;
    bool _control;
    bool _shift;

protected:
    void mouseReleaseEvent ( QMouseEvent * e );
    void mousePressEvent ( QMouseEvent * e );
    void paintEvent(QPaintEvent *event);

signals:
    void ItemClickedEvent(QWidget * widget, bool control, bool shift);

};

#endif // MEDIALISTITEMWIDGET_H
