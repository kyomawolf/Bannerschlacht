#include "raylib-cpp.hpp"
#include "Ui.hpp"
#include "Vector2.hpp"
#include <functional>
#include <map>

#include "EventHandlerType.hpp"

class ObjectLayer {
private:
    ObjectLayer*        _parent;
    ObjectLayer*        _child;
    EventHandlerType*   _eventHandlerType;
public:
    ObjectLayer();
    explicit ObjectLayer(ObjectLayer* initParent, ObjectLayer* initChild = nullptr);
    ~ObjectLayer() = default;

    void SetEventHandler(EventHandlerType* initEHT);
    void SetChild(ObjectLayer *child);

    void CallEvent();
};