import QtQuick 2.0

Item {
    property EntityView activeView : home

    function activateHome() {
        activeView = home
    }

    function activateAlbums() {
        activeView = albums
    }

    function activateUsers() {
        activeView = users
    }

    HomeView {
        id: home
        anchors.fill: parent
        active: activeView == home
    }

    UsersView {
        id: users
        anchors.fill: parent
        active: activeView == users
    }

    AlbumsView {
        id: albums
        anchors.fill: parent
        active: activeView == albums
    }



    Component.onCompleted: activateHome();
}
