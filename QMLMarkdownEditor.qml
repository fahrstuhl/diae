import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.1
import Qt.labs.platform 1.0
import MarkdownEditor 1.0

Frame {
    ColumnLayout{
        MarkdownEditor{
            id: editor
            onUrlChanged: textArea.text = text
            onTextChanged: {
                if (!textArea.activeFocus) {
                    textArea.text = html;
                }
            }
        }
        TextArea {
            id: urlArea
            text: editor.url
            Keys.onReturnPressed: editor.openArtefact(text)
        }
        TextArea {
            id: textArea
            text: editor.text
            onActiveFocusChanged: {
                if (activeFocus) {
                    textFormat = TextEdit.PlainText;
                    text = editor.text;
                    readOnly = false;
                }
                else {
                    textFormat = TextEdit.RichText;
                    text = editor.html;
                    readOnly = true;
                }
            }

            onTextChanged:{
                if (activeFocus && textFormat == TextEdit.PlainText) {
                    editor.setText(text)
                }
            }
        }
    }
}
