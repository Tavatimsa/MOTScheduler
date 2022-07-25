#include "tests.h"

bool operator==
(
    ZTest &zTest,
    const int &nTestID
)
{
    return zTest.nTestID == nTestID;
}

Tests::Tests(QObject *parent)
    : QObject{parent}
{
    nNextID = 1;
}

int Tests::Get
(
    int        pnTestID,
    int&       rpnVehicleID,
    int&       rpnTesterID,
    int&       rpnStationID,
    QDateTime& rpdDueDate,
    int&       rpnStatus
)
{
    auto iTest = std::find(vectTestList.begin(), vectTestList.end(), pnTestID);
    if (iTest == vectTestList.end())
    {
        return -1; //Test not found
    }
    rpnVehicleID = iTest->nVehicleID;
    rpnTesterID  = iTest->nTesterID;
    rpnStationID = iTest->nStationID;
    rpdDueDate   = iTest->dDueDate;
    rpnStatus    = iTest->nStatus;
    return 0;
}

int Tests::Schedule
(
        int       pnVehicleID,
        int       pnStationID
)
{
    nAvailableTester = 0;

    // Send the RequestAvailabily signal.
    // The received information will be used by the SetAvaialabily slot.

    emit RequestAvailability (pnStationID);

    if (nAvailableTester == 0)
    {
        return -1; // No available Tester
    }

    ZTest zNewTest {nNextID, pnVehicleID, nAvailableTester, pnStationID, dAvailableDate, SCHEDULED};
    vectTestList.push_back(zNewTest);

    // Make sure the Tester's Availability reflects the last test he/she is assigned to.

    emit UpdateAvailability (zNewTest.nTesterID);
    return nNextID++;
}


int Tests::Perform
(
    int       pnTestID
)
{
    auto iTest = std::find(vectTestList.begin(), vectTestList.end(), pnTestID);
    if (iTest == vectTestList.end())
    {
        return -1; //Test not found
    }
    if ((QRandomGenerator::global()->generate() % 100) + 1 <= CHANCE_OF_FAILED_PERCENT)
    {
        iTest->nStatus = FAILED;

        return this->Schedule(iTest->nVehicleID, iTest->nStationID);
    }
    else
    {
        iTest->nStatus = PASSED;

        // Make sure the Expiry Date of teh Vehicle is recalculated.
        emit UpdateExpiry (iTest->nVehicleID, iTest->dDueDate);
        return PASSED;
    }
}

void Tests::SetAvaialabily
(
        int pnTesterID,
        QDateTime pdAvailableFrom
)
{
    nAvailableTester = pnTesterID;
    dAvailableDate   = pdAvailableFrom;
}
