#include "NewMainWindow.h"
#include "ui_NewMainWindow.h"
#include <QtDebug>
#include <QMessageBox>

NewMainWindow::NewMainWindow(OCContext* context, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewMainWindow)
{
    ui->setupUi(this);

    _context = context;

    ui->topWdget->setTitleBarWidget(new QWidget());

    dirModel = new QFileSystemModel(this);

    dirModel->setRootPath("/");
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);

    ui->dirTreeView->setModel(dirModel);
    ui->dirTreeView->hideColumn(1);
    ui->dirTreeView->hideColumn(2);
    ui->dirTreeView->hideColumn(3);
    ui->dirTreeView->hideColumn(4);
    ui->dirTreeView->setHeaderHidden(true);
    ui->dirTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    connect(ui->dirTreeView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(fileTreeSelectionChanged(QItemSelection,QItemSelection)));

    browserMediaList = new MediaListWidget();
    browserMediaListModel = new MediaListFileSystemModel(browserMediaList->getListView());
    browserMediaList->setModel(browserMediaListModel);

    connect(this, SIGNAL(pathChanged()),browserMediaListModel,SLOT(pathChanged()));

    //Set Media Explorer widget
    ui->browserSplitter->addWidget(browserMediaList);

    playbackPresenter = new PlaybackPresenter(_context);
    previewPane = new PreviewPane(playbackPresenter);
    previewPane->setSizePolicy(QSizePolicy::Policy::Expanding,QSizePolicy::Policy::Expanding);
    playbackSlider = new PlaybackSlider(playbackPresenter);

    //Add preview pane
    ui->centralwidget->layout()->addWidget(previewPane);
    ui->centralwidget->layout()->addWidget(playbackSlider);
}

NewMainWindow::~NewMainWindow()
{
    delete dirModel;
    delete ui;
}

void NewMainWindow::fileTreeSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected)
{
    QModelIndexList indexes = ui->dirTreeView->selectionModel()->selection().indexes();
    QStringList selectedPaths;

    selectedPaths << dirModel->fileInfo(ui->dirTreeView->currentIndex()).absoluteFilePath();

    browserMediaListModel->setCurrentPath(selectedPaths.at(0));
    emit pathChanged();
}

