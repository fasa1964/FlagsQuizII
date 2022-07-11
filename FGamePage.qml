import QtQuick

Rectangle{
    id: gamepage
    width: parent.width-20
    height: parent.height - 60
    border.color: "#20B2AA"     // LightSeaGreen
    color: "transparent" //"#F08080"            // LightCoral
    x:parent.width
    y:55
    visible: false


    property int msecond: 0
    property int second: 0
    property int delay: 20
    property int wfill: 0


    function startBlink(key){
        if(key === "A")
            abtn.startBlink()
        if(key === "B")
            bbtn.startBlink()
        if(key === "C")
            cbtn.startBlink()
        if(key === "D")
            dbtn.startBlink()
    }

    function stopBlink(){
        abtn.stopBlink()
        bbtn.stopBlink()
        cbtn.stopBlink()
        dbtn.stopBlink()
    }

    function openGame(){
        gamepage.visible = true;
        open.start();
    }

    function closeGame(){  close.start() }


    // timecounter for questions
    function timeout(){

        msecond += 100
        wfill+=10

        if(msecond >= 1000)
        {
            msecond = 0
            second++;
        }

        if(second >= delay)
            nextQuestion()

    }

    function startTimer(){ questiontimer.start()  }

    Timer{
         id: questiontimer
         repeat: true
         interval: 100
         onTriggered: { timeout() }
    }



    // page animation
    NumberAnimation {
         id: open
         target: gamepage
         property: "x"
         duration: 750
         to: 10
         easing.type: Easing.InOutBack
    }

    NumberAnimation {
         id: close
         target: gamepage
         property: "x"
         duration: 750
         to: parent.width
         easing.type: Easing.InOutQuad
         onStopped: { gamepage.visible = false }
    }

    // Position the jokers
    Row {

        id: jokerrow
        spacing: 8
        anchors.bottom: questionrect.top
        anchors.left:  questionrect.left
        width: questionrect.width
        height: 45

        FAnimButton {
            id: joker50
            width: 65
            height: 35
            buttontext: ""
            sourceimage: Qt.resolvedUrl("images/Joker50.png")
            onSelect: { game.setJoker50(); /*joker50.enabled = false*/ }

        }

        FAnimButton {
            id: jokerTel
            width: 65
            height: 35
            buttontext: ""
            sourceimage: Qt.resolvedUrl("images/JokerTel.png")
            onSelect: { game.setJokerTel(); /*jokerTel.enabled = false*/ }
        }

        FAnimButton {
            id: jokerPub
            width: 65
            height: 35
            buttontext: ""
            sourceimage: Qt.resolvedUrl("images/JokerPub.png")
            onSelect: { game.setJokerPub(); /*jokerPub.enabled = false*/ }
        }
    }

    // Questioncounter
    Text{
        id: counter
        text: maxquestion + "/" + questioncounter
        anchors.right: questionrect.right
        anchors.top: jokerrow.top
        anchors.topMargin: 10
        font.pointSize: 15
        color: "steelblue"
    }

    // Position the question rect
    Rectangle {
        id: questionrect
        width: parent.width-120
        height: questionrect.width/2 + 15
        border.color: "steelblue"
        x: parent.width/2 - questionrect.width/2
        y: 75

        // Position flag Image {
        Image{
            id: flag
            source: gametype === "Flags" ? "file:///" + game.question : "file:///" + game.currentFlag
            width: parent.width-2
            height: parent.height-2
            anchors.centerIn: parent
            opacity: gametype === "Flags" ? 1.0 : 0.25
        }

        Text {
            id: capitalquestion
            text: qsTr("Capital of")
            font.pointSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
            y:15
            anchors.topMargin: 15
            visible: gametype === "Capitals" ? true : false
        }
        Text {
            id: borderquestion
            text: qsTr("Border of")
            font.pointSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
            y:15
            anchors.topMargin: 15
            visible: gametype === "Borders" ? true : false
        }
        Text {
            id: cquestion
            text: game.question
            font.pointSize: 18
            font.bold: true
            color: "steelblue"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:  capitalquestion.bottom
            anchors.topMargin: 18
            visible: gametype === "Capitals" ? true : false
        }
        Text {
            id: bquestion
            text: game.question
            font.pointSize: 18
            font.bold: true
            color: "steelblue"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top:  capitalquestion.bottom
            anchors.topMargin: 18
            visible: gametype === "Borders" ? true : false
        }
   }

    // Position the answers
    Column{
        id: answercol
        width: parent.width-20
        height: 120
        anchors.top: questionrect.bottom
        anchors.topMargin: 30
        x: 5
        spacing: 10
        Row{

            width: parent.width
            spacing: 5
            FButton{
                id: abtn
                width: parent.width/2
                height: 50
                buttontext: game.answerA
                //enable: buttontext == "" ? false : true
                onSelect: {

                    setAnswer(abtn.buttontext);
                    nextQuestion()

                }
            }
            FButton{
                id: bbtn
                width: parent.width/2
                height: 50
                buttontext: game.answerB
                //enable: buttontext === "" ? false : true
                onSelect: {
                    setAnswer(bbtn.buttontext);
                    nextQuestion()
                }
            }
        }
        Row{

            width: parent.width
            spacing: 5
            FButton{
                id: cbtn
                width: parent.width/2
                height: 50
                buttontext: game.answerC
                //enable: buttontext === "" ? false : true
                onSelect: {
                    setAnswer(cbtn.buttontext);
                    nextQuestion()
                }
            }
            FButton{
                id: dbtn
                width: parent.width/2
                height: 50
                buttontext: game.answerD
                //enable: buttontext === "" ? false : true
                onSelect: {
                    setAnswer(dbtn.buttontext);
                    nextQuestion()
                }
            }
        }
    }

    // Timerrect
    Rectangle{
        id: timerrect
        color: "white"
        border.color: "steelblue"
        width: questionrect.width
        height: 20
        x: parent.width/2 - timerrect.width/2
        anchors.top: questionrect.bottom
        anchors.topMargin: 5

        Rectangle{
            id: clockrect
            height: timerrect.height
            width:  timerrect.width/(delay*100) * wfill
            color: "steelblue"
        }
    }

    Text{
        id: pointsText
        text: points
        font.pointSize: 25
        color: "blue"
        z:2
        anchors.top: answercol.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: answercol.horizontalCenter
    }

}
