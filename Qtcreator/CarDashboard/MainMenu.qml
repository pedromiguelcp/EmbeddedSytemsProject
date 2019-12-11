import QtQuick 2.0
import QtQuick.VirtualKeyboard 2.2
import QtQuick.Controls 2.3
import Qt.labs.calendar 1.0
import QtQuick.Extras 1.4 //import gauges
import QtQuick.Controls.Styles 1.4//import gauge style

Item {
    id: element
    width: 800


    Image
    {
      source: "images/sky-background.svg"
    }


    Image {
        id: id_shut_down_img
        x: 700
        y: 0
        width: 100
        height: 100
        opacity: 1
        source: "images/power-off.svg"
        visible: true

        MouseArea{
            x:0
            y:0
            width: parent.width
            height: parent.height

            onClicked: {
                myclass.quitApp()
                //Qt.quit()
            }
        }
    }


    Rectangle{
        id:infobox
        x:200
        y:0
        color: "transparent"
        width: 400
        height: 80
        border.width: 1
        border.color: "transparent"

        Image {
            id: id_watch_img
            x: 5
            y: 2
            width: 30
            height: 30
            opacity: 1
            source: "images/watch.svg"
            visible: true
        }

        Text {
            id: id_time_text
            x: 37
            y: 2
            color: "white"
            text: qsTr(date.getHours() + ":" + (date.getMinutes() < 10 ? '0' : '') + date.getMinutes())
            renderType: Text.QtRendering
            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideLeft
            font.pixelSize: 25
            visible: window.bTimeVisibility
        }

        Image {
            id: id_calendar_img
            x: 5
            y: 40
            width: 30
            height: 30
            opacity: 1
            source: "images/calendar.svg"
            visible: true
        }

        Text {
            id: id_date_text
            x: 37
            y: 40
            color: "white"
            text: qsTr(currentDay + "/" + (currentMonth + 1) + "/" + currentYear)
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 25
            visible: window.bTimeVisibility
        }

        Image {
            id: id_weather_img
            x: 195
            y: 2
            width: 30
            height: 30
            opacity: 1
            source: "images/weather.svg"
            visible: true
        }

        Text {
            id: id_city_text
            x: 227
            y: 2
            color: "white"
            //text: qsTr((myclass.getWeatherCity() === "") ? "Searching..." : (myclass.getWeatherTemperature() + "ºC " + myclass.getWeatherCity() + ", " + myclass.getWeatherCountry()))
            text: qsTr((myclass.getWeather(1) === "") ? "Searching..." : (myclass.getWeather(3) + "ºC " + myclass.getWeather(2) + ", " + myclass.getWeather(1)))
            font.pixelSize: 18
            visible: true
        }

        Image {
            id: id_music_img
            x: 195
            y: 40
            width: 30
            height: 30
            opacity: 1
            source: "images/music.svg"
            visible: true
        }

        Text {
            id: id_music_text
            x: 227
            y: 40
            color: "white"
            text: qsTr((myclass.currentSong() === "") ? "No music selected" : (myclass.currentSong()))
            font.pixelSize: 18
            visible: true
        }
    }

    //choice menu button
    Image {
        id: id_button_menu1
        x: 20
        y: 20
        width: 70
        height: 70
        opacity: 1
        source: "images/menu-options.svg"
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
                stack.pop()
                stack.push(choice_menu)
                //stack.push(map)
            }
        }
    }

}
