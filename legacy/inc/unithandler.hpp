#include "unit.hpp"
#include <raylib.h>

class unithandler {
    private:
    unit    (*list)[64];
    public:
    //inits list, and puts a null-unit at the first position of the list. if data requested from this unit, it will return 0 values instead
    unithandler();
    ~unithandler();

    //returns id
    int     add_unit(int type);
    void    remove_unit(int id);
    //returns a referenced unit (null-unit if none is at the requested position)
    unit&   get_unit_by_position(Vec2D  pos);
    //returns a referenced unit (null-unit if no unit with that id exists)
    unit&   get_unit_position_by_id(int id);
    
    //wrapper functions. no unit memberfunctions will be called directly, but instead called by the handler
    //returns the id of the unit
    int     get_id_by_unit(const unit& object);
    //returns the units position
    Vec2D   get_position_by_unit(const unit &object);
};