import QtQuick 2.0

Item {
    property bool active: false;
    property alias title: titleLabel.text
    enabled: active
    opacity: active ? 1 : 0
    Behavior on opacity {
        NumberAnimation { duration: 300; }
    }


    Text {
        id: titleLabel
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 12
        color: palette.textColor
        font.pointSize: 28
    }
}
