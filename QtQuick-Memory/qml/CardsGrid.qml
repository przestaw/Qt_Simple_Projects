import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import QtQuick 2.0

Grid {
    id: cardsGrid
    
    property int selectedCard1: -1
    property int selectedCard2: -1
    property int scorePlayer1: 0
    property int scorePlayer2: 0
    property bool playing: true
    property bool restart: false
    property bool playerOne: true
    
    property var cardsModel: ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" ,"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"]
    property var cardSize: (horizontalSpace/(rows*1.2) > verticalSpace/(columns*1.3)) ? verticalSpace/(columns*1.3) : horizontalSpace/(rows*1.2)
    property var verticalSpace: height
    property var horizontalSpace: width

    rows: 4; columns: 6

    rowSpacing: (verticalSpace - (rows*cardSize)) / (rows + 1)
    columnSpacing: (horizontalSpace - (columns*cardSize)) / (columns + 3)
    
    Repeater {
        id: repeaterCards
        model: parent.cardsModel
        delegate: Card {
            letter: modelData
            width: parent.cardSize
            onSelected: {
                if (selectedCard1 >= 0 && selectedCard2 >= 0) {
                    checkTimer.stop();
                    checkGame();
                }
                if (selectedCard1 < 0) {
                    selectedCard1 = index;
                } else {
                    selectedCard2 = index;
                    checkTimer.start();
                }
            }
        }
    }
    
    function restartGame(){
        var newModel = cardsModel;
        var j, x, i;
        for (i = newModel.length - 1; i > 0; i--) {
            j = Math.floor(Math.random() * (i + 1));
            x = newModel[i];
            newModel[i] = newModel[j];
            newModel[j] = x;
        }
        playing = false; restart = true
        repeaterCards.model = newModel;
        scorePlayer1 = scorePlayer2 = 0;
        restart = false; playing = true;
    }
    
    Timer {
        id: checkTimer
        interval: 1000
        onTriggered: checkGame()
    }
    
    function checkGame(){
        if (children[selectedCard1].letter
                == children[selectedCard2].letter) {
            children[selectedCard1].opacity = children[selectedCard2].opacity = 0.2
            addPoint()
        } else {
            children[selectedCard1].flipped = children[selectedCard2].flipped = false
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
