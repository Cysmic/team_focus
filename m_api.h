#ifndef M_API_H
#define M_API_H

#include <QWidget>

namespace Ui {
class M_API;
}

class M_API : public QWidget
{
    Q_OBJECT

public:
    explicit M_API(QWidget *parent = nullptr);
    ~M_API();

private:
    Ui::M_API *ui;
};

#endif // M_API_H
