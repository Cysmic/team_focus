#ifndef M_PROGRESS_H
#define M_PROGRESS_H

#include "includes.h"
#include "datamanager.h"

class M_Progress : public QWidget
{
    Q_OBJECT
private:
    DataManager *dataManager;
public:
    explicit M_Progress(QWidget *parent = nullptr);

signals:
};

#endif // M_PROGRESS_H
