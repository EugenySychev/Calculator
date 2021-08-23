import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Calculator")

    ColumnLayout {
        anchors.fill: parent
        Layout.fillHeight: true
        Layout.fillWidth: true

        Label {
            Layout.margins: 10
            Layout.fillWidth: true
            id: resultLabel
            font.pointSize: 30
            text: "0"
            color: "darkgrey"
            font.italic: true
        }
        TextEdit {
            Layout.fillWidth: true
            Layout.fillHeight: true
            horizontalAlignment: TextEdit.AlignRight
            id: editText
            text: calcer.interrim_string
            font.pointSize: 40
        }

        GridLayout {
            rows: 4
            columns: 5
            Layout.margins: 10

            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "7"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "8"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "9"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "/"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: ""
            }

            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "4"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "5"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "6"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "*"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: ""
            }

            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "1"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "2"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "3"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "+"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: ""
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "0"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: ","
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "="
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "-"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: ""
            }
        }

    }
}


