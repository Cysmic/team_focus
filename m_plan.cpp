#include "m_plan.h"
#include "ui_m_plan.h"

M_Plan::M_Plan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::M_Plan)
{
    ui->setupUi(this);
    //ui->PlanList->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
    ui->PlanList->setDragEnabled(true);
    ui->PlanList->setAcceptDrops(true);
    ui->PlanList->setDropIndicatorShown(true);
    ui->PlanList->setDefaultDropAction(Qt::MoveAction);
    ui->PlanList->setDragDropMode(QAbstractItemView::InternalMove);


    connect(ui->Submit, &QPushButton::clicked, this, &M_Plan::sendSaveDataSignal);
    connect(ui->View_Progress, &QPushButton::clicked, this, &M_Plan::ChangeMenuToProgress);
    connect(ui->Reset_Plan, &QPushButton::clicked, this, &M_Plan::resetPlan);

}

M_Plan::~M_Plan()
{
    delete ui;
}


void M_Plan::fillPlanList(std::vector<std::string> plan){
    ui->PlanList->clear();
    if (plan.size() < 1)
        emit this->ChangeMenu(Menu::PROGRESS_M);
    for (auto iter = plan.begin(); iter != plan.end(); iter++){
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(getTask(*iter)));
        item->setData(Qt::UserRole, QVariant((*iter).c_str()));
        // Set the item to be checkable
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        // Initialize the item as unchecked
        item->setData(Qt::CheckStateRole, Qt::Unchecked);
        ui->PlanList->addItem(item);
    }
}

void M_Plan::sendSaveDataSignal(){
    std::vector<std::string> checkedItems; // To store checked items

    for(int i = 0; i < ui->PlanList->count(); ++i) {
        QListWidgetItem* item = ui->PlanList->item(i);
        if(item->checkState() == Qt::Checked) {
            checkedItems.push_back(item->data(Qt::UserRole).toString().toStdString()); // should be plan string encoding
            std::cout << "text of completed task? is it complete?" << std::endl;
            std::cout << item->data(Qt::UserRole).toString().toStdString() << std::endl;
        }
    }
    emit this->saveDataSignal(checkedItems);
}

void M_Plan::ChangeMenuToProgress(){
    emit this->ChangeMenu(Menu::PROGRESS_M);
}

void M_Plan::resetPlan(){
    emit ResetPlan();
    emit ChangeMenu(Menu::PLANGENERATION_M);
}
