#include "filerenamer.h"
#include "filesmodel.h"

FileRenamer::FileRenamer(QObject *parent)
{
}

//Получение файлов и каталогов в пути
void FileRenamer::openFilesAndFolders(const QString &pathDirectory, const QDir::SortFlag &sortFlag, const bool &reverse)
{
    QDir::setCurrent(pathDirectory);

    m_filesAndFolders = reverse ?
                QDir::current().entryInfoList(QStringList(), QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Reversed | sortFlag |  QDir::DirsFirst):
                QDir::current().entryInfoList(QStringList(), QDir::AllEntries | QDir::NoDotAndDotDot, sortFlag| QDir::DirsFirst);
}

//Получение флага сортировки
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

//Переименование файлов
void FileRenamer::fileRename(const QString &newFileName, const int &sort, const bool &reverse, const QJSValue &selectedRows, const int &selectedRowscount)
{
    QList<qint32> indexList = {};    //Список индексов выделенных строк
    QList<QChar> forbiddenSymbols = {'/','\\','|','?','*','"','>','<',':'};    //Список некорректных символов

    foreach(QChar symbols, forbiddenSymbols)    //Проверка строки нового названия на валидность
        if(newFileName.contains(symbols))
            return;

    for(int e = 0; e < selectedRowscount; e++)  //Заполнение списка индексами
        indexList.append(selectedRows.property(e).toInt());
    indexList.removeOne(0);

    QStringList newFileNameSplit = QStringList(newFileName.split("%%%"));   //Разделение строки нового названия на части
    if(newFileNameSplit.count() <= 1)
        newFileNameSplit.append("");

    openFilesAndFolders(QDir::currentPath(), getSortFlag(sort), reverse);   //Получение файлов и каталогов в пути

    qDebug() << indexList;

    int i = 0;  //Номер порядка
    if(indexList.count() >= 1)  //Проверка на наличие определённых индексов для переименования
        foreach(int index, indexList)
        {

            QFileInfo file = m_filesAndFolders[index - 1];
            i = rename(file, newFileNameSplit, i);
        }
    else
        foreach(QFileInfo const file, m_filesAndFolders)
            i = rename(file, newFileNameSplit, i);
}

//Получение пути
QString FileRenamer::getCurrentDirectory()
{
    return QDir::currentPath();
}

//Переименование файла
int FileRenamer::rename(const QFileInfo &file, const QStringList &newFileNameSplit, int index)
{
    if(file.isFile())    //Проверка файл ли
    {
        ++index;
        QString newName = newFileNameSplit[0] + QString().setNum(index) + newFileNameSplit[1] + "." + file.suffix();
        QFile::rename(file.fileName(), newName);
    }

    return index;
}
