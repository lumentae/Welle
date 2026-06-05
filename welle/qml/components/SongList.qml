import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ListView {
    anchors.fill: parent
    model: songModel
    clip: true

    delegate: Rectangle {
        width: ListView.view.width
        height: 56
        color: mouseArea.containsMouse ? primaryColorSelected : primaryColor

        Behavior on color { ColorAnimation { duration: 50 }}

        RowLayout {
            anchors.fill: parent
            width: parent.width
            height: 56
            spacing: 12

            Text {
                Layout.leftMargin: 16
                text: songIndex
                color: secondaryTextColor
                font.pixelSize: 13
                Layout.preferredWidth: 24
            }
            Image {
                source: coverArt
                asynchronous: true
                sourceSize.width: 56
                sourceSize.height: 56
            }
            Column {
                Layout.fillWidth: true
                Text {
                    text: title
                    color: primaryTextColor
                    font.pixelSize: 15
                }
                Text {
                    text: artist
                    color: secondaryTextColor
                    font.pixelSize: 13
                }
            }
            Text {
                text: album
                color: secondaryTextColor
                font.pixelSize: 13
            }
            Text {
                Layout.rightMargin: 16
                text: {
                    const m = Math.floor(duration / 60);
                    const s = duration % 60;
                    return m + ":" + (s < 10 ? "0" + s : s)
                }
                color: secondaryTextColor
                font.pixelSize: 13
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                songModel.play(songIndex)
            }
        }
    }

    onContentYChanged: {
        if (!songModel.isLoading && contentY + height >= contentHeight - 200)
            songModel.fetchNextPage()
    }

    footer: Item {
        width: parent.width
        height: 40
        visible: songModel.hasMore

        BusyIndicator {
            anchors.centerIn: parent
            running: songModel.isLoading
        }

        Component.onCompleted: songModel.fetchNextPage()
    }
}