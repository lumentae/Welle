import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "./components"

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600
    title: "Welle"
    color: "#0f0f0f"

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Sidebar {
            Layout.preferredWidth: 200
            Layout.fillHeight: true
        }
        Content {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}