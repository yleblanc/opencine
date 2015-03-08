#include "MediaListWidget.h"
#include "ui_MediaListWidget.h"

MediaListWidget::MediaListWidget(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::MediaListWidget)
{
    _ui->setupUi(this);
    _dataModel = NULL;
    _selectionModel = NULL;
}

MediaListWidget::~MediaListWidget()
{
    delete _ui;
    if(_dataModel) delete _dataModel;
    if(_selectionModel) delete _selectionModel;
}

void MediaListWidget::SetModel(QAbstractItemModel* model)
{
    if(_dataModel) delete _dataModel;
    if(_selectionModel) delete _selectionModel;
    _dataModel = model;
    _selectionModel = new QItemSelectionModel(_dataModel);
    connect(_dataModel,SIGNAL(dataChanged(const QModelIndex&,const QModelIndex&)),this,SLOT(DataChanged(const QModelIndex&,const QModelIndex&)));
    connect(_dataModel,SIGNAL(rowsRemoved(const QModelIndex&, int, int)),this,SLOT(RowsRemoved(const QModelIndex&, int, int)));
    connect(_dataModel,SIGNAL(rowsInserted(const QModelIndex&, int, int)),this,SLOT(RowsInserted(const QModelIndex&, int, int)));
    connect(_selectionModel,SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),this,SLOT(SelectionChanged(const QItemSelection&, const QItemSelection&)));
}

QWidget* MediaListWidget::GetListWidget()
{
    return _ui->mediaWidgetList;
}

void MediaListWidget::DataChanged(const QModelIndex& fromIndex,const QModelIndex& toIndex)
{
    for(int i = fromIndex.row(); i <= toIndex.row(); i++){
        MediaListItemWidget* curWidget = (MediaListItemWidget*)this->_ui->mediaWidgetList->layout()->itemAt(i)->widget();
        QString curMediaName = _dataModel->data(this->_dataModel->index(i,0),Qt::DisplayRole).toString();
        QImage* curThumbnail = (QImage*)_dataModel->data(this->_dataModel->index(i,0),Qt::DecorationRole).value<void*>();
        if(curThumbnail){
            curWidget->GetThumbnailView()->setPixmap(QPixmap::fromImage(*curThumbnail));
        }
        curWidget->GetLabelTop()->setText(curMediaName);
    }
}

void MediaListWidget::RowsRemoved(const QModelIndex & parent, int first, int last)
{
    for(int i = first; i <= last; i++){
        QLayoutItem* curItem = _ui->mediaWidgetList->layout()->takeAt(first);
        _ui->mediaWidgetList->layout()->removeItem(curItem);
        delete curItem->widget();

    }
}

void MediaListWidget::RowsInserted(const QModelIndex & parent, int first, int last)
{
    QVBoxLayout* listLayout = (QVBoxLayout*)this->_ui->mediaWidgetList->layout();
    for(int i = first; i <= last; i++){
        MediaListItemWidget* newWidget = new MediaListItemWidget(this);
        QWidget::connect(newWidget,SIGNAL(ItemClickedEvent(QWidget*,bool,bool)), this, SLOT(ItemClickedEvent(QWidget*,bool,bool)));
        listLayout->insertWidget(i,newWidget);
    }
}

void MediaListWidget::ItemClickedEvent(QWidget *widget, bool control, bool shift)
{
    int index = _ui->mediaWidgetList->layout()->indexOf(widget);

    if (control) {
        _selectionModel->select(_dataModel->index(index,0),QItemSelectionModel::Toggle);
        _selectionModel->setCurrentIndex(_dataModel->index(index,0), QItemSelectionModel::NoUpdate);
    }else{
        _selectionModel->select(_dataModel->index(index,0),QItemSelectionModel::ClearAndSelect);
        _selectionModel->setCurrentIndex(_dataModel->index(index,0), QItemSelectionModel::NoUpdate);
    }
}

void MediaListWidget::SelectionChanged(const QItemSelection & selected, const QItemSelection & deselected)
{
    for(int d = 0; d < selected.indexes().count(); d++){
        MediaListItemWidget *curWidget = (MediaListItemWidget*)_ui->mediaWidgetList->layout()->itemAt(selected.indexes().at(d).row())->widget();
        if(curWidget)curWidget->SetHighlighted(true);
    }

    for(int d = 0; d < deselected.indexes().count(); d++){
        MediaListItemWidget *curWidget = (MediaListItemWidget*)_ui->mediaWidgetList->layout()->itemAt(deselected.indexes().at(d).row())->widget();
        if(curWidget)curWidget->SetHighlighted(false);
    }
}
