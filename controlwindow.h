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

    void on_checkBox_stateChanged(int arg1);

    void on_GravityCB_stateChanged(int arg1);

    void on_FuelCB_stateChanged(int arg1);

    void on_CollisionsCB_stateChanged(int arg1);

    void on_gravSlider_valueChanged(int value);

    void on_fuelSlider_valueChanged(int value);

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
};

#endif // CONTROLWINDOW_H
