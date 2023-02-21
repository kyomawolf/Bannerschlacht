
#include "Data.hpp"

Data    Data::_instance = Data();
int     Data::_mapIndex = 0;

Data::Data() {
    _window = std::make_unique<raylib::Window>();
}

Data::~Data() {

}

Scene & Data::getSceneByEnum(scenes type) {
    for (auto & i: vecScenes)
        if (i->GetSceneType() == type)
            return *i;
    return *vecScenes.front();
}

std::unique_ptr<raylib::Window>& Data::GetWindow() {
    return _window;
}

const std::vector<raylib::Image> &Data::GetImageCollection() const {
    return imageCollection;
}

void Data::AddImageCollection(raylib::Image &image) {
    imageCollection.insert(imageCollection.end(), std::move(image));
}

const std::map<std::string, raylib::Texture&> &Data::GetTextureCollection() const {
    return textureCollection;
}

void Data::AddTextureCollection(std::string name, raylib::Texture& texture) {
    auto ins = std::pair<std::string, raylib::Texture&>(name, texture);
    textureCollection.insert(ins);
//    textureCollection.insert(textureCollection.end(), std::move(texture));
}

const std::vector<std::unique_ptr<Scene>> & Data::GetVecScenes() const {
    return vecScenes;
}

void Data::AddVecScenes(std::unique_ptr<Scene> scene) {
    vecScenes.insert(vecScenes.end(), std::move(scene));
}

Data &Data::GetInstance() {
    return _instance;
}

bool Data::InitWindow(int width, int height, const std::string &title) {
    _window->Init(width, height, title);
    while (!raylib::Window::IsReady());
    return true;
}

const Setting &Data::GetGameSettings() const {
    return gameSettings;
}

void Data::SetGameSettings(const Setting &settings) {
    Data::gameSettings = settings;
}

const std::vector<std::shared_ptr<UnitData>> &Data::GetUnitCollection() const {
    return unitCollection;
}

void Data::SetUnitCollection(std::vector<std::shared_ptr<UnitData>> unitCollectionNew) {
    Data::unitCollection = std::move(unitCollectionNew);
}

void Data::AddUnitToCollection(std::shared_ptr<UnitData> &unitToAdd) {
    unitCollection.push_back(unitToAdd);
}

int Data::DefaultAddUnit() {
    std::shared_ptr<Unit> newUnit;
    std::shared_ptr<UnitData> unitToAdd;
    int id = 0;
    for (auto &i: unitCollection){
        if (i->GetId() > id)
            id = i->GetId() + 1;
    }
    unitToAdd->SetMapUnit(newUnit);
    unitToAdd->SetId(id);
    this->AddUnitToCollection(unitToAdd);
    return id;
}


/* returns UnitData-reference by ID; if ID doesn't exist, it returns the 'null' unitdata, has an id of -1*/
std::shared_ptr<UnitData> &Data::GetUnit(int id) {
    for (auto &i: unitCollection){
        if (id == i->GetId())
            return i;
    }
    return unitCollection.front();
}

const std::vector<MapData> &Data::GetMapCollection() const {
    return mapCollection;
}

int Data::AddMapToCollection(MapData &mapToAdd) {
    mapToAdd.SetIndex(_mapIndex);
    this->mapCollection.push_back(mapToAdd);
    return _mapIndex++;
}

MapData &Data::GetMapDataByIdx(size_t idx) {
    return this->mapCollection.at(idx);
}

void Data::ClearUnits() {
    unitCollection.clear();
}

raylib::Texture &Data::GetTexture(std::string& key) const {
    return textureCollection.find(key)->second;
}

std::shared_ptr<UnitData> Data::GetUnitByLocation(TileIdx index) {
    for (auto &i : unitCollection) {
        if (i != nullptr && i->GetX() == index.x && i->GetY() == index.y)
            return i;
    }
    return nullptr;
}

const Data::InputCollection &Data::GetInput() const {
    return _input;
}

void Data::SetInput() {
    if (raylib::Mouse::IsButtonPressed(0))
        _input.mouseButton = 1;
    else if (raylib::Mouse::IsButtonPressed(1))
        _input.mouseButton = 2;
    else
        _input.mouseButton = 0;
    if (IsKeyDown(KEY_LEFT_SHIFT))
        _input.pressedKey = KEY_LEFT_SHIFT;
    else if (IsKeyDown(KEY_LEFT_CONTROL))
        _input.pressedKey = KEY_LEFT_CONTROL;
    else
        _input.pressedKey = KEY_NULL;
}

std::shared_ptr<Player> Data::GetPlayerById(int id) {
    for (auto &i : playerCollection) {
        if (i->GetId() == id)
            return i;
    }
    return nullptr;
}

std::vector<std::shared_ptr<Player>> &Data::GetPlayerCollection()  {
    return playerCollection;
}

void Data::AddPlayerToCollection(std::shared_ptr<Player> &singlePlayer) {
    Data::playerCollection.emplace_back(singlePlayer);
}

void    Data::UpdatePathfinder() {
    // pathCollection.UpdatePathfinder();
}

Pathfinder& Data::GetPathfinder() {

}

//void Data::SetMapCollection(const std::vector<MapData> &mapCollection) {
//    Data::mapCollection = mapCollection;
//}

