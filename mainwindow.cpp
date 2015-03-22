#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "objectmanager.h"
#include "baseobject.h"
#include "carobject.h"
#include "barrierobject.h"

#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    Score(0),
    Counter(0),
    //GameMode(0),
    Speed(15),
    CrashFlag(0)
{
    ui->setupUi(this);
    //setFocusPolicy(Qt::StrongFocus);
    ui->frame->setFocusPolicy(Qt::StrongFocus);

    ui->PauseMenu->setVisible(0);
    ui->gameOverWidget->setVisible(0);
    ui->menuWidget->setVisible(0);

    DrawFlag = 0;
    CellWidth = (ui->frame->width() - 40) / 3;
    CellHeight = ui->frame->height() / 5;
    FrameCenterX = ui->frame->x() + ui->frame->width() / 2 + 20;
    FrameCenterY = ui->frame->y() + ui->frame->height() / 2 + 20;
    Y0 = ui->frame->y();

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update_timer()));

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(start_timer()));
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(stop_timer()));
    connect(ui->continueButton, SIGNAL(clicked()), this, SLOT(start_timer()));
    connect(ui->startClassicButton, SIGNAL(clicked()), this, SLOT(start_timer()));
    connect(ui->restartButton, SIGNAL(clicked()), this, SLOT(restart()));
    connect(ui->restartButton, SIGNAL(clicked()), this, SLOT(start_timer()));
    connect(ui->restartButton, SIGNAL(clicked()), ui->gameOverWidget, SLOT(hide()));
    connect(ui->startTripButton, SIGNAL(clicked()), this, SLOT(start_timer()));
    connect(ui->exitToMenuButton, SIGNAL(clicked()), this, SLOT(stop_timer()));
    connect(ui->exitToMenuButton, SIGNAL(clicked()), this, SLOT(clearScreen()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    DrawRoad(&painter);
    if (DrawFlag != 0)
    {
        A.Draw(&painter);
        for(auto it = ObjManager.GetObjects()->begin(); it != ObjManager.GetObjects()->end(); ++it)
        {
            (*it)->Draw(&painter);
        }
    }
    if (CrashFlag)
    {
        QPixmap pixmap;
        if ( pixmap.load("/home/dima/Projects/F1_Race/005.png") )
            painter.drawPixmap( A.GetX() - pixmap.width() / 2, A.GetY(), pixmap);
    }
}

void MainWindow::keyPressEvent (QKeyEvent * event )
{
    if (!CrashFlag)
    {
        if (GameMode == 1)
        {
            if (event->type() == QEvent::KeyPress)
            {
                if (event->key() == Qt::Key_Left)
                {
                    if (A.GetX() >= ui->frame->x() + CellWidth)
                        A.SetX(A.GetX() - CellWidth);
                };
                if (event->key() == Qt::Key_Right)
                {
                    if (A.GetX() <= ui->frame->width() - CellWidth)
                        A.SetX(A.GetX() + CellWidth);
                };
                if (event->key() == Qt::Key_Escape)
                {
                    MainWindow::stop_timer();
                    ui->PauseMenu->setVisible(1);
                }
            }
        } else if (GameMode == 2)
        {
            if (event->key() == Qt::Key_Left)
            {
                if (A.GetX() >= ui->frame->x())
                    A.SetX(A.GetX() - A.GetAccuracy());
            };
            if (event->key() == Qt::Key_Right)
            {
                if (A.GetX() <= ui->frame->width())
                    A.SetX(A.GetX() + A.GetAccuracy());
            };
            if (event->key() == Qt::Key_Up)
            {
                if (A.GetY() >= ui->frame->y())
                    A.SetY(A.GetY() - A.GetAccelerator());
            };
            if (event->key() == Qt::Key_Down)
            {
                if (A.GetY() <= ui->frame->height())
                    A.SetY(A.GetY() + A.GetBrake());
            };
        }
    }
    MainWindow::update();
}

void MainWindow::update_timer()
{
    DrawFlag = 1;
    if (GameMode == 1) ClassicMode();
    else if (GameMode == 2) TripMode();
    MainWindow::update();
}

void MainWindow::start_timer()
{
    if (QObject::sender() == ui->startClassicButton)
    {
        GameMode = 1;
        StartClassicMode();
    }
    else if (QObject::sender() == ui->startTripButton)
    {
        GameMode = 2;
        StartTripMode();
    }
    updateTimer->start(100);
}

void MainWindow::stop_timer()
{
    updateTimer->stop();
    update();
}

void MainWindow::StartClassicMode()
{
    A.SetX((ui->frame->width() + ui->frame->x()) / 2);
    A.SetY((ui->frame->height() + ui->frame->y()) - CellHeight);

    BaseObject *B = new BarrierObject(FrameCenterX, Y0, Speed);

    ObjManager.AddObject(B);
    CrashFlag = 0;
}

void MainWindow::StartTripMode()
{
    A.SetX((ui->frame->width() + ui->frame->x()) / 2);
    A.SetY((ui->frame->height() + ui->frame->y()) - CellHeight);
    CrashFlag = 0;
}

void MainWindow::restart()
{
    auto it = ObjManager.GetObjects()->begin();
    while( it != ObjManager.GetObjects()->end() )
    {
            delete *it;
            it = ObjManager.GetObjects()->erase(it);
            qDebug() << "Delete!!!";
            continue;
        ++it;
    }
    StartClassicMode();
}

void MainWindow::ClassicMode()
{
    int randNum = 0;
    auto it_end = ObjManager.GetObjects()->end() - 1;
    if ((*it_end)->GetY() >= ui->frame->y() + CellHeight*1.5)
    {
        randNum = qrand() % 6;

        switch ( randNum ) {
        case 0:
        {
            BaseObject *B = new BarrierObject(FrameCenterX, Y0, Speed);
            ObjManager.AddObject(B);
            qDebug() << "0";
            break;
        }
        case 1:
        {
            BaseObject *B = new BarrierObject(FrameCenterX - CellWidth, Y0, Speed);
            ObjManager.AddObject(B);
            BaseObject *B1 = new BarrierObject(FrameCenterX + CellWidth, Y0, Speed);
            ObjManager.AddObject(B1);
            qDebug() << "1";
            break;
        }
        case 2:
        {
            BaseObject *B = new BarrierObject(FrameCenterX - CellWidth, Y0, Speed);
            ObjManager.AddObject(B);
            qDebug() << "2";
            break;
        }
        case 3:
        {
            BaseObject *B = new BarrierObject(FrameCenterX + CellWidth, Y0, Speed);
            ObjManager.AddObject(B);
            qDebug() << "3";
            break;
        }
        case 4:
        {
            BaseObject *B = new BarrierObject(FrameCenterX - CellWidth, Y0, Speed);
            ObjManager.AddObject(B);
            BaseObject *B1 = new BarrierObject(FrameCenterX, Y0, Speed);
            ObjManager.AddObject(B1);
            qDebug() << "4";
            break;
        }
        case 5:
        {
            BaseObject *B = new BarrierObject(FrameCenterX, Y0, Speed);
            ObjManager.AddObject(B);
            BaseObject *B1 = new BarrierObject(FrameCenterX + CellWidth, Y0, Speed);
            ObjManager.AddObject(B1);
            qDebug() << "5";
            break;
        }
        default:
        {
            break;
        }
        }
    }

    auto it = ObjManager.GetObjects()->begin();
    while( it != ObjManager.GetObjects()->end() )
    {
        (*it)->SetY((*it)->GetY() + (*it)->GetSpeed());
        if ((*it)->GetY() >= ui->frame->height())
        {
            delete *it;
            it = ObjManager.GetObjects()->erase(it);
            qDebug() << "Delete!!!";
            Score++;
            continue;
        }

        if (A.GetX() >= ((*it)->GetX() - CellWidth / 2) && A.GetX() <= ((*it)->GetX() + CellWidth / 2)
                && A.GetY() <= (*it)->GetY() && A.GetY() + 40 >= (*it)->GetY())
        {
            MainWindow::stop_timer();
            ui->gameOverWidget->setVisible(1);
            ui->scoreOverLabel->setText(QString::number(Score));
            CrashFlag = 1;
        }
        ++it;
    }

    Counter++;
    if (Speed < 25 && Counter == 50)
    {
        for(auto it = ObjManager.GetObjects()->begin(); it != ObjManager.GetObjects()->end(); ++it)
        {
            (*it)->SetSpeed(Speed);
            qDebug() << (*it)->GetSpeed();
        }
        if (Speed < 40) Speed++;
        Counter = 0;
    } else if (Speed < 35 && Counter == 100)
    {
        for(auto it = ObjManager.GetObjects()->begin(); it != ObjManager.GetObjects()->end(); ++it)
        {
            (*it)->SetSpeed(Speed);
            qDebug() << (*it)->GetSpeed();
        }
        if (Speed < 40) Speed++;
        Counter = 0;
    } else if(Speed < 40 && Counter == 100)
    {
        for(auto it = ObjManager.GetObjects()->begin(); it != ObjManager.GetObjects()->end(); ++it)
        {
            (*it)->SetSpeed(Speed);
            qDebug() << (*it)->GetSpeed();
        }
        if (Speed < 40) Speed++;
        Counter = 0;
    }
    ui->ScoreLabel->setText(QString::number(Score));
    if (Speed != 40) ui->SpeedLabel->setText(QString::number(Speed - 14));
    else ui->SpeedLabel->setText("Maximum!");
}

void MainWindow::TripMode()
{

}

void MainWindow::DrawRoad(QPainter *p)
{
    QPixmap pixmap;
    if ( pixmap.load("/home/dima/Projects/F1_Race/002_2.png") )
        p->drawPixmap( ui->frame->x(), ui->frame->y(), pixmap);
}

void MainWindow::clearScreen()
{
    GameMode = 0;
    DrawFlag = 0;
    auto it = ObjManager.GetObjects()->begin();
    while( it != ObjManager.GetObjects()->end() )
    {
            delete *it;
            it = ObjManager.GetObjects()->erase(it);
            qDebug() << "Delete!!!";
            continue;
        ++it;
    }
    update();
}
