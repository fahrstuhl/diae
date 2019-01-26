import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4

Frame {
    id: top
    property var nodes: []
    property bool deleted: false
    property real relWidth: 1
    property real relHeight: 1
    signal update
    function createObject(component) {
        var node = component.createObject(root);
        if (node == null) {
            // Error Handling
            console.log("Error creating object");
        }
        nodes.push(node);
        node.widthChanged.connect(update);
        node.heightChanged.connect(update);
        node.deletedChanged.connect(update);
        node.parent = layout;
    }

    function createEditorObjects() {
        var component = Qt.createComponent("QMLMarkdownEditor.qml");
        createObject(component);
    }
    function createContainerObjects() {
        var component = Qt.createComponent("DIAEContainer.qml");
        createObject(component);
    }

    function calculateRelativeSize(state){
        var n = nodes.length;
        for (var i=0; i < nodes.length; i++) {
            switch(state){
            case 0:
                nodes[i].relHeight = 1;
                nodes[i].relWidth = 1/n;
                break;
            case 1:
                nodes[i].relHeight = 1/n;
                nodes[i].relWidth = 1;
                break;
            case 2:
                nodes[i].relHeight = 1;
                nodes[i].relWidth = 1;
                break;
            }
            nodes[i].Layout.preferredWidth = nodes[i].relWidth * availableWidth;
            nodes[i].Layout.preferredHeight = nodes[i].relHeight * availableHeight;
        }
    }

    onUpdate: {
        console.log("state:", layout.state);
        for (var i = 0; i < nodes.length; i++) {
            console.log("#", i, "; deleted: ", nodes[i].deleted, "; item: ", nodes[i], "; type: ", typeof nodes[i], "; parent: ", nodes[i].parent, "; layout: ", layout);
            if (nodes[i].deleted) {
                nodes[i].destroy();
                nodes.splice(i,1);
                i--;
                continue;
            }
            switch(layout.state) {
            case 0:
                console.log("row: ", row);
                nodes[i].parent = row;
                break;
            case 1:
                console.log("column: ", column);
                nodes[i].parent = column;
                break;
            case 2:
                console.log("stack: ", stack);
                nodes[i].parent = stack;
                break;
            }
        }
        calculateRelativeSize(layout.state);
    }

    Component.onDestruction: {
        for (var i = 0; i < nodes.length; i++) {
            nodes[i].destroy();
        }
    }

    RowLayout {
        anchors.top: parent.top
        id: controller
        ComboBox {
            model: ["row", "column", "stack"]
            onActivated: {
                layout.state = index;
                top.update();
            }
        }
        Button {
            text: "editor"
            onClicked: {
                top.createEditorObjects();
                top.update()
            }
        }
        Button {
            text: "container"
            onClicked: {
                top.createContainerObjects();
                top.update()
            }
        }
        Button {
            text: "close container"
            onClicked: top.deleted = true
        }
    }
    Item {
        anchors.top: controller.bottom
        anchors.bottom: parent.bottom
        width: availableWidth
        property int state: 0
        id: layout
        RowLayout{
            id: row
            anchors.fill: parent
        }
        ColumnLayout{
            id: column
            anchors.fill: parent
        }
        StackLayout{
            id: stack
            anchors.fill: parent
        }
    }
}
