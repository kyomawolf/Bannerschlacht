#ifndef DATA_HPP
#define DATA_HPP

#include "BaseData.hpp"
#include "Ui.hpp"

class Data {
public:
    enum DataIndetify {MAP, PLAYER, UNIT, CUSTOM};
    typedef DataIndetify DIdent;
    struct DataLink {
//        int         id; TODO
        DIdent      indentifier;
        BaseData*   classData;
    };
private:
public:
    //all data will be held here
    //use generator function to create pointer to DataLinkobject
    //use generator function to create a vector list of all pointer of same classtype
    //TODO make private
    std::vector<DataLink>   vecLink; //used for deallocation or for searching a specific object (slow)
    std::vector<Unit*>      vecUnits;
    std::vector<TileData>   vecTiles;
    Ui                      gameUi;

    BaseData* FindNextIdent(DIdent type, std::vector<DataLink>::difference_type index = 0 );

    Data();
    Data(Ui initUi);
    ~Data();


    
    //// struct UnitData {
    ////     float       atk;
    ////     float       def;
    ////     int         men;
    ////     float       mov;
    ////     float       mor;
    ////     int          id;
    ////     unsigned int  x; ///pos
    ////     unsigned int  y;
    ////     int      player;
    ////     Unit*   class_d;
    //// };

    //// struct MapData {
    ////     unsigned int width;
    ////     unsigned int height;
    ////     //...
    //// };
protected:
};

#endif /*DATA_HPP*/