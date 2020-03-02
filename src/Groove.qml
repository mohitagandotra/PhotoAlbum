import QtQuick 2.0

Rectangle {
    gradient: Gradient {
        GradientStop { position: 0.0; color: palette.grooveBackgroundColor }
        GradientStop { position: 0.5; color: palette.grooveColor }
        GradientStop { position: 1.0; color: palette.grooveBackgroundColor }
    }
    radius: 8
    clip: true
}
