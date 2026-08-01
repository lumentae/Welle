import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../components"

ListView {
    anchors.fill: parent
    model: artistListModel
    clip: true

    function fetchMoreIfNeeded() {
        if (!artistListModel.isLoading && contentY + height >= contentHeight - 200)
            artistListModel.fetchNextPage()
    }

    delegate: Rectangle {
        width: ListView.view.width
        height: 100
        color: "red"

        ColumnLayout {
            anchors.fill: parent
            width: parent.width
            height: parent.height

            Text { text: "Artist" }
            Text { text: name ?? "" }
            Text { text: id ?? "" }
            Text { text: String(index ?? "") }
            Text { text: String(albumCount ?? "") }
        }
    }

    onContentYChanged: fetchMoreIfNeeded()
    onContentHeightChanged: fetchMoreIfNeeded()

    Connections {
        target: artistListModel

        function onIsLoadingChanged() {
            fetchMoreIfNeeded()
        }
    }

    footer: Item {
        width: parent.width
        height: 40
        visible: artistListModel.hasMore

        BusyIndicator {
            anchors.centerIn: parent
            running: artistListModel.isLoading
        }

        Component.onCompleted: artistListModel.fetchNextPage()
    }
}