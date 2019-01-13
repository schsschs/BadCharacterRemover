#ifndef GETFILESIZEWORKER_H
#define GETFILESIZEWORKER_H

#include "mainwindow.h"
#include "filehelpfullibrary.h"
#include <QThread>

class GetFileSizeWorker : public QThread
{
    Q_OBJECT
    void run()
    {
        qint64 result = 0;
        qint64 count = 0;

        for(QString str : m_list)
        {
            result += FileHelpfulLibrary::dirSize(str);
            emit progress(++count, result);
        }

        emit resultReady(result);
    }
public:
    QStringList m_list;
signals:
    void resultReady( qint64 result );
    void progress( qint64 value, qint64 total );
};

#endif // GETFILESIZEWORKER_H
