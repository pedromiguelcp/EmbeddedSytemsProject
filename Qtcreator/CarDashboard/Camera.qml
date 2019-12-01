import QtQuick 2.0
import QtQuick.Controls 2.4
import Qt.labs.folderlistmodel 2.2
import QtQuick.Layouts 1.3

Item {
    width: 800

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
