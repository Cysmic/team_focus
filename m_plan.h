#ifndef M_PLAN_H
#define M_PLAN_H

#include "includes.h"
#include "datamanager.h"

class M_Plan : public QWidget
{
    Q_OBJECT
private:
    DataManager *dataManager;
public:
    explicit M_Plan(QWidget *parent = nullptr);

signals:
};

#endif // M_PLAN_H
