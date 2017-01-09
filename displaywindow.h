#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <QWidget>


#include "particlesystem.h"

namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWindow(ParticleSystem *, QWidget *parent = 0);
    ~DisplayWindow();

    ParticleSystem *GetParticleSystem() const { return fParticleSystem; }
    void SetParticleSystem(ParticleSystem *system) { fParticleSystem = system; }

private slots:
    void paintEvent(QPaintEvent *);

private:
    Ui::DisplayWindow *ui;

    ParticleSystem* fParticleSystem;
    //double fScale;
};

#endif // DISPLAYWINDOW_H
