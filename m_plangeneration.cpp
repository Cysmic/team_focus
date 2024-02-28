#include "m_plangeneration.h"
#include "ui_m_plangeneration.h"

M_PlanGeneration::M_PlanGeneration(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::M_PlanGeneration)
{
    ui->setupUi(this);
    ui->TagList->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
    ui->TagList->setSpacing(3);
    ui->TagList->viewport()->setContentsMargins(5, 5, 5, 5);

    connect(ui->GenerateSchedule, &QPushButton::clicked, this, &M_PlanGeneration::activateSendFunc);
    connect(ui->ViewProgress, &QPushButton::clicked, this, &M_PlanGeneration::changeToProgressMenu);

}

M_PlanGeneration::~M_PlanGeneration()
{
    delete ui;
}

void M_PlanGeneration::createTagList(std::vector<Task> tasks){
    std::unordered_map<std::string, std::vector<Task>> hashTask;

    for (auto task : tasks){
        hashTask[task.tag].push_back(task);

        switch (task.priority){
        case 1:
            hashTask["*"].push_back(task);
            break;
        case 2:
            hashTask["**"].push_back(task);
            break;
        case 3:
            hashTask["***"].push_back(task);
            break;
        }
    }

    for (auto iter = hashTask.begin(); iter != hashTask.end(); iter++){
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(iter->first));

        // generate a random color
        int red = QRandomGenerator::global()->bounded(200);
        int green = QRandomGenerator::global()->bounded(200);
        int blue = QRandomGenerator::global()->bounded(200);
        QColor randomColor(red, green, blue);

        item->setBackground(QBrush(randomColor));
        ui->TagList->addItem(item);
    }
}

void M_PlanGeneration::changeToProgressMenu(){
    emit this->ChangeMenu(Menu::PROGRESS_M);
}

void M_PlanGeneration::activateSendFunc(){
    QVector<QListWidgetItem*> items_selected = ui->TagList->selectedItems().toVector();
    std::vector<std::string> tags_selected;

    for (int i = 0; i < items_selected.size(); i++){
        tags_selected.push_back(items_selected[i]->text().toStdString());
    }

    int numTasks = 3;

    try {
        numTasks = std::atoi(ui->TaskNum_I->text().toStdString().c_str());
    } catch (std::exception exception){
        numTasks = 3;
    }

    emit this->sendPlanInfo(tags_selected, numTasks);
    emit this->ChangeMenu(Menu::PLAN_M);
}
