#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->stackedWidget = ui->stackedWidget;

    //Slot/signal connections initialization here: - between menu signal emissions and slots for here and the data manager


    //------------------------
    this->dataManager = new DataManager();
    if (this->dataManager->retrieveSaveData()){
        if (this->dataManager->hasValidPlan()) this->stackedWidget->setCurrentIndex(2); // puts on plan page
        else this->stackedWidget->setCurrentIndex(1); // puts on generate plan page
    }else this->stackedWidget->setCurrentIndex(0); // puts it on the enter api page
}

MainWindow::~MainWindow()
{
    delete ui;
}
