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
                    Layout.fillWidth: true
                    text: playingSong.title
                    color: primaryTextColor
                    font.pixelSize: Qt.application.font.pixelSize + 2
                    elide: Text.ElideRight
                    maximumLineCount: 1
                }
                Text {
                    Layout.fillWidth: true
                    text: playingSong.artist
                    color: secondaryTextColor;
                    font.pixelSize: Qt.application.font.pixelSize;
                    elide: Text.ElideRight
                    maximumLineCount: 1
                }
                Text {
                    Layout.fillWidth: true
                    text: playingSong.album;
                    color: secondaryTextColor;
                    font.pixelSize: Qt.application.font.pixelSize;
                    elide: Text.ElideRight
                    maximumLineCount: 1
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
                    text: {
                        const total = Math.floor(playingSong.position)
                        const m = Math.floor(total / 60)
                        const s = total % 60
                        return m + ":" + (s < 10 ? "0" + s : s)
                    }
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

                    Rectangle {
                        width: playingSong.duration > 0
                            ? (playingSong.position / playingSong.duration) * parent.width
                            : 0
                        height: parent.height
                        radius: parent.radius
                        color: primaryTextColor

                        Behavior on width {
                            NumberAnimation { duration: 100; easing.type: Easing.Linear; }
                        }

                        DragHandler {}
                    }

                    MouseArea {
                        width: parent.width
                        height: parent.height

                        onClicked: (mouse) => {
                            playingSong.setPosition(mouse.x / parent.width * playingSong.duration)
                        }
                    }
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