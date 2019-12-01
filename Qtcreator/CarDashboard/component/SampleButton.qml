import QtQuick 2.0

Rectangle {
    id: sampleButtonComponent

    property int buttonWidth: 0
    property int buttonHeight: 0
    property string buttonText: ""
    property int isState: 0xFFFF // true(1) : tabButton / false(0) : backButton
    property color customButtonColor: "#222222"
    property color buttonColor: {
        if(buttonFocus==true)
        {
            if(buttonTouchArea.pressed) "skyblue"
            else                        customButtonColor
        }
        else
        {
            "#110000"
        }
    }

    property color buttonTextColor: {
        if(buttonFocus==true)
        {
            if(buttonTouchArea.pressed) "black"
            else                        "white"
        }
        else
        {
            "#666666"
        }
    }
    property int buttonTextSize: 0
    property bool buttonFocus: true

    signal touchPressed()
    signal touchReleased()
    signal touchLongPressed()

    width: buttonWidth
    height: buttonHeight
    radius: 5
    focus: buttonFocus

    color: buttonColor

    Text{
        id: buttonTextArea
        text: buttonText
        font.pixelSize: buttonTextSize
        font.bold: true
        font.family: "SpoqaHanSans"
        color: buttonTextColor
        anchors.centerIn: parent
    }

    MouseArea{
        id: buttonTouchArea
        anchors.fill: parent
        onPressed: {
            sampleButtonComponent.touchPressed()
        }
        onReleased: {
            sampleButtonComponent.touchReleased()
        }
        onPressAndHold: {
            sampleButtonComponent.touchLongPressed()
        }
    }
}
