#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include "shapes/PolygonItem.h"
#include "json/json.h"
#include "scene/CustomScene.h"
#include <string>
#include <mutex>

namespace json
{
    class JsonUtils
    {
        Json::Value toJson(std::vector<const PolygonItem *> polygonsPointers);
        std::vector<std::unique_ptr<PolygonItem>> fromJson(const Json::Value &value);

        static JsonUtils *instance();

    private:
        static std::unique_ptr<JsonUtils> m_instance;
        static std::mutex m_mutex;
    };
}

#endif
