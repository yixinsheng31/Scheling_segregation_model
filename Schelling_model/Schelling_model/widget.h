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



protected:
    void mousePressEvent(QMouseEvent* event);


private:
    Ui::Widget *ui;
    QGraphicsScene* scene;
    //City* city;
    City city;
    void updateCityView();
};

#endif // MAINWINDOW_H




