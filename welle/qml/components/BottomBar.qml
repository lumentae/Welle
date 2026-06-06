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
        uniformCellWidths: true

        RowLayout {
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.leftMargin: 16
            spacing: 8

            Image {
                source: playingSong.coverArt
                sourceSize.width: 80
                sourceSize.height: 80
                asynchronous: true
            }
            ColumnLayout {
                Layout.fillWidth: true
                spacing: 4
                Text {
                    text: playingSong.title.length > 60
                        ? playingSong.title.slice(0, 60) + "..."
                        : playingSong.title;
                    color: primaryTextColor;
                    font.pixelSize: Qt.application.font.pixelSize + 2;
                    elide: Text.ElideRight
                }
                Text {
                    text: playingSong.artist.length > 70
                        ? playingSong.artist.slice(0, 70) + "..."
                        : playingSong.artist;
                    color: secondaryTextColor;
                    font.pixelSize: Qt.application.font.pixelSize;
                    elide: Text.ElideRight
                }
                Text {
                    text: playingSong.album.length > 70
                        ? playingSong.album.slice(0, 70) + "..."
                        : playingSong.album;
                    color: secondaryTextColor;
                    font.pixelSize: Qt.application.font.pixelSize;
                    elide: Text.ElideRight
                }
            }
        }

        Item {
            Layout.column: 1
            Layout.fillWidth: true
            Layout.fillHeight: true

            Row {
                anchors.centerIn: parent
                width: parent.width - 32
                spacing: 8

                Text {
                    text: "0:00"
                    color: primaryTextColor
                    width: 36
                    horizontalAlignment: Text.AlignLeft
                    anchors.verticalCenter: parent.verticalCenter
                }
                Rectangle {
                    width: parent.width - 36 - 36 - 16
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
                    width: 36
                    horizontalAlignment: Text.AlignRight
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        Item {
            Layout.column: 2
            Layout.fillWidth: true
            Layout.fillHeight: true

            Row {
                anchors.right: parent.right
                anchors.rightMargin: 16
                anchors.verticalCenter: parent.verticalCenter
                spacing: 8

                Text {
                    text: "Right"
                    color: primaryTextColor
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }
}