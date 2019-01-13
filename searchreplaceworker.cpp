#include "searchreplaceworker.h"
#include "filehelpfullibrary.h"
#include <QFile>
#include <QByteArray>

void SearchReplaceWorker::run()
{
    if(!m_IsInit)
    {
        emit resultReady(-1);
    }

    ////
    // preparation
    ////
    QStringList completeFileList;
    m_Count = 0;
    if(!m_IsFile) // is dir list
    {
        for(QString path : m_FileList)
            completeFileList += FileHelpfulLibrary::getFileListFromDir(path);
    }
    else
    {
        completeFileList = m_FileList;
    }
    ////
    // process
    ////
    for(QString path : completeFileList)
    {
        QFile file(path);
        QByteArray byteArray = file.readAll();
        int startSearchIndex = 0;
        if(m_IsSearch)
        {
            while ((startSearchIndex=byteArray.indexOf(m_searchPattern, startSearchIndex)) >= 0)
                m_Count++;
        }
        else // Is Replace
        {
            byteArray.replace(m_searchPattern, m_replacePattern);
        }
        CurrentPoint += byteArray.size();
        emit progress(static_cast<int>((static_cast<float>(CurrentPoint / m_TotalSize) * 100)), m_Count);
    }
    ////
    // result
    ////
    emit resultReady(m_Count);
}


void SearchReplaceWorker::InitForSearch(const QStringList& FileList, bool IsFile, const QByteArray& SearchPattern)
{
    m_FileList = FileList;
    m_IsFile = IsFile;
    m_IsSearch = true;
    m_searchPattern = SearchPattern;
    m_IsInit = true;
}
void SearchReplaceWorker::InitForReplace(const QStringList& FileList, bool IsFile, const QByteArray& SearchPattern, const QByteArray& ReplacePattern)
{
    m_FileList = FileList;
    m_IsFile = IsFile;
    m_IsSearch = false;
    m_searchPattern = SearchPattern;
    m_replacePattern = ReplacePattern;
    m_IsInit = true;
}

