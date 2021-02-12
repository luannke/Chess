#include "Strategy.h"

bool GeneralsStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return false;
}

bool AdvisorsStrategy::is_movable(int &previous, int &current, std::vector<std::shared_ptr<Piece>> &pieces) {
    std::vector possoble_vector_ = possible_[pieces[previous]->camp_][previous];
    return std::find(possoble_vector_.begin(), possoble_vector_.end(), current) != possoble_vector_.end();
}

bool BishopsStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &pieces) {
    return false;
}

bool HorsesStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return false;
}

bool ChariotsStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return false;
}


bool CannonsStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return false;
}

bool SoldiersStrategy::is_movable(int &, int &, std::vector<std::shared_ptr<Piece>> &) {
    return false;
}