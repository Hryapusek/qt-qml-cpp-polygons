#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include "shapes/PolygonItem.h"
#include "json/json.h"
#include "scene/CustomScene.h"
#include <string>

namespace json
{
    class JsonUtils
    {
        static Json::Value serializePolygons(CustomScene *scene);
    };
}

#endif
