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
    connect(ui->startButton, &QPushButton::clicked, this, &Widget::start);
    connect(ui->moveButton, &QPushButton::clicked, this, &Widget::move);
    connect(ui->resetButton, &QPushButton::clicked, this, &Widget::reset);
    ui->moveButton->hide();
    ui->resetButton->hide();
    ui->cityView->hide();
    ui->raceComboBox->hide();
}



Widget::~Widget()
{
    delete ui;
}

/*void Widget::start()
{
    int width = ui->widthSpinBox->value();
    int height = ui->heightSpinBox->value();
    int numResidents = ui->numResidentsSlider->value();

    City city(width, height);
    for (int i = 0; i < numResidents; ++i) {
        city.addResident(Resident());
    }

    city.relocateResidents(3);

    QGraphicsScene* scene = new QGraphicsScene(this);
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            Resident resident = city.getResident(i, j);
            if (resident.isOccupied()) {
                QGraphicsRectItem* item = new QGraphicsRectItem(i * 10, j * 10, 10, 10);
                item->setBrush(resident.getRace() == Resident::Race1 ? Qt::red : Qt::blue);
                scene->addItem(item);
            }
        }
    }

    ui->graphicsView->setScene(scene);
}*/


// 在start槽中，显示所有的控件
void Widget::start()
{
    ui->moveButton->show();
    ui->resetButton->show();
    ui->cityView->show();
    ui->raceComboBox->show();
    city = City(10,10);
    updateCityView();
}

void Widget::move()
{
    city.relocateResidents(3);
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
    //for (int i = 0; i < city.getWidth(); ++i) {
    for (int i = 0; i < 10; ++i) {
        //for (int j = 0; j < city.getHeight(); ++j) {
        for (int j = 0; j < 10; ++j) {
            Resident resident = city.getResident(i, j);
            if (resident.isOccupied()) {
                QGraphicsRectItem* item = new QGraphicsRectItem(i * 10, j * 10, 10, 10);
                item->setBrush(resident.getRace() == Resident::Race1 ? Qt::red : Qt::blue);
                scene->addItem(item);
            }
        }
    }
}

