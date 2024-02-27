#ifndef M_PLAN_H
#define M_PLAN_H

#include <QWidget>
#include "datamanager.h"

namespace Ui {
class M_Plan;
}

class M_Plan : public QWidget
{
    Q_OBJECT
private:
    DataManager *dataManager;
    Ui::M_Plan *ui;

public:
    explicit M_Plan(QWidget *parent = nullptr);
    ~M_Plan();

signals:
};

#endif // M_PLAN_H
