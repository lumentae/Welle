import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    width: sidebar.width;
    height: 48;

    property string textContent: "";
    property string textColor: "white";
    property bool active: false;
    signal clicked;

    Rectangle {
        anchors.centerIn: parent;
        width: sidebar.width;
        height: parent.height;
        color: (active || mouseArea.containsMouse) ? primaryColorSelected : "transparent";

        Behavior on color { ColorAnimation { duration: 100; }}

        RowLayout {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft;
            anchors.fill: parent;

            Row {
                Layout.leftMargin: 16;
                spacing: 16;

                Rectangle {
                    width: 24;
                    height: 24;
                    color: "white";
                }
                Text {
                    height: 24;
                    text: textContent;
                    color: active ? accentColor : textColor ? textColor : "white";
                    verticalAlignment: Text.AlignVCenter;

                    Behavior on color { ColorAnimation { duration: 100; }}
                }
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: () => {
            parent.clicked();
        }
    }
}