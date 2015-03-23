#include "carobject.h"
#include <QLabel>
#include <QDebug>

CarObject::CarObject()
{

}

CarObject::~CarObject()
{

}

void CarObject::Draw(QPainter * p)
{
    //MainWindow::DrawRoad(&painter);
    QPixmap pixmap;
    if ( pixmap.load(":/Images/Car.png") )
        p->drawPixmap( X - pixmap.width() / 2, Y, pixmap);
    width = pixmap.width();
    height = pixmap.height();
}

int CarObject::GetAccuracy()
{
    return accuracy;
}

void CarObject::SetAccuracy(int a)
{
    accuracy = a;
}

int CarObject::GetAccelerator()
{
    return accelerator;
}

void CarObject::SetAccelerator(int a)
{
    accelerator = a;
}

int CarObject::GetBrake()
{
    return brake;
}

void CarObject::SetBrake(int b)
{
    brake = b;
}

void CarObject::SetWidth(int w)
{
    width = w;
}

int CarObject::GetWidth()
{
   return width;
}

void CarObject::SetHeight(int h)
{
    height = h;
}

int CarObject::GetHeight()
{
   return height;
}
