#ifndef FILERENAMER_H
#define FILERENAMER_H

#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <stdio.h>
#include <QDir>
#include <QDebug>

class FileRenamer : public QObject
{
    Q_OBJECT

    enum sortFlags
    {
        sortByName = Qt::DisplayRole,
        sortByDate,
        sortByType,
        sortBySize
    };

public:
    FileRenamer(QObject *parent = 0);

    Q_INVOKABLE QString getCurrentDirectory();
    Q_INVOKABLE void fileRename(const QString &newFileName, const int &sort, const bool &reverse, const QJSValue &selectedRows, const int &selectedRowscount);

    void openFilesAndFolders(const QString &pathDirectory, const QDir::SortFlag &sortFlag, const bool &reverse);
    int rename(const QFileInfo &file, const QStringList &newFileNameSplit, int index);

    QDir::SortFlag getSortFlag(const int &sort);
    QFileInfoList m_filesAndFolders;
};

#endif // FILERENAMER_H
