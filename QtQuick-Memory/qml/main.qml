import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import QtQuick 2.0

Window {
    id: root
    visible: true
    width: 900
    height: 700
    color: "lightgray"
    title: qsTr("Memory Game")

    property int basicFontSize: root.width/75

    TopLabel {
        id: topLabel
        anchors.horizontalCenter: parent.horizontalCenter
        y: basicSize
        basicSize: basicFontSize * 2
    }

    Grid {
        id: cardsGrid

        property int selectedCard1: -1
        property int selectedCard2: -1
        property int scorePlayer1: 0
        property int scorePlayer2: 0
        property bool playing: true
        property bool restart: false
        property bool playerOne: true

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

        property var cardsModel: ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" ,"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"]
        property var cardSize: (parent.width/10 > verticalSpace/6) ? verticalSpace/6 : parent.width/10
        property var verticalSpace: parent.height - 3 * basicFontSize*2 - 2 * bottomBar.height

        anchors.left: parent.left
        anchors.leftMargin: (parent.width - cardSize*6 - 5*columnSpacing) / 2
        anchors.bottomMargin: anchors.topMargin
        anchors.top: topLabel.bottom
        anchors.topMargin: basicFontSize*3
        rows: 4; columns: 6

        rowSpacing: verticalSpace/18
        columnSpacing: parent.width/20

        Repeater {
            id: repeaterCards
            model: parent.cardsModel
            delegate: Card {
                letter: modelData
                width: parent.cardSize
                onSelected: {
                    if (cardsGrid.selectedCard1 >= 0 && cardsGrid.selectedCard2 >= 0) {
                        checkTimer.stop();
                        cardsGrid.checkGame();
                    }
                    if (cardsGrid.selectedCard1 < 0) {
                        cardsGrid.selectedCard1 = index;
                    } else {
                        cardsGrid.selectedCard2 = index;
                        checkTimer.start();
                    }
                }
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

        function restartGame(){
            var array = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" ,"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"];
            var temp, j;
            for (var i = array.length - 1; i > 0; i--) {
              j = Math.floor(Math.random() * (i + 1)); // random index from 0 to i
              [array[i], array[j]] = [array[j], array[i]];
            }
            repeaterCards.model = array; cardsGrid.scorePlayer1 = cardsGrid.scorePlayer2 = 0;
            cardsGrid.restart = false; cardsGrid.playing = true;
        }

        Timer {
            id: checkTimer
            interval: 1000
            onTriggered: cardsGrid.checkGame()
        }

        function checkGame(){
            if (cardsGrid.children[selectedCard1].letter
                    == cardsGrid.children[selectedCard2].letter) {
                cardsGrid.children[selectedCard1].opacity = cardsGrid.children[selectedCard2].opacity = 0.2
                addPoint()
            } else {
                cardsGrid.children[selectedCard1].flipped = cardsGrid.children[selectedCard2].flipped = false
                playerOne = !playerOne
            }
            selectedCard1 = selectedCard2 = -1;
        }

        function addPoint(){
            if(scorePlayer1 + scorePlayer2 == 55)
                playing = false;
            if(playerOne)
                scorePlayer1 += 5;
            else
                scorePlayer2 += 5;

        }
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
                cardsGrid.playing = false; cardsGrid.restart = true
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
