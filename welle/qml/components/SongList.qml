import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ListView {
    anchors.fill: parent
    model: songModel

    delegate: Item {
        width: ListView.view.width
        height: 56

        Row {
            anchors.fill: parent
            anchors.margins: 12
            spacing: 12

            Text {
                text: title
                color: "#e0e0e0"
                font.pixelSize: 15
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                text: artist
                color: "#666"
                font.pixelSize: 15
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}