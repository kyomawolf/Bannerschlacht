//
// Created by Jascha Kasper on 11/9/22.
//

#ifndef BANNERSCHLACHT_PATHFINDER_HPP
#define BANNERSCHLACHT_PATHFINDER_HPP

#include "../map/Map.hpp"
#include <vector>

class PathFinder {
public:
    typedef struct tile_wrapper {
        tile_wrapper(int x, int y, tile_wrapper *pWrapper, Tile& tile);

        tile_wrapper&    operator=(const tile_wrapper& other);


        int   x;
        int   y;
        struct tile_wrapper* prev = NULL;
        Tile& tileRef;
    } tile_w;
private:
    tile_w                              _end;
    tile_w                              _start;
    Map&                                _map;
    std::vector<tile_w>                 _prio;
    std::vector<std::vector<tile_w> >   _vec_sec;
    std::vector<tile_w>                 _closed;
public:
    PathFinder(const tile_w &end, const tile_w &start, Map& map);

    int setTilePrio();

    bool IsHandled(std::pair<int, int> obj, std::vector<tile_w> &sec, std::vector<tile_w> &tmp);
    void calculate();
};


#endif //BANNERSCHLACHT_PATHFINDER_HPP
