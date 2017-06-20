#include "calcthread.h"

CalcThread::CalcThread()
{

}


void CalcThread::GetDataToStart(int A, int B, int XMin, int XMax)
{
    a=A;
    b=B;
    xMin=XMin;
    xMax=XMax;

}

void CalcThread::run()
{
    //вычисление координат и добавление точек в pointlist
    CoordinatesList pointlist;

    m_mutex.lock();
    pointlist.xMin=xMin;
    pointlist.xMax=xMax;
    m_mutex.unlock();

    float ymin=0.0f, ymax=0.0f;

    for (float x=(float)xMin; abs(x - xMax) < eps || x<(float)xMax; x=x+h)
    {
        int i=1;
        float yi=1.0f, y=0;

        while (abs(yi)>eps) {
                yi=pow(-1, i-1)*sin(i*(a*x-b))/i;
                y+=yi;
                i++;
        }
        y = floor(y*pow(10.0,4)+0.5)/pow(10.0,4); //округление
        x = floor(x*pow(10.0,1)+0.5)/pow(10.0,1);
        if(y < ymin)
            ymin = y;
        if(y > ymax)
            ymax = y;

        m_mutex.lock();
        pointlist.AddPoint(x, y);
        pointlist.yMin=ymin;
        pointlist.yMax=ymax;
        m_mutex.unlock();
        emit UpdateData(pointlist);
    }
    emit GraphIsOk();
    return;
}
