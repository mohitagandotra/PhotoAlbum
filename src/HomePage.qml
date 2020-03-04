import QtQuick 2.0
import QtQuick.Controls 2.14

EntityView {
    anchors.fill:parent
    title: qsTr("Home")

    AlbumsView {
        width:parent.width
        anchors.top: parent.top
        anchors.margins: 12
        anchors.bottom: bottomPanel.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    HomeScreenBottomPanel {
        id: bottomPanel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 12
    }

}
