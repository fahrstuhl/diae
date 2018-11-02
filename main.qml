import QtQuick 2.11
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.1
import QtQuick.Window 2.11
import Qt.labs.platform 1.0


Window {
    visible: true
    width: 1920
    height: 1080
    title: qsTr("DIAE")

    DIAEContainer {
        id: root
    }
}
