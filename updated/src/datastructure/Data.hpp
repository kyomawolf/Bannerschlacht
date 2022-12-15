#ifndef DATA_HPP
#define DATA_HPP

#include "BaseData.hpp"
#include "../ui/Ui.hpp"
#include "../Scene.hpp"
#include "../units/Unit.hpp"
class Scene;

class Data {
public:
private:

// make sure to call Window.init()
    raylib::Window*                 _window{nullptr};
    std::vector<raylib::Image>      imageCollection;
    std::vector<raylib::Texture>    textureCollection;
    std::vector<MapData>            mapCollection;
    std::vector<Unit>               unitCollection{};
    std::vector<TileData>           vecTiles;
    std::vector<Scene*>             vecScenes; //TODO make private

    static Data instance;

public:
    //all data will be held here
    //use generator function to create pointer to DataLinkobject
    //use generator function to create a vector list of all pointer of same classtype
    //TODO make private
    Scene& getSceneByEnum(scenes type);

    [[nodiscard]] raylib::Window* GetWindow() const;

    bool     InitWindow(int width, int height, const std::string& title);

    [[nodiscard]] const std::vector<raylib::Image> &GetImageCollection() const;

    [[nodiscard]] const std::vector<raylib::Texture> &GetTextureCollection() const;

    void AddTextureCollection(raylib::Texture &textureCollection);

    [[nodiscard]] const std::vector<Scene*> &GetVecScenes() const;

    void AddVecScenes(Scene* scene);

    void AddImageCollection(raylib::Image &imageCollection);

    Data();
    ~Data();

    static Data &GetInstance();

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