#include "m_plangeneration.h"
#include "ui_m_plangeneration.h"

M_PlanGeneration::M_PlanGeneration(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::M_PlanGeneration)
{
    ui->setupUi(this);
}

M_PlanGeneration::~M_PlanGeneration()
{
    delete ui;
}
