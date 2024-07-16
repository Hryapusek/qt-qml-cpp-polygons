import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.15
import QtQuick.Controls.Styles 1.4

Button {

    property bool isActive: false
    property string buttonText: ""

    signal toggled(isActibe: bool)

    onClicked: {
        isActive = !isActive;
        toggled(isActive)
    }

    style: ButtonStyle {
        background: Rectangle {
            border.width: isActive ? 3 : 1
            border.color: "white"
            radius: 4
            color:  isActive ? Qt.darker("gray") : "gray";
        }

        label: Text {
            color: "white"
            text: buttonText
            font.bold: true
            font.pointSize: 14
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
