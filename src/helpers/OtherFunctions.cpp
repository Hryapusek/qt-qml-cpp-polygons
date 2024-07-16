#include "helpers/OtherFunctions.h"
#include "scene/SceneUtils.h"
#include "json/JsonUtils.h"

#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QTextStream>

std::unique_ptr<OtherFunctions> OtherFunctions::m_instance;
std::mutex OtherFunctions::m_mutex;


void OtherFunctions::loadPolygonsFromJson(CustomScene *scene)
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open Json"), "", tr("Json files (*.json)"));
    qDebug() << "filename: " << fileName;
    if (fileName.isEmpty())
    {
        qDebug() << "Open operation canceled";
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Couldn't open file for reading:" << fileName;
        return;
    }

    QTextStream in(&file);
    QString jsonString = in.readAll();
    file.close();

    Json::CharReaderBuilder readerBuilder;
    Json::Value root;
    std::string errs;

    std::istringstream s(jsonString.toStdString());
    bool parsingSuccessful = Json::parseFromStream(readerBuilder, s, &root, &errs);
    if (!parsingSuccessful)
    {
        qWarning() << "Failed to parse JSON: " << QString::fromStdString(errs);
        return;
    }

    std::vector<std::unique_ptr<PolygonItem>> polygons = json::JsonUtils::instance()->fromJson(root);

    // Add the loaded polygons to the scene
    for (auto &polygon : polygons)
    {
        scene->addItem(polygon.release());
    }

    qDebug() << "Polygons loaded from" << fileName;
}

void OtherFunctions::savePolygonsInJson(CustomScene *scene)
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Save Json"), "", tr("Json files (*.json)"));
    qDebug() << "filename: " << fileName;
    if (fileName.isEmpty())
    {
        qDebug() << "Save operation canceled";
        return;
    }

    std::vector<const PolygonItem *> polygons = SceneUtils::instance()->getOnlyPolygons(scene);
    
    Json::Value root = json::JsonUtils::instance()->toJson(polygons);

    Json::StreamWriterBuilder writer;
    std::string jsonString = Json::writeString(writer, root);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning() << "Couldn't open file for writing:" << fileName;
        return;
    }

    file.write(jsonString.c_str());
    file.close();

    qDebug() << "Polygons saved to" << fileName;
}

OtherFunctions *OtherFunctions::instance()
{
    if (not m_instance)
    {
        std::unique_lock lock(m_mutex);
        if (not m_instance)
        {
            m_instance = std::make_unique<OtherFunctions>();
        }
    }
    return m_instance.get();
}
