import QtQuick 2.0
import QtQuick.Controls 2.14
import sumup.com 1.0

Item {

    ListView {
        id: albums
        anchors.verticalCenter: parent.verticalCenter
        width:parent.width
        height: parent.height / 2
        spacing: 10
        orientation: Qt.Horizontal
        delegate: Column {
            spacing: 10
            Image {
                id: thumbnailImage
                width: height
                height: 200
                asynchronous: true
                source:entityObject.albumThumbnail
                smooth: true

                Text {
                    text: qsTr("Loading...")
                    visible: thumbnailImage.status != Image.Ready
                    anchors.centerIn: parent
                }

            }

            Rectangle {
                width: thumbnailImage.width
                height: 28
                radius: height/3
                color: palette.itemColor
                smooth: true
                Text {
                    id: albumName
                    anchors.fill: parent
                    anchors.leftMargin: 4
                    anchors.rightMargin: 4
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    elide: Text.ElideRight
                    text: entityObject.title
                    color: palette.textColorAlt
                }
            }
        }
        focus: true
    }

    Connections {
        target: DataBank
        function onDataPoolReady() {
            albums.model = DataBank.entityDataModel(EntityDataBank.Albums);
        }

        function onDataPoolReset() {
            albums.model = 0;
        }
    }
}
