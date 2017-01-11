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
};

#endif // CONTROLWINDOW_H
