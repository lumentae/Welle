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

        Image {
            source: songModel.currentCoverArt
            width: 48
            height: 48
            asynchronous: true
        }

        ColumnLayout {
            Layout.leftMargin: 16
            Layout.fillHeight: true
            spacing: 6
            Text {
                color: primaryTextColor
                text: songModel.currentSong
            }
            Text {
                color: primaryTextColor
                text: songModel.currentArtist
            }
            Text {
                color: primaryTextColor
                text: songModel.currentAlbum
            }
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