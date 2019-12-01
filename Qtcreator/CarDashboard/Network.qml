import QtQuick 2.0
import QtQuick.Controls 2.4
import Qt.labs.folderlistmodel 2.2
import QtQuick.Layouts 1.3

Item {
    width: 800

    //Network Menu
    Text {
        id: id_networkmenu_text
        x: 224
        y: 22
        width: 350
        height: 57
        text: qsTr("Network Menu")
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

    Frame {
        id: filesFrame
        y: 100
        width: 800
        height: 285
        leftPadding: 1
        rightPadding: 1

        Layout.fillWidth: true
        Layout.fillHeight: true


        ListView {
            clip: true
            visible: true
            anchors.fill: parent
            id:myListView
            y: 0
            width: 310
            height: 228

            model: ListView {
                id: listModel
                Text {
                    id: name
                    width: 86
                    height: 69
                    text: qsTr("text")
                }
                /*folder: "file:" + myclass.getDeviceSongs()
                nameFilters: ["*.mp3"]
                showFiles: true
                showDirs: false*/
            }

            delegate: ItemDelegate {
                id: mydelegate
                text: fileName
                width: parent.width
                property int indexOfThisDelegate: index

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        myListView.currentIndex = index
                        myclass.selectSong(mydelegate.text)
                        //  console.log(mydelegate.text)
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {
                parent: filesFrame
                policy: ScrollBar.AlwaysOn
                anchors.top: parent.top
                anchors.topMargin: filesFrame.topPadding
                anchors.right: parent.right
                anchors.rightMargin: 1
                anchors.bottom: parent.bottom
                anchors.bottomMargin: filesFrame.bottomPadding
            }
        }
    }
}
