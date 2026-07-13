import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: sidebar;
    width: 200;
    height: parent.height;
    color: secondaryColor;

    property var selectedEntry;

    ColumnLayout {
        id: sidebarEntries;
        anchors.fill: parent;
        anchors.topMargin: 10;
        spacing: 4;

        SidebarEntry {
            textContent: "Home";
            active: selectedEntry === textContent;
            onClicked: () => {
                sidebar.selectedEntry = textContent;
                mainContent.loader.setSource("qrc:/qt/qml/welle/qml/pages/Home.qml");
            }
        }
        SidebarEntry {
            textContent: "Songs";
            active: selectedEntry === textContent;
            onClicked: () => {
                sidebar.selectedEntry = textContent;
                mainContent.loader.setSource("qrc:/qt/qml/welle/qml/pages/Songs.qml");
            }
        }
        SidebarEntry {
            textContent: "Albums";
            active: selectedEntry === textContent;
            onClicked: () => {
                sidebar.selectedEntry = textContent;
                mainContent.loader.setSource("qrc:/qt/qml/welle/qml/pages/Albums.qml");
            }
        }
        SidebarEntry {
            textContent: "Artists";
            active: selectedEntry === textContent;
            onClicked: () => {
                sidebar.selectedEntry = textContent;
                mainContent.loader.setSource("qrc:/qt/qml/welle/qml/pages/Artists.qml");
            }
        }

        Rectangle {
            Layout.fillWidth: true;
            Layout.preferredHeight: 1;
            color: borderColor
        }

        ListView {
            Layout.fillWidth: true;
            Layout.fillHeight: true;
            model: playlistModel
            clip: true
            spacing: 10

            delegate: Rectangle {
                width: ListView.view.width
                height: 56
                color: "transparent"

                RowLayout {
                    width: parent.width
                    height: parent.height
                    spacing: 4

                    Rectangle {
                        // margin
                        Layout.fillHeight: true
                        width: 4
                        color: "transparent"
                    }
                    Image {
                        source: coverArt
                        asynchronous: true
                        sourceSize.width: 48
                        sourceSize.height: 48
                    }
                    Rectangle {
                        // margin
                        Layout.fillHeight: true
                        width: 1
                        color: "transparent"
                    }
                    ColumnLayout {
                        Layout.fillWidth: true
                        Text {
                            text: title
                            color: primaryTextColor
                            font.pixelSize: 13
                            elide: Text.ElideRight
                            maximumLineCount: 1
                            Layout.fillWidth: true
                        }
                        Text {
                            text: artist
                            color: secondaryTextColor
                            font.pixelSize: 11
                            elide: Text.ElideRight
                            maximumLineCount: 1
                            Layout.fillWidth: true
                        }
                    }
                    Rectangle {
                        // margin
                        Layout.fillHeight: true
                        width: 1
                        color: "transparent"
                    }
                }
            }
        }
    }
}