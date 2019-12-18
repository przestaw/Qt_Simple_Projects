import QtQuick.Controls 2.5
import QtQuick.Window 2.10
import QtQuick 2.10

Rectangle {
    id: topLabel

    property string label: ""
    property color labelColor: "white"
    property int basicSize: 40

    width: topText.width + height
    height: basicSize * 3
    radius: height/8

    Text {
        id: topText
        anchors.centerIn: parent
        text: "Memory Game! " + parent.label
        font.pointSize: basicSize; font.family: "Heveltica"; font.bold: true
        color: labelColor //(parent.color == "white") ? "black" : "white"
    }

    Behavior on width{
        NumberAnimation {
            easing.type: Easing.OutCubic
            duration: 100
        }
    }
    Behavior on color{
        SequentialAnimation{
            ColorAnimation {
                to: "violet"
                duration: 150
                easing.type: Easing.OutCubic
            }
            ColorAnimation {
                from: "violet"
                duration: 150
                easing.type: Easing.OutCubic
            }
        }
    }
}
