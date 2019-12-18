import QtQuick.Controls 2.5
import QtQuick.Window 2.10
import QtQuick 2.10

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
