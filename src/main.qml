import QtQuick 2.12
import QtQuick.Window 2.12


Window {
    visible: true
    width: 640
    height: 480
    color: "#707070"

    Image {
        id: homeButton
        scale: homeMouse.pressed ? 0.9 : (homeMouse.containsMouse ? 1.2 : 1.0)
        Behavior on scale {
            NumberAnimation { duration: 100 }
        }

        anchors {
            right: parent.right
            rightMargin: 30
            top: parent.top
            topMargin: 8
        }
        source: "qrc:/images/home.svg"
        width: 24
        height: 24
        MouseArea {
            id: homeMouse
            hoverEnabled: true
            anchors.fill: parent
            onClicked: mainContainer.activateHome();
        }
    }

    ViewContainer {
        id: mainContainer
        anchors {
            //fill:parent
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            top: homeButton.bottom
            topMargin: 8
            bottomMargin: 20
            leftMargin: 20
            rightMargin: 20
        }
    }

}
