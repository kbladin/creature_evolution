import QtQuick 2.0
import OpenGLUnderQML 1.0

Item {
	width: 640
	height: 480

	QtWindowManager {
		id: qtwindowmanager
		objectName: "qtwindowmanager"
		//here we can do magic
	}

	Rectangle {
        color: Qt.rgba(1, 1, 1, 0.7)
        radius: 10
        border.width: 1
        border.color: "white"
        anchors.fill: label
        anchors.margins: -10
    }

    Text {
        id: label
        color: "black"
        wrapMode: Text.WordWrap
        text: "The background here is a QtWindowManager rendered with raw OpenGL using the 'beforeRender()' signal in QQuickWindow. This text label and its border is rendered using QML"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 20
    }
}