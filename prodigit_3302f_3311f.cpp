#include "prodigit_3302f_3311f.h"

void PRODIGIT_3302F_3311F::openPort(char* portname)
{
    serial.setPortName(portname);
    if(!serial.open(QIODevice::ReadWrite))
        cout<< "failed" << endl;
    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::HardwareControl);
   // serial.clear();
}

void PRODIGIT_3302F_3311F::reset()
{
        int w = serial.write("*RST\n\r");
        //serial.waitForBytesWritten(100);
        //serial.flush();
        cout << "Loader restart" << endl;
        if(w < 0)
        {
            cout << "Failed to restart Loader, " << "Error code: " << errno << ", " << strerror(errno) << endl;
            return;
        }
        sleep(5);
}

void PRODIGIT_3302F_3311F::load(bool switch1)
{
    if(switch1 == true)
    {
        int w = serial.write("LOAD ON\n\r");
        serial.waitForBytesWritten(100);
        //serial.flush();
        cout << "Turning on the LOAD" << endl;
        if(w < 0)
        {
            cout << "Failed to turn on the LOAD, " << "Error code: " << errno << ", " << strerror(errno) << endl;
            return;
        }
    }

    else
    {
        int w = serial.write("LOAD OFF\n\r");
        serial.waitForBytesWritten(100);
        //serial.flush();
        cout << "Turning off the LOAD" << endl;
        if(w < 0)
        {
            cout << "Failed to turn off the LOAD, " << "Error code: " << errno << ", " << strerror(errno) << endl;
            return;
        }
    }
}

void PRODIGIT_3302F_3311F::preset(bool switch2)
{
    if(switch2 == true)
    {
        int w = serial.write("PRESet ON\n\r");
        serial.waitForBytesWritten(100);
        //serial.flush();
        cout << "Turning on the Preset" << endl;
        if(w < 0)
        {
            cout << "Failed to turn on the Preset, " << "Error code: " << errno << ", " << strerror(errno) << endl;
            return;
        }
    }

    else
    {
        int w = serial.write("PRESet OFF\n\r");
        serial.waitForBytesWritten(100);
       //serial.flush();
        cout << "Turning off the Preset" << endl;
        if(w < 0)
        {
            cout << "Failed to turn off the Preset, " << "Error code: " << errno << ", " << strerror(errno) << endl;
            return;
        }
    }
}

void PRODIGIT_3302F_3311F::SetCURR(float CURR)
{
    char buf3 [256];
    sprintf(buf3, "CURR:HIGH %f\n\r", CURR);
    int w = serial.write(buf3);
    serial.waitForBytesWritten(100);
    //serial.flush();
    //cout << "No." << c << " The current is: "<< CURR << endl;
    if(w < 0)
        {
            cout << "Failed to set the current, " << "Error code: " << errno << ", " << strerror(errno) << endl;
            return;
        }
}

float PRODIGIT_3302F_3311F::GetCURR()
{
    int w = serial.write("GLOB:MEAS:CURR?\n\r");
    serial.waitForBytesWritten(1000);
    sleep(1);
    //serial.flush();
    if(w < 0){
        cout << "Failed to get the current, " << "Error code: " << errno << ", " << strerror(errno) << endl;
        return -1;
    }

    if(serial.bytesAvailable()>0 || serial.waitForReadyRead(1000)){
        char temp1[10];
        QByteArray getData1 = serial.readAll();
        for(int i=0; i<10; i++){
            temp1[i] = (char)getData1[i];
        }
        return float(atof(temp1));
    }
    else
        cout<<"No Data\n";
}

float PRODIGIT_3302F_3311F::GetVOLT()
{
    int w = serial.write("GLOB:MEAS:VOLT?\n\r");
    serial.waitForBytesWritten(1000);
    //serial.flush();
    sleep(1);
    if(w < 0)
        {
            cout << "Failed to get the voltage, " << "Error code: " << errno << ", " << strerror(errno) << endl;
            return -1;
        }

        if(serial.bytesAvailable()>0 || serial.waitForReadyRead(1000))
        {
            char temp2[10];
            QByteArray getData2 = serial.readAll();
            //QByteArray getData = serial.readLine();
            //serial.write(getData2);
            for(int i=0; i<10; i++)
            {
                temp2[i] = (char)getData2[i];
            }

            return float(atof(temp2));
            //printf("%4.8f\n" ,atof(c));
            //flush(cout);
        }
}

void PRODIGIT_3302F_3311F::closePort()
{

        serial.close();
        cout << "Closing the port... ";
        if(serial.NotOpen != 0)
        {
            cout << "Failed, " << "Error code: " << errno << ",  " << strerror(errno) << endl;
            return;
        }
        else
            cout << "Done" << endl << "Bye Bye" << endl;
}
