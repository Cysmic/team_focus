#ifndef M_CONGRATS_H
#define M_CONGRATS_H

#include <QWidget>
#include "datamanager.h"

namespace Ui {
class M_Congrats;
}

class M_Congrats : public QWidget
{
    Q_OBJECT
private:
    DataManager *dataManager;
    Ui::M_Congrats *ui;

public:
    explicit M_Congrats(QWidget *parent = nullptr);
    ~M_Congrats();

signals:
};

#endif // M_CONGRATS_H
