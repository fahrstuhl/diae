import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3
import MarkdownEditor 1.0

Frame {
    id: frame
    property bool deleted: false
    property real relWidth: 1
    property real relHeight: 1
    ColumnLayout {
        anchors.fill: parent
        MarkdownEditor {
            id: editor
            onUrlChanged: {
                textArea.show()
            }
            onTextChanged: {
                if (!textArea.activeFocus) {
                    textArea.show()
                }
            }
        }
        RowLayout {
            id: controls
            Button {
                id: edit_button
                text: "edit"
                onClicked: textArea.edit()
            }

            Button {
                id: show_button
                text: "show"
                onClicked: textArea.show()
            }

            Button {
                text: "open file"
                onClicked: fileDialog.open()
            }

            TextArea {
                id: urlArea
                text: editor.url
                Keys.onReturnPressed: editor.openArtefact(text)
            }
            Button {
                text: "close editor"
                onClicked: frame.deleted = true
            }
        }

        FileDialog {
            id: fileDialog
            title: "Select file to edit."
            folder: editor.getPath()
            selectExisting: false
            nameFilters: ["Markdown files: (*.md, *.txt)", "All files: (*)"]
            onAccepted: {
                editor.openArtefact(fileDialog.fileUrl)
                close()
            }
            onRejected: {
                close()
            }
        }

        ScrollView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentWidth: availableWidth
            contentHeight: availableHeight
            TextArea {
                function edit() {
                    focus = true
                    setPlaintext()
                }

                function show() {
                    setRichtext()
                }

                function setPlaintext() {
                    textFormat = TextEdit.PlainText
                    text = editor.text
                    readOnly = false
                    edit_button.visible = false
                    show_button.visible = true
                }
                function setRichtext() {
                    textFormat = TextEdit.RichText
                    text = editor.html
                    readOnly = true
                    edit_button.visible = true
                    show_button.visible = false
                }
                function decideIfEditable() {
                    if (activeFocus) {
                        setPlaintext()
                    } else {
                        setRichtext()
                    }
                }

                id: textArea
                text: editor.text
                width: parent.availableWidth
                wrapMode: TextEdit.Wrap
                selectByMouse: true
                Component.onCompleted: {
                    show()
                }

                onActiveFocusChanged: {
                    if (!activeFocus) {
                        show()
                    }
                }

                onTextChanged: {
                    if (activeFocus && !readOnly
                            && textFormat == TextEdit.PlainText) {
                        editor.setText(text)
                    }
                }

                onLinkActivated: {
                    editor.handleClickedLink(link)
                }
            }
        }
    }
}
