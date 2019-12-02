import QtQuick 2.0
import QtQuick.Controls 2.4

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

    Text {
        id: id_settingsmenu_text1
        x: 111
        y: 151
        width: 161
        height: 53
        text: qsTr("Brightness")
        font.bold: false
        elide: Text.ElideLeft
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 28
    }
    Slider {
        x:90
        y:180
        from:1
        value: myclass.getDashBright()
        to:255
        stepSize: 1.0
        onMoved: {
            myclass.adjustDashBright(value)
        }
    }

/*    Image {
        id: id_decrease_Bright
        x: 105
        y: 190
        width: 70
        height: 70
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/bright-minus.svg"
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
        y: 190
        width: 70
        height: 70
        visible: true
        fillMode: Image.PreserveAspectFit
        source: "images/bright-plus.svg"
        MouseArea {
            id: id_inscrease_mousearea
            anchors.fill: parent
            onClicked: {
                myclass.adjustDashBright("+")
            }
        }
    }*/

}
