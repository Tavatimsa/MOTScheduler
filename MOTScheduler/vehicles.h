#ifndef VEHICLES_H
#define VEHICLES_H

#include <QObject>
#include <QDateTime>
#include <QString>
#include <algorithm>
#include <vector>

const int MOT_EXPIRY_NEWCAR_YEARS       = 4;
const int MOT_EXPIRY_USEDCAR_YEARS      = 2;
const int MOT_EXAM_BEFORE_EXPIRY_MONTHS = 1;

struct ZVehicle
{
    int       nVehicleID;
    QString   sPlateNum;
    QString   sModelName;
    int       nOwnerID;
    QDateTime dMOTExpiryDate;
};

bool operator==
(
    const ZVehicle &zVehicle,
    const int &nVehicleID
);

class Vehicles : public QObject
{
    Q_OBJECT

public:

    explicit Vehicles(QObject *parent = nullptr);

    int Get
    (
        int        pnVehicleID,
        QString&   rpsPlateNum,
        QString&   rpsModelName,
        int&       rpnOwnerID,
        QDateTime& rpdMOTExpiryDate
    );

    int Add
    (
        QString   psPlateNum,
        QString   psModelName,
        int       pnOwnerID,
        QDateTime pdMOTExpiryDate
    );

    int Modify
    (
        int       pnVehicleID,
        QString   psPlateNum,
        QString   psModelName,
        int       pnOwnerID,
        QDateTime pdMOTExpiryDate
    );

public slots:
    void UpdateExpiry (int pnVehicleID, QDateTime pdExamDate);

private:
    std::vector<ZVehicle> vectVehicleList;
    int nNextID;

signals:

};

#endif // VEHICLES_H
