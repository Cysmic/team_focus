#include "m_api.h"
#include "ui_m_api.h"

M_API::M_API(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::M_API)
{
    ui->setupUi(this);
    connect(ui->Submit, &QPushButton::clicked, this, &M_API::submitData);
}

M_API::~M_API()
{
    delete ui;
}

// have to chain them since the ui is not directly exposed to the main menu
void M_API::submitData(){
    emit sendKey_ID(ui->API_KEY_I->text().toStdString(), ui->DATABASE_ID_I->text().toStdString());
}
