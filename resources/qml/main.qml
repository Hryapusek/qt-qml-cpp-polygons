import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.9
import Shapes 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600

    RowLayout {
        id: mainLayout
        anchors.fill: parent

        CustomScene {
            id: customScene
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width - sidePanel.width
        }

        Rectangle {
            id: sidePanel
            color: "lightgray"
            Layout.fillHeight: true
            Layout.minimumWidth: (parent.width / 8) > builderInstrument.width + 10 ? (parent.width / 8) : builderInstrument.width + 10
            Row {
                ToggleButton {
                    id: builderInstrument
                    buttonText: qsTr("Полигон")
                }
            }

            // You can add more UI components here for the side panel
        }
    }

    Component.onCompleted: {
        // Add PolygonBuilder item to the scene
        var ellipse = Qt.createQmlObject('import QtQuick 2.15; import Shapes 1.0; DraggableEllipse { x: 100; y: 100; radius: 50; pointIndex: 1 }', customScene);
        customScene.addItem(ellipse);
    }
}
