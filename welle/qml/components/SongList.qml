import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ListView {
    anchors.fill: parent
    model: songModel

    delegate: RowLayout {
        width: ListView.view.width
        height: 56
        spacing: 12

        Text {
            Layout.leftMargin: 16
            text: songIndex
            color: "#666"
            font.pixelSize: 13
            Layout.preferredWidth: 24
        }
        Column {
            Layout.fillWidth: true
            Text {
                text: title
                color: "#e0e0e0"
                font.pixelSize: 15
            }
            Text {
                text: artist
                color: "#666"
                font.pixelSize: 13
            }
        }
        Text {
            text: album
            color: "#666"
            font.pixelSize: 13
        }
        Text {
            Layout.rightMargin: 16
            text: {
                var m = Math.floor(duration / 60)
                var s = duration % 60
                return m + ":" + (s < 10 ? "0" + s : s)
            }
            color: "#666"
            font.pixelSize: 13
        }
    }
}