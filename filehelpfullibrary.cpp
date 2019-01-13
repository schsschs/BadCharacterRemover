#include "filehelpfullibrary.h"
#include <QDir>

qint64 FileHelpfulLibrary::dirSize(const QString &dirPath) // from https://stackoverflow.com/questions/47854288/can-not-get-directory-size-in-qt-c
{
    qint64 size = 0;
    QDir dir(dirPath);
    //calculate total size of current directories' files
    QDir::Filters fileFilters = QDir::Files|QDir::System|QDir::Hidden;
    for(QString filePath : dir.entryList(fileFilters)) {
        QFileInfo fi(dir, filePath);
        size+= fi.size();
    }
    //add size of child directories recursively
    QDir::Filters dirFilters = QDir::Dirs|QDir::NoDotAndDotDot|QDir::System|QDir::Hidden;
    for(QString childDirPath : dir.entryList(dirFilters))
        size+= dirSize(dirPath + QDir::separator() + childDirPath);
    return size;
}

qint64 FileHelpfulLibrary::dirsSize(const QStringList &dirsPath)
{
    qint64 totalSize = 0;

    foreach (const QString &str, dirsPath) {
        totalSize += FileHelpfulLibrary::dirSize(str);
    }

    return totalSize;
}

qint64 FileHelpfulLibrary::filesSize(const QStringList &filesPath)
{
    qint64 totalSize = 0;

    foreach (const QString &str, filesPath) {
        QFile file(str);
        if (file.open(QIODevice::ReadOnly)){
            totalSize +=file.size();  //when file does open.
            file.close();
        }
    }

    return totalSize;
}

QString FileHelpfulLibrary::fileSizeFormat(qint64 size) { // from https://stackoverflow.com/questions/47854288/can-not-get-directory-size-in-qt-c
    QStringList units = {"Bytes", "KB", "MB", "GB", "TB", "PB"};
    int i;
    double outputSize = size;
    for(i=0; i<units.size()-1; i++) {
        if(outputSize<1024) break;
        outputSize= outputSize/1024;
    }
    return QString("%0 %1").arg(outputSize, 0, 'f', 2).arg(units[i]);
}

QStringList FileHelpfulLibrary::getFileListFromDir(const QString &pathToRootDir, bool subdirInclusive)
{
    QStringList result;
    QDir dir(pathToRootDir);

    QDir::Filters fileFilters = QDir::Files|QDir::System|QDir::Hidden;
    for(QString filePath : dir.entryList(fileFilters))
        result += filePath;
    if(subdirInclusive)
    {
        QDir::Filters dirFilters = QDir::Dirs|QDir::NoDotAndDotDot|QDir::System|QDir::Hidden;
        for(QString childDirPath : dir.entryList(dirFilters))
            result += getFileListFromDir(pathToRootDir + QDir::separator() + childDirPath);
    }

    return result;
}
