import QtQuick

Rectangle {
    id: gamemenu
    width: parent.width-20
    height: 110
    opacity: 0.95
    border.color: "blue"
    x: parent.width

    function openPage(){
        gamemenu.visible = true;
        open.start();
    }

    function closePage(){  close.start() }

    signal gameSelect()

    // page animation
    NumberAnimation {
         id: open
         target: gamemenu
         property: "x"
         duration: 750
         to: 10
         easing.type: Easing.InOutBack
     }

    NumberAnimation {
         id: close
         target: gamemenu
         property: "x"
         duration: 750
         to: parent.width
         easing.type: Easing.InOutQuad
         onStopped: { gamemenu.visible = false }
     }


    Column{
        id: column
        width: parent.width
        height: parent.height
        Row{
            id: row1
            width: parent.width
            height: parent.height / 2 - 5
            spacing:5
            leftPadding: 5
            topPadding: 5
            FButton{
                id: flagsbtn
                width: parent.width/2 - 10
                height: parent.height - 2.5
                buttontext: qsTr("Flags")
                textcolor: game.flags <= 0 ? "gray" : "steelblue"
                buttoncolor: "white"
                buttondowncolor: "steelblue"
                enable: game.flags <= 0 ? false : true
                onSelect: {  game.startGame("Flags");  gametype = buttontext; gameSelect()}
                Text{
                    leftPadding: 5
                    topPadding: 5
                    text: game.flags
                    color: flagsbtn.down ? "white" : "steelblue"
                }

            }
            FButton{
                id: capitalbtn
                width: parent.width/2 - 10
                height: parent.height - 2.5
                buttontext: qsTr( "Capitals" )
                textcolor: "steelblue"
                buttoncolor: "white"
                buttondowncolor: "steelblue"
                onSelect: {  game.startGame("Capitals"); gametype = buttontext; gameSelect() }
                Text{
                    leftPadding: 5
                    topPadding: 5
                    text: game.capitals
                    color: capitalbtn.down ? "white" : "steelblue"
                }
            }
        }
        Row{
            id: row2
            width: parent.width
            height: parent.height / 2 - 5
            spacing:5
            leftPadding: 5
            topPadding: 5
            FButton{
                id: borderbtn
                width: parent.width/2 - 10
                height: parent.height - 2.5
                buttontext: qsTr( "Borders" )
                textcolor: "steelblue"
                buttoncolor: "white"
                buttondowncolor: "steelblue"
                onSelect: {  game.startGame("Borders"); gametype = buttontext; gameSelect() }

            }
            FButton{
                id: btn
                width: parent.width/2 - 10
                height: parent.height - 2.5
                buttontext: qsTr( "Continent" )
                textcolor: enable ? "steelblue" : "gray"
                buttoncolor: "white"
                buttondowncolor: "steelblue"
                enable: false
                onSelect: {  game.startGame("Continent");  gametype = buttontext; gameSelect()  }
            }
        }
    }
}
