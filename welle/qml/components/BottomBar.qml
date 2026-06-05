import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: bottomBar
    width: parent.width
    height: 90
    color: primaryColor

    // Border
    Rectangle {
        width: parent.width
        height: 1
        color: borderColor
        anchors.top: parent.top
    }

    // Real content
    RowLayout {
        anchors.fill: parent
        spacing: 10

        Text {
            Layout.leftMargin: 16
            text: "Left"
        }

        Item { Layout.fillWidth: true }

        Text {
            text: "Center"
        }

        Item { Layout.fillWidth: true }

        Text {
            Layout.rightMargin: 16
            text: "Right"
        }
    }
}