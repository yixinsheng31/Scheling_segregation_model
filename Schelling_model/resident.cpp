#include "resident.h"
#include "city.h"

Resident::Resident(Race race, bool isOccupied) : occupied(isOccupied), race(race) {
    switch (race) {
    // case NONE:
    //     icon = QIcon();  // 空的QIcon
    //     break;
    case Race1:
        icon = QIcon("C:/Users/sheng/Desktop/red.png");
        break;
    case Race2:
        icon = QIcon("C:/Users/sheng/Desktop/blue.png");
        break;
    }
}


QIcon Resident::getIcon() const {
    return icon;
}

bool Resident::isOccupied() const {
    return occupied;
}

Resident::Race Resident::getRace() const {
    return race;
}


bool Resident::isSatisfied(const City& city, int x, int y, int threshold) const {
    int sameRace = 0, total = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx, ny = y + dy;
            if (city.isValidPosition(nx, ny)) {
                ++total;
                if (city.getResident(nx, ny).getRace() == race) {
                    ++sameRace;
                }
            }
        }
    }
    //return sameRace >= threshold * total;
    return total <= threshold * sameRace;
}
