
#include "Data.hpp"

Data    Data::instance = Data();

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

const std::vector<raylib::Texture> &Data::GetTextureCollection() const {
    return textureCollection;
}

void Data::AddTextureCollection(raylib::Texture &texture) {
    textureCollection.insert(textureCollection.end(), std::move(texture));
}

const std::vector<std::unique_ptr<Scene>> & Data::GetVecScenes() const {
    return vecScenes;
}

void Data::AddVecScenes(std::unique_ptr<Scene> scene) {
    vecScenes.insert(vecScenes.end(), std::move(scene));
}

Data &Data::GetInstance() {
    return instance;
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
    unitCollection.push_back(std::move(unitToAdd));
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

void Data::AddMapToCollection(MapData &mapToAdd) {
    this->mapCollection.push_back(mapToAdd);
}

MapData &Data::GetMapDataByIdx(size_t idx) {
    return this->mapCollection.at(idx);
}

//void Data::SetMapCollection(const std::vector<MapData> &mapCollection) {
//    Data::mapCollection = mapCollection;
//}

