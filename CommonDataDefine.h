#ifndef COMMONDATADEFINE_H
#define COMMONDATADEFINE_H
#include <QString>

class ViewData
{
public:
    enum AnnoStatus
    {
        ANNOFINISHED = 0,
        ANNOTAINGING,
        UNANNOTATION,
        INVALID
    };
    ViewData():_serisId("0"),
        _finishTime("--/--/--"),
        _importTime("--/--/--"),
        _annotStatus(UNANNOTATION),
        _address("./"),
        _annResult("{}")
    {

    }
    ViewData(const QString &id, const QString &finishTime,const QString &importTime, ViewData::AnnoStatus status, QString address, QString result):
        _serisId(id),
        _finishTime(finishTime),
        _importTime(importTime),
        _annotStatus(status),
        _address(address),
        _annResult(result)
    {

    }

    ViewData(const ViewData &data)
    {
        this->_serisId = data._serisId;
        this->_finishTime = data._finishTime;
        this->_importTime = data._importTime;
        this->_annotStatus = data._annotStatus;
        this->_address = data._address;
        this->_annResult = data._annResult;
    }


public:
    QString _serisId;//序列号
    QString _finishTime;//标注完时间
    QString _importTime;//导入时间
    AnnoStatus _annotStatus;//状态
    QString _address;//文件所在地址
    QString _annResult;//标注结果
};

#endif // COMMONDATADEFINE_H
