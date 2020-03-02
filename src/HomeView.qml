import QtQuick 2.0
import QtQuick.Controls 2.14

EntityView {
    Rectangle {
        anchors.fill:parent
        color: "#A0A0A0"
        radius:20
        clip:true
        Column {
            anchors{
                fill: parent
                topMargin: 20
                leftMargin: 20
                rightMargin: 20
            }
            spacing:10

            Label {
                text: "Albums"
                color: "black"
                font.bold: true
                font.pointSize: 20
            }

            HomeScreenAlbumView{
                width:parent.width
                height: 250
            }

            HomeScreenBottomPanel {
                //anchors.left:parent.left
            }
        }
    }
}
