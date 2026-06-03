import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: sidebar;
    width: 200;
    height: parent.height;
    color: "#050505";

    Column {
        id: sidebarEntries;
        anchors.top: parent.top;
        anchors.horizontalCenter: parent.horizontalCenter;
        spacing: 4;
        topPadding: 20;

        SidebarEntry {
            textContent: "Songs";
            active: true;
        }
        SidebarEntry {
            textContent: "Albums";
            active: false;
        }
        SidebarEntry {
            textContent: "Artists";
            active: false;
        }
    }
}