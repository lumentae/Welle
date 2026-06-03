import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Row {
    anchors.fill: parent;

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
                textContent: "Home";
                active: true;
            }
            SidebarEntry {
                textContent: "Home";
                active: false;
            }
            SidebarEntry {
                textContent: "Home";
                textColor: "blue"
                active: false;
            }
            SidebarEntry {
                textContent: "Home";
                active: false;
            }
        }
    }
}