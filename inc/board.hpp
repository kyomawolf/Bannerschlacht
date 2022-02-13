#ifndef __BOARD_H__
#define __BOARD_H__

#include <string>
#include <map>
#include <unit.hpp>

using namespace std;

class tile {
    private:
    int _id;
    int _type;
    int _height;

    public:
    tile();
    tile(int nid, int ntype, int nheight);
    ~tile();
    void    printTile();
    string  tileTypeStr();
    int     tileTypeInt();
    char    tileTypeCha();
};

class board{
    private:
    int             _size_x;
    int             _size_y;
    map<int, tile>  _tileBoard;
    map<int, unit*> _armyBoard;

    public:
    board(/*savegame*/);
    board(int x, int y);
    ~board() {};
    void    printBoard();
    void    round();
};

#endif /* __BOARD_H__ */