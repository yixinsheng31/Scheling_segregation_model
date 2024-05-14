#include "widget.h"
#include "ui_widget.h"
#include "resident.h"
#include "city.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMouseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->cityView->setScene(scene);
    //QPushButton *button = new QPushButton("Replace City", this);
    connect(ui->platebutton, &QPushButton::clicked, this, &Widget::replaceCity);
    connect(ui->startButton, &QPushButton::clicked, this, &Widget::start);
    connect(ui->moveButton, &QPushButton::clicked, this, &Widget::move);
    connect(ui->resetButton, &QPushButton::clicked, this, &Widget::reset);
    //connect(ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(getHeight(int)));
    //connect(ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(getWidth(int)));
    ui->moveButton->hide();
    ui->resetButton->hide();
    ui->cityView->hide();
    ui->raceComboBox->hide();
    //ui->widthSpinBox->hide();
    //ui->heightSpinBox_2->hide();
}



Widget::~Widget()
{
    delete ui;
}


// 在start槽中，显示所有的控件
void Widget::start()
{
    ui->moveButton->show();
    ui->resetButton->show();
    ui->cityView->show();
    ui->raceComboBox->show();
    //ui->widthSpinBox->show();
    //ui->heightSpinBox_2->show();
    ui->startButton->hide();
    QApplication::processEvents();
    //int height = ui->heightSpinBox_2->value();
    //int width = ui->widthSpinBox->value();
    //city = new City(width, height);
    city = City(20,20);
    //city = new City();
    //city.getHeight(height);  // 设置City的height
    //city.getWidth(width);
    //updateCityView();
    //city = City(width,height);
    updateCityView();
}

void Widget::replaceCity() {
    // 创建新的城市
    City newCity(20, 20, 0.1);
    // 替换当前城市
    city = City(20,20,0.1);
    // 更新视图
    updateCityView();
}


void Widget::move()
{
    city.relocateResidents(2);
    updateCityView();
}

void Widget::reset()
{
    city.reset();
    updateCityView();
}

void Widget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        QPointF posF = event->globalPosition();
        QPoint pos = ui->cityView->mapFromGlobal(posF.toPoint());
        if (ui->cityView->rect().contains(pos)) {
            int x = pos.x() / 10;
            int y = pos.y() / 10;
            Resident::Race race = ui->raceComboBox->currentIndex() == 0 ? Resident::Race1 : Resident::Race2;
            city.addResident(Resident(race, true), x, y);
            updateCityView();
        }
    }
}


void Widget::updateCityView()
{
    scene->clear();
    //for (int i = 0; i < city.width; ++i) {
    for (int i = 0; i < 20; ++i) {
        //for (int j = 0; j < city.height; ++j) {
        for (int j = 0; j < 20; ++j) {
            Resident resident = city.getResident(i, j);
            if (resident.isOccupied()) {
                QGraphicsRectItem* item = new QGraphicsRectItem(i * 10, j * 10, 10, 10);
                item->setBrush(resident.getRace() == Resident::Race1 ? Qt::red : Qt::blue);//Resident::Race2 ? Qt::blue: Qt::black);
                scene->addItem(item);
            }
        }
    }
}

void Widget::getHeight(int value)
{
    city.getHeight(value);
}

void Widget::getWidth(int value)
{
    city.getWidth(value);
}
