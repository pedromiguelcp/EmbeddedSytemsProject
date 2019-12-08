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
        anchors.topMargin: 75
        anchors.fill: parent

        RowLayout {
            id: mainRowLayout
            anchors.fill: parent

            ColumnLayout {
                    id: carinfosRowLayout
                    y: 0

                    Label {
                        text: qsTr("Car informations")
                        color: "red"
                        leftPadding: 60
                        rightPadding: 0
                        topPadding: 50
                        bottomPadding: 0

                        Layout.fillWidth: true

                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.topMargin: 16

                        Label {
                            text: qsTr("Speed")
                            color: "white"
                            anchors.left: parent.left

                        }

                        Text  {
                            text: myclass.car_speed + qsTr("km/h")
                            color: "white"
                            anchors.right: parent.right
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.topMargin: 16

                        Label {
                            text: qsTr("RPM")
                            color: "white"
                            anchors.left: parent.left
                        }

                        Label  {
                            text: myclass.car_rpm + qsTr("rpm")
                            color: "white"
                            anchors.right: parent.right
                        }
                    }

                    Item {
                        implicitHeight: swpowerValueLabel.implicitHeight
                        Layout.fillWidth: true
                        Layout.topMargin: 16
                        Layout.bottomMargin: 360

                        Label {
                            text: qsTr("Engine temperature")
                            color: "white"
                            anchors.baseline: swpowerValueLabel.bottom
                            anchors.left: parent.left
                        }

                        Label  {
                            id: swpowerValueLabel
                            text: myclass.car_enginetemp + qsTr("ºC")
                            color: "white"
                            anchors.right: parent.right
                        }
                    }
            }

            Rectangle {
                color: colorMain
                implicitWidth: 1
                Layout.fillHeight: true
            }

            ColumnLayout {
                Image {
                    height: 1100
                    source: "images/carinfo.svg"
                    fillMode: Image.PreserveAspectFit

                }
            }

            Rectangle {
                color: colorMain
                implicitWidth: 1
                Layout.fillHeight: true
            }

            ColumnLayout {

                    id: externalcarinfosRowLayout
                    y: 0

                    Label {
                        text: qsTr("External car informations")
                        color: "red"
                        leftPadding: 30
                        rightPadding: 0
                        topPadding: 50
                        bottomPadding: 0

                        Layout.fillWidth: true

                    }

                    // QTBUG-63269
                    Item {
                        Layout.fillWidth: true
                        Layout.topMargin: 16

                        Label {
                            text: qsTr("Temperature")
                            color: "white"
                            anchors.left: parent.left
                        }

                        Label  {
                            text: myclass.car_temp + qsTr("ºC")
                            color: "white"
                            anchors.right: parent.right
                        }
                    }

                    // QTBUG-63269
                    Item {
                        Layout.fillWidth: true
                        Layout.topMargin: 16
                        Layout.bottomMargin: 400

                        Label {
                            text: qsTr("Brightness")
                            color: "white"
                            anchors.left: parent.left
                        }

                        Label  {
                            text: myclass.car_bright + qsTr("%")
                            color: "white"
                            anchors.right: parent.right
                        }
                    }
            }

        }
    }
}

