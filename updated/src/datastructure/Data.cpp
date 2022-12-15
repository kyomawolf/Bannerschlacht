
#include "Data.hpp"

Data    Data::instance = Data();

Data::Data() {
    _window = new raylib::Window();
}

Data::~Data() {

}

Scene & Data::getSceneByEnum(scenes type) {
    for (auto & i: vecScenes)
        if (i->GetSceneType() == type)
            return *i;
    return *vecScenes.front();
}

raylib::Window* Data::GetWindow() const {
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

const std::vector<Scene*> &Data::GetVecScenes() const {
    return vecScenes;
}

void Data::AddVecScenes(Scene* scene) {
    vecScenes.insert(vecScenes.end(), scene);
}

Data &Data::GetInstance() {
    return instance;
}

bool Data::InitWindow(int width, int height, const std::string &title) {
    _window->Init(width, height, title);
    while (!raylib::Window::IsReady());
    return true;
}

