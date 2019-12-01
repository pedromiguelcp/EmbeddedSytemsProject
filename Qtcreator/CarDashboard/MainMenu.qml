import QtQuick 2.0
import QtQuick.VirtualKeyboard 2.2
import QtQuick.Controls 2.3
import Qt.labs.calendar 1.0
import QtQuick.Extras 1.4 //import gauges
import QtQuick.Controls.Styles 1.4//import gauge style

Item {
    id: element
    width: 800

    property var months: ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]
    property var weekNames: ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]

            Image
            {
              source: "qrc:/images/BackGround.png"
            }
    //shut down image
    Image {
        id: id_shut_down_img
        x: 700
        y: 0
        width: 100
        height: 100
        opacity: 1
        source: "images/OnOff.png"
        visible: true

        MouseArea{
            x:0
            y:0
            width: parent.width
            height: parent.height

            onClicked: {
                myClass.quitApp()
                //Qt.quit()
            }
        }
    }

    //VARIAVEL A DIZER AS HORAS ATUAIS
    Rectangle{
        id:timeDateBox
        //time var
        x:200
        y:0
        color: "white"
        width: 400
        height: 100
        border.width: 1
        border.color: "blue"

        Text {
            id: id_time_var
            x: 0
            y: 0
            text: qsTr(date.getHours()+":"+(date.getMinutes()<10?'0':'') + date.getMinutes())
            renderType: Text.QtRendering
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideLeft
            font.pixelSize: 100
            visible: window.bTimeVisibility
        }

        //date var
        Text {
            id: id_date_var
            x: 0
            y: 125
            text: qsTr(currentDay + " of " + months[currentMonth] + ", " + currentYear)
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 38
            visible: window.bTimeVisibility
        }

    }

    //choice menu button
    Image {
        id: id_button_menu1
        x: 0
        y: 0
        width: 100
        height: 100
        opacity: 1
        source: "images/Options.png"
        visible: true
        //mousearea, click to go for MainMenu
        MouseArea {
            id: id_mouseArea_ButtonMenu1
            x: 0
            y: 0
            width: 100
            height: 100
            visible: true
            onClicked: {
                stack.push(choice_menu)
            }
        }
    }
}
