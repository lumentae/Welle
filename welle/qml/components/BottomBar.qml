import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: bottomBar
    width: parent.width
    height: 90
    color: primaryColor

    Rectangle {
        width: parent.width
        height: 1
        color: borderColor
        anchors.top: parent.top
    }

    GridLayout {
        anchors.fill: parent
        columns: 3
        columnSpacing: 0
        rowSpacing: 0

        RowLayout {
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.leftMargin: 16
            spacing: 8

            Image {
                source: playingSong.coverArt
                sourceSize.width: 48
                sourceSize.height: 48
                asynchronous: true
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 4
                Text { text: playingSong.title;  color: primaryTextColor;   font.pixelSize: Qt.application.font.pixelSize + 2; elide: Text.ElideRight }
                Text { text: playingSong.artist; color: secondaryTextColor; font.pixelSize: Qt.application.font.pixelSize;     elide: Text.ElideRight }
                Text { text: playingSong.album;  color: secondaryTextColor; font.pixelSize: Qt.application.font.pixelSize;     elide: Text.ElideRight }
            }
        }

        Row {
            Layout.column: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            spacing: 8

            Text {
                text: "0:00"
                color: primaryTextColor
                width: 40
                horizontalAlignment: Text.AlignLeft
                anchors.verticalCenter: parent.verticalCenter
            }
            Rectangle {
                width: parent.width - 200 - 40 - 16
                height: 8
                radius: 3
                anchors.verticalCenter: parent.verticalCenter
                color: secondaryTextColor
            }
            Text {
                text: {
                    const m = Math.floor(playingSong.duration / 60)
                    const s = playingSong.duration % 60
                    return m + ":" + (s < 10 ? "0" + s : s)
                }
                color: secondaryTextColor
                width: 40
                horizontalAlignment: Text.AlignRight
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Item {
            Layout.column: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            Text {
                anchors.right: parent.right
                anchors.rightMargin: 16
                anchors.verticalCenter: parent.verticalCenter
                text: "Right"
                color: primaryTextColor
            }
        }
    }
}