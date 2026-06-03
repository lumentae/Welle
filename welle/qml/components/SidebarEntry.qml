import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    width: sidebar.width;
    height: 48;

    property string textContent: "";
    property string textColor: "white";
    property bool active: false;

    Rectangle {
        anchors.centerIn: parent;
        width: sidebar.width;
        height: parent.height;
        color: (active || mouseArea.containsMouse) ? "#242424" : "transparent";

        Behavior on color { ColorAnimation { duration: 100; }}

        Row {
            spacing: 16;
            anchors.centerIn: parent;

            Rectangle {
                width: 24;
                height: 24;
                color: "white";
            }

            Text {
                height: 24;
                text: textContent;
                color: active ? "#ff0000" : textColor ? textColor : "white";
                verticalAlignment: Text.AlignVCenter;
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
    }
}