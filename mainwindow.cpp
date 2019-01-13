#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filehelpfullibrary.h"
#include "getfilesizeworker.h"
#include "infodialog.h"
#include "hexconverter.h"
#include "searchpatternparser.h"
#include <QFileDialog>
#include <QListView>
#include <QTreeView>
#include <QTimer>

QStringList MainWindow::SelectedFiles;
QStringList MainWindow::SelectedDirs;
qint64 MainWindow::TotalSize = 0;
qint64 MainWindow::CurentPoint = 0;
FileHelpfulLibrary hlib();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    SetSelectedToEmpty();

    // create objects for the label and progress bar
    statusLabel = new QLabel(this);
    statusProgressBar = new QProgressBar(this);

    statusLabel->setText("Ready");
    // make progress bar text invisible
    statusProgressBar->setTextVisible(false);
    // add the two controls to the status bar
    ui->statusBar->addPermanentWidget(statusLabel);
    ui->statusBar->addPermanentWidget(statusProgressBar,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbSelectFileOrDir_clicked()
{
    QFileDialog dialog(this);

    if(ui->radioButtonFile->isChecked()) // Files
    {
        MainWindow::SelectedFiles = QFileDialog::getOpenFileNames(this,tr("All files"),QDir::currentPath(),tr("All files (*.*)") );
        if( !MainWindow::SelectedFiles.isEmpty() )
        {
            QString link = MainWindow::SelectedFiles[0];
            if(MainWindow::SelectedFiles.count()>1) {
                link += " ...";
            }
            ui->lePath->setText(link);

            MainWindow::TotalSize = FileHelpfulLibrary::filesSize(MainWindow::SelectedFiles);
            statusLabel->setText(FileHelpfulLibrary::fileSizeFormat(MainWindow::TotalSize));

            FileOrDirSelected = true;
        }
    }
    else {  // Directorys
        dialog.setFileMode(QFileDialog::DirectoryOnly);
        dialog.setOption(QFileDialog::DontUseNativeDialog, true);
        QListView *listView = dialog.findChild<QListView *>("listView");
        if(listView)
        {
            listView->setSelectionMode(QAbstractItemView::MultiSelection);
        }
        QTreeView *treeView = dialog.findChild<QTreeView *>();
        if(treeView)
        {
            treeView->setSelectionMode(QAbstractItemView::MultiSelection);
        }

        if(dialog.exec())
        {
            MainWindow::SelectedDirs = dialog.selectedFiles();
            if( !MainWindow::SelectedDirs.isEmpty() )
            {
                QString link = MainWindow::SelectedDirs[0];
                if(MainWindow::SelectedDirs.count()>1) {
                    link += " ...";
                }
                ui->lePath->setText(link);
                // Start get size dir thread
                GetFileSizeWorker* worker = new GetFileSizeWorker();
                worker->m_list = MainWindow::SelectedDirs;
                QObject::connect(worker, SIGNAL(progress(qint64,qint64)), this, SLOT(onProgress(qint64,qint64)));
                QObject::connect(worker, SIGNAL(resultReady(qint64)), this, SLOT(onGetSizeComplete(qint64)));
                QObject::connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
                // set corectly progressbar max value
                statusProgressBar->setMaximum(MainWindow::SelectedDirs.count());
                //
                worker->start();

                FileOrDirSelected = true;
            }
        }
    }
}

void MainWindow::on_radioButtonFile_clicked()
{
    if(selectedMode == SelectedMode::SM_FILE) return; // Not changed

    SetSelectedToEmpty();
    selectedMode = SelectedMode::SM_FILE;
}

void MainWindow::on_radioButtonDir_clicked()
{
    if(selectedMode == SelectedMode::SM_DIR) return; // Not changed

    SetSelectedToEmpty();
    selectedMode = SelectedMode::SM_DIR;
}

void MainWindow::SetSelectedToEmpty()
{
    FileOrDirSelected = false;
    ui->lePath->setText("Please select files or directories");
}

void MainWindow::onProgress( qint64 i, qint64 total )
{
    statusProgressBar->setValue(static_cast<int>(i));
    statusLabel->setText(FileHelpfulLibrary::fileSizeFormat(total));
}

void MainWindow::onGetSizeComplete( qint64 i )
{
    MainWindow::TotalSize = i;
    statusLabel->setText(FileHelpfulLibrary::fileSizeFormat(MainWindow::TotalSize));
}

void MainWindow::on_pushButton_Search_clicked()
{
    SelectCheck();
    // TODO
}

void MainWindow::on_pushButton_Correct_clicked()
{
    SelectCheck();
    // TODO
}

bool MainWindow::SelectCheck()
{
    if(!FileOrDirSelected)
    {
        ui->groupBox_FileOrDir->setStyleSheet("background-color:red;");
        bgColor = ui->groupBox_FileOrDir->palette().background().color();
        QTimer::singleShot(200, this, SLOT(on_SetErrorRedBack()));
        return false;
    }
    return true;
}
void MainWindow::on_SetErrorRedBack()
{
    QPalette pal = ui->groupBox_FileOrDir->palette();
    pal.setColor(QPalette::Background, bgColor);

    //ui->groupBox_FileOrDir->setStyleSheet("background-color:lightgray;");
    //ui->groupBox_FileOrDir->palette().background();
}

void MainWindow::on_pushButton_Info_clicked()
{
    InfoDialog infoDialog;
    infoDialog.setModal(true);
    infoDialog.exec();
}

void MainWindow::on_lineEdit_bc_TextSymbol_textChanged(const QString &arg1)
{
    ui->lineEdit_bc_Hex->setText(HexConverter::ToHex(SearchPatternParser::Parse(arg1)));
}
