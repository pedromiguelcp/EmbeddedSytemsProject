import QtQuick 2.0

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

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        spacing: 6

        Rectangle { color: "#6cc4e0"; radius: 10.0
            width: 700; height: 50;
                    Text { anchors.centerIn: parent
                           font.pointSize: 11; text: myclass.getNews(0) } }
        Rectangle { color: "#50eb50"; radius: 10.0
            width: 700; height: 50
                    Text { anchors.centerIn: parent
                           font.pointSize: 11; text: myclass.getNews(1) } }
        Rectangle { color: "#6cc4e0"; radius: 10.0
                    width: 700; height: 50
                    Text { anchors.centerIn: parent
                           font.pointSize: 11; text: myclass.getNews(2) } }
        Rectangle { color: "#50eb50"; radius: 10.0
            width: 700; height: 50
            Text { anchors.centerIn: parent
                font.pointSize: 11; text: myclass.getNews(3) } }
        Rectangle { color: "#6cc4e0"; radius: 10.0
            width: 700; height: 50
            Text { anchors.centerIn: parent
                font.pointSize: 11; text: myclass.getNews(4) } }
    }
}
