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
