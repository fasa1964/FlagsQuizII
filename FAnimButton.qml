import QtQuick

Rectangle {
    id: control
    width: 200
    height: 80
    radius: 5
    color: backgroundcolor
    border.color: down ? Qt.darker( bordercolor ) : bordercolor
    border.width: down ? 2 : 1

    property string buttontext: qsTr( "Button" )
    property string textcolor: "steelblue"
    property string downcolor: "red"
    property string backgroundcolor: "transparent"
    property string bordercolor: "steelblue"
    property string animcolor: "green"
    property string sourceimage: ""

    property int textsize: 12
    property bool down: false
    property bool animation: false
    property bool bold: false

    signal select()

    Image {
        id: image
        fillMode: Image.PreserveAspectFit

        horizontalAlignment: buttontext === "" ? Image.AlignHCenter : Image.AlignLeft
        width: down ? parent.width-8 : parent.width-5
        height: down ? parent.height-8 : parent.height-5
        anchors.centerIn: parent
        source: sourceimage
        opacity: enabled ? 1.0 : 0.3
    }

    Text {
        id: text
        text: buttontext
        width: parent.width - 10
        height: parent.height - 6
        color: {

           down ? downcolor : textcolor


          // enabled ? textcolor : "lightgray"



        }
        wrapMode: Text.Wrap
        font.pointSize: down ? textsize-1 : textsize
        font.bold: bold
        horizontalAlignment: sourceimage == "" ? Text.AlignHCenter : Text.AlignRight
        verticalAlignment: Text.AlignVCenter

    }

    MouseArea{
        anchors.fill: parent
        onPressed:  { down = true;  if(animation) { animateColor.start() }  }
        onReleased: {

            down = false;
            if(animation)
                animateBack.start()
            else
                select()
        }
    }

    PropertyAnimation {
        id: animateColor;
        target: control;
        properties: "color";
        to: animcolor;
        duration: 100
        easing.type: Easing.OutInElastic;
        easing.amplitude: 2.0;
        easing.period: 1.5

    }

    PropertyAnimation {
        id: animateBack
        target: control
        properties: "color"
        to: backgroundcolor
        duration: 100
        easing.type: Easing.InOutElastic;
        easing.amplitude: 2.0;
        easing.period: 1.5
        onFinished: select()
    }

}
