#include "owners.h"

bool operator==
(
    ZOwner &zOwner,
    const int &nOwnerID
)
{
    return zOwner.nOwnerID == nOwnerID;
}

Owners::Owners(QObject *parent)
    : QObject{parent}
{
    nNextID = 1;
}

int Owners::Get
(
    int      pnOwnerID,
    QString& rpsFistName,
    QString& rpsLastName,
    QString& rpsPhoneNum
)
{
    auto iOwner = std::find(vectOwnerList.begin(), vectOwnerList.end(), pnOwnerID);
    if (iOwner == vectOwnerList.end())
    {
        return -1; //Owner not found
    }
    rpsFistName = iOwner->sFistName;
    rpsLastName = iOwner->sLastName;
    rpsPhoneNum = iOwner->sPhoneNum;
    return 0;
}

int Owners::Add
(
    QString psFistName,
    QString psLastName,
    QString psPhoneNum
)
{
    ZOwner zNewOwner {nNextID,psFistName, psLastName, psPhoneNum};
    vectOwnerList.push_back(zNewOwner);
    return nNextID++;
}

int Owners::Modify
(
    int     pnOwnerID,
    QString psFistName,
    QString psLastName,
    QString psPhoneNum
)
{
    auto iOwner = std::find(vectOwnerList.begin(), vectOwnerList.end(), pnOwnerID);
    if (iOwner == vectOwnerList.end())
    {
        return -1; //Owner not found
    }
    else
    {
        iOwner->sFistName = psFistName;
        iOwner->sLastName = psLastName;
        iOwner->sPhoneNum = psPhoneNum;
    }
    return 0;
}
