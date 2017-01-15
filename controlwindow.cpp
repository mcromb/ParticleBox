/*  Name: Marion Cromb
    Project: 2D balls in a box
    Date Due: 20/01/17
    Summary: Implementation of user controls of the GUI
*/

#include "controlwindow.h"
#include "ui_controlwindow.h"

#include <QTimer>

#include "DisplayWindow.h"

#include "gravity.h"
#include "collision.h"

#include <string>

ControlWindow::ControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlWindow)
{  
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

/* ***METHOD***
    Name:  CreateSystem
    About: Creates a particle system to simulate
     There will always be one particle system existing for the lifetime
     of the program run once Run is clicked for the first time.
*/
void ControlWindow::CreateSystem() {
    ParticleSystem *system = new ParticleSystem();
    fSystem = system;
}

/* ***METHOD***
    Name:  Update
    About: If the simulation is running, updates the particle system
*/
void ControlWindow::Update() {
    if(fStatus == kRun)
        fSystem->Update();
}

/* ***METHOD***
    Name:  Fuel
    About: If the simulation is running and being fuelled, adds particles to the system (up to a relevant limit)
     This method is triggered every time the fueltimer pops.
*/
void ControlWindow::Fuel() {
    if((fStatus == kRun) && (fFuelStatus == kFuelling))
    {
        if (fMode == kWaterfall) {
            //want lots of particles added to system (no limit) to replenish those falling off the screen.
            //all added from same point
            fSystem->AddParticles(3, Vector2(0,6), 0.1);
        } else {
            //For non-waterfall mode, collisions can be turned on
            //collisions make the simulation lag if checking over lots of particles
            //so prevent further fuelling if system particles are over a certain limit
            if (fSystem->GetNParticles() < fSystem->GetMaxColliding()){
                //Add particles from centre:
                //fSystem->AddParticles(1, Vector2(0,0), ((double)fFuelSize)/10.0);
                //add particles anywhere in box
                fSystem->AddParticles(1, Vector2(10*((randomFloat()*2)-1),10*((randomFloat()*2)-1)), ((double)fFuelSize)/10.0);
            }
        }
    }
}

/* ***METHOD***
    Name:  on_runButton_clicked
    About: Toggles the run state of the simulation
*/
void ControlWindow::on_runButton_clicked()
{
    if (fStatus == kIdle) {
        ui->runButton->setStyleSheet("background-color:green"); //toggle
        ui->runButton->setText("Stop"); //toggle
        if (fSystem == NULL) CreateSystem();
        if ( fWin == NULL ) {
            fWin = new DisplayWindow((ParticleSystem*)fSystem);
        } else {
            if ( !fWin->isVisible() )
            {
                //Window has been closed by the user- can either re show and continue
                //fWin->show();
                //or restart program:
                fWin->close();
                delete fSystem;
                CreateSystem();
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

/* ***METHOD***
    Name:  on_WallsCB_stateChanged
    About: Toggles the solidity of the walls
*/
void ControlWindow::on_WallsCB_stateChanged(int state)
{
    if (state == Qt::Checked) {
        //Solid walls
        fSystem->SetWallStatus(0);
    } else {
        //permeable walls
        fSystem->SetWallStatus(1);
    }
}

/* ***METHOD***
    Name:  on_GravityCB_stateChanged
    About: Toggles the gravity of the situation
*/
void ControlWindow::on_GravityCB_stateChanged(int state)
{
    if (state == Qt::Checked){
        //turn gravity on
        Gravity *grav = new Gravity();
        fSystem->AddForce(grav);
        if (fGravSliderStored != -1){
            //if the value has been changed from default
            grav->SetGravity((double)fGravSliderStored);
        }
    }else {
        //remove gravity
        fSystem->RemoveForce("Gravity");
    }
}

/* ***METHOD***
    Name:  on_FuelCB_stateChanged
    About: Toggles the fuelling of the system
*/
void ControlWindow::on_FuelCB_stateChanged(int state)
{
    if (state == Qt::Checked){
        fFuelStatus = kFuelling;
    }else{
        fFuelStatus = kSteady;
    }
}

/* ***METHOD***
    Name:  on_CollisionsCB_stateChange
    About: Toggles the fuelling of the system
*/
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

void ControlWindow::on_fuelSlider_valueChanged(int value)
{
    fFuelSize = value;
}

void ControlWindow::on_waterfallMode_toggled(bool checked)
{
    if (checked == true){
        //Start Waterfall Mode
        fMode = kWaterfall;
        if (!(ui->FuelCB->isChecked())){
            ui->FuelCB->setChecked(Qt::Checked);
        }
        if (ui->CollisionsCB->isChecked()){
            ui->CollisionsCB->setChecked(Qt::Unchecked);
        }
        if (!(ui->GravityCB->isChecked())){
            ui->GravityCB->setChecked(Qt::Checked);
        }
        if (ui->WallsCB->isChecked()){
            ui->WallsCB->setChecked(Qt::Unchecked);
        }
    } else{
        fMode = kBox;
        if (ui->FuelCB->isChecked()){
            ui->FuelCB->setChecked(Qt::Unchecked);
        }
    }
}

void ControlWindow::on_ClearB_clicked()
{
    fSystem->ClearParticles();
}
