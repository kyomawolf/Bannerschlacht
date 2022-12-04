#include "ObjectLayer.hpp"

ObjectLayer::ObjectLayer() : _parent(nullptr), _child(nullptr), _eventHandlerType(nullptr) {}

ObjectLayer::ObjectLayer(ObjectLayer *initParent, ObjectLayer *initChild) : _parent(initParent), _child(initChild), _eventHandlerType(nullptr) {}



void ObjectLayer::SetEventHandler(EventHandlerType *initEHT) {
    _eventHandlerType = initEHT;
}

void ObjectLayer::CallEvent() {
    if (_eventHandlerType->IsActive()) {
        if (!_eventHandlerType->Handler() && _child != nullptr) {
            _child->CallEvent();
        }
    }
    else if (_child != nullptr)
        _child->CallEvent();
}

void ObjectLayer::SetChild(ObjectLayer *child) {
    _child = child;
}
