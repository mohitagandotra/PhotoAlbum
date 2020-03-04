import QtQuick 2.0
import QtQuick.Controls 2.14
import sumup.com 1.0

EntityView {
    id: entityView

    Item {
        id: photosViewBackground
        anchors.top: parent.top
        anchors.topMargin: 12
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.left: parent.left
        anchors.leftMargin: 12
        height: 200
        clip:true
        PhotosView {
            id: photosView
            anchors.fill: parent
            anchors.margins: 12
        }
    }

    Item {
        id: usersViewBackground
        width: parent.width / 3
        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 12
        anchors.top: photosViewBackground.bottom
        anchors.topMargin: 22
        clip:true
        ListView {
            id:usersView
            anchors.fill: parent
            anchors.margins: 12
            spacing: 8
            orientation: Qt.Vertical
            delegate: UserDelegate {
                width: parent.width
                nameText: qsTr("Name: ") + entityObject.name
                userNameText: qsTr("Login Id: ") + entityObject.userName
                emailText: qsTr("Email Id: ") + entityObject.email
                color: index === usersView.currentIndex ? palette.activeItemColor : palette.itemColor
                onActivated: {
                    usersView.currentIndex = index
                    Manager.filterAlbumsByUser(entityObject.entityId, true)
                }
            }
            focus: true
        }
    }

    Item {
        anchors.left: usersViewBackground.right
        anchors.leftMargin: 12
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 12
        anchors.top: photosViewBackground.bottom
        anchors.topMargin: 22
        anchors.right: parent.right
        anchors.rightMargin: 12
        clip:true
        ListView {
            id: userAlbums
            anchors.fill: parent
            anchors.margins: 12
            spacing: 8
            orientation: Qt.Vertical
            delegate: UserAlbumDelegate {
                width: parent.width
                albumNameText: entityObject.title
                thumbnailUrl: entityObject.albumThumbnail
                color: index === userAlbums.currentIndex ? palette.activeItemColor : palette.itemColor
                onActivated: {
                    userAlbums.currentIndex = index
                    Manager.filterPhotosByAlbum(entityObject.entityId)
                }
            }
        }
    }

    Connections {
        target: DataBank
        function onDataPoolReady() {
            usersView.model = DataBank.entityDataModel(EntityDataBank.Users);
            photosView.model = DataBank.entityProxyModel(EntityDataBank.Photos);
            userAlbums.model = DataBank.entityProxyModel(EntityDataBank.Albums);
        }
    }
}
