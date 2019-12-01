import QtQuick 2.0

import QtQuick.Dialogs 1.1

MessageDialog {
    title: "New USB Device"
    icon: StandardIcon.Information
    text: "New USB Device available"
    standardButtons: StandardButton.Ok
    Component.onCompleted: visible = true
    onAccepted: {
        console.log("Ok pressed")

    }
}
