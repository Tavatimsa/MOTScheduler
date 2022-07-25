#include "stations.h"

bool operator==
(
    ZStation &zStation,
    const int &nStationID
)
{
    return zStation.nStationID == nStationID;
}

Stations::Stations(QObject *parent)
    : QObject{parent}
{
    nNextID = 1;
}

int Stations::Get
(
    int      pnStationID,
    QString& rpsName,
    QString& rpsAddress
)
{
    auto iStation = std::find(vectStationList.begin(), vectStationList.end(), pnStationID);
    if (iStation == vectStationList.end())
    {
        return -1; //Station not found
    }
    rpsName = iStation->sName;
    rpsAddress = iStation->sAddress;
    return 0;
}

int Stations::Add
(
    QString psName,
    QString psAddress
)
{
    ZStation zNewStation {nNextID,psName, psAddress};
    vectStationList.push_back(zNewStation);
    return nNextID++;
}

int Stations::Modify
(
    int     pnStationID,
    QString psName,
    QString psAddress
)
{
    auto iStation = std::find(vectStationList.begin(), vectStationList.end(), pnStationID);
    if (iStation == vectStationList.end())
    {
        return -1; //Station not found
    }
    else
    {
        iStation->sName = psName;
        iStation->sAddress = psAddress;
    }
    return 0;
}
