import QtQuick 2.0
import QtQuick.Controls 2.14
import sumup.com 1.0

Row {
    property string userCount: qsTr("Users\n") + Manager.usersCount
    property string albumCount: qsTr("Albums\n") + Manager.albumsCount
    property string photosCount: qsTr("Photos\n") + Manager.photosCount

    anchors.horizontalCenter: parent.horizontalCenter
    spacing:10
    Repeater {


        //model: [ qsTr("Users\n") +userCount, qsTr("Albums"), qsTr("Photos"), qsTr("Comments"), qsTr("Posts") ]
        model: [ userCount, albumCount, photosCount, qsTr("Comments"), qsTr("Posts") ]
        RoundButton {

            width: 100
            height: 100
            radius: 20
            font.bold: true
            text: modelData //+ qsTr("\n100")

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(index == 0) {
                        mainContainer.activateUsers();
                    } else if (index == 1) {
                        mainContainer.activateAlbums()
                    }
                }
            }
        }
    }
}




