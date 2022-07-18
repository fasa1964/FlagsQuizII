import QtQuick 2.0

Rectangle {
    id: appmenu

    width: parent.width - 30
    height: 40
    x: parent.width

    border.color: "steelblue"
    color: "transparent"

    property bool quit: false
    property int margin: 6

    function openMenu(){
        appmenu.visible = true;
        menuopen.start();
    }

    function closeMenu(){  menuclose.start() }


    // Menu animation
    NumberAnimation {
         id: menuopen
         target: appmenu
         property: "x"
         duration: 750
         to: 0
         easing.type: Easing.InOutBack
     }

    NumberAnimation {
         id: menuclose
         target: appmenu
         property: "x"
         duration: 750
         to: parent.width
         easing.type: Easing.InOutQuad
         onStopped: {
             appmenu.visible = false
             if(quit)
                 Qt.quit();
         }
     }

    Row{
        spacing: 5
        width: parent.width-10
        height: parent.height
        x:5; y:5

        FAnimButton{
            id: infoBtn
            width: parent.width/4 - margin
            height: parent.height-8
            buttontext: qsTr("Info")
            sourceimage: "images/Info.svg"
            onSelect: {  }
        }

        FAnimButton{
            id: settingsBtn
            width: parent.width/4 - margin
            height: parent.height-8
            buttontext: qsTr("Settings")
            textsize: 10
            sourceimage: "images/Settings.svg"
            onSelect: {  }
        }
        FAnimButton{
            id: gameBtn
            width: parent.width/4 - margin
            height: parent.height-8
            buttontext: qsTr("Menu")
            sourceimage: "images/GMenu.svg"
            onSelect: {

                gamepage.closeGame()
                gamepage.deleteBonus()

                //gamemenu.openPage()
                //imageOn()
            }
        }

        FAnimButton{
            id: quitBtn
            width: parent.width/4 - margin
            height: parent.height-8
            buttontext: qsTr("Quit")
            sourceimage: "images/quit.png"
            onSelect: { Qt.quit() }
        }
    }



}
