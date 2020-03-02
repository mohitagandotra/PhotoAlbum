import QtQuick 2.4

Rectangle {
    id: userRoot
    property alias nameText: name.text
    property alias userNameText: userName.text
    property alias emailText: email.text

    signal activated()


    height: 100
    width: 300

    scale: mouse.containsMouse ? 0.97 - (mouse.pressed ? 0.02: 0) : 1.0

    Behavior on scale {
        NumberAnimation { duration: 100 }
    }

    radius:8

    Text {
        id: name
        y: 17
        height: 20
        elide: Text.ElideRight
        anchors.right: parent.right
        anchors.rightMargin: 24
        anchors.left: parent.left
        anchors.leftMargin: 24
        font.pixelSize: 18
    }

    Text {
        id: userName
        elide: Text.ElideRight
        anchors.top: name.bottom
        anchors.topMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 24
        anchors.left: parent.left
        anchors.leftMargin: 24
        font.pixelSize: 14
    }

    Text {
        id: email
        elide: Text.ElideRight
        anchors.top: userName.bottom
        anchors.topMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 24
        anchors.left: parent.left
        anchors.leftMargin: 24
        font.pixelSize: 14
    }

    MouseArea {
        id :mouse
        anchors.fill: parent
        hoverEnabled: true
        onClicked: userRoot.activated()
    }


}


