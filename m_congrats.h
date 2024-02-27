#ifndef M_CONGRATS_H
#define M_CONGRATS_H

#include "includes.h"
#include "datamanager.h"

class M_Congrats : public QWidget
{
    Q_OBJECT
private:
    DataManager *dataManager;
public:
    explicit M_Congrats(QWidget *parent = nullptr);

signals:

};

#endif // M_CONGRATS_H
