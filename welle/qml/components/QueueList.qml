import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: queueList;
    width: 400;
    height: parent.height;
    color: secondaryColor;

    property var selectedEntry;

    ColumnLayout {
        anchors.fill: parent
        id: queueListEntries;
        spacing: 4;

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: queueListView
            model: queueListModel
            clip: true

            delegate: Rectangle {
                width: ListView.view.width
                height: 56
                color: mouseArea.containsMouse ? secondaryColorSelected : secondaryColor

                Behavior on color { ColorAnimation { duration: 50 }}

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 16
                    width: parent.width
                    height: 56
                    spacing: 12

                    Image {
                        source: coverArt
                        asynchronous: true
                        sourceSize.width: 56
                        sourceSize.height: 56
                    }
                    ColumnLayout {
                        Layout.fillWidth: true
                        Text {
                            Layout.fillWidth: true
                            text: title
                            color: primaryTextColor
                            font.pixelSize: 12
                            elide: Text.ElideRight
                            maximumLineCount: 1
                        }
                        Text {
                            Layout.fillWidth: true
                            text: artist
                            color: secondaryTextColor
                            font.pixelSize: 10
                            elide: Text.ElideRight
                            maximumLineCount: 1
                        }
                    }
                    Text {
                        Layout.rightMargin: 16
                        text: {
                            const m = Math.floor(duration / 60);
                            const s = duration % 60;
                            return m + ":" + (s < 10 ? "0" + s : s)
                        }
                        color: secondaryTextColor
                        font.pixelSize: 10
                    }
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: (mouse) => {
                        if (mouse.button === Qt.RightButton) {
                            contextMenu.songIndex = songIndex
                            contextMenu.popup()
                        } else {
                            queueListModel.play(songIndex)
                        }
                    }
                }
            }

            Menu {
                id: contextMenu
                property int songIndex: -1

                MenuItem {
                    text: "Remove from queue"
                    onClicked: {
                        queueListModel.remove(songIndex)
                    }
                }
            }
        }
    }
}