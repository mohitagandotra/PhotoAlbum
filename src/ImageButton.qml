import QtQuick 2.0

Image {
    id: root
    signal activated()

    scale: mouse.pressed ? 0.9 : (mouse.containsMouse ? 1.2 : 1.0)
    Behavior on scale {
        NumberAnimation { duration: 100 }
    }
    width: 24
    height: 24
    MouseArea {
        id: mouse
        hoverEnabled: true
        anchors.fill: parent
        onClicked: root.activated();
    }
}
