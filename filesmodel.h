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
    QString fileType;
    QString fileSize;
};

class FilesModel : public QAbstractListModel
{
    Q_OBJECT

    enum filesModelRules
    {
        nameRole = 0,
        dateRole,
        typeRole,
        sizeRole
    };

public:
    FilesModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void getFilesAndFolders(const QString &directory, const int &sort, const bool &reverse);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
private:
    QList<FileParametrs> m_filesAndFolders;
};

#endif // FILESMODEL_H
