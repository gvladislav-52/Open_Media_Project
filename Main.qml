import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    minimumWidth: 400
    minimumHeight: 400
    color: "gray"
    visible: true

    ColumnLayout
    {
        anchors.fill: parent

    GridLayout {
        Layout.preferredHeight: parent.height * 0.4
        Layout.preferredWidth: parent.width
        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

        columns: 2
        rows: 2

        Rectangle {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: parent.height * 0.3
            Layout.preferredWidth: parent.width * 0.6
            color: "white"
            Layout.row: 0
            Layout.column: 0
            border.color: "black"
            border.width: parent.height * 0.01
            clip: true

            Text
            {
                anchors
                {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: parent.width * 0.025
                }

                text: file_proc.file_one
            }
        }

        ToolButton {
            id: button_file_1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: parent.height * 0.3
            Layout.preferredWidth: parent.width * 0.2
            Layout.row: 0
            Layout.column: 1
            background: Rectangle
            {
                color: button_file_1.pressed ? "black" : (button_file_1.hovered ? "darkred" : "red")
                radius: parent.height * 0.7
                border.color: "black"
                border.width: parent.height * 0.025
            }


            Text
            {
                anchors.centerIn: parent
                text: "File 1"
                color: "gray"
                font.pixelSize: parent.height * 0.4
                font.bold: true
            }

            onClicked:
            {
                file_proc.file_srav()
            }
        }

        Rectangle {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: parent.height * 0.3
            Layout.preferredWidth: parent.width * 0.6
            color: "white"
            Layout.row: 1
            Layout.column: 0
            border.color: "black"
            border.width: parent.height * 0.01
            clip: true

            Text
            {
                anchors
                {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: parent.width * 0.025
                }

                text: file_proc.file_one
            }
        }

        ToolButton {
            id: button_file_2
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: parent.height * 0.3
            Layout.preferredWidth: parent.width * 0.2
            Layout.row: 1
            Layout.column: 1
            background: Rectangle
            {
                color: button_file_2.pressed ? "black" : (button_file_2.hovered ? "darkred" : "red")
                radius: parent.height * 0.7
                border.color: "black"
                border.width: parent.height * 0.025
            }

            Text
            {
                anchors.centerIn: parent
                text: "File 2"
                color: "gray"
                font.pixelSize: parent.height * 0.4
                font.bold: true
            }

            onClicked:
            {
                file_proc.openFile_two()
            }
        }
    }

    Rectangle
    {
        id: rect_data
        Layout.fillHeight: true
        Layout.fillWidth: true
        color: "white"

        ScrollView
        {
            anchors.fill: parent
            clip: true
            ScrollBar.vertical.policy: ScrollBar.AlwaysOff
            contentHeight: scroll_id.height

        ColumnLayout {
            id: scroll_id
            width: parent.width
            spacing: 0
            anchors
            {
            horizontalCenter: parent.horizontalCenter
            verticalCenter: parent.verticalCenter
            }

            Repeater
            {
                model: 100

                Rectangle {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredHeight: rect_data.height * 0.1
                    Layout.preferredWidth: rect_data.width
                    color: "white"
                    border.color: "black"

                    Text
                    {
                        anchors.centerIn: parent
                        text: "Hello wsdfsdfsdforld!"
                    }
                }
            }
        }
        }
    }

    }
}
