#ifndef SEARCHWORKER_H
#define SEARCHWORKER_H

#include <QThread>

class SearchReplaceWorker : public QThread
{
    Q_OBJECT
protected:
    void run();
public:

    void InitForSearch(const QStringList& FileList, bool IsFile, const QByteArray& SearchPattern);
    void InitForReplace(const QStringList& FileList, bool IsFile, const QByteArray& SearchPattern, const QByteArray& ReplacePattern);

private:
    bool m_IsFile = false; // false is dir
    bool m_IsSearch = true; // search or replace
    bool m_IsInit = false;
    QStringList m_FileList;
    qint64 m_TotalSize = 0;
    int m_Count = 0;
    QByteArray m_searchPattern;
    QByteArray m_replacePattern;

    qint64 CurrentPoint = 0;

signals:
    void resultReady( qint64 result );
    void progress( int percent, int count );
};

#endif // SEARCHWORKER_H
