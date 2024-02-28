#ifndef M_PLANGENERATION_H
#define M_PLANGENERATION_H

#include <QWidget>
#include "datamanager.h"

namespace Ui {
class M_PlanGeneration;
}

class M_PlanGeneration : public QWidget
{
    Q_OBJECT
private:
    DataManager *dataManager;
    Ui::M_PlanGeneration *ui;

public:
    explicit M_PlanGeneration(QWidget *parent = nullptr);
    ~M_PlanGeneration();

    void createTagList(std::vector<Task> tasks); //slot
    void activateSendFunc(); //slot
    void changeToProgressMenu(); //slot



signals:
    void sendPlanInfo(std::vector<std::string> filters, int numTasks); //no breaks for now for simplicity
    void ChangeMenu(Menu menu);
};

#endif // M_PLANGENERATION_H
