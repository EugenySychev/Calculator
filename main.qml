import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Calculator")

//    header: ToolBar {
//        RowLayout {
//            anchors.fill: parent
//            Label {
//                Layout.leftMargin: 10
//                text: "Calculator"
//            }

//            ComboBox {
//                Layout.rightMargin: 10

//                Layout.alignment: Qt.AlignRight
//                model: ["Simple", "Programmers"]
//            }
//        }
//    }
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
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: height / 3
                text: "MR"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: height / 3
                text: "MC"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: height / 3
                text: "M+"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: height / 3
                text: "M-"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                text: "C"
                palette.buttonText: "#CC0000"
                font.pixelSize: height / 3
                onPressed: calcer.onClick("clear")

            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: height / 3
                text: "("
                onPressed: calcer.onClick(text)
            }

            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                text: ")"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                icon.source: "backspace.png"

                onPressed: calcer.onClick("back")
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "7"
                font.pixelSize: height / 3
                onPressed: {
                    calcer.onClick(text)
                }
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: height / 3
                text: "8"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: height / 3
                text: "9"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                text: "*"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                text: "4"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                text: "5"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                text: "6"
                onPressed: calcer.onClick(text)
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                font.pixelSize: height / 3
                text: "/"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                text: "1"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                text: "2"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                text: "3"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                text: "+"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                background: Rectangle {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color:  "#CCCCFF"
                }

                text: "="
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                text: "0"
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                text: ","
                onPressed: calcer.onClick(text)
            }
            Button {
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: height / 3
                text: "-"
                onPressed: calcer.onClick(text)
            }
        }
    }
}


