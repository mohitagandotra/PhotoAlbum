import QtQuick 2.13
import QtQuick.Window 2.13
import sumup.com 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text {
        id: users
        x: 8
        y: 8
        font.pixelSize: 12
        text: qsTr("Users: ") + Manager.usersCount
    }

    Text {
        id: albums
        x: 8
        anchors.top: users.bottom
        font.pixelSize: 12
        text: qsTr("Albums: ") + Manager.albumsCount
    }

    Text {
        id: photos
        x: 8
        anchors.top: albums.bottom
        font.pixelSize: 12
        text: qsTr("Photos: ") + Manager.photosCount
    }

    ListView {
        id: albumView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: photos.bottom
        delegate: Rectangle {
            width: parent.width
            height: 20
            color: "lightblue"
            Text {
                anchors.centerIn: parent
                text: entityObject.title
            }
        }
        spacing: 1
    }

    Text {
        id: loading
        anchors.centerIn: parent
        text: qsTr("Loading ...")
    }

    Connections {
        target: DataBank
        function onDataPoolReady() {
            loading.visible = false
            albumView.model = DataBank.entityProxyModel(EntityDataBank.Albums);
        }
    }

    Timer {
        interval: 8000; running: true; repeat: true
        onTriggered: Manager.filterAlbumsByUser(5);
    }
}
