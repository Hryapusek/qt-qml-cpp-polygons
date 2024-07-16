#include "json/JsonUtils.h"
#include "shapes/PolygonItem.h"

namespace
{
    template < class Iterator_t >
    std::vector<PolygonItem *> filterPolygons(Iterator_t begin, Iterator_t end)
    {
        std::vector<PolygonItem *> polygonsPointers;
        for (auto it = begin; it != end; it++)
        {
            PolygonItem *polygonPtr = nullptr;
            if (not (polygonPtr = dynamic_cast<PolygonItem *>(*it)))
            {
                continue;
            }
            polygonsPointers.push_back(polygonPtr);
        }
        return polygonsPointers;
    }
}

namespace json
{
    Json::Value JsonUtils::serializePolygons(CustomScene * scene)
    {
        std::vector<PolygonItem *> polygonsPointers = filterPolygons(scene->getItems().begin(), scene->getItems().end());
    }
}
