import QtQuick

Rectangle{
    id: button
    width: 100
    height: 38
    border.color: "gray"
    border.width: 1
    color: buttoncolor
    opacity: 0.95

    property string buttontext: qsTr("Click me")
    property string textcolor: enable ? "black" : "gray"
    property string textcolordown: "blue"
    property string blinkcolor: "red"
    property string buttoncolor: "lightgray"
    property string buttondowncolor: "steelblue"
    property bool enable: true
    property bool down: false
    property bool blinking: false


    signal select()


    function setEnable(e){
        button.enable = e
        if(!e){
            text.color = Qt.darker(textcolor, 150)
        }else{
            text.color = textcolor
        }
        update()
    }

    function startBlink(){ blinking = true; blink.running = true; text.color = blinkcolor }
    function stopBlink(){  blinking = false; blink.running = false; text.opacity = 1.0; text.color = textcolor }

    Text {
        id: text
        text: buttontext
        width: parent.width
        height: parent.height
        color: down ? textcolordown : textcolor
        font.letterSpacing: 2
        font.pointSize: 15
        minimumPointSize: 7
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
        font.bold: blinking ? true : false
        OpacityAnimator on opacity{
            id: blink
            target: text
            from: 1
            to: 0
            duration: 500
            running: false
            loops: Animation.Infinite
        }
    }

    MouseArea{
        anchors.fill: parent
        onPressed: { if(enable) { down = true;  button.border.width = 1.5; button.color = buttondowncolor; text.color = "white" } }
        onReleased: {  button.border.width = 1 ; if(enable){ down = false; ; button.color = buttoncolor; text.color = textcolor;  select() } }
    }
}
