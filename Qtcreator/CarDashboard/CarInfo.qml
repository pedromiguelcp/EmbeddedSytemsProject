import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Imagine 2.3
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

    //Settings Menu
    Text {
        id: id_carinfomenu_text
        x: 224
        y: 22
        width: 350
        height: 57
        text: qsTr("Car Informations")
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

    readonly property color colorGlow: "#1d6d64"
    readonly property color colorWarning: "#d5232f"
    readonly property color colorMain: "#d5232f"
    readonly property color colorBright: "#ffffff"
    readonly property color colorLightGrey: "#888"
    readonly property color colorDarkGrey: "#333"

    Component.onCompleted: {
        x = Screen.width / 1 - width / 8
        y = Screen.height / 1 - height / 8
    }

    Frame {
        id: frame
        topPadding: 10
        visible: true
        opacity: 1
        scale: 1
        anchors.bottomMargin: 0
        anchors.topMargin: 75
        anchors.fill: parent
        background: color("black")


        RowLayout {
            id: mainRowLayout
            scale: 1
            anchors.fill: parent


            ColumnLayout {
                    id: carinfosRowLayout
                    y: 0
                    height: 400
                    Layout.rightMargin: 0
                    Layout.maximumWidth: 350

                    Label {
                        text: qsTr("Car informations")
                        color: "red"
                        leftPadding: 60
                        rightPadding: 0
                        topPadding: 50
                        Layout.fillWidth: true
                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.topMargin: 16

                    Image {
                        width: 30
                        height: 30
                        visible: true
                        source: "images/speedometer.svg"
                        }

                        Text  {
                            x: 80
                            text: myclass.car_speed + qsTr(" km/h")
                            color: "white"
                            font.pointSize: 24
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.topMargin: 31
                        Image {
                            width: 30
                            height: 30
                            visible: true
                            source: "images/RPMs.svg"
                            }
                        Text  {
                            x: 80
                            text: myclass.car_rpm + qsTr(" rpm")
                            color: "white"
                            font.pointSize: 24
                        }
                    }

                    Item {
                        implicitHeight: swpowerValueLabel.implicitHeight
                        Layout.fillWidth: true
                        Layout.topMargin: 34
                        Image {
                            width: 30
                            height: 30
                            visible: true
                            source: "images/engine.svg"
                            }
                        Text  {
                            x: 80
                            id: swpowerValueLabel
                            text: myclass.car_enginetemp + qsTr(" ºC")
                            color: "white"
                            font.pointSize: 24
                        }
                    }



                    Label {
                        text: qsTr("External car informations")
                        color: "red"
                        leftPadding: 30
                        rightPadding: 30
                        topPadding: 50

                        Layout.fillWidth: true

                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.topMargin: 4
                        Image {
                            width: 30
                            height: 30
                            visible: true
                            source: "images/temperature.svg"
                            }
                        Text  {
                            x: 80
                            text: myclass.car_temp + qsTr(" ºC")
                            color: "white"
                            font.pointSize: 24
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.topMargin: 30
                        Image {
                            width: 30
                            height: 30
                            visible: true
                            source: "images/brightness.svg"
                            }
                        Text  {
                            x: 80
                            text: myclass.car_bright + qsTr(" %")
                            color: "white"
                            font.pointSize: 24
                        }
                    }

                    Label {
                        color: "red"
                        leftPadding: 60
                        rightPadding: 0
                        topPadding: 50
                        bottomPadding: 500

                        Layout.fillWidth: true

                    }
            }

            Rectangle {
                height: 400
                color: colorMain
                implicitWidth: 1
                Layout.fillHeight: true
            }

            ColumnLayout {
                y: 0
                height: 400
                Image {
                    source: "images/carinfo.svg"
                    Layout.bottomMargin: 500
                }
            }

            Rectangle {
                height: 400
                color: colorMain
                implicitWidth: 1
                Layout.fillHeight: true
            }

            ColumnLayout {

                    id: externalcarinfosRowLayout
                    y: -100
                    height: 400
                    Layout.rightMargin: 25

                    Label {
                        text: qsTr("Car problems detected")
                        color: "red"
                        leftPadding: 30
                        rightPadding: 0
                        topPadding: 50
                        bottomPadding: 0

                        Layout.fillWidth: true

                    }
                    Column {
                        height: 100
                        width: 230
                        Layout.leftMargin: 30
                        Layout.fillWidth: true
                        Layout.bottomMargin: 750
                        Repeater {
                            id: news_repeater
                            x: 0
                            model: [myclass.getCarProblems()]
                            Text {
                                x: -10
                                font.pixelSize: 16
                                text: modelData
                                color: "White"
                            }
                        }
                    }


            }

        }
    }
}


