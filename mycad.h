#pragma once

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include "ui_mycad.h"
#include "main_canvas.h"

class mycad : public QMainWindow
{
    Q_OBJECT

public:
    mycad(QWidget *parent = Q_NULLPTR);

private:
    Ui::mycadClass ui;
    MainCanvas* main_canvas; 

public slots:

};
