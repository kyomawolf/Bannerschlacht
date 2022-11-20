//
// Created by Jascha Kasper on 11/9/22.
//


#include "PathFinder.hpp"
#include "raylib-cpp.hpp"

bool    PathFinder::IsHandled(std::pair<int, int> obj, std::vector<tile_w>& sec, std::vector<tile_w>& tmp) {
    for (auto & i : _prio) {
        if (obj.first == i.x && obj.second == i.y)
            return false;
    }
    for (auto & i : sec) {
        if (obj.first == i.x && obj.second == i.y)
            return false;
    }
    for (auto & i : tmp) {
        if (obj.first == i.x && obj.second == i.y)
            return false;
    }
    for (auto & i : _closed) {
        if (obj.first == i.x && obj.second == i.y)
            return false;
    }
    return true;
}

int PathFinder::setTilePrio() {
    std::vector<tile_w> tmp;
    std::vector<tile_w> sec;

    for (auto & i : _prio) {
        int diff_s = (int) hypot(_end.y - i.y, _end.x - i.x);
        if (diff_s == 0) {
            _end = i;
            return 0;
        }
        int diff_o;
        if (i.x != 0 &&
            _map.at(i.x - 1, i.y).GetCost() &&
            IsHandled(std::make_pair(i.x - 1, i.y), sec, tmp)) { //up

            diff_o = (int) hypot(_end.y - i.y, _end.x - (i.x - 1));
            if (diff_o < diff_s)
                tmp.emplace_back(tile_w(i.x - 1, i.y, &i, _map.at(i.x - 1, i.y)));
            else
                sec.emplace_back(tile_w(i.x - 1, i.y, &i, _map.at(i.x - 1, i.y)));
        }
        if (i.y != 0 &&
            _map.at(i.x, i.y - 1).GetCost() &&
            IsHandled(std::make_pair(i.x, i.y - 1), sec, tmp)) { //left

            diff_o = (int) hypot(_end.y - (i.y - 1), _end.x - i.x);
            if (diff_o < diff_s)
                tmp.emplace_back(tile_w(i.x, i.y - 1, &i, _map.at(i.x, i.y - 1)));
            else
                sec.emplace_back(tile_w(i.x, i.y - 1, &i, _map.at(i.x, i.y - 1)));
        }
        if (i.x != (int) _map._size.x &&
            _map.at(i.x + 1, i.y).GetCost() &&
            IsHandled(std::make_pair(i.x + 1, i.y), sec, tmp)) { //down
            diff_o = (int) hypot(_end.y - i.y, _end.x - (i.x + 1));
            if (diff_o < diff_s)
                tmp.emplace_back(tile_w(i.x + 1, i.y, &i, _map.at(i.x + 1, i.y)));
            else
                sec.emplace_back(tile_w(i.x + 1, i.y, &i, _map.at(i.x + 1, i.y)));
        }
        if (i.y != (int) _map._size.y &&
            _map.at(i.x, i.y + 1).GetCost() &&
            IsHandled(std::make_pair(i.x, i.y + 1), sec, tmp)) { //right
            diff_o = (int) hypot(_end.y - (i.y + 1), _end.x - i.x);
            if (diff_o < diff_s)
                tmp.emplace_back(tile_w(i.x, i.y + 1, &i, _map.at(i.x, i.y + 1)));
            else // add modifier option
                sec.emplace_back(tile_w(i.x, i.y + 1, &i, _map.at(i.x, i.y + 1)));
        }
        _closed.push_back(i);
        if (!sec.empty())
            _vec_sec.insert(_vec_sec.begin(), sec);
    }
    _prio.clear();
    if (tmp.empty() && !_vec_sec.empty())
        _prio.assign(_vec_sec.begin()->begin(), _vec_sec.begin()->end());
    else
        _prio.assign(tmp.begin(), tmp.end());
    tmp.clear();

    return 1;
}

PathFinder::PathFinder(const PathFinder::tile_w &end, const PathFinder::tile_w &start, Map& map) : _end(end),
                                                                                                   _start(start),
                                                                                                   _map(map) {
    _prio.emplace_back(_start);
}

void PathFinder::calculate() {
    while (setTilePrio()) {
//#ifdef DEBUG
//#ifdef TRACE_PATH
        for (auto &i:  _map.at(_start.x, _start.y)) {

        }
//#endif //TRACE_PATH
//#endif //DEBUG
    }
}

PathFinder::tile_wrapper::tile_wrapper(int i, int i1, PathFinder::tile_wrapper *pWrapper, Tile& tile): x(i),
                                                                                                       y(i1),
                                                                                                       prev(pWrapper),
                                                                                                       tileRef(tile) { }

PathFinder::tile_wrapper& PathFinder::tile_wrapper::operator=(const PathFinder::tile_wrapper &other) {
    this->x = other.x;
    this->y = other.y;
    this->tileRef = other.tileRef;
    this->prev = other.prev;
}
