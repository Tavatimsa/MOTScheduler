#ifndef STATIONS_H
#define STATIONS_H

#include <QObject>
#include <QDateTime>
#include <QString>
#include <algorithm>
#include <vector>

struct ZStation
{
    int     nStationID;
    QString sName;
    QString sAddress;
};

bool operator==
(
    ZStation &zStation,
    const int &nStationID
);

class Stations : public QObject
{
    Q_OBJECT
public:

    explicit Stations(QObject *parent = nullptr);

    int Get
    (
        int      pnStationID,
        QString& rpsName,
        QString& rpsAddress
    );

    int Add
    (
        QString psStationName,
        QString psAddress
    );

    int Modify
    (
        int     pnStationID,
        QString psName,
        QString psAddress
    );

public slots:

private:

    std::vector<ZStation> vectStationList;
    int nNextID;

signals:

};

#endif // STATIONS_H
