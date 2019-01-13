#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QLabel>
#include <QProgressBar>
#include <QListView>

namespace Ui {
class MainWindow;
}

enum SelectedMode {
    SM_FILE,
    SM_DIR
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static QStringList SelectedFiles;
    static QStringList SelectedDirs;
    static qint64 TotalSize;
    static qint64 CurentPoint;

private slots:
    void on_pbSelectFileOrDir_clicked();

    void on_radioButtonFile_clicked();

    void on_radioButtonDir_clicked();

    void on_pushButton_Search_clicked();

    void on_pushButton_Correct_clicked();

    void on_SetErrorRedBack();

    void on_pushButton_Info_clicked();

    void on_lineEdit_bc_TextSymbol_textChanged(const QString &arg1);

public slots:
    void onProgress( qint64 i, qint64 total );
    void onGetSizeComplete( qint64 i );

private:
    Ui::MainWindow *ui;

    // add references to Label and ProgressBar
    QLabel *statusLabel;
    QProgressBar *statusProgressBar;

    SelectedMode selectedMode = SelectedMode::SM_FILE;
    bool FileOrDirSelected = false;
    void SetSelectedToEmpty();
    bool SelectCheck();
    QColor bgColor;
    QListView m_lvCommandAssist;
};

#endif // MAINWINDOW_H
