#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

public slots:
    void update_timer();
    void start_timer();
    void stop_timer();
    void restart();
    void clearScreen();

private:
    Ui::MainWindow *ui;
    QTimer *updateTimer;
    ObjectManager ObjManager;
    CarObject A;

    int CellWidth;
    int CellHeight;
    int FrameCenterX;
    int FrameCenterY;
    int Y0;
    int Score;
    int Counter;
    int Speed;
    bool DrawFlag;
    bool CrashFlag;
    int GameMode;

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent * event);
};

#endif // MAINWINDOW_H
