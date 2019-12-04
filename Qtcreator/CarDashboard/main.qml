import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import MyClassLib 1.0
import QtQuick.VirtualKeyboard 2.2

Window {
    id: window
    visible: true
    width: 800
    height: 480
    FontLoader { id: fixedFont; name: "Courier" }
    FontLoader { id: webFont; source: "qrc:/OpenSans-Bold.ttf" }


    title: "Car Dashboard"
    property bool bNewsVisibility:      true
    property bool bWeatherVisibility:   true
    property bool bTimeVisibility:      true
    property bool bTempVisibility:      true
    property int  iCityID:              2742032 //valor por defeito da cidade


    property var date:          new Date();
    property int currentDay:    date.getDate()
    property int currentMonth:  date.getMonth()
    property int currentYear:   date.getFullYear()
    property int week:          date.getDay()



    Timer{
        id:timer_for_clock
        interval: 1000
        running: true
        repeat: true

        onTriggered: {
            window.date = new Date()
            currentDay: window.date.getDate()
            currentMonth: window.date.getMonth()
            currentYear: window.date.getFullYear()
            week: window.date.getDay()
        }
    }




    StackView {
        id: stack
        initialItem: main_menu
    }

    Component{
        id: main_menu
        MainMenu{}
    }

    Component{
        id: choice_menu
        ChoiceMenu{}
    }

    Component{
        id: ambient_light_menu
        AmbientLight{}
    }

    Component{
        id: music
        Music{}
    }

    Component{
        id: windowauto
        Automotive{}
    }

    Component{
        id: camera
        Camera{}
    }

    Component{
        id: settings
        Settings{}
    }

    Component{
        id: network
        Network{}
    }

    InputPanel {
        id: inputPanel
        z: 89
        y: active ? parent.height - height : parent.height
        anchors.left: parent.left
        anchors.right: parent.right
        //InputMethod: Qt.ImhUppercaseOnly | Qt.ImhDigitsOnly
    }
}
