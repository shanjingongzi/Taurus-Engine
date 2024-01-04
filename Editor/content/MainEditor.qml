import QtQuick 6.2
import OpenGLViewport 6.0
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.3

Rectangle {
    id:root
    width:1920
    height:1080
    visible: true
    color:"black"
    Text{
        text:"hello world"
    }
    Rectangle{
        id:hierarchy
        anchors.left:parent.left
        anchors.top:parent.top
        anchors.bottom:project.top
        width:parent.width/7
        Text{
            text:"hierarchy"
        }
        color: "#2e2f30"
        border.color: "#1582de"
        border.width: 3
    }




    Viewport{
        id:scene
        objectName:"sceneItem"
        anchors.left:hierarchy.right
        anchors.bottom:project.top
        anchors.top:parent.top
        anchors.right:inspector.left
        Text{
            text:"SceneViewport"
        }
        transformOrigin: Item.TopLeft

    }
    Rectangle{
        id:inspector
        anchors.right:parent.right
        anchors.bottom:project.top
        anchors.top:parent.top
        width:parent.width/7
        color: "#2e2f30"
        border.color: "#1582de"
        border.width: 3
    }
    Rectangle{
        id:project
        anchors.left:parent.left
        anchors.right:parent.right
        anchors.bottom:parent.bottom
        height:parent.height/7
        Text{
            text:"project"
        }
        color: "#2e2f30"
        border.color: "#1582de"
        border.width: 3
        Button{
            anchors.centerIn: parent
            Text{
                text:"create component"
            }
            width:150
        }
    }
}

