import QtQuick

Rectangle {
    id: downloadpage

    width: parent.width - 40
    height: parent.height - 80
    x: parent.width

    border.color: "steelblue"
    color: "#FEFCFF"

    property int size: 12

    property string btext:  qsTr("Start to download game data")

    function openDownloadPage(){
        downloadpage.visible = true;
        open.start();
    }

    function closeDownloadPage(){  close.start() }

    // Menu animation
    NumberAnimation {
         id: open
         target: downloadpage
         property: "x"
         duration: 750
         to: 20
         easing.type: Easing.InOutBack
     }

    NumberAnimation {
         id: close
         target: downloadpage
         property: "x"
         duration: 750
         to: parent.width
         easing.type: Easing.InOutQuad
         onStopped: { downloadpage.visible = false }
     }

    FButton{
        id: startDownloadBtn
        buttontext: btext
        width: parent.width - 40
        height: 38
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 5
        onSelect: {  setup.startDownloadGamesData("Flags")  }
    }


    Column{
        spacing: 5
        anchors.top: startDownloadBtn.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 10
        Row{
            x:5
            Text { text: qsTr("File: "); font.pointSize: size; font.letterSpacing: 2 }
            Text { text: setup.downloadFilename; font.pointSize: size; color: "blue" }
        }
        Row{
            x:5
            Text { text: qsTr("Speed: "); font.pointSize: size; font.letterSpacing: 2   }
            Text { text: setup.downloadSpeed + " " + setup.unit; font.pointSize: size; color: "blue"  }
        }
        Row{
            x:5
            Text { text: qsTr("Bytes: "); font.pointSize: size; font.letterSpacing: 2   }
            Text { text: setup.receivedBytes; font.pointSize: size; color: "blue"  }
            Text { text: setup.unit; font.pointSize: size; color: "blue"  }
        }
        Row{
            x:5
            Text { text: qsTr("Total bytes: "); font.pointSize: size; font.letterSpacing: 2   }
            Text { text: setup.totalBytes ; font.pointSize: size; color: "blue"  }
        }
    }
}
