#include "m_progress.h"
#include "ui_m_progress.h"

M_Progress::M_Progress(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::M_Progress)
{
    ui->setupUi(this);
}

M_Progress::~M_Progress()
{
    delete ui;
}
