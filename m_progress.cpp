#include "m_progress.h"
#include "ui_m_progress.h"

M_Progress::M_Progress(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::M_Progress)
{
    ui->setupUi(this);
    connect(ui->ViewSchedule, &QPushButton::clicked, this, &M_Progress::ChangeMenuToSchedule);

    ui->HistoryList->setSpacing(3);
    ui->HistoryList->viewport()->setContentsMargins(5, 5, 5, 5);

    ui->DailyProgress->setMaximum(1);
}

M_Progress::~M_Progress()
{
    delete ui;
}

void M_Progress::ChangeMenuToSchedule(){
    emit this->ChangeMenu(Menu::PLAN_M);
}

void M_Progress::HistoryUpdated(std::vector<std::string> history){
    ui->HistoryList->clear();

    int value = 0;

    for (auto iter = history.begin(); iter != history.end(); iter++){
        std::string textToDisplay = getDateCompleted(*iter) + '\n' + "+" + getPoints(*iter) + " - " + getTask(*iter);
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(textToDisplay));
        item->setBackground(QBrush(QColor(56, 93, 56)));
        ui->HistoryList->addItem(item);

        if (getDateCompleted(*iter) == getCurrentDate()){
            value += atoi(getPriority(*iter).c_str());
        }
    }

    ui->DailyProgress->setValue(value);

    if (value >= ui->DailyProgress->maximum()){
        ui->Title->setText("Congratulations!");
    }
}

void M_Progress::setMaxPoints(std::vector<std::string> plan){
    int max = 0;
    for (std::string task : plan){
        max += atoi(getPriority(task).c_str());
    }
    std::cout << "Max: " << max << std::endl;
    ui->DailyProgress->setMinimum(0);
    if (max > this->maxValue)
        ui->DailyProgress->setMaximum(max);
}
