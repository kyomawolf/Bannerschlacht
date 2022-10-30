#include "EventHandlerType.hpp"

bool EventHandlerType::IsActive() {
    return _active;
}

void EventHandlerType::EnableHandler() {
    _active = true;
}

void EventHandlerType::DisableHandler() {
    _active = false;
}

EventHandlerType::EventHandlerType() : _active(false) { }

EventHandlerType::~EventHandlerType() { }

