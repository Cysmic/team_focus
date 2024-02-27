#ifndef M_PROGRESS_H
#define M_PROGRESS_H

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

private:
    Ui::M_Progress *ui;
};

#endif // M_PROGRESS_H
