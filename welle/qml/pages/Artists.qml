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
        height: 56
        color: mouseArea.containsMouse ? primaryColorSelected : primaryColor

        Behavior on color {
            ColorAnimation {
                duration: 50
            }
        }

        RowLayout {
            anchors.fill: parent
            width: parent.width
            height: 68
            spacing: 12

            Text {
                Layout.leftMargin: 16
                text: index
                color: secondaryTextColor
                font.pixelSize: 13
                Layout.preferredWidth: 24
            }
            Image {
                source: coverArt
                asynchronous: true
            }
            Text {
                Layout.fillWidth: true
                text: name
                color: primaryTextColor
                font.pixelSize: 15
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
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