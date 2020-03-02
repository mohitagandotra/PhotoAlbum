import QtQuick 2.4

Item {
    id: photoRoot
    height: 120
    width: height
    property alias photoSource: photo.source

    Rectangle {
        radius: 4
        anchors.fill: parent
        color: palette.itemColor
    }

    Image {
        id: photo
        anchors.fill: parent
        anchors.margins: 2
        fillMode: Image.PreserveAspectFit
        asynchronous: true
    }

    Rectangle {
        color: "transparent"
        radius: 4
        anchors.fill: parent
        border.width: 3
        border.color: palette.itemBorderColor
    }

    Text {
        id: element
        visible: photo.status != Image.Ready
        text: qsTr("Loading...")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 12
    }
}
