/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Control Window class header: Allows user to change parameters of the simulation.
*/

#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>

#include <particlesystem.h>
#include <displaywindow.h>

namespace Ui {
class ControlWindow;
}

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = 0);
    ~ControlWindow();

    void createSystem();

private slots:

    void Update();
    void Fuel();

    void on_runButton_clicked();

    //Change the permeability of the walls
    void on_WallsCB_stateChanged(int arg1);

    void on_GravityCB_stateChanged(int arg1);

    void on_FuelCB_stateChanged(int arg1);

    void on_CollisionsCB_stateChanged(int arg1);

    void on_gravSlider_valueChanged(int value);

    void on_fuelSlider_valueChanged(int value);

    void on_waterfallMode_toggled(bool checked);

    void on_ClearB_clicked();

private:
    Ui::ControlWindow *ui;
    ParticleSystem* fSystem;
    DisplayWindow* fWin;

    enum{
        kIdle,
        kRun
    };
    int fStatus;

    enum{
        kFuelling,
        kSteady
    };
    int fFuelStatus;
    int fFuelSize = 1;

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
