import QtQuick 2.3
import QtQuick.Window 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import mymodell 1.0

ApplicationWindow {
    id: main
    title: "Game"

    visible: true
    width: 430
    height: 440
    minimumHeight: 215
    minimumWidth: 200
    maximumHeight: 800
    maximumWidth: 800
    color: "#19172B"

    menuBar: MenuBar {
        Menu {
            title: "Menu"
            MenuItem {
                text: "New Game"
                shortcut: "Ctrl+N"
                onTriggered: { dataModel.getMix() }
            }
            MenuItem {
                text: "Quit"
                shortcut: "Ctrl+Q"
                onTriggered: Qt.quit()
            }
        }
    }

    Component {
        id: delegate

        Item {
            width: view.cellWidth
            height: view.cellHeight
            Rectangle {
                visible: status
                anchors.centerIn: parent
                width: main.width / 4.5
                height: main.width / 4.55
                border.color: "black"
                radius: 5
                color: "lightblue"
                Text {
                    id: txt

                    text: value
                    font.pixelSize: parent.width / 4
                    anchors.centerIn: parent
                    color: "#19172B"
                }
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true

                    onEntered: {
                        parent.color = "#4B678B"
                        parent.border.color = "white"
                        txt.color = "#CECECE"
                    }
                    onExited: {
                        parent.color = "lightblue"
                        parent.border.color = "black"
                        txt.color = "#19172B"
                    }

                    onClicked: {
                        dataModel.activate(index)

                    }

                }

            }

        }
    }

    GridView {
        id: view

        focus: true
        cellWidth: main.width / 4.2
        cellHeight: main.width / 4.3

        add: Transition {
            ParallelAnimation {
                NumberAnimation { easing.type: Easing.InOutCubic; properties: "x,y"; from: 150; duration: 250 }
                NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 250 }
            }
        }

        move: Transition {
                NumberAnimation { easing.overshoot: 1.2; easing.type: Easing.InOutBack; properties: "x,y"; duration: 300 }
        }

        remove: Transition {
                ParallelAnimation {
                    NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 250 }
                    NumberAnimation { easing.type: Easing.InOutQuart; properties: "x,y"; to: 150; duration: 250 }
                }
        }

        anchors.fill: parent
        anchors.margins: main.width / 43

        model: MyModell {
            id: dataModel

            onVictory: {
               messageDialog.open()
            }
        }

        delegate: delegate
    }

    MessageDialog {
        id: messageDialog
        objectName: "mDialog"
        visible: false
        modality: Qt.WindowModal
        title: "Victory"
        informativeText: "Congratulations, you are the winner!"
        onAccepted: { dataModel.getMix() }
    }
}
