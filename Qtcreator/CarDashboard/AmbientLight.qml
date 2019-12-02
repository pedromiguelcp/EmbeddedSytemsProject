import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    width: 800

    //Ambient Light Menu
    Text {
        id: id_ambientlightmenu_text
        x: 224
        y: 22
        width: 350
        height: 57
        text: qsTr("Ambient Light")
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideLeft
        font.pixelSize: 36
    }

    //Back
    Image {
        id: id_back_img
        x: 10
        y: 20
        width: 50
        height: 50
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/back.svg"
        MouseArea {
            id: id_back_mousearea
            anchors.fill: parent
            onClicked: {
                stack.pop()
            }
        }
    }
    SwitchDelegate {
        text: qsTr("AC")
        leftPadding: 0
        rightPadding: 0
        topPadding: 0
        bottomPadding: 0

    }

    Image {
        id: id_lightoff_img
        x: 100
        y: 150
        width: 100
        height: 100
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/light-off.svg"
        MouseArea {
            id: id_lightoff_mousearea
            anchors.fill: parent
            onClicked: {
                myclass.setColor("0")
            }
        }
    }
    Image {
        id: id_lightblue_img
        x: 200
        y: 150
        width: 100
        height: 100
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/light-blue.svg"
        MouseArea {
            id: id_lightblue_mousearea
            anchors.fill: parent
            onClicked: {
                myclass.setColor("4")
            }
        }
    }
    Image {
        id: id_lightred_img
        x: 300
        y: 150
        width: 100
        height: 100
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/light-red.svg"
        MouseArea {
            id: id_lightred_mousearea
            anchors.fill: parent
            onClicked: {
                myclass.setColor("1")
            }
        }
    }
    Image {
        id: id_lightgreen_img
        x: 400
        y: 150
        width: 100
        height: 100
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/light-green.svg"
        MouseArea {
            id: id_lightgreen_mousearea
            anchors.fill: parent
            onClicked: {
                 //myclass.setColor("2")
                 myclass.sendCommand("VER \n")
            }
        }
    }
    Image {
        id: id_lightmagenta_img
        x: 500
        y: 150
        width: 100
        height: 100
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/light-magenta.svg"
        MouseArea {
            id: id_lightmagenta_mousearea
            anchors.fill: parent
            onClicked: {
                myclass.setColor("5")
            }
        }
    }
    Image {
        id: id_lightaqua_img
        x: 600
        y: 150
        width: 100
        height: 100
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/light-aqua.svg"
        MouseArea {
            id: id_lightaqua_mousearea
            anchors.fill: parent
            onClicked: {
                myclass.setColor("6")
            }
        }
    }


}
