import QtQuick 2.0

Groove {
    property EntityView activeView : home
    radius: 12

    function activateHome() {
        activeView = home
    }

    function activateAlbums() {
        activeView = albums
    }

    function activateUsers() {
        activeView = users
    }

    HomePage {
        id: home
        anchors.fill: parent
        active: activeView == home
    }

    UsersPage {
        id: users
        anchors.fill: parent
        active: activeView == users
    }

    AlbumsPage {
        id: albums
        anchors.fill: parent
        active: activeView == albums
    }



    Component.onCompleted: activateHome();
}
