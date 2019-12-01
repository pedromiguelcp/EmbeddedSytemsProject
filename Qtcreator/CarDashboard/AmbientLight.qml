import QtQuick 2.0

Item {
    width: 800

    //Ambient Light Menu
    Text {
        id: id_ambientlightmenu_text
        x: 224
        y: 22
        width: 350
        height: 57
        text: qsTr("Ambient Light Menu")
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


    Rectangle {
        id: id_turn_off_rectangle
        x: 494
        y: 166
        width: 100
        height: 100
        color: "#090808"
        border.width: 0
        border.color: "#000000"
        /*Text {
            id: id_turn_off_text
            color: "#ffffff"
            text: qsTr("Turn Off")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 18
        }*/
        MouseArea {
            id: id_turn_off_mousearea
            width: id_turn_off_rectangle.width
            height: id_turn_off_rectangle.height
            onClicked: {
                myclass.setColor("0")
            }
        }
    }

    Rectangle {
        id: id_red_rectangle
        x: 49
        y: 186
        width: 143
        height: 39
        color: "#ff0000"
        border.width: 0
        border.color: "#000000"
        /*Text {
            id: id_red_text
            text: qsTr("Red")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 24
        }*/
        MouseArea {
            id: id_red_button
            width: parent.width
            height: parent.height
            onClicked: {
                myclass.setColor("1")
            }
        }
    }

    Rectangle {
        id: id_green_rectangle
        x: 48
        y: 237
        width: 144
        height: 39
        color: "#00ff00"
        border.width: 0
        border.color: "#000000"
        /*Text {
            id: id_green_text
            text: qsTr("Green")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }*/
        MouseArea {
            id: id_green_button
            width: id_green_rectangle.width
            height: id_green_rectangle.height
            onClicked: {
               // myclass.setColor("2")
                myclass.sendCommand("VER \n")
            }
        }

    }

    Rectangle {
        id: id_blue_rectangle
        x: 48
        y: 141
        width: 144
        height: 39
        color: "#0000ff"
        border.width: 0
        border.color: "#000000"
        /*Text {
            id: id_blue_text
            text: qsTr("Blue")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }*/
        MouseArea {
            id: id_blue_button
            width: parent.width
            height: parent.height
            enabled: true
            onClicked: {
                myclass.setColor("4")
            }
        }
    }

    Rectangle {
        id: id_cyan_rectangle
        x: 50
        y: 347
        width: 140
        height: 39
        color: "#00ffff"
        border.width: 0
        border.color: "#000000"
        /*Text {
            id: id_cyan_text
            text: qsTr("Cyan")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }*/
        MouseArea {
            id: id_cyan_button
            x: 0
            y: 0
            width: 145
            height: 39
            onClicked: {
                myclass.setColor("6")
            }
        }
    }

    Rectangle {
        id: id_violet_rectangle
        x: 48
        y: 290
        width: 144
        height: 39
        color: "#880b8b"
        border.width: 0
        border.color: "#000000"
        /*Text {
            id: id_magenta_text
            text: qsTr("Violet")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }*/
        MouseArea {
            id: id_violet_button
            y: 0
            width: 0
            height: 37
            scale: 1
            onClicked: {
                myclass.setColor("5")
            }
        }
    }
}
