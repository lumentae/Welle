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
    color: primaryColor

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            Sidebar {
                Layout.preferredWidth: 200
                Layout.fillHeight: true
            }
            Content {
                id: mainContent
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
        BottomBar {
            Layout.fillWidth: true
            Layout.preferredHeight: 90
        }
    }

    FontLoader {
        source: "qrc:/qt/qml/welle/external/MaterialSymbols/MaterialSymbols.ttf"
    }
}