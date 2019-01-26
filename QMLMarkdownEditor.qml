import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.1
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.0
import MarkdownEditor 1.0

Frame {
    id: frame
    property bool deleted: false
    property real relWidth: 1
    property real relHeight: 0.9
    Layout.margins: 5
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
            onClicked: fileDialog.visible = true;
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
            folder: editor.getPath()
            selectExisting: false
            nameFilters: ["Markdown files: (*.md, *.txt)", "All files: (*)"]
            onAccepted: {
                editor.openArtefact(fileDialog.fileUrl);
                visible = false;
            }
            onRejected: {
                visible = false;
            }
        }

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
            wrapMode: TextEdit.Wrap
            Layout.fillHeight: true
            Layout.fillWidth: true
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
