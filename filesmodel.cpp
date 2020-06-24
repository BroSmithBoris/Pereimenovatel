#include "filesmodel.h"
#include "filerenamer.h"

FilesModel::FilesModel(QObject *parent)
{
    getFilesAndFolders("C:/TestFilesFolder", 0, false);
}

QVariant FilesModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() > m_filesAndFolders.size())
    {
        return  QVariant();
    }

    switch (role) {
    case nameRole:
        return m_filesAndFolders[index.row()].fileName;
    case dateRole:
        return m_filesAndFolders[index.row()].fileDateCreate;
    case typeRole:
        return m_filesAndFolders[index.row()].fileType;
    case sizeRole:
        return m_filesAndFolders[index.row()].fileSize;
    default:
        return m_filesAndFolders[index.row()].fileName;
    }
}

QHash<int, QByteArray> FilesModel::roleNames() const
{
    QHash<int, QByteArray> roleNames;
    roleNames[nameRole] = "name";
    roleNames[dateRole] = "date";
    roleNames[typeRole] = "type";
    roleNames[sizeRole] = "size";
    return  roleNames;
}

int FilesModel::rowCount(const QModelIndex &parent) const
{
    return  m_filesAndFolders.size();
}

void FilesModel::getFilesAndFolders(const QString &directory, const int &sort, const bool &reverse)
{
    beginResetModel();

    FileRenamer files;
    files.openFilesAndFolders(directory, files.getSortFlag(sort), reverse);
    m_filesAndFolders.clear();
    m_filesAndFolders.append(FileParametrs{"..","","",""});
    foreach(auto &e, files.m_filesAndFolders)
    {
        if(e.isFile())
        {
            qint64 i = 0;
            QStringList sizeType = { "Б", "КБ", "МБ", "ГБ", "ТБ" };
            qint64 nSize = e.size();
            for (; nSize > 1023; nSize /= 1024, ++i) { }
            QString fileSize = QString().setNum(nSize) + " " + sizeType[i];
            m_filesAndFolders.append(FileParametrs{e.fileName(),
                                                   e.fileTime(QFileDevice::FileModificationTime).toString("dd.MM.yyyy hh:mm"),
                                                   e.suffix(),
                                                   fileSize});
        }
        else
            m_filesAndFolders.append(FileParametrs{e.fileName(),
                                                   e.fileTime(QFileDevice::FileModificationTime).toString("dd.MM.yyyy hh:mm"),
                                                   "",
                                                   ""});
    }
    endResetModel();
}
