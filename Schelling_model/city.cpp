#include "city.h"
#include "resident.h"
#include <cstdlib>  // 用于rand函数
#include <algorithm>
#include <random>
City::City(int width, int height) : width(width), height(height), residents(width, std::vector<Resident>(height)) {}

City::City(int width, int height, double empty_ratio) : width(width), height(height), empty_ratio(empty_ratio) {
    // 初始化居民板
    residents = std::vector<std::vector<Resident>>(width, std::vector<Resident>(height));
    // 创建所有可能的位置列表
    std::vector<std::pair<int, int>> positions;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            positions.push_back({i, j});
        }
    }
    // 随机打乱位置列表
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions.begin(), positions.end(), g);
    // 计算空置房屋数量
    int empty_house_num = static_cast<int>(empty_ratio * width * height);
    // 分割位置列表为空置房屋和非空置房屋
    std::vector<std::pair<int, int>> empty_positions(positions.begin(), positions.begin() + empty_house_num);
    std::vector<std::pair<int, int>> not_empty_positions(positions.begin() + empty_house_num, positions.end());
    // 为非空置房屋分配种族
    // for (const auto& pos : not_empty_positions) {
    //     residents[pos.first][pos.second] = Resident(static_cast<Resident::Race>((pos.first + pos.second) % 2));
    // }

    // for (const auto& pos : not_empty_positions) {
    //     switch ((pos.first + pos.second) % 2) {
    //     case 0:
    //         residents[pos.first][pos.second] = Resident(Resident::Race1);
    //         break;
    //     case 1:
    //         residents[pos.first][pos.second] = Resident(Resident::Race2);
    //         break;
    //     }
    // }

    for (const auto& pos : not_empty_positions) {
        switch ((pos.first + pos.second) % 2) {
        case 0:
            addResident(Resident(Resident::Race1, true), pos.first, pos.second);
            break;
        case 1:
            addResident(Resident(Resident::Race2, true), pos.first, pos.second);
            break;
        }
    }
    // 为空置房屋分配空居民
    for (const auto& pos : empty_positions) {
        addResident(Resident(), pos.first, pos.second);
        //residents[pos.first][pos.second] = Resident();  // 假设种族为0表示空置
    }
}

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
    std::vector<std::pair<int, int>> vacant_positions;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (residents[i][j].isOccupied()) {
                if (!residents[i][j].isSatisfied(*this, i, j, threshold)) {
                    unsatisfied.push_back(std::make_pair(i, j));
                }
            } else {
                vacant_positions.push_back(std::make_pair(i, j));
            }
        }
    }
    for (const auto& pos : unsatisfied) {
        int index = rand() % vacant_positions.size();
        std::pair<int, int> vacant_position = vacant_positions[index];
        std::swap(residents[pos.first][pos.second], residents[vacant_position.first][vacant_position.second]);
        vacant_positions[index] = pos;
    }
}
// void City::relocateResidents(int threshold) {
//     std::vector<std::pair<int, int>> unsatisfied;
//     for (int i = 0; i < width; ++i) {
//         for (int j = 0; j < height; ++j) {
//             if (residents[i][j].isOccupied() && !residents[i][j].isSatisfied(*this, i, j, threshold)) {
//                 unsatisfied.push_back(std::make_pair(i, j));
//             }
//         }
//     }
//     for (const auto& pos : unsatisfied) {
//         int x, y;
//         do {
//             x = rand() % width;
//             y = rand() % height;
//         } while (residents[x][y].isOccupied());
//         std::swap(residents[pos.first][pos.second], residents[x][y]);
//     }
// }


void City::reset() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            residents[i][j] = Resident();
        }
    }
}

