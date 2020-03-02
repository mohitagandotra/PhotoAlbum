import QtQuick 2.0
import QtQuick.Controls 2.14
import sumup.com 1.0

EntityView {

    property string selectedName: ""
    property string selectedUserName: ""
    property string selectedEmail: ""

    clip:true

    ListView {
        id:usersView
        width: 300
        height:parent.height
        spacing: 8
        orientation: Qt.Vertical
        delegate: usersDelegate
        focus: true

        onCurrentIndexChanged: {
            var currentUser = DataBank.entityDataModel(EntityDataBank.Users).entityObject(usersView.currentIndex)
            Manager.filterAlbumsByUser(currentUser.id)
            selectedName = currentUser.name
            selectedUserName = currentUser.userName
            selectedEmail = currentUser.email
        }


    }




    Component {
        id: usersDelegate

        Rectangle {
            anchors.left:parent.left
            height:100
            width:300
            radius:20
            color: index === usersView.currentIndex ? "#484848" : "#A0A0A0"
            scale: mouse.containsMouse ? 0.97 - (mouse.pressed ? 0.02: 0) : 1.0
            Behavior on scale {
                NumberAnimation { duration: 100 }
            }
            MouseArea {
                id :mouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    usersView.currentIndex = index
                }
            }

            Text {
                anchors {
                    top:parent.top
                    topMargin: 12
                    left:parent.left
                    leftMargin: 10
                }
                height:20
                text: '<b>Name:</b> ' + entityObject.name

            }
            Text {
                anchors {
                    top:parent.top
                    topMargin: 34
                    left:parent.left
                    leftMargin: 10
                }
                height:20
                text: '<b>UserName:</b> ' + entityObject.userName

            }
            Text {
                anchors {
                    top:parent.top
                    topMargin: 56
                    left:parent.left
                    leftMargin: 10
                }
                height:20
                text: '<b>Email:</b> '+ entityObject.email
            }

        }

    }

    Connections {
        target: DataBank
        function onDataPoolReady() {
            //loading.visible = false
            usersView.model = DataBank.entityDataModel(EntityDataBank.Users);
            userDetailView.model = DataBank.entityProxyModel(EntityDataBank.Albums);
            console.log("onDataPoolReady slot")
        }
    }


    Rectangle {
        anchors {
            fill: parent
            leftMargin: 310
        }
        color: "#A0A0A0"
        radius:20

        Component {
            id: userDetailViewdelegate
            Column {
                id: wrapper
                //anchors.horizontalCenter: parent.horizontalCenter
                clip:true

                Image {
                    width: 50; height: 50
                    //anchors.horizontalCenter: parent.horizontalCenter
                    source: entityObject.albumThumbnail
                }
                Text {
                    id: nameText
                    text: entityObject.title
                    width: 20
                    font.pointSize: 16
                    elide: Text.ElideRight
                    wrapMode: Text.WordWrap
                }
            }

        }

        GridView {
            id:userDetailView
            //width: 300; height: 200
            anchors.fill: parent
            cellWidth: 80; cellHeight: 80
            delegate: userDetailViewdelegate


        }


    }



}
