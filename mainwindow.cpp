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
    Speed(2),
    CrashFlag(0),
    SoundFlag(1)
{
    ui->setupUi(this);
    ui->frame->setFocusPolicy(Qt::StrongFocus);
    setWindowIcon(QIcon(":/Images/icon.png"));
    FirstDrawFlag = 1;

    Music = new QMediaPlayer(this);
    PlayMusic();

    QIcon icon;
    icon.addFile(":/Images/EnabledSound.jpg");
    ui->soundButton->setIcon(icon);
    ui->soundButton->setFocusPolicy(Qt::NoFocus);
    ui->leaderBoardButton->setFocusPolicy(Qt::NoFocus);
    ui->PauseMenu->setVisible(0);
    ui->gameOverWidget->setVisible(0);
    ui->menuWidget->setVisible(0);
    ui->leadersWidget->setVisible(0);

    RoadX = ui->frame->x();
    RoadY = ui->frame->y() - ui->frame->height()/2 + 40;

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
    connect(ui->leaderBoardButton, SIGNAL(clicked()), this, SLOT(leaderBoard()));
    connect(ui->soundButton, SIGNAL(clicked()), this, SLOT(enableOrDisableSound()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (FirstDrawFlag)
    {
        QPixmap pixmap;
        if ( pixmap.load(":/Images/RaceBackground.png") )
            painter.drawPixmap(ui->centralWidget->x(), ui->centralWidget->y(), pixmap);
    }
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
        if ( pixmap.load(":/Images/Crash.png") )
            painter.drawPixmap( A.GetX() - pixmap.width() / 2 + 4, A.GetY(), pixmap);
    }
}

void MainWindow::PlayMusic()
{
    if (SoundFlag)
    {
        Music->setVolume(50);
        Music->setMedia(QUrl::fromLocalFile("/home/dima/Projects/F1_Race/GameTheme.mp3"));
        Music->play();
    } else
    {
        Music->stop();
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
                if (A.GetX() - A.GetWidth() >= ui->frame->x())
                    A.SetX(A.GetX() - A.GetAccuracy());
            };
            if (event->key() == Qt::Key_Right)
            {
                if (A.GetX() + A.GetWidth() <= ui->frame->width())
                    A.SetX(A.GetX() + A.GetAccuracy());
            };
            if (event->key() == Qt::Key_Up)
            {
                if (A.GetY() >= ui->frame->y())
                    A.SetY(A.GetY() - A.GetAccelerator());
            };
            if (event->key() == Qt::Key_Down)
            {
                if (A.GetY() + A.GetHeight() <= ui->frame->height())
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
    ui->leaderBoardButton->setEnabled(false);
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
    updateTimer->start(10);
}

void MainWindow::stop_timer()
{
    ui->leaderBoardButton->setEnabled(true);
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
    Score = 0;
    Speed = 2;
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

//    if (RoadY <= ui->frame->y() - 20)
//    {
        RoadY += (*it)->GetSpeed();
//    } else
//        RoadY = ui->frame->y() - ui->frame->height()/2 + 40;

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
                && A.GetY() <= (*it)->GetY() && A.GetY() + 60 >= (*it)->GetY())
        {
            GameOver();
        }
        ++it;
    }

    Counter++;
    if (Speed < 5 && Counter == 100)
    {
        if (Speed < 11) Speed += 0.1;
        for(auto it = ObjManager.GetObjects()->begin(); it != ObjManager.GetObjects()->end(); ++it)
        {
            (*it)->SetSpeed(Speed);
            qDebug() << (*it)->GetSpeed();
        }
        Counter = 0;
    } else if (Speed < 8 && Counter == 400)
    {
        if (Speed < 11) Speed += 0.1;
        for(auto it = ObjManager.GetObjects()->begin(); it != ObjManager.GetObjects()->end(); ++it)
        {
            (*it)->SetSpeed(Speed);
            qDebug() << (*it)->GetSpeed();
        }
        Counter = 0;
    } else if(Speed < 11 && Counter == 800)
    {
        if (Speed < 11) Speed += 0.1;
        for(auto it = ObjManager.GetObjects()->begin(); it != ObjManager.GetObjects()->end(); ++it)
        {
            (*it)->SetSpeed(Speed);
            qDebug() << (*it)->GetSpeed();
        }
        Counter = 0;
    }
    ui->ScoreLabel->setText(QString::number(Score));
    if (Speed != 11) ui->SpeedLabel->setText(QString::number(Speed));
    else ui->SpeedLabel->setText("Maximum!");

    if (MusicCounter <= 1541)
    {
        MusicCounter++;
    } else
    {
        Music->stop();
        PlayMusic();
        MusicCounter = 0;
    }
}


void MainWindow::GameOver()
{

    MainWindow::stop_timer();
    ui->gameOverWidget->setVisible(1);
    ui->scoreOverLabel->setText(QString::number(Score));
    if (SoundFlag)
    {
        //            QSound *CrashSound = new QSound(":/Sounds/Test.wav");
        //            CrashSound->play();
        QMediaPlayer *player = new QMediaPlayer(this);
        player->setVolume(50);
        player->setMedia(QUrl::fromLocalFile("/home/dima/Projects/F1_Race/Crash.mp3"));
        player->play();
    }
    QFile file("./LeaderBoard.txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << "Player:   " <<Score;
    out << "\n";
    file.close();
    CrashFlag = 1;

}

void MainWindow::TripMode()
{

}

void MainWindow::DrawRoad(QPainter *p)
{
    QPixmap pixmap1;
    if ( pixmap1.load(":/Images/Road.png") )
    {
        float RoadX1 = RoadX, RoadY1 = RoadY;
        float RoadX2 = RoadX, RoadY2 = RoadY - pixmap1.height();
        if (RoadY2 + pixmap1.height() >= ui->frame->height())
        {
            RoadY1 = RoadY2 - pixmap1.height();
            RoadY = RoadY2;
        }
        if (RoadY1 + pixmap1.height() >= ui->frame->height())
        {
            RoadY2 = RoadY1 - pixmap1.height();
            RoadY = RoadY1;
        }
        p->drawPixmap(RoadX1, RoadY1, pixmap1);
        p->drawPixmap(RoadX2, RoadY2, pixmap1);
    }
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

void MainWindow::leaderBoard()
{
    QFile file("./LeaderBoard.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        file.open(QIODevice::Append | QIODevice::Text);
        QTextStream out(&file);
        out << "Player:   " <<Score;
        out << "\n";
        file.close();
    }
    QTextStream text(&file);
    QString strText = text.readAll();
    ui->textBrowser->clear();
    ui->textBrowser->setAlignment(Qt::AlignCenter);

    ui->textBrowser->append(strText);
    file.close();
    ui->leadersWidget->show();
}

void MainWindow::enableOrDisableSound()
{
    QIcon icon;
    if (SoundFlag)
    {
        SoundFlag = 0;
        icon.addFile(":/Images/DisabledSound.jpg");
        ui->soundButton->setIcon(icon);
    } else
    {
        SoundFlag = 1;
        icon.addFile(":/Images/EnabledSound.jpg");
        ui->soundButton->setIcon(icon);
    }
    PlayMusic();
}
