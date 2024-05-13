#include "city.h"
#include <cstdlib>  // 用于rand函数

City::City(int width, int height) : width(width), height(height), residents(width, std::vector<Resident>(height)) {}

void City::getHeight(int h)
{
    height = h;
}

void City::getWidth(int w)
{
    width = w;
}


void City::addResident(const Resident& resident, int x, int y) {
    if (isValidPosition(x, y) && !residents[x][y].isOccupied()) {
        residents[x][y] = resident;
    } else {
        // 如果位置无效或已被占据，你可以选择抛出一个异常
    }
}

Resident City::getResident(int x, int y) const {
    return residents[x][y];
}

bool City::isValidPosition(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void City::relocateResidents(int threshold) {
    std::vector<std::pair<int, int>> unsatisfied;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (residents[i][j].isOccupied() && !residents[i][j].isSatisfied(*this, i, j, threshold)) {
                unsatisfied.push_back(std::make_pair(i, j));
            }
        }
    }
    for (const auto& pos : unsatisfied) {
        int x, y;
        do {
            x = rand() % width;
            y = rand() % height;
        } while (residents[x][y].isOccupied());
        std::swap(residents[pos.first][pos.second], residents[x][y]);
    }
}

void City::reset() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            residents[i][j] = Resident();
        }
    }
}

