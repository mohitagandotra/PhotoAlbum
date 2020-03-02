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
        PathView {
            id: photosView
            anchors.fill: parent
            anchors.margins: 12
            pathItemCount: (photosView.width / photosView.height) + 3
            preferredHighlightBegin: 0.5
            preferredHighlightEnd: 0.5
            highlightRangeMode: PathView.StrictlyEnforceRange
            delegate: PhotoDelegate {
                property double r : PathView.imageRotation
                scale: PathView.imageScale
                opacity: PathView.imageOpacity
                transform: Rotation { axis { x: 0; y: 1; z: 0 } angle: r }
                z: PathView.imageOrder
                height: parent.height
                photoSource: entityObject.thumbnailUrl
            }
            path: Path {
                startX: 0; startY: photosView.height/2
                PathAttribute { name: "imageScale"; value: 0.6 }
                PathAttribute { name: "imageOpacity"; value: 0.7 }
                PathAttribute { name: "imageOrder"; value: 0 }
                PathAttribute { name: "imageRotation"; value: 60 }
                PathLine {x: photosView.width / 2; y: photosView.height/2 }
                PathAttribute { name: "imageScale"; value: 1.0 }
                PathAttribute { name: "imageOpacity"; value: 1 }
                PathAttribute { name: "imageOrder"; value: 10 }
                PathAttribute { name: "imageRotation"; value: 0 }
                PathLine {x: photosView.width; y: photosView.height/2 }
                PathAttribute { name: "imageRotation"; value: -60 }
            }
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
        anchors.topMargin: 12
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
        anchors.topMargin: 12
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
