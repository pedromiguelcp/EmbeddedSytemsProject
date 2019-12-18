import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Window 2.0


Item {
    width: 800
    height: 500

    Rectangle {
        width: 800; height: 500
        gradient: Gradient {
            GradientStop { position: 0.0; color: "purple" }
            GradientStop { position: 1.0; color: "blue" }
        }
    }
    Component.onCompleted: {
        x = Screen.width / 1 - width / 8
        y = Screen.height / 1 - height / 8
    }


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
        y: 100
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
        y:140
        from:1
        value: myclass.car_bright
        to:255
        stepSize: 1.0
        onMoved: {
            myclass.adjustDashBright(value)
        }
    }

    Text {
        id: id_settingsmenu_text11
        x: 465
        y: 100
        width: 161
        height: 53
        text: qsTr("Network")
        font.bold: false
        elide: Text.ElideLeft
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 28
    }

    TextField {
        id: nwSSID
        x:470
        y:140
        width: 150
        height: 50
        placeholderText: qsTr("SSID")
    }

    TextField {
        id: nwPSW
        x:470
        y:180
        width: 150
        height: 50
        placeholderText: qsTr("Password")
    }
    Button {
        x:635
        y:200
        width: 100
        height: 30

            text: "Connect"
            onClicked: myclass.newNetworkConfig(nwSSID.text, nwPSW.text)
    }

}
