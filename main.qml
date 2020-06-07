import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import FileRenamer 1.0
import FilesModel 1.0

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Переименователь")

    FileRenamer {
        id:renamer
    }

    FilesModel {
        id:filesModel
    }

    Item {
        id: pontrolPanel
        anchors.right: parent.right
        width: parent.width/2
        height: parent.height

        TextField {
            id: newNameTextField
            width: parent.width -10
            height: 25
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            verticalAlignment: TextEdit.AlignVCenter
            placeholderText: "Укажите новое имя файлов"
        }

        Button {
            id: renameButton
            width: newNameTextField.width
            height: newNameTextField.height
            anchors.top: newNameTextField.bottom
            anchors.horizontalCenter: newNameTextField.horizontalCenter

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Переименовать")
            }

            onClicked: {
                var newNameText = newNameTextField.text
                if(newNameText.length > 0) {
                    renamer.fileRename(newNameText)
                    filesModel.getFilesAndFolders(".", 0)
                }
            }
        }


    }

    Item {
        id: explorer
        anchors.left: parent.left
        width: parent.width/2
        height: parent.height

        Button {
            id: enterButton
            anchors.right: tableView.right
            anchors.bottom: tableView.top
            width: 25
            height: 25

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr(">")
            }

            onClicked: {
                filesModel.getFilesAndFolders(pathTextField.text, 0)
            }
        }

        TextField {
            id: pathTextField
            width: tableView.width - enterButton.width
            height: 25
            anchors.left: tableView.left
            anchors.bottom: tableView.top
            verticalAlignment: TextEdit.AlignVCenter
            placeholderText: "Укажите путь"
            text: renamer.getCurrentDirectory()
        }

        TableView {
            id: tableView
            model: filesModel
            anchors.fill: parent
            anchors.topMargin: enterButton.height + 10
            anchors.margins: 10
            clip: true

            TableViewColumn {
                id: nameColumn
                width: tableView.width / 3
                title: "Имя"
                role: "name"

                delegate: Item {
                    id: colomn
                    Text {
                        id: nameText
                        text: styleData.value
                        anchors.fill: parent
                        anchors.leftMargin: 3
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: 14
                        color: "#292929"
                        elide: Text.ElideRight
                    }

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: false
                        cursorShape: Qt.PointingHandCursor

                        onDoubleClicked: {
                            filesModel.getFilesAndFolders(nameText.text, 0)
                            pathTextField.text = renamer.getCurrentDirectory()
                        }
                    }
                }
            }

            TableViewColumn {
                id: dateColumn
                width: tableView.width / 3
                title: "Дата изменения"
                role: "date"
            }

            TableViewColumn {
                id: sizeColumn
                width: tableView.width - nameColumn.width - dateColumn.width
                title: "Размер"
                role: "size"
                resizable: false;
            }

    //        style: TableViewStyle{
    //            id: tableStyle
    //            backgroundColor: "#DEDEDE"
    //            alternateBackgroundColor: "#C4C4C4"
    //            textColor: "#000"
    //        }

            itemDelegate: Item {
                Text {
                    id: itemText
                    text: styleData.value
                    anchors.fill: parent
                    anchors.leftMargin: 3
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 14
                    color: "#292929"
                    elide: Text.ElideRight
                }
            }
        }
    }
}
