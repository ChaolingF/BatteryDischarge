#ifndef PRODIGIT_3302F_3311F_H
#define PRODIGIT_3302F_3311F_H
#include <QtSerialPort/QSerialPort>
#include <iostream>
#include <unistd.h>
#include <QDebug>
#include <errno.h>
#include <cstdlib>

using namespace std;
class PRODIGIT_3302F_3311F
{
public:
    void openPort(char* portname);
    void reset();
    void load(bool switch1);
    void preset(bool switch2);
    void SetCURR(float CURR);
    float GetVOLT();
    float GetCURR();
    void closePort();
    float Load_Value;
private:
    QSerialPort serial;
};

#endif // PRODIGIT_3302F_3311F_H
