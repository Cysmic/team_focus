#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->dataManager = new DataManager();

    //Slot/signal connections initialization here: - between menu signal emissions and slots for here and the data manager
    connect(ui->api_m, &M_API::sendKey_ID, this->dataManager, &DataManager::setAPI_Database);

    connect(this->dataManager, &DataManager::ChangeMenu, this, &MainWindow::ChangeMenu);
    connect(this->dataManager, &DataManager::tasksUpdated, ui->plangeneration_m, &M_PlanGeneration::createTagList);

    connect(ui->plangeneration_m, &M_PlanGeneration::ChangeMenu, this, &MainWindow::ChangeMenu);
    connect(ui->plangeneration_m, &M_PlanGeneration::sendPlanInfo, this->dataManager, &DataManager::receivePlanInfo);

    connect(ui->plan_m, &M_Plan::ChangeMenu, this, &MainWindow::ChangeMenu);
    connect(this->dataManager, &DataManager::planUpdated, ui->plan_m, &M_Plan::fillPlanList);
    connect(ui->plan_m, &M_Plan::saveDataSignal, this->dataManager, &DataManager::updateTasksInNotion);
    connect(ui->plan_m, &M_Plan::ResetPlan, this->dataManager, &DataManager::resetPlan);

    connect(ui->progress_m, &M_Progress::ChangeMenu, this, &MainWindow::ChangeMenu);
    connect(this->dataManager, &DataManager::historyUpdated, ui->progress_m, &M_Progress::HistoryUpdated);
    connect(this->dataManager, &DataManager::planUpdated, ui->progress_m, &M_Progress::setMaxPoints);
    //------------------------

    if (this->dataManager->retrieveSaveData()){
        if (this->dataManager->hasValidPlan()) ui->stackedWidget->setCurrentIndex(Menu::PLAN_M); // puts on plan page
        else ui->stackedWidget->setCurrentIndex(Menu::PLANGENERATION_M); // puts on generate plan page
    }else ui->stackedWidget->setCurrentIndex(Menu::API_M); // puts it on the enter api page
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ChangeMenu(Menu menu){
    ui->stackedWidget->setCurrentIndex(menu);
}
