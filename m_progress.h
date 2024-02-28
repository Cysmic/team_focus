#ifndef M_PROGRESS_H
#define M_PROGRESS_H

#include "datamanager.h"
#include <QWidget>

namespace Ui {
class M_Progress;
}

class M_Progress : public QWidget
{
    Q_OBJECT

public:
    explicit M_Progress(QWidget *parent = nullptr);
    ~M_Progress();

    void ChangeMenuToSchedule(); //slot

    void HistoryUpdated(std::vector<std::string> history); //slot

    void setMaxPoints(std::vector<std::string> plan); //slot

private:
    Ui::M_Progress *ui;
    int maxValue;

signals:
    void ChangeMenu(Menu menu);
};

#endif // M_PROGRESS_H
