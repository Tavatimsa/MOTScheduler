#ifndef TESTS_H
#define TESTS_H

#include <QObject>
#include <QDateTime>
#include <QString>
#include <algorithm>
#include <vector>
#include <QRandomGenerator>

const int FAILED  = -1;
const int PASSED  = 0;
const int SCHEDULED = 1;

const int CHANCE_OF_FAILED_PERCENT = 15;

struct ZTest
{
    int       nTestID;
    int       nVehicleID;
    int       nTesterID;
    int       nStationID;
    QDateTime dDueDate;
    int       nStatus;
};

bool operator==
(
    ZTest &zTest,
    const int &nTestID
);

class Tests : public QObject
{
    Q_OBJECT
public:

    explicit Tests(QObject *parent = nullptr);

    int Get
    (
        int        pnTestID,
        int&       rpnVehicleID,
        int&       rpnTesterID,
        int&       rpnStationID,
        QDateTime& rpdDueDate,
        int&       rpnStatus
    );

    /* Schedules a MOT Test.
       If there is no available tester, returns -1.
       Otherwise returns the ID of the new test. */

    int Schedule
    (
        int       pnVehicleID,
        int       pnStationID
    );

    /* Performs a MOT Test.
       If the test is not found returns -2.
       If the test passes, returns 0.
       If the test fails, schedules another test and returns the return value of Tests::Schedule. */

    int Perform
    (
        int       nTestID
    );


public slots:
    void SetAvaialabily (int pnTesterID, QDateTime pdAvailableFrom);

private:

    std::vector<ZTest> vectTestList;
    int       nNextID;
    int       nAvailableTester;
    QDateTime dAvailableDate;

signals:

    void RequestAvailability (int pnStationID);
    void UpdateAvailability (int pnTesterID);
    void UpdateExpiry (int pnVehicleID, QDateTime pdExamDate);
};

#endif // TESTS_H
