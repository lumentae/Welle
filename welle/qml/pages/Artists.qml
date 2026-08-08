import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import "../components"

ListView {
    anchors.fill: parent
    model: artistListModel
    clip: true
    spacing: 8

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
            Layout.topMargin: 3
            Layout.bottomMargin: 3

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
                sourceSize.width: 56
                sourceSize.height: 56
                Layout.preferredWidth: 56
                Layout.preferredHeight: 56
                Layout.maximumWidth: 56
                Layout.maximumHeight: 56
                fillMode: Image.PreserveAspectCrop
                clip: true
                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource: mask
                }
            }
            Rectangle {
                id: mask
                width: parent.width
                height: width
                radius: width/6
                visible: false
            }

            Text {
                Layout.fillWidth: true
                text: name
                color: primaryTextColor
                font.pixelSize: 15
            }
            Text {
                Layout.rightMargin: 16
                text: albumCount + " albums"
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