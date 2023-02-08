//
// Created by Jascha Kasper on 11/9/22.
//

#include "PathFinder.hpp"


Pathfinder::Pathfinder(Map* parent) : _parent(parent), _pathTileCollection() {
    auto maxSize = parent->GetSize();
    for (auto countX = 0; countX != maxSize.x; countX++) { //future: use iterator instead
        _pathTileCollection.emplace_back(std::vector<PathTile>());
        for (auto countY = 0; countY != maxSize.y; countY++) {
            _pathTileCollection.at(countX).emplace_back(PathTile(maxSize, {countX, countY}));
        }
    }
}

bool Pathfinder::checkPath(const Pathfinder::Path &path) {
    // if (path._oldweather != _weather) return false; //enable when weather has been implemented
    if (path._usedTiles.size() != path._oldDifficulty.size() != path._oldPassability.size())
        return false;
    for (unsigned index = 0; index != path._usedTiles.size(); index++) {
        //complicated, let me explain: tilecollection needs [x][y]; for it, we use the usedtile[index]->x|y and its position for using the right tile
        PathTile& current = _pathTileCollection.at(path._usedTiles.at(index).x).at(path._usedTiles.at(index).y);
        if (current._passable != path._oldPassability.at(index) || current._difficulty != path._oldDifficulty.at(index))
            return false;
    }
    return true;
}

static bool IsHandled(TileIndex current, std::vector<TileIndex>& prio, std::vector<TileIndex>& sec, std::vector<TileIndex>& tmp, std::vector<TileIndex>& closed) {
    for (auto& idx : prio) {
        if (current == idx)
            return false;
    }
    for (auto& idx : sec) {
        if (current == idx)
            return false;
    }
    for (auto& idx : tmp) {
        if (current == idx)
            return false;
    }
    for (auto& idx : closed) {
        if (current == idx)
            return false;
    }
    return true;
}

bool Pathfinder::SearchNext(std::vector<TileIndex>& prio, std::vector<std::vector<TileIndex>>& sec, std::vector<TileIndex>& closed, const TileIndex& end) {
    std::vector<std::vector<TileIndex> > preferredPaths;
    std::vector<std::vector<TileIndex> > backupPaths;

    for (auto& i : prio) {
        long differenceEnd = (long) hypot(end.y - i.y, end.x - end.x);
        if (differenceEnd == 0)
            return false;
        long differenceAdjacent;
        /// up
        if (i.x != 0 && _pathTileCollection[i.x - 1][i.y]._passable &&
            IsHandled({i.x - 1, i.y}, prio, sec_tmp, tmp, closed)) {
            differenceAdjacent = (long) hypot(end.y - i.y, end.x - (i.x - 1));
            if (differenceAdjacent < differenceEnd)
                tmp.emplace_back(i.x - 1, i.y);
            else
                sec_tmp.emplace_back(i.x - 1, i.y);
        }
        ///down
        if (i.x != _parent->GetSize().x && _pathTileCollection[i.x + 1][i.y]._passable &&
            IsHandled({i.x + 1, i.y}, prio, sec_tmp, tmp, closed)) {
            differenceAdjacent = (long) hypot(end.y - i.y, end.x - (i.x + 1));
            if (differenceAdjacent < differenceEnd)
                tmp.emplace_back(i.x + 1, i.y);
            else
                sec_tmp.emplace_back(i.x + 1, i.y);
        }
        ///left
        if (i.y != 0 && _pathTileCollection[i.x][i.y - 1]._passable &&
            IsHandled({i.x, i.y - 1}, prio, sec_tmp, tmp, closed)) {
            differenceAdjacent = (long) hypot(end.y - (i.y - 1), end.x - i.x);
            if (differenceAdjacent < differenceEnd)
                tmp.emplace_back(i.x, i.y - 1);
            else
                sec_tmp.emplace_back(i.x, i.y - 1);
        }
        ///right
        if (i.y != _parent->GetSize().y && _pathTileCollection[i.x][i.y + 1]._passable &&
            IsHandled({i.x, i.y + 1}, prio, sec_tmp, tmp, closed)) {
            differenceAdjacent = (long) hypot(end.y - (i.y + 1), end.x - i.x);
            if (differenceAdjacent < differenceEnd)
                tmp.emplace_back(i.x, i.y + 1);
            else
                sec_tmp.emplace_back(i.x, i.y + 1);
        }
        closed.push_back(i);
        if (!sec_tmp.empty())
            sec.insert(sec.begin(), sec_tmp);
    }

    prio.clear();
    if (tmp.empty() && !sec.empty())
        prio.assign(sec.begin()->begin(), sec.begin()->end());
    else
        prio.assign(tmp.begin(), tmp.end());
    return true;
}

Pathfinder::Path &Pathfinder::GeneratePath(const TileIndex &start, const TileIndex &end) {
    auto existingPath = _pathsGenerated.find({start, end});
    if (existingPath != _pathsGenerated.end() && checkPath(existingPath->second))
        return existingPath->second;
    std::vector<TileIndex> prioList;
    prioList.emplace_back(start);
    std::vector<std::vector<TileIndex>> secondList;
    std::vector<TileIndex> closedList;
    while (SearchNext(prioList, secondList, closedList, end)) { }
    for (auto& idx : prioList)
        std::cout << idx << std::endl;
}

//Pathfinder::Path &Pathfinder::FindExistingPath(const TileIndex& start, const TileIndex& end) {
//
//}

Pathfinder::PathTile::PathTile(const TileIndex& maxIndex, const TileIndex& index) : _index(index), _maxIndex(maxIndex) { }

