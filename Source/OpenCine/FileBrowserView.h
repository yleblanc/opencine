#ifndef FILEBROWSERVIEW_H
#define FILEBROWSERVIEW_H

#include <QWidget>

namespace Ui {
class FileBrowserView;
}

class FileBrowserView : public QWidget
{
    Q_OBJECT

public:
    explicit FileBrowserView(QWidget *parent = 0);
    ~FileBrowserView();

private:
    Ui::FileBrowserView *ui;
};

#endif // FILEBROWSERVIEW_H
