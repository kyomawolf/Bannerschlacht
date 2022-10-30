#pragma once

class EventHandlerType {
protected:
    bool _active;
public:
    EventHandlerType();
    virtual ~EventHandlerType();
    bool IsActive();
    void EnableHandler();
    void DisableHandler();
    virtual bool Handler() = 0;
};