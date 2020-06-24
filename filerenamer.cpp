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
}

QDir::SortFlag FileRenamer::getSortFlag(const int &sort)
{
    switch (sort)
    {
    case sortByName:
        return QDir::Name;
    case sortByDate:
        return QDir::Time;
    case sortByType:
        return QDir::Type;
    case sortBySize:
        return QDir::Size;
    default:
        return QDir::Unsorted;
    }
}

void FileRenamer::fileRename(const QString &newFileName, const int &sort, const bool &reverse, const QJSValue &selectedRows, const int &selectedRowscount)
{
    QList<qint32> indexList = {};
    for(int e = 0; e < selectedRowscount; e++)
        indexList.append(selectedRows.property(e).toInt());
    indexList.removeOne(0);

    QStringList newFileNameSplit = QStringList(newFileName.split("%%%"));
    if(newFileNameSplit.count() <= 1)
        newFileNameSplit.append("");

    openFilesAndFolders(QDir::currentPath(), getSortFlag(sort), reverse);

    int i = 0;

    if(indexList.count() >= 1)
    {
        foreach(int index, indexList)
        {
            QFileInfo file = m_filesAndFolders[index - 1];
            if(file.isFile())
            {
                ++i;
                QString newName = newFileNameSplit[0] + QString().setNum(i) + newFileNameSplit[1] + "." + file.suffix();
                QFile::rename(file.fileName(), newName);
            }
        }
    }
    else
    {
        foreach(QFileInfo const file, m_filesAndFolders)
        {
            if(file.isFile())
            {
                ++i;
                QString newName = newFileNameSplit[0] + QString().setNum(i) + newFileNameSplit[1] + "." + file.suffix();
                QFile::rename(file.fileName(), newName);
            }
        }
    }
}

QString FileRenamer::getCurrentDirectory()
{
    return QDir::currentPath();
}
