#include "filerenamer.h"
#include "filesmodel.h"

FileRenamer::FileRenamer(QObject *parent)
{
}

void FileRenamer::openFilesAndFolders(const QString &pathDirectory, const QDir::SortFlag &sortFlag)
{
    QDir::setCurrent(pathDirectory);

    m_filesAndFolders = QDir::current().entryInfoList(QStringList(), QDir::AllEntries | QDir::NoDot, sortFlag | QDir::DirsFirst);

/*
    foreach(QFileInfo file, m_filesAndFolders)
    {
        qDebug() << QString("%1").arg(file.fileName());
    }
*/
}

void FileRenamer::fileRename(const QString &newFileName)
{
    openFilesAndFolders(QDir::currentPath(), QDir::Name);
    qint64 i = 0;
    foreach(QFileInfo const file, m_filesAndFolders)
    {;
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
