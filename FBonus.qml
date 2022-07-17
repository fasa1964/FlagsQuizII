import QtQuick

Rectangle {
    id: bonus

    height: 40
    width: 70
    radius: 5
    color: "orange"
    opacity: 0.0

    border.color: "green"
    border.width: 2


    property string bonustext: "50€"


    Text {
        id: name
        text: bonustext
        anchors.centerIn: parent
        color: "blue"

    }

    function startAnimate(){
          panimation.running = true
    }


    ParallelAnimation{
        id: panimation

        NumberAnimation {
            target: bonus
            property: "x"
            to: 30
            duration: 800
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: bonus
            property: "y"
            to: parent.height-50
            duration: 800
            easing.type: Easing.InOutBounce
        }
        NumberAnimation {
            target: bonus
            property: "opacity"
            to: 1.0
            duration: 200
            easing.type: Easing.InOutCubic
        }
    }
}
