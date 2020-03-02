import QtQuick 2.0
import QtQuick.Controls 2.14

EntityView {
    anchors.fill:parent

    Text {
        id: titleLabel
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 12
        text: qsTr("Albums")
        color: palette.textColor
        font.pointSize: 28
    }


    HomeScreenAlbumView {
        width:parent.width
        anchors.top: titleLabel.bottom
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
