//
// Created by kyomawolf on 26.08.22.
//

#ifndef PROJEKT_DIESCHLACHT_MAP_HPP
#define PROJEKT_DIESCHLACHT_MAP_HPP

#include <string>
#include "../Utils.hpp"
#include "raylib-cpp.hpp"
#include "Tile.hpp"

class Map {
public:
private:
    TileIdx _size;
    constexpr static const float _sizeScaling = 100;
    constexpr static const float _imageScaling = 1;
    TileIdx _selectedIndex = TileIdx(-1, -1);
    bool     _selected;
    std::vector<std::vector<Tile> > _field;
    raylib::Texture* _tileTex;
public:
    typedef TileIterator iterator;

    Map();
    Map(unsigned int height, unsigned int length);

    iterator begin();
    iterator end();

    Tile&   front();
    Tile&   back();

    iterator getIter(int x, int y);
    void    Draw(raylib::Texture& tex);
    void    Draw();
    TileIdx positionToIndex(TileIdx& worldPosition);
    bool    OnClick(TileIdx worldPosition);
    static raylib::Vector2 LocalToWorld(unsigned int index_x, unsigned int index_y);
    Tile& at(unsigned int x, unsigned int y);
    Tile& at(TileIdx pos);
    Tile* atPosition(TileIdx pos);

    [[nodiscard]] raylib::Texture *GetTileTex() const;
    const TileIdx &GetSize() const;

    void SetSize(const TileIdx &size);
    void SetTileTex(raylib::Texture *tileTex);
};

#endif //PROJEKT_DIESCHLACHT_MAP_HPP
