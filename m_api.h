#ifndef M_API_H
#define M_API_H

#include "includes.h"
#include "datamanager.h"

class M_API : public QWidget
{
    Q_OBJECT
private:
    DataManager *dataManager;
public:
    explicit M_API(QWidget *parent = nullptr);

signals:
};

#endif // M_API_H
