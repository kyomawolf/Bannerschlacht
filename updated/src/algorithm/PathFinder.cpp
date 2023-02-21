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

static bool IsHandled(PathTileIndex current, std::vector<PathTileIndex>& prio, std::vector<std::vector<PathTileIndex>>& sec, std::vector<PathTileIndex>& tmp, std::vector<std::vector<PathTileIndex>>& closed) {
    for (auto& idx : prio) {
        if (current == idx)
            return false;
    }
    for (auto& idxFirst : sec) {
        for (auto& idxSecond : idxFirst) {
            if (current == idxSecond)
                return false;
        }
    }
    for (auto& idx : tmp) {
        if (current == idx)
            return false;
    }
    for (auto& idxFirst : closed) {
        for (auto& idxSecond : idxFirst) {
            if (current == idxSecond)
                return false;
        }
    }
    return true;
}

void Pathfinder::SearchNext(std::vector<std::vector <PathTileIndex>>& paths, std::vector<std::vector<PathTileIndex>>& sec, std::vector<std::vector<PathTileIndex>>& closed, const TileIndex& end) {
    std::vector<PathTileIndex>  temporary;
    std::vector<int>            indexes;
    std::vector<std::vector<PathTileIndex>>  newPaths;
    bool                    first_possibility;
    int                     pathIndex;
    long                    differenceAdjacent;
    int                     maxPriorityLevel = 1;

    for (int idxFirst = 0; idxFirst <= maxPriorityLevel; idxFirst++) {
        pathIndex = 0;
        for (auto& firstIdx : paths) { /// TODO copy into temporary if inserting a new path. otherwise, heap buffer overflow as iterator gets destroyed
            first_possibility = true;
//            std::cout << "---" << std::endl;
//            for (auto& idx : firstIdx)
//                std:: cout << idx << std::endl;
//            std::cout << "---" << std::endl;
            auto& i = firstIdx.back();
            if (i.priority != idxFirst) {
                ++pathIndex;
                continue;
            }
            long differenceEnd = (long) hypot(end.y - i.y, end.x - i.x);
            if (differenceEnd == 0) {
                std::cout << "skipping, index: " << pathIndex;
                ++pathIndex;
                continue;
            }
            /// up
            if (i.x != 0 && _pathTileCollection[i.x - 1][i.y]._passable &&
                IsHandled({i.x - 1, i.y}, firstIdx, newPaths, temporary, closed)) {
                differenceAdjacent = (long) hypot(end.y - i.y, end.x - (i.x - 1));
                if (differenceAdjacent < differenceEnd) {
//                    std::cout << "up" << std::endl;
                    first_possibility = false;
                    temporary.emplace_back(i.x - 1, i.y);
                } else {
                    /* if (!first_possibility && differenceAdjacent < differenceEnd) */
//                    std::cout << "up" << std::endl;
                    newPaths.push_back(firstIdx);
                    newPaths.back().push_back({i.x - 1, i.y, 1});
                }
            }
            ///down
            if (i.x != _parent->GetSize().x && _pathTileCollection[i.x + 1][i.y]._passable &&
                IsHandled({i.x + 1, i.y}, firstIdx, newPaths, temporary, closed)) {
                differenceAdjacent = (long) hypot(end.y - i.y, end.x - (i.x + 1));
                if (first_possibility && differenceAdjacent < differenceEnd) {
//                    std::cout << "down" << std::endl;
                    first_possibility = false;
                    temporary.emplace_back(i.x + 1, i.y);
                } else {
//                    std::cout << "down" << std::endl;
                    newPaths.push_back(firstIdx);
                    newPaths.back().push_back({i.x + 1, i.y, 1});
                }
            }
            ///left
            if (i.y != 0 && _pathTileCollection[i.x][i.y - 1]._passable &&
                IsHandled({i.x, i.y - 1}, firstIdx, newPaths, temporary, closed)) {
                differenceAdjacent = (long) hypot(end.y - (i.y - 1), end.x - i.x);
                if (first_possibility && differenceAdjacent < differenceEnd) {
//                    std::cout << "left" << std::endl;
                    first_possibility = false;
                    temporary.emplace_back(i.x, i.y - 1);
                } else {
//                    std::cout << "left" << std::endl;
                    newPaths.push_back(firstIdx);
                    newPaths.back().push_back({i.x, i.y - 1, 1});
                }
            }
            ///right
            if (i.y != _parent->GetSize().y && _pathTileCollection[i.x][i.y + 1]._passable &&
                IsHandled({i.x, i.y + 1}, firstIdx, newPaths, temporary, closed)) {
                differenceAdjacent = (long) hypot(end.y - (i.y + 1), end.x - i.x);
                if (first_possibility && differenceAdjacent < differenceEnd) {
//                    std::cout << "right" << std::endl;
                    first_possibility = false;
                    temporary.emplace_back(i.x, i.y + 1);
                } else {
//                    std::cout << "right" << std::endl;
                    newPaths.push_back(firstIdx);
                    newPaths.back().push_back({i.x, i.y + 1, 1});
                }
            }
            if (!first_possibility)
                indexes.push_back(pathIndex);
            ++pathIndex;
        }
    }
    int i = 0;
    for (auto& idx : indexes) {
        paths[idx].push_back(temporary[i]);
        i++;
    }
    paths.insert(paths.end(), newPaths.begin(), newPaths.end());
//        closed.push_back(i);
//        if (!backupPaths.empty())
//            sec.insert(sec.begin(), backupPaths);
//    if (tmp.empty() && !sec.empty())
//        prio.assign(sec.begin()->begin(), sec.begin()->end());
//    else
//        prio.assign(tmp.begin(), tmp.end());
//    return true;
}

Pathfinder::Path Pathfinder::GeneratePath(const TileIndex &start, const TileIndex &end) {
    auto existingPath = _pathsGenerated.find({start, end});
    if (existingPath != _pathsGenerated.end() && checkPath(existingPath->second))
        return existingPath->second;
    std::vector<std::vector<PathTileIndex>> prioList;
    prioList.emplace_back();
    prioList.begin()->push_back(start);
    std::vector<std::vector<PathTileIndex>> secondList;
    std::vector<std::vector<PathTileIndex>> closedList;
    Path        finalPath;
    finalPath._start = start; //todo put into proper constructor
    finalPath._end = end;
    std::cout << "start: " << start << " end: " << end << std::endl;
    std::string none;
    bool    looping = true;
    while (looping) {
//        std::cout << "press enter";
//        std::getline( std::cin, none );
//        std::cout << "something" << std::endl;
        SearchNext(prioList, secondList, closedList, end);
        for  (auto& i : prioList) {
            for (auto& ii : i) {
                long differenceEnd = (long) hypot(end.y - ii.y, end.x - ii.x);
                if (differenceEnd == 0)
                    looping = false;
            }
            if (!looping) {
                for (auto &ii: i)
                    finalPath._usedTiles.push_back(ii);
                break;
            }
        }
    }
//    for (auto & idx : prioList.back())
//        std::cout << idx << std::endl;
std::cout << "final: " << std::endl;
    for (auto &ii: finalPath._usedTiles)
        std::cout << ii << std::endl;
    return finalPath;
}

//Pathfinder::Path &Pathfinder::FindExistingPath(const TileIndex& start, const TileIndex& end) {
//
//}

Pathfinder::PathTile::PathTile(const TileIndex& maxIndex, const TileIndex& index) : _index(index), _maxIndex(maxIndex) { }

PathTileIndex::PathTileIndex(long initX, long initY, int prio) : TileIndex(initX, initY), priority(prio) {

}

TileIndex::TileIndex(const PathTileIndex& pathTile) : x(pathTile.x), y(pathTile.y) {}
TileIndex& TileIndex::operator=(const PathTileIndex& other) { x = other.x; y = other.y; return *this; }

PathTileIndex::PathTileIndex(const TileIndex& index) : TileIndex(index) {

}

// void     Pathfinder::UpdatePathfinder() {
//     _parent->
// }
