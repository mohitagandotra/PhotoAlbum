import QtQuick 2.0

Item {
    property bool active: false;
    enabled: active
    opacity: active ? 1 : 0
    Behavior on opacity {
        NumberAnimation { duration: 300; }
    }
}
