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

Pathfinder::Path &Pathfinder::GeneratePath(const TileIndex &start, const TileIndex &end) {
    auto existingPath = _pathsGenerated.find({start, end});
    if (existingPath != _pathsGenerated.end() && checkPath(existingPath->second))
        return existingPath->second;

}

//Pathfinder::Path &Pathfinder::FindExistingPath(const TileIndex& start, const TileIndex& end) {
//
//}

Pathfinder::PathTile::PathTile(const TileIndex& maxIndex, const TileIndex& index) : _index(index), _maxIndex(maxIndex) { }

