#include "m_congrats.h"
#include "ui_m_congrats.h"

M_Congrats::M_Congrats(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::M_Congrats)
{
    ui->setupUi(this);
}

M_Congrats::~M_Congrats()
{
    delete ui;
}
