#ifndef CALCTHREAD_H
#define CALCTHREAD_H

#include <QObject>
#include <QThread>
#include <windows.h>
#include "coordinateslist.h"

class CalcThread : public QThread
{
    Q_OBJECT
public:
    CalcThread();
    void run();
private:
    QMutex	m_mutex;

    int a;
    int b;
    int xMin;
    int xMax;
    float h=0.1f;
    float eps=0.0001f;

signals:
    void UpdateData(CoordinatesList pointlist);
    void GraphIsOk();

public slots:

    void GetDataToStart(int A, int B, int XMin, int XMax);
};

#endif // CALCTHREAD_H
