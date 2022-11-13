
#include "Data.hpp"

BaseData* Data::FindNextIdent(Data::DataIndetify type, std::vector<DataLink>::difference_type index) {
    if (index >= vecLink.size())
        return nullptr;
    for (auto i = vecLink.begin() + index; i != vecLink.end(); i++) {
        if (i->indentifier == type)
            return i->classData;
    }
    return nullptr;
}

Data::Data() : vecLink(), vecUnits(), vecTiles(), _window(nullptr) {

}

Data::~Data() {

}

Scene * Data::getSceneByEnum(scenes type) {
    for (auto & i: vecScenes)
        if (i->sceneType == type)
            return i;
}

const raylib::Window* Data::GetWindow() const {
    return _window;
}

void Data::SetWindow(raylib::Window* window) {
    _window = window;
}