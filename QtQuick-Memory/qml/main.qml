import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import QtQuick 2.0

Window {
    id: root
    visible: true
    width: 900
    height: 600
    color: "lightgray"
    title: qsTr("Memory Game")

    property int basicFontSize: (root.width/75 < root.height/54) ? root.width/75 : root.height/54

    TopLabel {
        id: topLabel
        anchors.horizontalCenter: parent.horizontalCenter
        y: basicSize
        basicSize: basicFontSize * 2
    }

    CardsGrid {
        id: cardsGrid
        anchors.left: parent.left
        anchors.top: topLabel.bottom
        anchors.leftMargin: (parent.width - cardSize*columns - columnSpacing*(columns-1) ) / 2
        anchors.topMargin: basicFontSize * 4

        horizontalSpace: parent.width
        verticalSpace: parent.height - 2 * anchors.topMargin - 2 * bottomBar.height

        //cardsModel:  ["A","A","B","B","C","C","D","D"]
        //rows: 2; columns: 4

        cardsModel: ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
                     "A", "B", "C", "D", "E", "F", "G", "H", "I", "J"]
        rows: 4; columns: 5

        //cardsModel: ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "O",
        //             "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "O"]
        //rows: 4; columns: 7

        Behavior on scorePlayer1 {
            PropertyAnimation {
                easing.type: Easing.InQuad
                duration: 350
            }
        }
        Behavior on scorePlayer2 {
            PropertyAnimation {
                easing.type: Easing.InQuad
                duration: 350
            }
        }

        states: [
            State {
                name: "level"
                when: !cardsGrid.playing & !cardsGrid.restart
                PropertyChanges {
                    target: cardsGrid
                    visible: false
                }
                PropertyChanges {
                    target: topLabel
                    label: (cardsGrid.scorePlayer1 == cardsGrid.scorePlayer2) ?
                               "Draw !" : (cardsGrid.scorePlayer1 < cardsGrid.scorePlayer2) ?
                                   "Player 2 won!" : "Player 1 won!"
                    color: (cardsGrid.scorePlayer1 == cardsGrid.scorePlayer2) ?
                               "white" : (cardsGrid.scorePlayer1 < cardsGrid.scorePlayer2) ?
                                   "red" : "blue"
                }
                PropertyChanges {
                    target: topLabel
                    labelColor: (cardsGrid.scorePlayer1 == cardsGrid.scorePlayer2) ? "black" : "white"
                }
                PropertyChanges {
                    target: bottomBar
                    label: "Start New Game !"
                    color: (cardsGrid.scorePlayer1 == cardsGrid.scorePlayer2) ?
                               "white" : (cardsGrid.scorePlayer1 < cardsGrid.scorePlayer2) ?
                                   "red" : "blue"
                }
            },
            State {
                name: "restart"
                when: !cardsGrid.playing & cardsGrid.restart
                PropertyChanges {
                    target: cardsGrid
                    visible: false
                }
                PropertyChanges {
                    target: topLabel
                    label: ""
                    color: "white"
                    labelColor: "black"
                }
            },
            State {
                name: "player1"
                when: cardsGrid.playing && cardsGrid.playerOne
                PropertyChanges {
                    target: cardsGrid
                    visible: true
                }
                PropertyChanges {
                    target: topLabel
                    label: "Player " + 1
                    color: "blue"
                }
                PropertyChanges {
                    target: bottomBar
                    label: "Score : " + cardsGrid.scorePlayer1
                    color: "blue"
                }
            },
            State {
                name: "player2"
                when: cardsGrid.playing && !cardsGrid.playerOne
                PropertyChanges {
                    target: cardsGrid
                    visible: true
                }
                PropertyChanges {
                    target: topLabel
                    label: "Player 2"
                    color: "red"
                }
                PropertyChanges {
                    target: bottomBar
                    label: "Score : " + cardsGrid.scorePlayer2
                    color: "red"
                }
            }
        ]

        transitions: [
            Transition {
                from: "*"
                to: "level"
                NumberAnimation {
                    target: topLabel
                    property: "basicSize"
                    from: basicFontSize*2; to: basicFontSize*3; duration: 300
                    easing.type: Easing.InCubic
                }
            },
            Transition {
                from: "level"
                to: "*"
                NumberAnimation {
                    target: topLabel
                    property: "basicSize"
                    from: basicFontSize*3; to: basicFontSize*2; duration: 300
                    easing.type: Easing.InCubic
                }
            }
        ]
    }

    ScoreBar {
        id: bottomBar
        anchors.bottom: parent.bottom
        height: newGame.height
        scoreTextColor: topLabel.labelColor

        width: root.width;
        Button {
            id: newGame
            anchors { left: parent.left; verticalCenter: parent.verticalCenter }
            text: "New Game"
            font.pixelSize: basicFontSize*1.5; font.family: "Heveltica"; font.bold: true
            height: basicFontSize*3; width: text.length*font.pixelSize
            onPressed: {
                cardsGrid.restartGame()
            }
        }
        Button {
            id: quitGame
            anchors { right: parent.right; verticalCenter: parent.verticalCenter }
            text: "Quit game"
            font.pixelSize: basicFontSize*1.5; font.family: "Heveltica"; font.bold: true
            height: basicFontSize*3; width: text.length*font.pixelSize
            onPressed: {
                Qt.quit()
            }
        }
    }
}
