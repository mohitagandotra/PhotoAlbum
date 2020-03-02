import QtQuick 2.0

PathView {
    id: photosView
    property double photoHeight : height
    pathItemCount: (width / photoHeight) + 3
    preferredHighlightBegin: 0.5
    preferredHighlightEnd: 0.5
    highlightRangeMode: PathView.StrictlyEnforceRange
    delegate: PhotoDelegate {
        property double r : PathView.imageRotation
        scale: PathView.imageScale
        opacity: PathView.imageOpacity
        transform: Rotation { origin.x: width/2; origin.y: height/2; axis { x: 0; y: 0.5; z: 0 } angle: r }
        z: PathView.imageOrder
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
