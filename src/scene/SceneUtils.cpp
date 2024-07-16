#include "scene/SceneUtils.h"

namespace
{
    template < class Iterator_t >
    std::vector<const PolygonItem *> filterPolygons(Iterator_t begin, Iterator_t end)
    {
        std::vector<const PolygonItem *> polygonsPointers;
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

std::unique_ptr<SceneUtils> SceneUtils::m_instance;
std::mutex SceneUtils::m_mutex;

std::vector<const PolygonItem *> SceneUtils::getOnlyPolygons(CustomScene *scene)
{
    auto items = scene->getItems();
    return filterPolygons(items.begin(), items.end());
}

SceneUtils *SceneUtils::instance()
{
    if (not m_instance)
    {
        std::unique_lock lock(m_mutex);
        if (not m_instance)
        {
            m_instance = std::make_unique<SceneUtils>();
        }
    }
    return m_instance.get();
}
