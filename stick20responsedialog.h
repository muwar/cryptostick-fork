/*
* Author: Copyright (C) Rudolf Boeddeker  Date: 2013-08-13
*
* This file is part of GPF Crypto Stick 2
*
* GPF Crypto Stick 2  is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* GPF Crypto Stick is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with GPF Crypto Stick. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef STICK20RESPONSEDIALOG_H
#define STICK20RESPONSEDIALOG_H

#include <QDialog>
#include <QTimer>
#include "device.h"
#include "response.h"


#define STICK20_DEBUG_TEXT_LEN          600000

#ifdef __cplusplus
extern "C" {
#endif
    extern char DebugText_Stick20[STICK20_DEBUG_TEXT_LEN];
    extern unsigned long DebugTextlen_Stick20;
    extern int DebugingActive;
    extern int DebugingStick20PoolingActive;

    void DebugAppendText (char *Text);
#ifdef __cplusplus
} // extern "C"
#endif



class Stick20ResponseTask : public QObject
{
    Q_OBJECT

public:
    Stick20ResponseTask(QWidget *parent,Device *Cryptostick20,QSystemTrayIcon *MainWndTrayIcon);
    ~Stick20ResponseTask();
    void done (int Status);
    void checkStick20Status();
    void GetResponse (void);
    void NoStopWhenStatusOK ();
    void ShowIconMessage(QString IconText);

    QWidget         *Stick20ResponseTaskParent;

    Device          *cryptostick;
    QSystemTrayIcon *trayIcon;
    Response        *stick20Response;

    int  ActiveCommand;
    bool FlagNoStopWhenStatusOK;
    int  ResultValue;
    int  EndFlag;
    int  Counter_u32;
    int  retStick20Respone;
};



namespace Ui {
class Stick20ResponseDialog;
}

class Stick20ResponseDialog : public QDialog
{
    Q_OBJECT

    
public:
    Stick20ResponseTask *Stick20Task;

    explicit Stick20ResponseDialog(QWidget *parent = 0);
    ~Stick20ResponseDialog();

    void checkStick20StatusDebug(Response *stick20Response,int Status);
    void showStick20Configuration (int Status);

    QTimer *pollStick20Timer;

private:
    Ui::Stick20ResponseDialog *ui;
//    int  ActiveCommand;
//    int Counter_u32;
//    bool FlagNoStopWhenStatusOK;

private slots:
    void checkStick20StatusDialog();
    void on_pushButton_clicked();
};




#endif // STICK20RESPONSEDIALOG_H
