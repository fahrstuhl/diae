import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4

Frame {
    id: frame
    property bool deleted: false
    ColumnLayout {
        id: top
        property var nodes: []
        signal update
        function createEditorObjects() {
            var component = Qt.createComponent("QMLMarkdownEditor.qml");
            var node = component.createObject(root);
            if (node == null) {
                // Error Handling
                console.log("Error creating object");
            }
            nodes.push(node);
            node.widthChanged.connect(update);
            node.heightChanged.connect(update);
            node.deletedChanged.connect(update);
        }
        function createContainerObjects() {
            var component = Qt.createComponent("DIAEContainer.qml");
            var node = component.createObject(root);
            if (node == null) {
                // Error Handling
                console.log("Error creating object");
            }
            nodes.push(node);
            node.widthChanged.connect(update);
            node.heightChanged.connect(update);
            node.deletedChanged.connect(update);
        }
        function calculateSize(state) {
            var w = 0;
            var h = 0;
            for (var i=0; i < nodes.length; i++) {
                if (state == 0) {
                    w += nodes[i].width;
                    h = Math.max(h, nodes[i].height);
                }
                else if (state == 1) {
                    h += nodes[i].height;
                    w = Math.max(w, nodes[i].width);
                }
                else if (state == 2) {
                    w = Math.max(w, nodes[i].width);
                    h = Math.max(h, nodes[i].height);
                }
            }
            return [Math.max(controller.width,w), h + controller.height];
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
            var size = calculateSize(layout.state);
            console.log("width: ", size[0], "; height: ", size[1]);
            top.width = size[0];
            top.height = size[1];
            frame.contentWidth = top.width;
            frame.contentHeight = top.height;
            console.log("frame width: ", frame.width, "; frame height: ", frame.height);
        }

        Component.onDestruction: {
            for (var i = 0; i < nodes.length; i++) {
                nodes[i].destroy();
            }
        }

        RowLayout {
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
                onClicked: frame.deleted = true
            }
        }
        Item {
            property int state: 0
            id: layout
            Layout.fillHeight: true
            Layout.fillWidth: true
            RowLayout {
                anchors.fill: parent
                id: row
            }
            ColumnLayout {
                anchors.fill: parent
                id: column
            }
            StackLayout {
                anchors.fill: parent
                id: stack
            }
        }
    }
}
