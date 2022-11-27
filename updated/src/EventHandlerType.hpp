#ifndef BANNERSCHLACHT_EVENTHANDLERTYPE_HPP
#define BANNERSCHLACHT_EVENTHANDLERTYPE_HPP

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
#endif
