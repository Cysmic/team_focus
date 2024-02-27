#ifndef M_API_TEST_H
#define M_API_TEST_H

#include "includes.h"
#include "datamanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class M_API;
}
QT_END_NAMESPACE

class M_API : public QWidget
{
    Q_OBJECT
private:
    DataManager *dataManager;
    Ui::M_API *ui;
public:
    explicit M_API(QWidget *parent = nullptr);

signals:
};

#endif // M_API_TEST_H
