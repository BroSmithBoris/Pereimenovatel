#ifndef FILESMODEL_H
#define FILESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QDir>
#include <QDateTime>

struct FileParametrs
{
    QString fileName;
    QString fileDateCreate;
    QString fileSize;
};

class FilesModel : public QAbstractListModel
{
    Q_OBJECT

    enum filesModelRules
    {
        nameRole = Qt::DisplayRole,
        dateRole,
        sizeRole
    };

    enum sortFlags
    {
        sortByName = Qt::DisplayRole,
        sortByDate,
        sortBySize
    };

public:
    FilesModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void getFilesAndFolders(const QString &directory, const int &sort);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
private:
    QList<FileParametrs> m_filesAndFolders;
};

#endif // FILESMODEL_H
