
#ifndef CLIENTLOC_SERIALIZER_H
#define CLIENTLOC_SERIALIZER_H

#include <string>
#include <nlohmann/json.hpp>

#include "graphicsItem.h"
//#include "canvasController.h"


class Serializer {
public:

    static std::string serializeDiff(const std::vector<GraphicsItem>& graphicsItems, unsigned int canvasId);

    static void parseDiff(const std::string& inJson_str, std::vector<GraphicsItem>& itemsToDisplay);

    static int parseId(const std::string &inJson_str);

private:

};

#endif //CLIENTLOC_SERIALIZER_H
