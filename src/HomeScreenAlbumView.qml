import QtQuick 2.0
import QtQuick.Controls 2.14
import sumup.com 1.0

Item {
    ListView {
        id: albums
        anchors.fill:parent

        spacing: 10
        orientation: Qt.Horizontal
        model: 20
        delegate: homeScreenAlbumDelegate
        focus: true
    }

    Component {
        id: homeScreenAlbumDelegate
        Column {
            spacing: 10

            Image {
                id: thumbnailImage
                width: 150
                height: 150
                asynchronous: true
                source:entityObject.albumThumbnail

                Text {
                    text: qsTr("Loading...")
                    visible: thumbnailImage.status != Image.Ready
                    anchors.centerIn: parent
                }

            }

            Text {
                id: contactInfo
                width: 100
                height: 100
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                font.bold: true
                elide: Text.ElideRight
                wrapMode: Text.WordWrap
                text: entityObject.title

            }

        }

    }
    Connections {
        target: DataBank
        function onDataPoolReady() {
            albums.model = DataBank.entityDataModel(EntityDataBank.Albums);
        }
    }
}
