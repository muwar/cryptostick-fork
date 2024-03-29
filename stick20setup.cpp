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

#include <QMessageBox>
#include "stick20setup.h"
#include "ui_stick20setup.h"

#include "device.h"
#include "stick20matrixpassworddialog.h"
#include "stick20changepassworddialog.h"
#include "stick20responsedialog.h"

/*******************************************************************************

 Local defines

*******************************************************************************/

/*******************************************************************************

 External declarations

*******************************************************************************/


/*******************************************************************************

  Stick20Setup

  Constructor Stick20Setup

  Reviews
  Date      Reviewer        Info
  12.08.13  RB              First review

*******************************************************************************/

Stick20Setup::Stick20Setup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stick20Setup)
{
    ui->setupUi(this);
}

/*******************************************************************************

  Stick20Setup

  Destructor Stick20Setup

  Reviews
  Date      Reviewer        Info
  12.08.13  RB              First review

*******************************************************************************/

Stick20Setup::~Stick20Setup()
{
    delete ui;
}

/*******************************************************************************

  on_pushButton_Change_AdminPW_clicked

  Reviews
  Date      Reviewer        Info
  12.08.13  RB              First review

*******************************************************************************/

void Stick20Setup::on_pushButton_Change_AdminPW_clicked()
{
    DialogChangePassword dialog(this);

    dialog.setModal (TRUE);

    dialog.cryptostick        = cryptostick;

    dialog.PasswordKind       = STICK20_PASSWORD_KIND_ADMIN;

    dialog.InitData ();
    dialog.exec();
}
/*******************************************************************************

  on_pushButton_Ch_Mat_APW_clicked

  Reviews
  Date      Reviewer        Info
  12.08.13  RB              First review

*******************************************************************************/

void Stick20Setup::on_pushButton_Ch_Mat_APW_clicked()
{
    QMessageBox          msgBox;
    MatrixPasswordDialog dialog(this);


    msgBox.setText("The selected lines must be greater then greatest password length");
    msgBox.exec();

    dialog.setModal (TRUE);

    dialog.cryptostick        = cryptostick;
    dialog.SetupInterfaceFlag = TRUE;

    dialog.InitSecurePasswordDialog ();

    dialog.exec();
}
/*******************************************************************************

  on_pushButton_Ch_PW_clicked

  Reviews
  Date      Reviewer        Info
  12.08.13  RB              First review

*******************************************************************************/

void Stick20Setup::on_pushButton_Ch_PW_clicked()
{
    DialogChangePassword dialog(this);

    dialog.setModal (TRUE);

    dialog.cryptostick        = cryptostick;

    dialog.PasswordKind       = STICK20_PASSWORD_KIND_USER;

    dialog.InitData ();
    dialog.exec();
}

/*******************************************************************************

  on_pushButton_Ch_HiddenVol_clicked

  Reviews
  Date      Reviewer        Info
  12.08.13  RB              First review

*******************************************************************************/

void Stick20Setup::on_pushButton_Ch_HiddenVol_clicked()
{
    int        ret;
    QMessageBox msgBox;

    msgBox.setText("Build a new base key for the hidden volume, all data get lost");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setEscapeButton(QMessageBox::No);

    ret = msgBox.exec();
    if (QMessageBox::Yes == ret)
    {
        ret = cryptostick->stick20SetupHiddenVolume ();

        if (TRUE == ret)
        {
/*
            Stick20ResponseDialog ResponseDialog(this);

            ResponseDialog.cryptostick=cryptostick;

            ResponseDialog.NoStopWhenStatusOK ();

            ResponseDialog.exec();
*/
            Stick20ResponseTask ResponseTask(this,cryptostick,NULL);
            ResponseTask.NoStopWhenStatusOK ();
            ResponseTask.GetResponse ();


        }
    }
}






