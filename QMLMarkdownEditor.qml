import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.1
import Qt.labs.platform 1.0
import MarkdownEditor 1.0

ColumnLayout{
    MarkdownEditor{
        id: editor
        onUrlChanged: textArea.text = text
        onTextChanged: {
            if (!textArea.activeFocus) {
                textArea.text = text
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
        onTextChanged:{
            if (activeFocus) {
                editor.setText(text)
            }
        }
    }
}
