#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QSound>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QFile>
#include <objectmanager.h>
#include <baseobject.h>
#include <carobject.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void ClassicMode();
    void StartClassicMode();
    void TripMode();
    void StartTripMode();
    void DrawRoad(QPainter *p);
    void GameOver();
    void PlayMusic();

public slots:
    void update_timer();
    void start_timer();
    void stop_timer();
    void restart();
    void clearScreen();
    void leaderBoard();
    void enableOrDisableSound();

private:
    Ui::MainWindow *ui;
    QTimer *updateTimer;
    ObjectManager ObjManager;
    CarObject A;
    QMediaPlayer *Music;

    int CellWidth;
    int CellHeight;
    int FrameCenterX;
    int FrameCenterY;
    int Y0;
    int Score;
    int Counter, MusicCounter;
    float Speed;
    bool DrawFlag, CrashFlag, SoundFlag, FirstDrawFlag;
    int GameMode;
    float RoadX, RoadY;

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent * event);

};

#endif // MAINWINDOW_H
