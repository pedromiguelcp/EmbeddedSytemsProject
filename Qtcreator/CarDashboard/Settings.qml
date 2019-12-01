import QtQuick 2.0

Item {
    width: 800

    //Settings Menu
    Text {
        id: id_settingsmenu_text
        x: 224
        y: 22
        width: 350
        height: 57
        text: qsTr("Settings")
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideLeft
        font.pixelSize: 36
    }

    //Back
    Image {
        id: id_back_img
        x: 0
        y: 0
        width: 100
        height: 100
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/Back.png"
        MouseArea {
            id: id_back_mousearea
            anchors.fill: parent
            onClicked: {
                stack.pop()
            }
        }
    }

    Text {
        id: id_settingsmenu_text1
        x: 128
        y: 157
        width: 161
        height: 53
        text: qsTr("Brightness")
        font.bold: false
        elide: Text.ElideLeft
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 28
    }

    Image {
        id: id_decrease_Bright
        x: 105
        y: 180
        width: 100
        height: 100
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/BrightMinus.png"
        MouseArea {
            id: id_decrease_mousearea
            anchors.fill: parent
            onClicked: {
                myclass.adjustDashBright("-")
            }
        }
    }

    Image {
        id: id_inscrease_Bright
        x: 215
        y: 180
        width: 100
        height: 100
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/BrightPlus.png"
        MouseArea {
            id: id_inscrease_mousearea
            anchors.fill: parent
            onClicked: {
                myclass.adjustDashBright("+")
            }
        }
    }

}
