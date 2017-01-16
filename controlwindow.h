/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Control Window class header: The control window
     allows the user to change parameters of the simulation.
*/

#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>

#include "particlesystem.h"
#include "displaywindow.h"

namespace Ui {
class ControlWindow;
}

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = 0);
    ~ControlWindow();

    void CreateSystem();

private slots:

    void Update();

    void Fuel();

    //User interaction slots
    void on_runButton_clicked();

    void on_WallsCB_stateChanged(int state);

    void on_GravityCB_stateChanged(int state);

    void on_FuelCB_stateChanged(int state);

    void on_CollisionsCB_stateChanged(int state);

    void on_gravSlider_valueChanged(int value);

    void on_fuelSlider_valueChanged(int value);

    void on_waterfallMode_toggled(bool checked);

    void on_ClearB_clicked();

    void on_dampingSlider_valueChanged(int value);

private:
    Ui::ControlWindow *ui;    
    DisplayWindow* fWin;
    ParticleSystem* fSystem;

    enum{
        kIdle,
        kRun
    };
    int fStatus = kIdle;
    //initialised to Idle state

    enum{
        kFuelling,
        kSteady
    };
    int fFuelStatus = kSteady;
    int fFuelSize = 1;
    //Initialised to non-fuelling state
    //so user can set inital conditions

    int fGravSliderStored = -1;
    //initialised to a value the slider cannot take
    //to check whether the slider has moved from default

    enum{
        kWaterfall,
        kBox
    };
    int fMode = kBox;
};

#endif // CONTROLWINDOW_H
