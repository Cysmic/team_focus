#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "includes.h"
#include "m_api.h"
#include "m_congrats.h"
#include "m_plan.h"
#include "m_plangeneration.h"
#include "m_progress.h"
#include "datamanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ChangeMenu(Menu menu);

private:
    Ui::MainWindow *ui;
    DataManager *dataManager;
};
#endif // MAINWINDOW_H
