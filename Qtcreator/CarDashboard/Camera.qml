import QtQuick 2.0
import QtQuick.Controls 2.4
import Qt.labs.folderlistmodel 2.2
import QtQuick.Layouts 1.3
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

    Rectangle {
        x:690
        y:0
        width: 110; height: 50
        color: "#edd400"
        Text {
            width: 32
            height: 26
            text: myclass.distancetoobjects
            font.pointSize: 33

        }

        Text {
            width: 32
            height: 26
            x:80
            y:20
            text: qsTr("cm")
            font.pointSize: 15

        }
    }
    Component.onCompleted: {
        x = Screen.width / 1 - width / 8
        y = Screen.height / 1 - height / 8
    }
    //Music Menu
    Text {
        id: id_musicmenu_text
        x: 224
        y: 22
        width: 350
        height: 57
        text: qsTr("Car's camera")
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
                myclass.closeCamera()
                stack.pop()
            }
        }
    }
}
