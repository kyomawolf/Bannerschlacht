#include "board.hpp"
#include <iostream>

tile::tile(int nid, int ntype, int nheight) : _id(nid), _type(ntype), _height(nheight) {
}

tile::tile() : _id(0), _type(0), _height(0) {

}

tile::~tile(){};

void    tile::printTile() {
    std::cout << tileTypeStr() << " with id " << _id <<"\nheight: " << _height << "\n";
}

std::string tile::tileTypeStr() {
    switch(_type) {
        case 0:
            return "grassland";
        case 1:
            return "hill";
        case 2:
            return "river";
        case 3:
            return "swamp";
        case 4:
            return "beach";
        case 5:
            return "ocean";
        case 6:
            return "lake";
        case 7:
            return "forest";
        default:
            return "grassland";
    }
}

int tile::tileTypeInt() {
    return _type;
}

char tile::tileTypeCha() {
    switch(_type) {
        case 0:
            return 'o';
        case 1:
            return '^';
        case 2:
            return '~';
        case 3:
            return 'o';
        case 4:
            return 'w';
        case 5:
            return '~';
        case 6:
            return '~';
        case 7:
            return 'f';
        default:
            return 'o';
    }
}

/*BOARD*/

board::board() : _size_x(20), _size_y(10) {
    for (int i = 0; i < _size_x; i++) {
        for (int ii = 0; ii < _size_y; ii++) {
            _tileBoard.insert(pair<int, tile>((ii * 100) + i, tile((ii * 100) + i, 0, 0)));
        }
    }
}

board::board(int x, int y) : _size_x(x), _size_y(y) {
    for (int i = 0; i < _size_x; i++) {
        for (int ii = 0; ii < _size_y; ii++) {
            _tileBoard.insert(pair<int, tile>((ii * 100) + i, tile((ii * 100) + i, 0, 0)));
        }
    }
}

void    board::printBoard() {
    for (int ii = 0; ii < _size_y; ii++) {
        for (int i = 0; i < _size_x; i++) {
            std::cout << _tileBoard[ii*100 + i].tileTypeCha();
        }
        std::cout << "\n";
    }
}