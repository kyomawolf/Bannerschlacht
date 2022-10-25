
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

Data::Data() : vecLink(), vecUnits(), vecTiles(), gameUi() {

}

Data::~Data() {

}

Data::Data(Ui initUi) : vecLink(), vecUnits(), vecTiles(), gameUi(initUi) {

}
