import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import Shapes 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600

    CustomScene {
        id: customScene
        width: parent.width
        height: parent.height

        DraggableEllipse {
            id: ellipse
            x: 100
            y: 100
            radius: 10
            pointIndex: 0
            scene: customScene
        }
    }
}
