import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4

Button {

    property bool isActive: false
    property string buttonText: ""

    onClicked: {
        isActive = !isActive;
    }

    style: ButtonStyle {
        id: btnStyle
        background: Rectangle {
            border.width: isActive ? 3 : 1
            border.color: "white"
            radius: 4
            color:  isActive ? Qt.darker("gray") : "gray";
        }

        label: Text {
            id: textLabel
            color: "white"
            text: buttonText
            font.bold: true
            font.pointSize: 14
        }
    }
}
