import QtQuick 2.0
import QtQuick.Controls 2.14
import sumup.com 1.0

Row {
    property string userCount: qsTr("Users\n") + Manager.usersCount
    property string albumCount: qsTr("Albums\n") + Manager.albumsCount
    property string photosCount: qsTr("Photos\n") + Manager.photosCount

    spacing:10
    Repeater {

        model: [ userCount, albumCount, photosCount, qsTr("Comments\n500"), qsTr("Posts\n100") ]
        RoundButton {

            width: 100
            height: 100
            radius: 20
            font.bold: true
            text: modelData //+ qsTr("\n100")
            onClicked: {
                if(index == 0) {
                    mainContainer.activateUsers();
                } else if (index == 1) {
                    mainContainer.activateAlbums()
                } else if (index == 2) {
                    mainContainer.activatePhotos()
                }
            }
        }
    }
}




