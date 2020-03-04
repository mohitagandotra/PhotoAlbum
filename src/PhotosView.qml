import QtQuick 2.0
import QtQuick.Controls 2.14

Item {
    property alias model: photosView.model
    property double photoHeight : photosView.height
    PathView {
        id: photosView
        anchors.fill: parent
        anchors.bottomMargin: 30
        pathItemCount: (width / photoHeight) + 3
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        highlightRangeMode: PathView.StrictlyEnforceRange

        delegate: PhotoDelegate {
            property double r : PathView.imageRotation ? PathView.imageRotation : 0
            scale: PathView.imageScale ? PathView.imageScale : scale
            opacity: PathView.imageOpacity ? PathView.imageOpacity: opacity
            transform: Rotation { origin.x: width/2; origin.y: height/2; axis { x: 0; y: 0.5; z: 0 } angle: r }
            z: PathView.imageOrder ? PathView.imageOrder : z
            height: photoHeight
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

    Slider {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.left:parent.left
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        height: 20
        from: 0
        value: photosView.currentIndex
        to: photosView.count
        onValueChanged: {
            photosView.currentIndex = value
        }
    }
}
