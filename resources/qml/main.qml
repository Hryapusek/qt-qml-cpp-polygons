import QtQuick 2.9
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.9
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.15
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
            Layout.minimumWidth: 140
            Row {
                leftPadding: 5
                rightPadding: 5
                ToggleButton {
                    id: builderInstrument
                    width: 120
                    buttonText: qsTr("Build")
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
                id: saveBtnRow
                leftPadding: 5
                rightPadding: 5
                y: builderInstrument.height
                Button {
                    id: saveBtn
                    text: qsTr("Save")
                    width: 120
                    background: Rectangle {
                        border.width: parent.pressed ? 3 : 1
                        border.color: "white"
                        radius: 4
                        color: parent.pressed ? Qt.darker("gray") : "gray";
                    }

                    contentItem: Text {
                        color: "white"
                        font.bold: true
                        font.pointSize: 14
                        text: parent.text
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.centerIn: parent
                    }

                    onClicked: () => {
                                   otherFunctions.savePolygonsInJson(customScene)
                               }
                }
            }

            Row {
                leftPadding: 5
                rightPadding: 5
                y: saveBtn.height + saveBtnRow.y
                Button {
                    text: qsTr("Load")
                    width: 120
                    background: Rectangle {
                        border.width: parent.pressed ? 3 : 1
                        border.color: "white"
                        radius: 4
                        color: parent.pressed ? Qt.darker("gray") : "gray";
                    }

                    contentItem: Text {
                        color: "white"
                        font.bold: true
                        font.pointSize: 14
                        text: parent.text
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.centerIn: parent
                    }

                    onClicked: () => {
                                   otherFunctions.loadPolygonsFromJson(customScene)
                               }
                }
            }

            // You can add more UI components here for the side panel
        }
    }
}
