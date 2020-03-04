import QtQuick 2.0
import sumup.com 1.0

EntityView {
    PhotosView {
        id: photosView
        anchors.fill: parent
        anchors.margins: 12
        photoHeight: height / 2
    }

    Connections {
        target: DataBank
        function onDataPoolReady() {
            photosView.model = DataBank.entityDataModel(EntityDataBank.Photos);
        }

        function onDataPoolReset() {
            photosView.model = 0;
        }
    }
}
