#ifndef SCENE_UTILS_H
#define SCENE_UTILS_H

#include "shapes/PolygonItem.h"
#include "scene/CustomScene.h"

#include <vector>
#include <mutex>

class SceneUtils
{
public:
    std::vector<const PolygonItem *> getOnlyPolygons(CustomScene *scene);

    static SceneUtils *instance();

private:
    static std::unique_ptr<SceneUtils> m_instance;
    static std::mutex m_mutex;
};

#endif
