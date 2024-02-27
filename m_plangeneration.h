#ifndef M_PLANGENERATION_H
#define M_PLANGENERATION_H

#include "includes.h"
#include "datamanager.h"

class M_PlanGeneration : public QWidget
{
    Q_OBJECT
private:
    DataManager *dataManager;
public:
    explicit M_PlanGeneration(QWidget *parent = nullptr);

signals:
};

#endif // M_PLANGENERATION_H
