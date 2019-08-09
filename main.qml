import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        anchors.fill: parent

        Column {
            anchors.fill: parent
            Rectangle {
                width: parent.width
                height: 50
                color: "blue"

                Text {
                    anchors.centerIn: parent
                    text: qsTr("initAccount")
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        voip.initAccount();
                    }
                }
            }

            Rectangle {
                width: parent.width
                height: 50
                color: "pink"

                Text {
                    anchors.centerIn: parent
                    text: qsTr("call1002")
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        voip.makeAudioCall();
                    }
                }
            }

            Rectangle {
                width: parent.width
                height: 50
                color: "yellow"

                Text {
                    anchors.centerIn: parent
                    text: qsTr("answer")
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        voip.answer();
                    }
                }
            }
            Rectangle {
                width: parent.width
                height: 50
                color: "green"

                Text {
                    anchors.centerIn: parent
                    text: qsTr("hangup")
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        voip.hangup()
                    }
                }
            }
            Rectangle {
                width: parent.width
                height: 50
                color: "purple"

                Text {
                    anchors.centerIn: parent
                    text: qsTr("reject")
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        voip.reject()
                    }
                }
            }
        }
    }
}
