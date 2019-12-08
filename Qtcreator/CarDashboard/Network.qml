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

    //news ITEM
    Rectangle{
        x:0
        y:76
        width: 792
        height: 404
        border.color: "black"
        border.width: 1

        Text {
            id: id_news
            x: 10
            y: 0
            text: qsTr("News:\n\n")
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideLeft
            font.pixelSize: 20
        }

        Column {
            x: 15
            y: 30
            width: 0
            height: 27
            spacing: 5
            Repeater {
                id: news_repeater
                x: 0
                model: [myclass.getNews(0),
                    myclass.getNews(1),
                    myclass.getNews(2),
                    myclass.getNews(3),
                    myclass.getNews(4)
                ]
                Text {
                    x: -10
                    font.pixelSize: 16
                    text: modelData
                }
            }
        }
    }
}
