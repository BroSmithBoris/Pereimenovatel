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
public:
    FileRenamer(QObject *parent = 0);

    Q_INVOKABLE QString getCurrentDirectory();
    Q_INVOKABLE void fileRename(const QString &newFileName);

    void openFilesAndFolders(const QString &pathDirectory, const QDir::SortFlag &sortFlag);

    QFileInfoList m_filesAndFolders;
};

#endif // FILERENAMER_H
