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

        RowLayout {

            Layout.fillHeight: true
            Layout.fillWidth: true

            Label {
                Layout.margins: 10
                Layout.fillWidth: true
                id: resultLabel
                font.pointSize: 30
                text: calcer.result_string
                color: "darkgrey"
                font.italic: true
            }
            Label {
                Layout.alignment: Qt.AlignRight
                text: "M"
                font.pointSize: 30
                Layout.margins: 10
                color: calcer.memory_is_empty ? "lightgrey" : "black"
            }
        }


        TextEdit {
            Layout.fillWidth: true
            Layout.fillHeight: true
            horizontalAlignment: TextEdit.AlignRight
            id: editText
            text: calcer.interrim_string
            font.pointSize: 40
            focus: true
            cursorPosition: calcer.cursorPosition
            Component.onCompleted: {
                Qt.inputMethod.visibleChanged.connect(function () {
                    if (Qt.inputMethod.visible)
                        Qt.inputMethod.hide()
                })
            }
            onCursorPositionChanged: {
                calcer.onCursorPositionChanged(cursorPosition);
            }

            onTextChanged: {
                cursorPosition = calcer.cursorPosition
            }

            Keys.onPressed: {
                calcer.onPressed(event.key);
                if (event.key !== Qt.Key_Back)
                    event.accepted  = true;
            }
        }

        GridLayout {
            rows: 5
            columns: 4
//            Layout.margins: 10
            columnSpacing: 0
            rowSpacing: 0

            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Button {
                Layout.maximumHeight: 3000
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "MR"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.maximumHeight: 3000
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "MC"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.maximumHeight: 3000
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "M+"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.maximumHeight: 3000
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "M-"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "C"
                onPressed: calcer.onClick("clear")

            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "("
                onPressed: calcer.onClick(text)
            }

            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: ")"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                icon.source: "backspace.png"
                leftPadding: 2
                rightPadding: 2
                onPressed: calcer.onClick("back")
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "7"
                onPressed: {
                    calcer.onClick(text)
                }
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
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "*"
                onPressed: calcer.onClick(text)
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
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "/"
                onPressed: calcer.onClick(text)
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
                text: "="
                onPressed: calcer.onClick(text)
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
                text: "-"
                onPressed: calcer.onClick(text)
            }
        }
    }
}


