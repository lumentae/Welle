import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "./components"

ApplicationWindow {
    id: root
    visible: true
    width: 400
    height: 800
    title: "Welle"

    color: "#0f0f0f"

    SongList {}
}