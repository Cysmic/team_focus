#include "m_plan.h"
#include "ui_m_plan.h"

M_Plan::M_Plan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::M_Plan)
{
    ui->setupUi(this);
}

M_Plan::~M_Plan()
{
    delete ui;
}
