import QtQuick

Rectangle {
    id: questionbox
    width: parent.width-50
    height: 135

    color: "#F8F8FF"
    border.color: "#21ABCD"

    signal accept()
    signal cancel()

    property string caption: "Question"
    property string captioncolor: "steelblue"
    property string message: "Here stands the question for the user or gamer"
    property string messagecolor: "#4997D0"
    Text {
        id: ctext
        width: parent.width
        text: caption
        color: captioncolor
        font.pointSize: 15
        font.bold: true
        font.letterSpacing: 2
        horizontalAlignment: Text.AlignHCenter
        //anchors.horizontalCenter: parent
        //verticalAlignment: Text.AlignVCenter
        //topPadding: 5
    }
    Text {
        id: mtext
        width: parent.width-10
        height: parent.height-ctext.height-25-10
        text: message
        color: captioncolor
        font.pointSize: 12
        font.letterSpacing: 2
        horizontalAlignment: Text.AlignLeft
        leftPadding: 5
        anchors.top: ctext.bottom
        topPadding: 5
        wrapMode: Text.WordWrap
    }

    Row{
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10
        FButton{
            id: noBtn
            buttontext: "No"
            width: 80
            height: 25
            onSelect: { cancel() }
        }
        FButton{
            id: yesBtn
            buttontext: "Yes"
            width: 80
            height: 25
            onSelect: { accept() }
        }
    }

}
