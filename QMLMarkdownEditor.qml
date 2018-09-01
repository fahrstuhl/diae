import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.1
import Qt.labs.platform 1.0
import MarkdownArtefact 1.0

ColumnLayout{
    id: top
    //property  document
    Text {
        text: top.document.fileUrl
    }

    TextArea {
        id: area
        text: top.document.text
        readOnly: top.document.isInUse
    }

    Binding {
        target: top.current_document1
        when: !top.document.isInUse
        property: "text"
        value: area1.text
    }
}
