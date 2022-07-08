#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void first_graph();
    void second_graph();
    void third_graph();

    bool eventFilter(QObject *watched, QEvent *event);

    void le_0();
    void le_1();
    void le_2();
    void le_3();    

private slots:

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
