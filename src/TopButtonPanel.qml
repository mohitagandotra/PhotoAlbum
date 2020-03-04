import QtQuick 2.4

Row {
    spacing:10
    Repeater {
        model: ListModel {
            ListElement{icon: "qrc:/images/home.svg";}
            ListElement{icon: "qrc:/images/refresh.svg";}
            ListElement{icon: "qrc:/images/cancel.svg";}
        }

        ImageButton {
            width: 24
            height: 24
            source: icon
            onActivated: {
                switch (index) {
                case 0:
                    mainContainer.activateHome();
                    break
                case 1:
                    refresh();
                    break;
                case 2:
                    showQuitMessage()
                    break;
                }
            }
        }
    }
}

