import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Imagine 2.3
import QtQuick.Window 2.0
import "qrc:/component"

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

    //Options Menu
    Text {
        id: id_optionsmenu_text
        x: 224
        y: 22
        width: 350
        height: 57
        text: qsTr("Menu Options")
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
                stack.push(main_menu)
            }
        }
    }




    //Car Info
    Rectangle {
        id: id_carinfo_rectangle
        x: 0
        y: 100
        width: 266
        height: 190
        color: "#ffffff"
        border.color: "white"
        border.width: 1
        SampleButton{
            id: modeButton
            buttonWidth: 266
            buttonHeight: 190
            anchors.centerIn: parent
            Image {
                id: id_carinfo_image
                x: 48
                y: 27
                width: 168
                height: 117
                fillMode: Image.PreserveAspectFit
                source: "images/car.svg"
            }
            Text {
                id: id_carinfo_text
                text: qsTr("Car Info")
                anchors.topMargin: 145
                fontSizeMode: Text.Fit
                renderType: Text.NativeRendering
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 24
                color: "white"
            }
            onTouchReleased: {
                stack.push(carinfo)
            }
        }


       /* MouseArea {
            id: id_carinfo_mousearea
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            visible: true
            onClicked: {
                console.log("Button clicked!")// para debug do botao
                stack.push(windowauto)
            }
        }*/
    }

    //Network
    Rectangle {
        id: id_network_rectangle
        x: 266
        y: 100
        width: 266
        height: 190
        color: "#ffffff"
        border.color: "white"
        border.width: 1
        SampleButton{
            id: modeButton1
            buttonWidth: 266
            buttonHeight: 190
            anchors.centerIn: parent
            Image {
                id: id_network_image
                x: 75
                y: 39
                width: 117
                height: 89
                fillMode: Image.PreserveAspectFit
                source: "images/internet.svg"
            }
            Text {
                id: id_network_text
                text: qsTr("Network")
                anchors.topMargin: 145
                fontSizeMode: Text.Fit
                renderType: Text.NativeRendering
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 24
                color: "white"
            }
            onTouchReleased: {
                stack.push(news)
            }
        }

        /*MouseArea {
            id: id_network_mousearea
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            visible: true
            onClicked: {
                console.log("Button clicked!")// para debug do botao
            }
        }*/
    }

    //Settings
    Rectangle {
        id: id_settings_rectangle
        x: 532
        y: 100
        width: 266
        height: 190
        color: "#ffffff"
        border.color: "white"
        border.width: 1
        SampleButton{
            id: modeButton2
            buttonWidth: 266
            buttonHeight: 190
            anchors.centerIn: parent
            Image {
                id: id_settings_image
                x: 75
                y: 39
                width: 117
                height: 89
                fillMode: Image.PreserveAspectFit
                source: "images/settings.svg"
            }
            Text {
                id: id_settings_text
                text: qsTr("Settings")
                anchors.topMargin: 145
                fontSizeMode: Text.Fit
                renderType: Text.NativeRendering
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 24
                color: "white"
            }
            onTouchReleased: {
                stack.push(settings)
            }
        }

        /*MouseArea {
            id: id_settings_mousearea
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            visible: true
            onClicked: {
                console.log("Settings button clicked!")// para debug do botao
                stack.push(homeMainWindow)
            }
        }*/
    }

    //Camera
    Rectangle {
        id: id_camera_rectangle
        x: 0
        y: 290
        width: 266
        height: 190
        color: "#ffffff"
        border.color: "white"
        border.width: 1
        SampleButton{
            id: modeButton3
            buttonWidth: 266
            buttonHeight: 190
            anchors.centerIn: parent
            Image {
                id: id_camera_image
                x: 75
                y: 39
                width: 117
                height: 89
                fillMode: Image.PreserveAspectFit
                source: "images/camera.svg"
            }
            Text {
                id: id_camera_text
                text: qsTr("Camera")
                anchors.topMargin: 145
                fontSizeMode: Text.Fit
                renderType: Text.NativeRendering
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 24
                color: "white"
            }
            onTouchReleased: {
                myclass.openCamera()
                stack.push(camera)
            }
        }

       /* MouseArea {
            id: id_camera_mousearea
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            visible: true
            onClicked: {
                console.log("Button clicked!")// para debug do botao
                myclass.openCamera()
                stack.push(camera)
            }
        }*/
    }

    //Music
    Rectangle {
        id: id_music_rectangle
        x: 266
        y: 290
        width: 266
        height: 190
        color: "#ffffff"
        border.color: "white"
        border.width: 1
        SampleButton{
            id: modeButton4
            buttonWidth: 266
            buttonHeight: 190
            anchors.centerIn: parent
            Image {
                id: id_music_image
                x: 75
                y: 39
                width: 117
                height: 89
                fillMode: Image.PreserveAspectFit
                source: "images/music-file.svg"
            }
            Text {
                id: id_music_text
                text: qsTr("Music")
                anchors.topMargin: 145
                fontSizeMode: Text.Fit
                renderType: Text.NativeRendering
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 24
                color: "white"
            }
            onTouchReleased: {
                stack.push(music)
            }
        }


        /*MouseArea {
            id: id_music_mousearea
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            visible: true
            onClicked: {
                console.log("Button clicked!")// para debug do botao
                stack.push(music)
            }
        }*/
    }

    //Ambient Light
    Rectangle {
        id: id_ambientlight_rectangle
        x: 532
        y: 290
        width: 266
        height: 190
        color: "#ffffff"
        border.color: "white"
        border.width: 1
        SampleButton{
            id: modeButton5
            buttonWidth: 266
            buttonHeight: 190
            anchors.centerIn: parent
            Image {
                id: id_ambientlightblue_image
                x: 40
                y: 17
                width: 85
                height: 58
                fillMode: Image.PreserveAspectFit
                source: "images/light-blue.svg"
            }
            Image {
                id: id_ambientlightgreen_image
                x: 131
                y: 17
                width: 85
                height: 58
                fillMode: Image.PreserveAspectFit
                source: "images/light-green.svg"
            }
            Image {
                id: id_ambientlightred_image
                x: 40
                y: 81
                width: 85
                height: 58
                fillMode: Image.PreserveAspectFit
                source: "images/light-red.svg"
            }
            Image {
                id: id_ambientlightyellow_image
                x: 131
                y: 81
                width: 85
                height: 58
                fillMode: Image.PreserveAspectFit
                source: "images/light-yellow.svg"
            }
            Text {
                id: id_ambientlight_text
                text: qsTr("Ambient Light")
                anchors.topMargin: 145
                fontSizeMode: Text.Fit
                renderType: Text.NativeRendering
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 24
                color: "white"
            }
            onTouchReleased: {
                stack.push(ambient_light_menu)
            }
        }


        /*MouseArea {
            id: id_ambientlight_mousearea
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            visible: true
            onClicked: {
                console.log("Button clicked!")// para debug do botao
                stack.push(ambient_light_menu)
            }
        }*/
    }

}
