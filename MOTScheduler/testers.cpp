#include "testers.h"

bool operator==
(
    ZTester &zTester,
    const int &nTesterID
)
{
    return zTester.nTesterID == nTesterID;
}

Testers::Testers(QObject *parent)
    : QObject{parent}
{
    nNextID = 1;
}

int Testers::Get
(
    int        pnTesterID,
    QString&   rpsFistName,
    QString&   rpsLastName,
    int&       rpnStationID,
    QDateTime& rpdAvailableFrom
)
{
    auto iTester = std::find(vectTesterList.begin(), vectTesterList.end(), pnTesterID);
    if (iTester == vectTesterList.end())
    {
        return -1; //Tester not found
    }
    rpsFistName      = iTester->sFistName;
    rpsLastName      = iTester->sLastName;
    rpnStationID     = iTester->nStationID;
    rpdAvailableFrom = iTester->dAvailableFrom;
    return 0;
}

int Testers::Add
(
    QString   psFistName,
    QString   psLastName,
    int       pnStationID,
    QDateTime pdAvailableFrom
)
{
    ZTester zNewTester {nNextID,psFistName, psLastName, pnStationID, pdAvailableFrom};
    vectTesterList.push_back(zNewTester);
    return nNextID++;
}

int Testers::Modify
(
    int       pnTesterID,
    QString   psFistName,
    QString   psLastName,
    int       pnStationID,
    QDateTime pdAvailableFrom
)
{
    auto iTester = std::find(vectTesterList.begin(), vectTesterList.end(), pnTesterID);
    if (iTester == vectTesterList.end())
    {
        return -1; //Tester not found
    }
    iTester->sFistName      = psFistName;
    iTester->sLastName      = psLastName;
    iTester->nStationID     = pnStationID;
    iTester->dAvailableFrom = pdAvailableFrom;
    return 0;
}

int Testers::Remove
(
    int       pnTesterID
)
{
    auto iTester = std::find(vectTesterList.begin(), vectTesterList.end(), pnTesterID);
    if (iTester == vectTesterList.end())
    {
        return -1; //Tester not found
    }
    vectTesterList.erase(iTester);
    return 0;
}

void Testers::UpdateAvailability
(
    int pnTesterID
)
{
    auto iTester = std::find(vectTesterList.begin(), vectTesterList.end(), pnTesterID);
    if (iTester != vectTesterList.end())
    {
        iTester->dAvailableFrom = iTester->dAvailableFrom.addSecs((EXAM_MINUTES * 60) + (BREAK_MINUTES * 60));
    }
}

void Testers::RequestAvailability
(
    int pnStationID
)
{
    // Determine which Tester working on the given Station frees up the earliest.

    std::vector<ZTester> vectFilteredTesters;
    std::copy_if (vectTesterList.begin(), vectTesterList.end(), std::back_inserter(vectFilteredTesters),
                  [pnStationID](ZTester zTester){return zTester.nStationID ==pnStationID;} );
    ZTester zNextTester = *min_element(vectTesterList.begin(), vectTesterList.end());

    // Send the tester and the date to the Tests class.

    emit SendAvaialabily (zNextTester.nTesterID, zNextTester.dAvailableFrom);
}
