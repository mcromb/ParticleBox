#include "controlwindow.h"
#include "ui_controlwindow.h"

#include <QTimer>

#include "DisplayWindow.h"

#include <gravity.h>
#include <collision.h>

#include <string>

ControlWindow::ControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlWindow)
{
    fStatus = kIdle;
    fFuelStatus = kSteady;    
    fSystem = NULL;
    fWin = NULL;
    ui->setupUi(this);

    ui->runButton->setStyleSheet("background-color:red"); //toggle

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start(10);

    QTimer *fueltimer = new QTimer(this);
    connect(fueltimer, SIGNAL(timeout()), this, SLOT(Fuel()));
    fueltimer->start(10);
}

ControlWindow::~ControlWindow()
{
    delete ui;
}

void ControlWindow::Update() {
    if(fStatus == kRun)//If it's in Run state Update the particle system
        fSystem->Update();
}

void ControlWindow::on_runButton_clicked()
{
    if (fStatus == kIdle) {
        ui->runButton->setStyleSheet("background-color:green"); //toggle
        ui->runButton->setText("Stop"); //toggle
        if (fSystem == NULL) createSystem();
        if ( fWin == NULL ) {
            fWin = new DisplayWindow((ParticleSystem*)fSystem);
        } else {
            if ( !fWin->isVisible() )
            {
                //window has been closed - can either show and start where left
                //fWin->show();
                //or restart program
                fWin->close();
                delete fSystem;
                createSystem();
                fWin = new DisplayWindow((ParticleSystem*)fSystem);
            }
        }
        //Change the status
        fStatus = kRun;
    }else {
        ui->runButton->setStyleSheet("background-color:red"); //toggle
        ui->runButton->setText("Run"); //toggle
        //Change the status
        fStatus = kIdle;
    }
}

void ControlWindow::createSystem() {
    ParticleSystem *system = new ParticleSystem();
    fSystem = system;
}

void ControlWindow::Fuel() {
    if((fStatus == kRun) && (fFuelStatus == kFuelling))//If it's in Run state and user is fuelling,  fuel it
    {
        //up to a certain particle limit
        //if too high, collision algorithm far too slow
        if (fSystem->GetNParticles() < 500){
            fSystem->fuel(1, Vector2(0,0));
        }
    }
}

//Solid/walls
void ControlWindow::on_checkBox_stateChanged(int state)
{
    //way to do this with enum (public?)
    if (state == Qt::Checked) {
        //Solid walls
        fSystem->setWallStatus(0);
    } else {
        //permeable walls
        fSystem->setWallStatus(1);
    }
}

void ControlWindow::on_GravityCB_stateChanged(int state)
{
    if (state == Qt::Checked){
        //gravity
        Gravity *grav = new Gravity();
        fSystem->AddForce(grav);
        if (fGravSliderStored != -1){
            //the value has been changed from default
            grav->SetGravity((double)fGravSliderStored);
        }
    }else {
        //remove gravity
        fSystem->RemoveForce("Gravity");
    }
}

void ControlWindow::on_FuelCB_stateChanged(int state)
{
    if (state == Qt::Checked){
        fFuelStatus = kFuelling;
    }else{
        fFuelStatus = kSteady;
    }
}

void ControlWindow::on_CollisionsCB_stateChanged(int state)
{
    if (state == Qt::Checked){
        //collisions
        Collision *collision = new Collision();
        fSystem->AddForce(collision);        
    }else {
        //remove collisions
        fSystem->RemoveForce("Collision");
    }
}
// *** IS THIS A MEMORY LEAK? or fine cos deleted in remove force
//check if not already one?

void ControlWindow::on_gravSlider_valueChanged(int value)
{
    Gravity* force = (Gravity*)fSystem->FindForce("Gravity");
    if (force != NULL) {
        force->SetGravity((double)value);
    }else {
        fGravSliderStored = value;
    }
}
