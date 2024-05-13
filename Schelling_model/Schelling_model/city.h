#ifndef CITY_H
#define CITY_H

#include <vector>
#include "resident.h"

class City {
public:
    City(){};
    City(int width, int height);
    void addResident(const Resident& resident, int x, int y);
    Resident getResident(int x, int y) const;
    void relocateResidents(int threshold);
    bool isValidPosition(int x, int y) const;
    void reset();

public:
    int width;
    int height;
    std::vector<std::vector<Resident>> residents;
    // 添加setHeight和setWeight函数
    void getHeight(int h);
    void getWidth(int w);
};

#endif // CITY_H
