#include "m_api.h"
#include "ui_m_api.h"

M_API::M_API(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::M_API)
{
    ui->setupUi(this);
    //ui->pushButton->setText("happy potat");
}

M_API::~M_API()
{
    delete ui;
}
