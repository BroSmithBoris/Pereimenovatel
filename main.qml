import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import FileRenamer 1.0
import FilesModel 1.0

Window
{
    id: root
    visible: true
    width: 480
    height: 640
    title: qsTr("Переименователь")
    property int columnNumber: 0
    property bool reverse: false
    property bool clickCheck: false

    FileRenamer
    {
        id:renamer
    }

    FilesModel
    {
        id:filesModel
    }


    Item {

        anchors.fill: parent
        anchors.margins: 10

        TextField
        {
            id: newNameTextField
            width: parent.width
            height: 25
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 10
            verticalAlignment: TextEdit.AlignVCenter
            placeholderText: "Укажите новое имя файлов, где %%% маска для порядка"
        }

        Button
        {
            id: renameButton
            width: newNameTextField.width
            height: newNameTextField.height
            anchors.top: newNameTextField.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            Text
            {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Переименовать")
            }

            onClicked:
            {
                var newNameText = newNameTextField.text
                if(newNameText.length > 0)
                {
                    renamer.fileRename(newNameText, columnNumber, reverse)
                    filesModel.getFilesAndFolders(".", columnNumber, reverse)
                }
            }
        }

        TextField
        {
            id: pathTextField
            width: parent.width - enterButton.width
            height: 25
            anchors.top: renameButton.bottom
            anchors.topMargin: 10
            anchors.left: renameButton.left
            verticalAlignment: TextEdit.AlignVCenter
            placeholderText: "Укажите путь"
            text: renamer.getCurrentDirectory()

            Button
            {
                id: enterButton
                anchors.left: parent.right
                //anchors.verticalCenter: parent.verticalCenter
                width: 25
                height: 25

                Text
                {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr(">")
                }

                onClicked:
                {
                    filesModel.getFilesAndFolders(pathTextField.text, columnNumber, reverse)
                }
            }
        }

        TableView
        {
            id: tableView
            model: filesModel
            width: parent.width
            anchors.top: pathTextField.bottom
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            //anchors.margins: 10
            clip: true

            TableViewColumn
            {
                id: nameColumn
                width: tableView.width / 3
                title: "Имя"
                role: "name"

                delegate: Item
                {
                    id: colomn
                    Text
                    {
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

                    MouseArea
                    {
                        anchors.fill: parent
                        hoverEnabled: false
                        cursorShape: Qt.PointingHandCursor

                        onDoubleClicked:
                        {
                            filesModel.getFilesAndFolders(nameText.text, columnNumber, reverse)
                            pathTextField.text = renamer.getCurrentDirectory()
                        }
                    }
                }
            }

            TableViewColumn
            {
                id: dateColumn
                width: tableView.width / 3
                title: "Дата изменения"
                role: "date"
            }

            TableViewColumn
            {
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

            itemDelegate: tableItem
            headerDelegate: tableHeader

            Component
            {
                id: tableItem
                Text
                {
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

            Component
            {
                id: tableHeader

                Rectangle
                {
                    width: textHeader.text.length * 1.2
                    height: textHeader.font.pixelSize * 1.2
                    color: "#C4C4C4"

                    border
                    {
                        width: 1
                        color: "#808080"
                    }

                    Text
                    {
                        id: textHeader
                        anchors.fill: parent
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.Center
                        text: styleData.value
                        elide: Text.ElideRight
                    }

                    Connections
                    {
                        target: styleData
                        onPressedChanged:
                        {
                            if (styleData.pressed === true && !clickCheck)
                            {
                                reverse = (columnNumber === styleData.column)? !reverse : reverse;
                                columnNumber = styleData.column
                                filesModel.getFilesAndFolders(".", columnNumber, reverse)
                            }
                            clickCheck = !clickCheck
                        }
                    }
                }
            }
        }
    }
}
