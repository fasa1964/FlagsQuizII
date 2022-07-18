import QtQuick

import ClassSetupFlags 1.0
import ClassGameQuiz 1.0


Window {
    id: main
    width: 450
    height: 620
    visible: true
    title: qsTr("FlagsQuizII")

    property string gametype: ""
    property int questioncounter: 0
    property int maxquestion: 16

    property int points: 0
    property int bonuscounter: 0
    property int xvalue: 0

    ListModel{
        id: arrayBonus

    }

    function startGame(){

        questioncounter = 0
        points = 0
        gamemenu.closePage()
        imageOff();
        gamepage.openGame();
        nextQuestion();
    }

    function setAnswer(answer){

        if(answer === game.solution){
            points += 10
            gamepage.createBonus()
        }
    }

    function nextQuestion(){
        gamepage.wfill = 0;
        gamepage.second = 0;
        gamepage.msecond = 0;
        game.nextQuestion();
        gamepage.stopBlink();
        gamepage.startTimer();
        questioncounter++;

    }

    // For image off and on
    function imageOff(){
        off.start();
    }

    function imageOn(){
        on.start();
    }

    // Create bonus object


    OpacityAnimator on opacity {
         id: off
         target: iconapp
         duration: 750
         to: 0.0
    }

    OpacityAnimator on opacity {
         id: on
         target: iconapp
         duration: 750
         to: 0.85
    }



    SetupFlags{
        id: setup
        onErrorOccurred: function(error) {

                messagebox.message = error
                messagebox.visible = true
         }
        onFinishedDownloadFlags: {

            if(downloadpage.visible){
                downloadpage.closeDownloadPage();
                messagebox.caption = "Download"
                messagebox.message = "Downloading flags finished!"
                messagebox.visible = true
            }
        }
    }

    // C++ ClassGameQuiz
    Game{
        id: game
        onErrorOccurred: function(error) {
                messagebox.message = error
                messagebox.visible = true
        }
        onSetJokerPublic: function(key) { gamepage.startBlink(key) }
        onSetJokerTelefon: function(key) { gamepage.startBlink(key) }
    }


    Rectangle{
        id: mainrect
        anchors.fill: parent

        gradient: Gradient{
            GradientStop{ position: 0.0; color: "#FFF5EE" } // SeaShell
            GradientStop{ position: 1.0; color: "#FF7F50" } // Coral
        }


        // Background Image
        Image {
            id: iconapp
            source: "images/IconAppFlags.svg"
            width: parent.width-80
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
            opacity: 0.8
        }


        FAppMenu{
            id: menu
            width: parent.width - menubutton.width - 5
            height: menubutton.height
        }

        GameMenu{
            id: gamemenu
            y:100
            visible: false
            onGameSelect: {  startGame() /*gamemenu.closePage(); imageOff()  ; gamepage.openGame()*/ }

        }

        FAnimButton{
            id: menubutton
            width: 30
            height: 48
            buttontext: ""
            sourceimage: "images/3Points.svg"
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 5
            onSelect: {

                if(menu.visible)
                    menu.closeMenu()
                else
                    menu.openMenu()
            }

        }

        FDownloadPage{
            id: downloadpage
            y: 50
            visible: false
        }

        FMessageBox{
            id: messagebox
            anchors.centerIn: parent
            visible: false
            z:2
        }

        FQuestionBox{
            id: qbox
            anchors.centerIn: parent
            visible: false
            z:2
            onCancel: { qbox.visible = false }
            onAccept: {

                qbox.visible = false

                if(qbox.caption === "Download FLAGS"){
                    downloadpage.openDownloadPage();
                }
            }
        }

        FGamePage{
            id: gamepage
        }

    }

    Item{
        id: container

        Component.onCompleted: {
            var item = Qt.createComponent("FBonus.qml")
            for(var i = 0; i < 5; i++){
                var object = item.createObject(container)

            }

        }
    }

    Component.onCompleted: {

        menu.closeMenu()

        if(!setup.countriesFile )
            downloadpage.openDownloadPage()
        else
            game.createGameData()

        if(game.flags < game.codes){
            qbox.caption = qsTr("Download FLAGS")
            qbox.message = qsTr("The Flags counts only: ") + game.flags +  qsTr(" Do you want to download the flags?")
            downloadpage.btext = qsTr("Start download flags")
            qbox.visible = true
        }

        if(game.flags == game.codes)
            gamemenu.openPage();


        imageOn()




    }

}
