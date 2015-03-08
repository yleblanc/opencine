#include "MediaListItemWidget.h"
#include "ui_MediaListItemWidget.h"

MediaListItemWidget::MediaListItemWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::MediaListItemWidget)
{
    _ui->setupUi(this);
    this->SetHighlighted(false);
}

MediaListItemWidget::~MediaListItemWidget()
{
    delete _ui;
}

QLabel* MediaListItemWidget::GetLabelTop()
{
    return _ui->labelTop;
}

QLabel* MediaListItemWidget::GetLabelMiddle()
{
    return _ui->labelCenter;
}

QLabel* MediaListItemWidget::GetLabelBottom()
{
    return _ui->labelBottom;
}

QLabel* MediaListItemWidget::GetThumbnailView()
{
    return _ui->thumbnailView;
}

void MediaListItemWidget::mousePressEvent ( QMouseEvent * e )
{
    _lastPoint = e->pos();
    _mouseClick = true;
    _control = e->modifiers().testFlag(Qt::ControlModifier);
    _shift = e->modifiers().testFlag(Qt::ShiftModifier);
}

void MediaListItemWidget::mouseReleaseEvent ( QMouseEvent * e )
{
    if ((_mouseClick) && (e->pos() == _lastPoint))
    {
        emit ItemClickedEvent((QWidget*)this, _control, _shift);
    }
}

void MediaListItemWidget::SetHighlighted(bool highlight)
{
    if(highlight){
        this->setStyleSheet("background: #5b5b5b");
    }else{
        this->setStyleSheet("background: #1e1e1e");
    }
}

void MediaListItemWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
