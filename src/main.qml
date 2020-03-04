import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.3


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

    ImageButton {
        id: homeButton
        anchors {
            right: parent.right
            rightMargin: 30
            top: parent.top
            topMargin: 8
        }
        source: "qrc:/images/home.svg"
        onActivated: mainContainer.activateHome();
    }

    ImageButton {
        id: cancelButton
        anchors {
            right: homeButton.left
            rightMargin: 8
            top: parent.top
            topMargin: 8
        }
        source: "qrc:/images/cancel.svg"
        onActivated: quitDialog.visible = true
    }


    MessageDialog {
        id: quitDialog
        title: "Quit?"
        icon: StandardIcon.NoIcon
        text: qsTr("Quit Application?")
        standardButtons: StandardButton.Yes  | StandardButton.No
        onYes: Qt.quit()
    }


    ViewContainer {
        id: mainContainer
        anchors {
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
