/* UT_MOTScheduler is a test project consisting of unit tests, each covering a class of MOTScheduler.
   The class named "Test" in the MOTScheduler base project is designed to be connected with the classes "Testers" and "Vehicles" by slots and signals.
   The unit test "UT_Tests" covers the slots and signals of "Tests", "Testers" and "Vehicles".
   Running this file subsequentally executes the unit tests and demonstrates the following workflow:
      1. Add, modify and query vehicle owners
      2. Add, modify and query Vehicles belogning to the added owners
      3. Add, modify and query MOT Stations.
      4. Hire and let leave MOT Testers working on the added stations. Modify and query their data.
      5. Schedule and execute MOT Tests.
      6. Verify that MOT Tester avaialabilty changes according to the scheduling and vehicle MOT expiry changes according to the results.*/

#include <QtTest>
#include <QObject>
#include "owners.h"
#include "vehicles.h"
#include "stations.h"
#include "testers.h"
#include "tests.h"

class UT_MOTScheduler : public QObject
{
    Q_OBJECT

public:
    UT_MOTScheduler();
    ~UT_MOTScheduler();

private:

    // Instants of classes being tested
    Owners   clOwners;
    Vehicles clVehicles;
    Stations clStations;
    Testers  clTesters;
    Tests    clTests;

    // Test Data for the Owners class
    const QString sFistNameInput1 = "Jakab";
    const QString sLastNameInput1 = "Gipsz";
    const QString sPhoneNumInput1 = "06 5 555 5555";
    const QString sFistNameInput2 = "Jakab Ákos";
    const QString sLastNameInput2 = "Gipsssz";
    const QString sPhoneNumInput2 = "06 6 666 6666";
    const QString sFistNameInput3 = "János";
    const QString sLastNameInput3 = "Minta";
    const QString sPhoneNumInput3 = "06 7 777 7777";
    int     nOwnerIDOutput1;
    int     nOwnerIDOutput2;
    QString sFistNameOutput;
    QString sLastNameOutput;
    QString sPhoneNumOutput;


    // Test Data for the Vehicles class
    const QString sPlateNumInput1        = "HEI-555";
    const QString sModelNameInput1       = "Opel Astra";
    const QDateTime dMOTExpiryDateInput1 = QDateTime::currentDateTime().addDays(20);
    const QString sPlateNumInput2        = "HEL-666";
    const QString sModelNameInput2       = "Opel Metal";
    const QDateTime dMOTExpiryDateInput2 = QDateTime::currentDateTime().addDays(15);
    const QString sPlateNumInput3        = "III-111";
    const QString sModelNameInput3       = "Nissan Qiraly";
    const QDateTime dMOTExpiryDateInput3 = QDateTime::currentDateTime().addDays(-1);;
    int       nVehicleIDOutput1;
    int       nVehicleIDOutput2;
    QString   sPlateNumOutput;
    QString   sModelNameOutput;
    int       nOwnerIDOutput;
    QDateTime dMOTExpiryDateOutput;

    // Test Data for the Stations class
    const QString sStationNameInput1    = "Marcal 1";
    const QString sStationAddressInput1 = "Győr city, Heaven Street 1.";
    const QString sStationNameInput2    = "Marcal 2";
    const QString sStationAddressInput2 = "Marcal city, Heaven Street 7.";
    const QString sStationNameInput3    = "Ady";
    const QString sStationAddressInput3 = "Ady city, Léda utca 12.";
    int     nStationIDOutput1;
    int     nStationIDOutput2;
    QString sStationNameOutput;
    QString sStationAddressOutput;

    // Test Data for the Testers class
    const QString sTrFistNameInput1        = "John";
    const QString sTrLastNameInput1        = "Doe";
    const QDateTime dTrAvailableFromInput1 = QDateTime::currentDateTime().addSecs(-(10 * 60));
    const QString sTrFistNameInput2        = "Jane";
    const QString sTrLastNameInput2        = "Dough";
    const QDateTime dTrAvailableFromInput2 = QDateTime::currentDateTime();
    const QString sTrFistNameInput3        = "James";
    const QString sTrLastNameInput3        = "Tester";
    const QDateTime dTrAvailableFromInput3 = QDateTime::currentDateTime().addSecs(10 * 60);
    int       nTesterIDOutput1;
    int       nTesterIDOutput2;
    QString   sTrFistNameOutput;
    QString   sTrLastNameOutput;
    int       nTrStationIDOutput;
    QDateTime dTrAvailableFromOutput1;
    QDateTime dTrAvailableFromOutput2;

    // Test Data for the Tests class
    int       nTestIDOutput1;
    int       nTestIDOutput2;
    int       nTsVehicleIDOutput;
    int       nTsTesterIDOutput;
    int       nTsStationIDOutput;
    QDateTime dTsDueDateOutput1;
    QDateTime dTsDueDateOutput2;
    int       nTsStatusOutput;
    QString   sTsTrFistNameOutput;
    QString   sTsTrLastNameOutput;
    int       nTsTrStationIDOutput;
    QDateTime dTsTrAvailableFromOutput;
    int       nTsPerformOutput;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void UT_Owners();
    void UT_Vehicles();
    void UT_Stations();
    void UT_Testers();
    void UT_Tests();

};

UT_MOTScheduler::UT_MOTScheduler()
{

}

UT_MOTScheduler::~UT_MOTScheduler()
{

}

void UT_MOTScheduler::initTestCase()
{
    // Connections between slots and signals of the instants

    QObject::connect(&clTests,   &Tests::RequestAvailability,
                     &clTesters, &Testers::RequestAvailability);

    QObject::connect(&clTesters,   &Testers::SendAvaialabily,
                     &clTests,     &Tests::SetAvaialabily);

    QObject::connect(&clTests,   &Tests::UpdateAvailability,
                     &clTesters, &Testers::UpdateAvailability);

    QObject::connect(&clTests,    &Tests::UpdateExpiry,
                     &clVehicles, &Vehicles::UpdateExpiry);
}

void UT_MOTScheduler::cleanupTestCase()
{

}

void UT_MOTScheduler::UT_Owners()
{  
    nOwnerIDOutput1 = clOwners.Add(sFistNameInput1, sLastNameInput1, sPhoneNumInput1);
    clOwners.Get(nOwnerIDOutput1, sFistNameOutput, sLastNameOutput, sPhoneNumOutput);
    QCOMPARE(sFistNameOutput, sFistNameInput1);
    QCOMPARE(sLastNameOutput, sLastNameInput1);
    QCOMPARE(sPhoneNumOutput, sPhoneNumInput1);

    nOwnerIDOutput2 = clOwners.Add(sFistNameInput3, sLastNameInput3, sPhoneNumInput3);
    clOwners.Get(nOwnerIDOutput2, sFistNameOutput, sLastNameOutput, sPhoneNumOutput);
    QCOMPARE(sFistNameOutput, sFistNameInput3);
    QCOMPARE(sLastNameOutput, sLastNameInput3);
    QCOMPARE(sPhoneNumOutput, sPhoneNumInput3);

    QCOMPARE (clOwners.Modify(nOwnerIDOutput1, sFistNameInput2, sLastNameInput2, sPhoneNumInput2), 0);
    clOwners.Get(nOwnerIDOutput1, sFistNameOutput, sLastNameOutput, sPhoneNumOutput);
    QCOMPARE(sFistNameOutput, sFistNameInput2);
    QCOMPARE(sLastNameOutput, sLastNameInput2);
    QCOMPARE(sPhoneNumOutput, sPhoneNumInput2);
}

void UT_MOTScheduler::UT_Vehicles()
{
    // Use the OwnerID outputs from the previous unit test as input

    nVehicleIDOutput1 = clVehicles.Add(sPlateNumInput1, sModelNameInput1, nOwnerIDOutput1, dMOTExpiryDateInput1);
    clVehicles.Get(nVehicleIDOutput1, sPlateNumOutput, sModelNameOutput, nOwnerIDOutput, dMOTExpiryDateOutput);
    QCOMPARE(sPlateNumOutput, sPlateNumInput1);
    QCOMPARE(sModelNameOutput, sModelNameInput1);
    QCOMPARE(nOwnerIDOutput, nOwnerIDOutput1);
    QCOMPARE(dMOTExpiryDateOutput, dMOTExpiryDateInput1);

    nVehicleIDOutput2 = clVehicles.Add(sPlateNumInput3, sModelNameInput3, nOwnerIDOutput2, dMOTExpiryDateInput3);
    clVehicles.Get(nVehicleIDOutput2, sPlateNumOutput, sModelNameOutput, nOwnerIDOutput, dMOTExpiryDateOutput);
    QCOMPARE(sPlateNumOutput, sPlateNumInput3);
    QCOMPARE(sModelNameOutput, sModelNameInput3);
    QCOMPARE(nOwnerIDOutput, nOwnerIDOutput2);
    QCOMPARE(dMOTExpiryDateOutput, dMOTExpiryDateInput3);

    QCOMPARE (clVehicles.Modify(nVehicleIDOutput1, sPlateNumInput2, sModelNameInput2, nOwnerIDOutput2, dMOTExpiryDateInput2), 0);
    clVehicles.Get(nVehicleIDOutput1, sPlateNumOutput, sModelNameOutput, nOwnerIDOutput, dMOTExpiryDateOutput);
    QCOMPARE(sPlateNumOutput, sPlateNumInput2);
    QCOMPARE(sModelNameOutput, sModelNameInput2);
    QCOMPARE(nOwnerIDOutput, nOwnerIDOutput2);
    QCOMPARE(dMOTExpiryDateOutput, dMOTExpiryDateInput2);
}

void UT_MOTScheduler::UT_Stations()
{
    nStationIDOutput1 = clStations.Add(sStationNameInput1, sStationAddressInput1);
    clStations.Get(nStationIDOutput1, sStationNameOutput, sStationAddressOutput);
    QCOMPARE(sStationNameOutput, sStationNameInput1);
    QCOMPARE(sStationAddressOutput, sStationAddressInput1);

    nStationIDOutput2 = clStations.Add(sStationNameInput3, sStationAddressInput3);
    clStations.Get(nStationIDOutput2, sStationNameOutput, sStationAddressOutput);
    QCOMPARE(sStationNameOutput, sStationNameInput3);
    QCOMPARE(sStationAddressOutput, sStationAddressInput3);


    QCOMPARE (clStations.Modify(nStationIDOutput1, sStationNameInput2, sStationAddressInput2), 0);
    clStations.Get(nStationIDOutput1, sStationNameOutput, sStationAddressOutput);
    QCOMPARE(sStationNameOutput, sStationNameInput2);
    QCOMPARE(sStationAddressOutput, sStationAddressInput2);
}

void UT_MOTScheduler::UT_Testers()
{
    // Use the StationID outputs from the previous unit test as input

    nTesterIDOutput1 = clTesters.Add(sTrFistNameInput1, sTrLastNameInput1, nStationIDOutput1, dTrAvailableFromInput1);
    clTesters.Get(nTesterIDOutput1, sTrFistNameOutput, sTrLastNameOutput, nTrStationIDOutput, dTrAvailableFromOutput1);
    QCOMPARE(sTrFistNameOutput, sTrFistNameInput1);
    QCOMPARE(sTrLastNameOutput, sTrLastNameInput1);
    QCOMPARE(nTrStationIDOutput, nStationIDOutput1);
    QCOMPARE(dTrAvailableFromOutput1, dTrAvailableFromInput1);

    nTesterIDOutput2 = clTesters.Add(sTrFistNameInput3, sTrLastNameInput3, nStationIDOutput2, dTrAvailableFromInput3);
    clTesters.Get(nTesterIDOutput2, sTrFistNameOutput, sTrLastNameOutput, nTrStationIDOutput, dTrAvailableFromOutput2);
    QCOMPARE(sTrFistNameOutput, sTrFistNameInput3);
    QCOMPARE(sTrLastNameOutput, sTrLastNameInput3);
    QCOMPARE(nTrStationIDOutput, nStationIDOutput2);
    QCOMPARE(dTrAvailableFromOutput2, dTrAvailableFromInput3);

    QCOMPARE (clTesters.Remove(nTesterIDOutput1), 0);
    QCOMPARE (clTesters.Get(nTesterIDOutput1, sTrFistNameOutput, sTrLastNameOutput, nTrStationIDOutput, dTrAvailableFromOutput1), -1);
    nTesterIDOutput1 = clTesters.Add(sTrFistNameInput1, sTrLastNameInput1, nStationIDOutput1, dTrAvailableFromInput1);

    QCOMPARE (clTesters.Modify(nTesterIDOutput1, sTrFistNameInput2, sTrLastNameInput2, nStationIDOutput1, dTrAvailableFromInput2), 0);
    clTesters.Get(nTesterIDOutput1, sTrFistNameOutput, sTrLastNameOutput, nTrStationIDOutput, dTrAvailableFromOutput1);
    QCOMPARE(sTrFistNameOutput, sTrFistNameInput2);
    QCOMPARE(sTrLastNameOutput, sTrLastNameInput2);
    QCOMPARE(nTrStationIDOutput, nStationIDOutput1);
    QCOMPARE(dTrAvailableFromOutput1, dTrAvailableFromInput2);
}

void UT_MOTScheduler::UT_Tests()
{
    // Use outputs from previous tests to verify the results of this unit test

    nTestIDOutput1 = clTests.Schedule(nVehicleIDOutput1, nStationIDOutput1);
    clTests.Get(nTestIDOutput1, nTsVehicleIDOutput, nTsTesterIDOutput, nTsStationIDOutput, dTsDueDateOutput1, nTsStatusOutput);
    QCOMPARE(nTsVehicleIDOutput, nVehicleIDOutput1);
    QCOMPARE(nTsTesterIDOutput, nTesterIDOutput1); // The first tester must be avaialble 10 minutes earlier
    QCOMPARE(nTsStationIDOutput, nStationIDOutput1);
    QCOMPARE(dTsDueDateOutput1, dTrAvailableFromInput2);
    QCOMPARE(nTsStatusOutput, SCHEDULED);

    // Verify that the avaialbility of the tester has been updated
    clTesters.Get(nTsTesterIDOutput, sTsTrFistNameOutput, sTsTrLastNameOutput, nTsTrStationIDOutput, dTsTrAvailableFromOutput);
    QCOMPARE(dTsTrAvailableFromOutput, dTrAvailableFromOutput1.addSecs((EXAM_MINUTES * 60) + (BREAK_MINUTES * 60)));

    nTestIDOutput2 = clTests.Schedule(nVehicleIDOutput2, nStationIDOutput1);
    clTests.Get(nTestIDOutput2, nTsVehicleIDOutput, nTsTesterIDOutput, nTsStationIDOutput, dTsDueDateOutput2, nTsStatusOutput);
    QCOMPARE(nTsVehicleIDOutput, nVehicleIDOutput2);
    QCOMPARE(nTsTesterIDOutput, nTesterIDOutput2); // The second tester must be avaialble 60 minutes earlier
    QCOMPARE(nTsStationIDOutput, nStationIDOutput1);
    QCOMPARE(dTsDueDateOutput2, dTrAvailableFromInput3);
    QCOMPARE(nTsStatusOutput, SCHEDULED);

    nTsPerformOutput = clTests.Perform(nTestIDOutput1);

    /* The below branches are triggered depending on the random generator.
       To ensure a specific result set CHANCE_OF_FAILED_PERCENT to '0' or '100' in tests.h */

    if (nTsPerformOutput == PASSED)
    {
        // Verify that the MOT expiry of the vehicle has been updated based on the former expiry date
        QCOMPARE (clVehicles.Get(nVehicleIDOutput1, sPlateNumOutput, sModelNameOutput, nOwnerIDOutput, dMOTExpiryDateOutput), 0);
        QCOMPARE(dMOTExpiryDateOutput, dMOTExpiryDateInput2.addYears(MOT_EXPIRY_USEDCAR_YEARS));
    }
    else // The Test has failed.
    {
        // Verify that a new Test has been scheduled.
        QCOMPARE(clTests.Get(nTsPerformOutput, nTsVehicleIDOutput, nTsTesterIDOutput, nTsStationIDOutput, dTsDueDateOutput1, nTsStatusOutput), 0);
        QCOMPARE(nTsTesterIDOutput, nTesterIDOutput1); // The first tester must be avaialble 10 minutes earlier
        QCOMPARE(dTsDueDateOutput1, dTsTrAvailableFromOutput);
    }

    nTsPerformOutput = clTests.Perform(nTestIDOutput2);

    if (nTsPerformOutput == PASSED)
    {
        // Verify that the MOT expiry of the vehicle has been updated based on the exam date
        QCOMPARE(clVehicles.Get(nVehicleIDOutput2, sPlateNumOutput, sModelNameOutput, nOwnerIDOutput, dMOTExpiryDateOutput), 0);
        QCOMPARE(dMOTExpiryDateOutput, dTsDueDateOutput2.addYears(MOT_EXPIRY_USEDCAR_YEARS));
    }
}

QTEST_APPLESS_MAIN(UT_MOTScheduler)

#include "tst_ut_motscheduler.moc"
