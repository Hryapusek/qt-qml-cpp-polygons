#ifndef OTHER_FUNCTIONS_H
#define OTHER_FUNCTIONS_H

#include <memory>
#include <mutex>

#include <QObject>

#include "scene/CustomScene.h"

class OtherFunctions : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void loadPolygonsFromJson(CustomScene *scene);
    Q_INVOKABLE void savePolygonsInJson(CustomScene *scene);
    static OtherFunctions *instance();

private:
    static std::unique_ptr<OtherFunctions> m_instance;
    static std::mutex m_mutex;
};

#endif
