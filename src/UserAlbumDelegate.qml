import QtQuick 2.4

Rectangle {
    id: albumRoot

    property alias albumNameText: albumName.text
    property alias thumbnailUrl : thumbnailImage.source
    signal activated()

    width: 400
    height: 60

    radius: 8

    Image {
        id: thumbnailImage
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        asynchronous: true
        width: height
    }

    Text {
        id: albumName
        text: qsTr("Text")
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: thumbnailImage.right
        anchors.leftMargin: 12
        elide: Text.ElideRight
        font.pixelSize: 14
        color: palette.textColorAlt
    }

    MouseArea {
        id :mouse
        anchors.fill: parent
        hoverEnabled: true
        onClicked: albumRoot.activated()
    }
}
