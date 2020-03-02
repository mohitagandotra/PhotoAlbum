import QtQuick 2.12
import QtQuick.Window 2.12


Window {
    visible: true
    minimumWidth: 800
    minimumHeight: 640

    QtObject {
        id: palette
        property color grooveColor: "#f2f2f2"
        property color grooveBackgroundColor: "#8c8c8c"
        property color backgroundColor: "#4c4c4c"
        property color itemColor: "#666666"
        property color itemBorderColor: "#404040"
        property color activeItemColor: "#004d66"
        property color textColor: "#000000"
        property color textColorAlt: "#F0F0F0"
    }

    color: palette.backgroundColor

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
