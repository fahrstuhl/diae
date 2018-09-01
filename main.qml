import QtQuick 2.11
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.1
import QtQuick.Window 2.11
import Qt.labs.platform 1.0
import MarkdownEditor 1.0


Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("DIAE")
    RowLayout {
        id: top
        TextArea {
            id: area2
            text: editor.text
            onTextChanged:
                editor.setText(text)
            MarkdownEditor{
                id: editor
            }
        }
    }
}
