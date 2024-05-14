#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "city.h"
#include "resident.h"
#include <QMainWindow>
#include <QGraphicsScene>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void start();
    void move();
    void reset();
public slots:
    void getHeight(int value);
    void getWidth(int value);
    void replaceCity();/*{
        // 创建新的城市
        City newCity(20, 20, 0.1);
        // 替换当前城市
        currentCity = newCity;
        // 更新视图
        updateCityView();
    }*/


protected:
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::Widget *ui;
    QGraphicsScene* scene;
    //City* city;
public:
    City city;
public:
    //City currentCity;
    void updateCityView();
};

#endif // MAINWINDOW_H




