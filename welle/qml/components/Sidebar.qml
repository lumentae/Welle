import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: sidebar;
    width: 200;
    height: parent.height;
    color: secondaryColor;

    property var selectedEntry;

    Column {
        id: sidebarEntries;
        anchors.top: parent.top;
        anchors.horizontalCenter: parent.horizontalCenter;
        spacing: 4;
        topPadding: 8;

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
    }
}