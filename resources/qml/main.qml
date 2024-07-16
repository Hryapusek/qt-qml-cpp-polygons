import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.9
import Shapes 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600

    property PolygonBuilder polygonBuilder: PolygonBuilder {
        id: builder
        onPolygonCreated: (polygon) => {
                              // Add PolygonBuilder item to the scene
                              var ellipse = Qt.createQmlObject('import QtQuick 2.15; import Shapes 1.0; PolygonItem { scene: customScene }', customScene);
                              ellipse.polygon = polygon
                              console.log(`Created object ${ellipse}`)
                              customScene.addItem(ellipse)
                              customScene.update()
                              builderInstrument.isActive = false
                              builderInstrument.update()
                          }
    }

    property PolygonPointModel pointsModel: PolygonPointModel {
        id: pointModel
    }

    RowLayout {
        id: mainLayout
        anchors.fill: parent

        CustomScene {
            id: customScene
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width - sidePanel.width
            onItemAdded: (item) => {
                             pointModel.connectPolygon(item)
                             item.itemSelected(item)
                         }
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
                    onToggled: (isActive) => {
                        if (isActive) {
                            console.log("Enabling builder")
                            customScene.addItem(builder)
                        }
                        else {
                            console.log("Disabling builder")
                            customScene.releaseItem(builder)
                        }
                    }
                }
            }

            Row {
                TableView {
                    id: tableView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: pointModel
                    anchors.margins: 10
                }
            }

            // You can add more UI components here for the side panel
        }
    }
}
