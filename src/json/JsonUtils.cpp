#include "json/JsonUtils.h"
#include "shapes/PolygonItem.h"

namespace json
{
    std::unique_ptr<JsonUtils> JsonUtils::m_instance;
    std::mutex JsonUtils::m_mutex;

    Json::Value JsonUtils::toJson(std::vector<const PolygonItem *> polygonsPointers)
    {
        Json::Value value;
        value["polygons"] = Json::Value(Json::arrayValue);
        auto &polygonsJson = value["polygons"];
        for (auto polygonPtr : polygonsPointers)
        {
            polygonsJson.append(json::toJson(*polygonPtr));
        }
        return value;
    }

    std::vector<std::unique_ptr<PolygonItem>> json::JsonUtils::fromJson(const Json::Value &value)
    {
        std::vector<std::unique_ptr<PolygonItem>> polygonsPointers;
        auto &polygonsJson = value["polygons"];
        for (const auto &value : polygonsJson)
        {
            polygonsPointers.push_back(json::fromJson(value));
        }
        return polygonsPointers;
    }

    JsonUtils *json::JsonUtils::instance()
    {
        if (not m_instance)
        {
            std::unique_lock lock(m_mutex);
            if (not m_instance)
            {
                m_instance = std::make_unique<JsonUtils>();
            }
        }
        return m_instance.get();
    }
}
