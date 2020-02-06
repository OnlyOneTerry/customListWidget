#ifndef CUSTOMLISTMODEL_H
#define CUSTOMLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "CommonDataDefine.h"

class CustomListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CustomListModel(QObject *parent = Q_NULLPTR);
    ~CustomListModel();

    enum AnnoRole
    {
        SerisId = Qt::UserRole + 1,//序列号
        SerisStatus, //标注状态（已完成标注，标注中，未标注）
        SerisFinishTime,//标注完成时间
        SerisImportTime,//序列导入的时间
        SerisAddress,  //序列地址
        SerisAnnoResult//序列标注结果，已json格式的字符串保存
    };
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    void clear();

    //Add data;
    void insert(int index, Data *data);
    //Remove data;
    void remove(int index);
    bool deleteIndexFile(QString path);
   void append(const QString &id, const QString &finishTime,
               const QString &importTime,
         Data::AnnoStatus state,
         QString address,
         QString result);
    bool checkFileExist(int index);
    Data* findAt(int index);
    int getIndexById(QString serisID);
signals:
    void dataChanged();
public slots:
    void resetModel(const QString &id, const QString &finishTime,const QString& importTime, Data::AnnoStatus status, QString address, QString result);
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    int m_RobotCount;
    QList<Data*> m_data;//用QList<Data>做数据源
    QList<QString> m_serisIdlist;//用于检测是否有重复的id
    int m_currentIndex = 0;
    QString m_currentId ="";
};
#endif // CUSTOMLISTMODEL_H
