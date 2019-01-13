#ifndef FILEHELPFULLIBRARY_H
#define FILEHELPFULLIBRARY_H

#include <QObject>

class FileHelpfulLibrary : public QObject
{
    Q_OBJECT
public:

    static qint64 dirSize(const QString &dirPath);
    static qint64 dirsSize(const QStringList &dirsPath);
    static qint64 filesSize(const QStringList &filesPath);
    static QString fileSizeFormat(qint64 size);

    static QStringList getFileListFromDir(const QString &pathToRootDir, bool subdirInclusive = true);

signals:

public slots:
};

#endif // FILEHELPFULLIBRARY_H
