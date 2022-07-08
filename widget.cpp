#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lineEdit->installEventFilter(this);//给lineEdit安装事件过滤器

}

Widget::~Widget()
{
    delete ui;
}

void Widget::first_graph()
{
    // 生成数据，画出的是抛物线
    QVector<double> x(101), y(101); //初始化向量x和y
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x范围[-1,1]
        y[i] = x[i]*x[i]; // y=x*x
    }
    ui->customPlot->addGraph();//添加数据曲线（一个图像可以有多个数据曲线）

    // graph(0);可以获取某个数据曲线（按添加先后排序）
    // setData();为数据曲线关联数据
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->graph(0)->setName("第一个示例");// 设置图例名称
    // 为坐标轴添加标签
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // 设置坐标轴的范围，以看到所有数据
    ui->customPlot->xAxis->setRange(-1, 1);
    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->legend->setVisible(true); // 显示图例
    // 重画图像
    ui->customPlot->replot();
}

void Widget::second_graph()
{
    //每条曲线都会独占一个graph()
    ui->customPlot_2->addGraph();
    ui->customPlot_2->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    ui->customPlot_2->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色


    ui->customPlot_2->addGraph();//添加graph等价于添加一条新曲线
    ui->customPlot_2->graph(1)->setPen(QPen(Qt::red)); // 曲线的颜色
    // 生成模拟数据点 (x-y0 第一条曲线, x-y1为第2条曲线):
    QVector<double> x(251), y0(251), y1(251);
    for (int i=0; i<251; ++i)
    {
        x[i] = i;
        y0[i] = qExp(-i/150.0)*qCos(i/10.0); // 第一条曲线：y0衰减cos
        y1[i] = qExp(-i/150.0);              // 第二条曲线：y1衰减指数
    }
    // 边框右侧和上侧均显示刻度线，但不显示刻度值:
    ui->customPlot_2->xAxis2->setVisible(true);
    ui->customPlot_2->xAxis2->setTickLabels(false);
    ui->customPlot_2->yAxis2->setVisible(true);
    ui->customPlot_2->yAxis2->setTickLabels(false);
    // 使上下两个X轴的范围总是相等，使左右两个Y轴的范围总是相等
    connect(ui->customPlot_2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot_2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot_2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot_2->yAxis2, SLOT(setRange(QCPRange)));

    ui->customPlot_2->graph(1)->setName("第二个示例");// 设置图例名称

    // 把已存在的数据填充进graph的数据区
    ui->customPlot_2->graph(0)->setData(x, y0);
    ui->customPlot_2->graph(1)->setData(x, y1);
    //自动调整XY轴的范围，以便显示出graph(0)中所有的点（下面会单独讲到这个函数）
    ui->customPlot_2->graph(0)->rescaleAxes();
    //自动调整XY轴的范围，以便显示出graph(1)中所有的点
    ui->customPlot_2->graph(1)->rescaleAxes(true);
    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    // 立即刷新图像
    ui->customPlot_2->replot();
}

void Widget::third_graph()
{
    // 生成数据，画出的是抛物线
    QVector<double> x(101), y(101); //初始化向量x和y
    for (int i=0; i<101; ++i)
    {
        x[i] = i/50.0 - 1; // x范围[-1,1]
        y[i] = 2*x[i]+3;
    }
    ui->customPlot_3->addGraph();//添加数据曲线（一个图像可以有多个数据曲线）

    // graph(0);可以获取某个数据曲线（按添加先后排序）
    // setData();为数据曲线关联数据
    ui->customPlot_3->graph(0)->setData(x, y);
    ui->customPlot_3->graph(0)->setName("第三个示例");// 设置图例名称
    // 为坐标轴添加标签
    ui->customPlot_3->xAxis->setLabel("x");
    ui->customPlot_3->yAxis->setLabel("y");
    // 设置坐标轴的范围，以看到所有数据
    ui->customPlot_3->xAxis->setRange(-1, 1);
    ui->customPlot_3->yAxis->setRange(1, 5);
    ui->customPlot_3->legend->setVisible(true); // 显示图例
    // 重画图像
    ui->customPlot_3->replot();

}


void Widget::le_0()
{
    ui->customPlot->clearPlottables();
    ui->customPlot->replot();

    ui->customPlot_2->clearPlottables();
    ui->customPlot_2->replot();

    ui->customPlot_3->clearPlottables();
    ui->customPlot_3->legend->setVisible(false);
    ui->customPlot_3->replot();

}

void Widget::le_1()
{
    le_0();
    first_graph();
}

void Widget::le_2()
{
    le_1();
    second_graph();
}

void Widget::le_3()
{
    le_2();
    third_graph();
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        switch (keyEvent->key())
        {
        case Qt::Key_0:
            le_0();
            return false;//返回false即表示不过滤该事件
        case Qt::Key_1:
            le_1();
            return false;
        case Qt::Key_2:
            le_2();
            return false;
        case Qt::Key_3:
            le_3();
            return false;
        default:
            return true;
        }
    }
    return false;
}

