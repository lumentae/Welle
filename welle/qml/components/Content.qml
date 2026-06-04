import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../pages"

Rectangle {
    id: content;
    color: "transparent";
    property alias loader: loader;

    Loader {
        anchors.fill: parent
        id: loader;
    }
}