//
// Created by Jascha Kasper on 11/9/22.
//

#ifndef BANNERSCHLACHT_PATHFINDER_HPP
#define BANNERSCHLACHT_PATHFINDER_HPP

#include "../map/Map.hpp"
#include "../Utils.hpp"
#include <vector>
#include <map>

class Pathfinder {
private:

    // this saves paths for reuse-ability
    struct Path {
        std::vector<TileIndex> _usedTiles;
        std::vector<int>       _oldDifficulty;
        std::vector<bool>      _oldPassability;
        int                    _oldWeather;
        long                   _length = 0;
        TileIndex              _start = {-1, -1};
        TileIndex              _end = { -1, -1};
    };

    // Tile class specifically formatted for pathfinding
    struct PathTile {
        int       _weather = 0;
        int       _difficulty = 0;
        bool      _passable = true;
        TileIndex _index = {-1, -1};
        TileIndex _maxIndex = {-1, -1};
        PathTile(const TileIndex& maxIndex, const TileIndex& index);
    };

    Map*                                _parent;
    std::vector<std::vector<PathTile> > _pathTileCollection;
    //   start and end tile, path
    std::map<std::pair<TileIndex, TileIndex>, Path>  _pathsGenerated;

    bool    checkPath(const Path& path);
public:
    explicit Pathfinder(Map* parent);
//    Path&    FindExistingPath(const TileIndex& start, const TileIndex& end);
    Path&    GeneratePath(const TileIndex& start, const TileIndex& end);
    bool     SearchNext(std::vector<std::vector<TileIndex>>& prio, std::vector<std::vector<TileIndex> >& sec, std::vector<TileIndex>& closed, const TileIndex& end);
};


///**
// * Pathfinding algorithm used for any navigation during the game.
// * Uses an A* pathfinding algorithm
// */
//class PathFinder { /// tf did I do there??
//public:
//    typedef struct tile_wrapper {
//        tile_wrapper(int x, int y, tile_wrapper *pWrapper, Tile& tile);
//
//        tile_wrapper&    operator=(const tile_wrapper& other);
//
//
//        int   x;
//        int   y;
//        struct tile_wrapper* prev = NULL;
//        Tile& tileRef;
//    } tile_w;
//private:
//    tile_w                              _end;
//    tile_w                              _start;
//    Map&                                _map;
//    std::vector<tile_w>                 _prio;
//    std::vector<std::vector<tile_w> >   _vec_sec;
//    std::vector<tile_w>                 _closed;
//public:
//    PathFinder(const tile_w &end, const tile_w &start, Map& map);
//
//    int setTilePrio();
//
//    bool IsHandled(std::pair<int, int> obj, std::vector<tile_w> &sec, std::vector<tile_w> &tmp);
//    void calculate();
//};


#endif //BANNERSCHLACHT_PATHFINDER_HPP
