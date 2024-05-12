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
    int width=10;
    int height=10;
    std::vector<std::vector<Resident>> residents;
};

#endif // CITY_H
