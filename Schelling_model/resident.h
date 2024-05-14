#ifndef RESIDENT_H
#define RESIDENT_H
#include <QIcon>

class City;
class Resident {
public:
    enum Race {Race1, Race2};
    Resident(Race race = Race1, bool isOccupied = false);
    QIcon getIcon() const;
    bool isOccupied() const;
    Race getRace() const;
    bool isSatisfied(const City& city, int x, int y, int threshold) const;

private:
    QIcon icon;
    bool occupied;
    Race race;
};

#endif // RESIDENT_H
//enum Race {NONE, Race1, Race2 };
 //Resident(Race race = NONE, bool isOccupied = false);
