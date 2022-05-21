
#ifndef CLIENTLOC_SERIALIZER_H
#define CLIENTLOC_SERIALIZER_H

#include <string>
#include <nlohmann/json.hpp>


#include "point.h"
//#include "canvasController.h"


class Serializer {
public:



    nlohmann::json serializeDiff(const std::vector<Point>& points, unsigned int canvasId);


    void parseCanvas(const std::string& inJson_str, std::vector<Point>& canvasArr);

    int parseId(std::string inJson_str);

private:

};

#endif //CLIENTLOC_SERIALIZER_H
