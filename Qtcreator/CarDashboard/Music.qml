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
        text: qsTr("Music Menu")
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

    //Music Control
    Rectangle {
        id: id_musiccontrol_rectangle
        x: 0
        y: 385
        width: 800
        height: 95
        color: "#ffffff"
        border.color: "white"
        border.width: 1

        Image {
            id: id_playmusic_image
            x: 356
            y: 7
            width: 89
            height: 81
            //fillMode: Image.PreserveAspectFit
            source: "images/music-play.svg"
            MouseArea {
                id: id_musicplay_mousearea
                anchors.rightMargin: 70
                anchors.bottomMargin: -190
                anchors.leftMargin: -70
                anchors.topMargin: 190
                anchors.fill: parent
                onClicked: {
                    myclass.resumeSong()
                }
            }
        }

        Image {
            id: id_nextmusic_image
            x: 516
            y: 26
            width: 35
            height: 35
            //fillMode: Image.PreserveAspectFit
            source: "images/music-forward.svg"
            MouseArea {
                id: id_musicnext_mousearea
                anchors.rightMargin: -150
                anchors.bottomMargin: 0
                anchors.leftMargin: 160
                anchors.topMargin: 18
                anchors.fill: parent
                onClicked: {
                    myclass.pauseSong()
                }
            }
         }

        Image {
            id: id_backmusic_image
            x: 221
            y: 26
            width: 35
            height: 35
            //fillMode: Image.PreserveAspectFit
            source: "images/music-backward.svg"
            MouseArea {
                id: id_musicback_mousearea
                anchors.rightMargin: -150
                anchors.bottomMargin: 0
                anchors.leftMargin: 160
                anchors.topMargin: 18
                anchors.fill: parent
                onClicked: {
                    myclass.pauseSong()
                }
            }
         }
    }
    Slider {
        x:590
        y:410
        from:1
        value: myclass.getMusicVolume()
        to:100
        stepSize: 1.0
        onMoved: {
            myclass.controlMusicVolume(value)
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

            model: FolderListModel {
                id: folderModel
                folder: "file:" + myclass.getDeviceSongs()
                nameFilters: ["*.mp3"]
                showFiles: true
                showDirs: false
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
