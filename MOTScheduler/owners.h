#ifndef OWNERS_H
#define OWNERS_H

#include <QObject>
#include <QString>
#include <algorithm>
#include <vector>

struct ZOwner
{
    int     nOwnerID;
    QString sFistName;
    QString sLastName;
    QString sPhoneNum;
};

bool operator==
(
    ZOwner &zOwner,
    const int &nOwnerID
);

class Owners : public QObject
{
    Q_OBJECT
public:

    explicit Owners(QObject *parent = nullptr);

    int Get
    (
        int      pnOwnerID,
        QString& rpsFistName,
        QString& rpsLastName,
        QString& rpsPhoneNum
    );

    int Add
    (
        QString psFistName,
        QString psLastName,
        QString psPhoneNum
    );

    int Modify
    (
        int     pnOwnerID,
        QString psFistName,
        QString psLastName,
        QString psPhoneNum
    );

public slots:

private:

    std::vector<ZOwner> vectOwnerList;
    int nNextID;

signals:

};

#endif // OWNERS_H
