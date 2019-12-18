import QtQuick 2.0

Flipable {
    id: card
    signal selected
    property int value: 0
    property bool flipped: false
    state: "back"
    property string letter: 'X'
    width: 40; height: width

    front: Rectangle{
        id: frontCard
        anchors.fill: parent
        radius: parent.width/10
        border.color: "white"
        border.width: parent.width/18
        color: "black"
    }

    back: Rectangle{
        id: backCard
        anchors.fill: parent
        radius: parent.width/10
        border.color: "white"; border.width: parent.width/20
        color: "green"
        Text {
                id: memoLetter
                anchors.centerIn: parent
                text: card.letter
                color: "black"
                font.pointSize: card.width/2; font.family: "Heveltica"; font.bold: true
            }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            if (!card.flipped) {
                card.flipped = true; card.selected()
            }
        }
    }

    transform: Rotation {
        id: rotation
        origin.x: card.width/2
        origin.y: card.height/2
        axis.x: 1; axis.y: 0; axis.z: 0
        angle: 0
    }

    states: State {
            name: "back"
            when: card.flipped
            PropertyChanges {
                target: rotation; angle: 180
            }
        }


    transitions: Transition {
        ParallelAnimation {
            NumberAnimation {target: rotation; easing.type: Easing.OutInSine; property: "angle"; duration: 420}
            SequentialAnimation {
                NumberAnimation {target: card; easing.type: Easing.OutCubic; property: "scale"; from: 1; to: 0.6; duration: 210}
                NumberAnimation {target: card; easing.type: Easing.OutCubic; property: "scale"; from: 0.6; to: 1; duration: 210}
            }
        }
    }

    Behavior on opacity {
        NumberAnimation {
            easing.type: Easing.OutElastic
            duration: 500
        }
    }
}
