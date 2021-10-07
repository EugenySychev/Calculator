import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: appWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Calculator")

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            Label {
                Layout.leftMargin: 10
                text: "Calculator"
            }

            ComboBox {
                Layout.rightMargin: 10
                Layout.leftMargin: width / 10
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight

                model: ["Simple", "Programmers"]
            }
        }
    }


    ColumnLayout {
        anchors.fill: parent
        Layout.fillHeight: true
        Layout.fillWidth: true

        RowLayout {

            Layout.fillHeight: true
            Layout.fillWidth: true

            Label {

                Layout.margins: {
                    left: 10
                    top: 0
                    right: 10
                    bottom: 0
                }
                Layout.fillWidth: true
                id: resultLabel
                font.pointSize: 25
                text: calcer.result_string
                color: "darkgrey"
                font.italic: true
            }
            Label {
                Layout.alignment: Qt.AlignRight
                text: "M"
                font.pointSize: 25

                Layout.margins: {
                    left: 10
                    top: 0
                    right: 10
                    bottom: 0
                }

                color: calcer.memory_is_empty ? "lightgrey" : "black"
            }
        }


        TextEdit {
            Layout.fillWidth: true
            Layout.fillHeight: true
            horizontalAlignment: TextEdit.AlignRight
            id: editText
            text: calcer.interrim_string
            font.pointSize: 30
            focus: true
            Layout.margins: {
                left: 10
                top: 0
                right: 10
                bottom: 0
            }
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
        RowLayout {
            spacing: 0
            GridLayout {
                rows: 6
                columns: 3
                columnSpacing: 0
                rowSpacing: 0
                visible: appWindow.height < appWindow.width
                Layout.alignment: Qt.AlignHCenter
                Layout.fillWidth: true
                Layout.fillHeight: true

                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "n!"
                    onPressed: calcer.onClick("!")
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "%"
                    onPressed: calcer.onClick(text)
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: ""
                    onPressed: calcer.onClick(text)
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "sin"
                    onPressed: calcer.onClick(text + "(")
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "cos"
                    onPressed: calcer.onClick(text + "(")
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "tan"
                    onPressed: calcer.onClick(text + "(")
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "asin"
                    onPressed: calcer.onClick(text + "(")
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "acos"
                    onPressed: calcer.onClick(text + "(")
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "atan"
                    onPressed: calcer.onClick(text + "(")
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "xⁿ"
                    onPressed: calcer.onClick("^")
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "√"
                    onPressed: calcer.onClick(text + "(")
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "mod"
                    onPressed: calcer.onClick(text)
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "log"
                    onPressed: calcer.onClick(text + "(")
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "ln"
                    onPressed: calcer.onClick(text + "(")
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "e"
                    onPressed: calcer.onClick(text)
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "π"
                    onPressed: calcer.onClick(text)
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: calcer.degRadMode
                    onPressed: calcer.onClick(text)
                }
                Button {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.pixelSize: height / 3
                    text: "|x|"
                    onPressed: calcer.onClick("|")
                }
            }
            GridLayout {
                rows: 6
                columns: 4
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
}


