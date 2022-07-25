#ifndef TESTERS_H
#define TESTERS_H

#include <QObject>
#include <QDateTime>
#include <QString>
#include <algorithm>
#include <vector>

const int EXAM_MINUTES  = 60;
const int BREAK_MINUTES = 10;

struct ZTester
{
    int       nTesterID;
    QString   sFistName;
    QString   sLastName;
    int       nStationID;
    QDateTime dAvailableFrom;
    bool operator<(const ZTester& T) const
    {
        return (dAvailableFrom < T.dAvailableFrom);
    }
};

bool operator==
(
    ZTester &zTester,
    const int &nTesterID
);

class Testers : public QObject
{
    Q_OBJECT
public:

    explicit Testers(QObject *parent = nullptr);

    int Get
    (
        int        pnTesterID,
        QString&   rpsFistName,
        QString&   rpsLastName,
        int&       rpnStationID,
        QDateTime& rpdAvailableFrom
    );

    int Add
    (
        QString   psFistName,
        QString   psLastName,
        int       pnStationID,
        QDateTime pdAvailableFrom
    );

    int Modify
    (
        int       pnTesterID,
        QString   psFistName,
        QString   psLastName,
        int       pnStationID,
        QDateTime pdAvailableFrom
    );

    int Remove
    (
        int       pnTesterID
    );

public slots:
    void RequestAvailability (int pnStationID);
    void UpdateAvailability (int pnTesterID);

private:

    std::vector<ZTester> vectTesterList;
    int nNextID;

signals:
    void SendAvaialabily (int pnTesterID, QDateTime pdAvailableFrom);
};

#endif // TESTERS_H
