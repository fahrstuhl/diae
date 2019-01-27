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
    ColumnLayout{
        anchors.fill: parent
        MarkdownEditor{
            id: editor
            onUrlChanged: {
                textArea.text = text;
                textArea.decideIfEditable();
            }
            onTextChanged: {
                if (!textArea.activeFocus) {
                    textArea.text = html;
                }
            }
        }
        RowLayout{
            Button {
                text: "open file"
                onClicked: fileDialog.open();
            }

            TextArea {
                id: urlArea
                text: editor.url
                Keys.onReturnPressed: editor.openArtefact(text);
            }
            Button {
                text: "close editor"
                onClicked: frame.deleted = true
            }
        }

        FileDialog {
            id: fileDialog
            title: "Select file to edit."
            //folder: editor.getPath()
            selectExisting: false
            nameFilters: ["Markdown files: (*.md, *.txt)", "All files: (*)"]
            onAccepted: {
                editor.openArtefact(fileDialog.fileUrl);
                close();
            }
            onRejected: {
                close();
            }
        }

        ScrollView{
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentWidth: availableWidth
            contentHeight: availableHeight
            TextArea {
                function setPlaintext() {
                    textFormat = TextEdit.PlainText;
                    text = editor.text;
                    readOnly = false;
                }
                function setRichtext() {
                    textFormat = TextEdit.RichText;
                    text = editor.html;
                    readOnly = true;
                }
                function decideIfEditable() {
                    if (activeFocus) {
                        setPlaintext();
                    }
                    else {
                        setRichtext();
                    }

                }

                id: textArea
                text: editor.text
                width: parent.availableWidth
                wrapMode: TextEdit.Wrap
                Component.onCompleted: {
                    decideIfEditable();
                }

                onActiveFocusChanged: {
                    decideIfEditable();
                }

                onTextChanged:{
                    if (activeFocus && textFormat == TextEdit.PlainText) {
                        editor.setText(text)
                    }
                }
            }
        }
    }
}
