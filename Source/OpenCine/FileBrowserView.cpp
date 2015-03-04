#include "filebrowserview.h"
#include "ui_filebrowserview.h"

FileBrowserView::FileBrowserView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileBrowserView)
{
    ui->setupUi(this);
}

FileBrowserView::~FileBrowserView()
{
    delete ui;
}
