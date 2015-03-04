#ifndef NEWMAINWINDOW_H
#define NEWMAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QItemSelection>

#include "Core/Context.h"
#include "PlaybackSlider.h"
#include "PreviewPane.h"
#include "MediaListWidget.h"
#include "MediaListFileSystemModel.h"

namespace Ui {
class NewMainWindow;
}

class NewMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMainWindow(OCContext* context, QWidget *parent = 0);
    ~NewMainWindow();

private:
    Ui::NewMainWindow *ui;

    QFileSystemModel *dirModel;

    OCContext* _context;

    PlaybackPresenter* playbackPresenter;
    PreviewPane* previewPane;
    PlaybackSlider* playbackSlider;
    MediaListWidget* browserMediaList;
    MediaListFileSystemModel* browserMediaListModel;

public slots:

    void fileTreeSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected);

signals:
    void pathChanged();

};

#endif // NEWMAINWINDOW_H
