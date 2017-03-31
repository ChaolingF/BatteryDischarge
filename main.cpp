#include "prodigit_3302f_3311f.h"
#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QDateTime>
#include <QThread>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set Time format
    QTime time;
    QString t_format = "hh:mm:ss.zzz"; //time format
    QString d_format = "yyyy.MM.dd"; // date format
    QDateTime local(QDateTime::currentDateTime());


    PRODIGIT_3302F_3311F Load;
    char portname[10];
    float end_volt;
    float discharge_current;

    cout << "Pleae enter Load port (i.e. COM63):";
    cin >> portname;

    cout << endl << "Please enter the current to discharge (i.e. 8.6):";
    cin >> discharge_current;

    cout << endl << "Please enter the end-of-discharge voltage (i.e. 10.5):";
    cin >> end_volt;

    Load.openPort(portname);
    Load.reset();
    Load.SetCURR(discharge_current);

    Load.load(true);
    Load.preset(true);
    // Create log file
    fstream log("log.txt",ios::out | ios::app);
    log << "Test date" << local.currentDateTime().toString(d_format).toStdString().c_str();
    log << " " << time.currentTime().toString(t_format).toStdString().c_str() << "\n\n";
    log << "Time;";
    log << "Voltage;";
    log << "Current;";


    log << "\n";
    log.close();

    while (Load.GetVOLT()>= end_volt){
        cout << "Voltage:" << Load.GetVOLT()<< "     " << "Current:" << Load.GetCURR();
        cout << endl << endl;
        fstream log("log.txt",ios::out | ios::app);
        log << time.currentTime().toString(t_format).toStdString().c_str()<<";";
        log << Load.GetVOLT() << ";";
        log << Load.GetCURR() << ";";
        log << "\n";
        log.close();
        QThread::sleep(5);
    }

    Load.load(false);
    Load.preset(false);
    Load.closePort();

    printf("Finished\n");

    return a.exec();
}
