#ifndef GENERAL_TEXT_WIDGET_H
#define GENERAL_TEXT_WIDGET_H

#include <QWidget>

enum TEXT_TYPE{
    HEADER,
    SUBHEADER,
    SUBTEXT
};

class General_Text_Widget : public QWidget
{
    Q_OBJECT
private:
    std::string text;
    TEXT_TYPE textType;
public:
    explicit General_Text_Widget(QWidget *parent = nullptr);
    void SetText(std::string text) {this->text = text;}
    void SetTextType(TEXT_TYPE textType) {this->textType = textType;}

signals:
};

#endif // GENERAL_TEXT_WIDGET_H
