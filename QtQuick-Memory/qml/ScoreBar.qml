import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import QtQuick 2.0

Rectangle {
    id: scoreBar
    color: "white"
    height: 50
    property string label: ""
    property color scoreTextColor: "white"
    Text {
        id: scoreText
        anchors { centerIn: parent }
        font.pointSize: (1+parent.height)/2 ;
        text: label
        color: scoreTextColor
    }
    Behavior on color {
        SequentialAnimation{
            ColorAnimation {
                to: "white"
                duration: 200
                easing.type: Easing.OutCubic
            }
            ColorAnimation {
                from: "white"
                duration: 200
                easing.type: Easing.OutCubic
            }
        }
    }
}
