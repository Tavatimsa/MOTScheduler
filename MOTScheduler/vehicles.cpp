#include "vehicles.h"

bool operator==
(
    const ZVehicle &zVehicle,
    const int &nVehicleID
)
{
    return nVehicleID == zVehicle.nVehicleID;
}

Vehicles::Vehicles(QObject *parent)
    : QObject{parent}
{
    nNextID = 1;
}

int Vehicles::Get
(
    int        pnVehicleID,
    QString&   rpsPlateNum,
    QString&   rpsModelName,
    int&       rpnOwnerID,
    QDateTime& rpdMOTExpiryDate
)
{
    auto iVehicle = std::find(vectVehicleList.begin(), vectVehicleList.end(), pnVehicleID);
    if (iVehicle == vectVehicleList.end())
    {
        return -1; //Vehicle not found
    }
    else
    {
        rpsPlateNum      = iVehicle->sPlateNum;
        rpsModelName     = iVehicle->sModelName;
        rpnOwnerID       = iVehicle->nOwnerID;
        rpdMOTExpiryDate = iVehicle->dMOTExpiryDate;
    }
    return 0;
}

int Vehicles::Add
(
    QString   psPlateNum,
    QString   psModelName,
    int       pnOwnerID,
    QDateTime pdMOTExpiryDate
)
{
    ZVehicle zNewVehicle {nNextID,psPlateNum, psModelName, pnOwnerID, pdMOTExpiryDate};
    vectVehicleList.push_back(zNewVehicle);
    return nNextID++;
}

int Vehicles::Modify
(
    int       pnVehicleID,
    QString   psPlateNum,
    QString   psModelName,
    int       pnOwnerID,
    QDateTime pdMOTExpiryDate
)
{
    auto iVehicle = std::find(vectVehicleList.begin(), vectVehicleList.end(), pnVehicleID);
    if (iVehicle == vectVehicleList.end())
    {
        return -1; //Vehicle not found
    }
    iVehicle->sPlateNum       = psPlateNum;
    iVehicle->sModelName      = psModelName;
    iVehicle->nOwnerID        = pnOwnerID;
    iVehicle->dMOTExpiryDate  = pdMOTExpiryDate;
    return 0;
}

void Vehicles::UpdateExpiry
(
    int       pnVehicleID,
    QDateTime pdExamDate
)
{
    auto iVehicle = std::find(vectVehicleList.begin(), vectVehicleList.end(), pnVehicleID);
    if (iVehicle != vectVehicleList.end())
    {
        if (iVehicle->dMOTExpiryDate.isNull())
        {
            // The vehicle is new, this is the first tests and is valid for longer

            iVehicle->dMOTExpiryDate = (pdExamDate.addYears(MOT_EXPIRY_NEWCAR_YEARS));
        }
        else if ((pdExamDate < iVehicle->dMOTExpiryDate) &&
                 (pdExamDate > iVehicle->dMOTExpiryDate.addMonths(-(MOT_EXAM_BEFORE_EXPIRY_MONTHS))))
        {
            // The vehicle is used and the test is performed in the last month before the expiry of the last test.

            iVehicle->dMOTExpiryDate = (iVehicle->dMOTExpiryDate.addYears(MOT_EXPIRY_USEDCAR_YEARS));
        }
        else
        {
            // The vehicle is used, we just add the expiry time to the test time.

            iVehicle->dMOTExpiryDate = (pdExamDate.addYears(MOT_EXPIRY_USEDCAR_YEARS));
        }

    }
}
