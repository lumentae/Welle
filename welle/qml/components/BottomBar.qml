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

            ColumnLayout {
                width: parent.width
                anchors.centerIn: parent
                spacing: 4

                RowLayout {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 36
                    spacing: 4

                    // margin left
                    Rectangle {
                        color: "transparent"
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }

                    // Previous button
                    RoundButton {
                        implicitWidth: parent.height
                        implicitHeight: parent.height
                        onClicked: {
                            playingSong.previous()
                        }
                        contentItem: Text {
                            font.family: "Material Symbols Rounded"
                            font.pixelSize: 24
                            text: "\ue045"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: primaryTextColor
                        }
                        background: Rectangle {
                            color: "transparent"
                            implicitWidth: parent.width
                            implicitHeight: parent.height
                            radius: parent.height / 2
                        }
                    }

                    // Pause/play button
                    RoundButton {
                        implicitWidth: parent.height
                        implicitHeight: parent.height
                        onClicked: {
                            playingSong.playOrPause()
                        }
                        contentItem: Text {
                            font.family: "Material Symbols Rounded"
                            font.pixelSize: 24
                            text: playingSong.paused ? "\ue034" : "\ue037"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        background: Rectangle {
                            color: "white"
                            implicitWidth: parent.width
                            implicitHeight: parent.height
                            radius: parent.height / 2
                        }
                    }

                    // Next button
                    RoundButton {
                        implicitWidth: parent.height
                        implicitHeight: parent.height
                        onClicked: {
                            playingSong.next()
                        }
                        contentItem: Text {
                            font.family: "Material Symbols Rounded"
                            font.pixelSize: 24
                            text: "\ue044"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: primaryTextColor
                        }
                        background: Rectangle {
                            color: "transparent"
                            implicitWidth: parent.width
                            implicitHeight: parent.height
                            radius: parent.height / 2
                        }
                    }

                    // margin right
                    Rectangle {
                        color: "transparent"
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
                Row {
                    Layout.fillWidth: true
                    Layout.leftMargin: 16
                    Layout.rightMargin: 16
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
                        id: seekBar
                        width: parent.width - 36 - 36 - 16
                        height: 8
                        radius: 3
                        anchors.verticalCenter: parent.verticalCenter
                        color: secondaryTextColor

                        Rectangle {
                            id: progressBar
                            width: 0
                            height: parent.height
                            radius: parent.radius
                            color: primaryTextColor

                            Connections {
                                target: playingSong
                                function onPositionChanged() {
                                    if (!seekMouseArea.pressed) {
                                        progressBar.width = playingSong.duration > 0
                                            ? (playingSong.position / playingSong.duration) * seekBar.width
                                            : 0
                                    }
                                }
                            }

                            Behavior on width {
                                enabled: !seekMouseArea.pressed
                                NumberAnimation { duration: 100; easing.type: Easing.Linear; }
                            }
                        }

                        MouseArea {
                            id: seekMouseArea
                            anchors.fill: parent
                            onClicked: (mouse) => {
                                playingSong.setPosition(mouse.x / parent.width * playingSong.duration)
                            }
                            onPressed: (mouse) => {
                                progressBar.width = Math.max(0, Math.min(mouse.x, seekBar.width))
                            }
                            onPositionChanged: (mouse) => {
                                progressBar.width = Math.max(0, Math.min(mouse.x, seekBar.width))
                            }
                            onReleased: {
                                playingSong.setPosition(progressBar.width / seekBar.width * playingSong.duration)
                            }
                        }
                    }
                    Text {
                        text: {
                            const m = Math.floor(playingSong.duration / 60)
                            const s = playingSong.duration % 60
                            return m + ":" + (s < 10 ? "0" + s : s)
                        }
                        color: primaryTextColor
                        width: 36
                        horizontalAlignment: Text.AlignRight
                        anchors.verticalCenter: parent.verticalCenter
                    }
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