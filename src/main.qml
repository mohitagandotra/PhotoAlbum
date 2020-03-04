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

    TopButtonPanel {
        id:topButtonPanel
        anchors {
            right: parent.right
            rightMargin: 30
            top: parent.top
            topMargin: 8
        }
    }

    MessageDialog {
        id: quitDialog
        title: "Quit?"
        icon: StandardIcon.NoIcon
        text: qsTr("Quit Application?")
        standardButtons: StandardButton.Yes  | StandardButton.No
        onYes: Qt.quit()
    }

    MessageDialog {
        id: timeoutMessage
        title: "Timeout"
        icon: StandardIcon.NoIcon
        text: qsTr("Data fetching timed out. Retry?")
        standardButtons: StandardButton.Yes  | StandardButton.No
        onYes: DataBank.populate()
    }

    ViewContainer {
        id: mainContainer
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            top: topButtonPanel.bottom
            topMargin: 8
            bottomMargin: 20
            leftMargin: 20
            rightMargin: 20
        }
    }

    Text {
        id: loading
        anchors.centerIn: parent
        text: qsTr("Loading...")
        color: palette.textColor
        font {
            pixelSize: 28
        }
    }

    Connections {
        target: DataBank
        function onDataPoolReady() {
            loading.visible = false
        }

        function onDataPoolTimedout() {
            timeoutMessage.visible = true
        }
    }

    function refresh() {
        DataBank.populate()
    }

    function showQuitMessage() {
        quitDialog.visible = true
    }

}
