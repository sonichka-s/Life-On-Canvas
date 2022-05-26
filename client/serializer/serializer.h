
#ifndef CLIENTLOC_SERIALIZER_H
#define CLIENTLOC_SERIALIZER_H

#include <string>
#include <nlohmann/json.hpp>


#include "graphicsItem.h"
//#include "canvasController.h"


class Serializer {
public:

    nlohmann::json serializeDiff(const std::vector<GraphicsItem>& lineItems, unsigned int canvasId);

    void parseCanvas(const std::string& inJson_str, std::vector<GraphicsItem>& itemsToDisplay);

    int parseId(std::string inJson_str);

private:

};

#endif //CLIENTLOC_SERIALIZER_H
