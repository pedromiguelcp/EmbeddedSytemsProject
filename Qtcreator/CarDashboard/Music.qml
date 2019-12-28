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
        color: "transparent"

        Image {
            id: id_playmusic_image
            x: 356
            y: 7
            width: 89
            height: 70
            //fillMode: Image.PreserveAspectFit
            source: "images/music-play.svg"
            MouseArea {
                id: id_musicplay_mousearea
                anchors.fill: parent
                onClicked: {
                    myclass.pauseSong()
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
                anchors.fill: parent
                onClicked: {
                    //myclass.selectSong(folderModel.get(2,"/media1"))
                    myclass.nextSong()
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
                anchors.fill: parent
                onClicked: {
                    myclass.previousSong()
                }
            }
         }

        Slider {
            x:586
            y:37
            from:1
            value: myclass.getMusicVolume()
            to:100
            stepSize: 1.0
            onMoved: {
                myclass.controlMusicVolume(value)
            }
        }

        Image {
            id: id_musicvolume_image
            x:669
            y:0
            width: 35
            height: 35
            source: "images/music-volume.svg"
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
        background: color("blue")



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
