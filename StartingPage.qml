import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

Item {
    Connections {
        target: voip
        onStateChanged: {
            if (voip.state == "INCOMING") {
                load_page('incomingCallPage')
            }
        }
    }

    Column {
        anchors.fill: parent
        Rectangle {
            width: parent.width
            height: 50
            color: "blue"

            Text {
                anchors.centerIn: parent
                text: qsTr("showCallingPage")
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    load_page('audioCallingPage')
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 50
            color: "pink"

            Text {
                anchors.centerIn: parent
                text: qsTr("call1000")
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    voip.makeAudioCall();
                    load_page('audioCallingPage')
                }
            }
        }

        Rectangle {
            width: parent.width
            height: 50
            color: "sky blue"

            Text {
                anchors.centerIn: parent
                text: qsTr("incomingcall")
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    load_page('incomingCallPage')
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
        Rectangle {
            width: parent.width
            height: 50
            color: "orange"

            Text {
                anchors.centerIn: parent
                text: qsTr("confirmed")
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    load_page('audioCallConfirmedPage')
                }
            }
        }
    }
}
