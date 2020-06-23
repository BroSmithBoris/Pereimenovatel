#include "filerenamer.h"
#include "filesmodel.h"

FileRenamer::FileRenamer(QObject *parent)
{
}

void FileRenamer::openFilesAndFolders(const QString &pathDirectory, const QDir::SortFlag &sortFlag, const bool &reverse)
{
    QDir::setCurrent(pathDirectory);

    m_filesAndFolders = reverse ?
                QDir::current().entryInfoList(QStringList(), QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Reversed | sortFlag |  QDir::DirsFirst):
                QDir::current().entryInfoList(QStringList(), QDir::AllEntries | QDir::NoDotAndDotDot, sortFlag| QDir::DirsFirst);

/*
    foreach(QFileInfo file, m_filesAndFolders)
    {
        qDebug() << QString("%1").arg(file.fileName());
    }
*/
}

QDir::SortFlag FileRenamer::getSortFlag(const int &sort)
{
    switch (sort)
    {
    case sortByName:
        return QDir::Name;
    case sortByDate:
        return QDir::Time;
    case sortBySize:
        return QDir::Size;
    default:
        return QDir::Unsorted;
    }
}

void FileRenamer::fileRename(const QString &newFileName, const int &sort, const bool &reverse)
{
    openFilesAndFolders(QDir::currentPath(), getSortFlag(sort), reverse);
    qint64 i = 0;
    foreach(QFileInfo const file, m_filesAndFolders)
    {
        //qDebug() << QString("%1").arg(file.fileName());
        if(file.isFile())
        {
            ++i;
            //qDebug() << file.fileName();
            QString newName = newFileName + "_" + QString().setNum(i) + "." + file.suffix();
            qDebug() << newName;
            QFile::rename(file.fileName(), newName);
        }
    }
}

QString FileRenamer::getCurrentDirectory()
{
    return QDir::currentPath();
}
