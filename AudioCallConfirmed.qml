import QtQuick 2.11
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.2

Item {
    property int initTime: 0
    property var totalSeconds_ipt
    property var totalSeconds_sys
    property var trigger_ipt

    function toTime(s) {
        var time
        if (s > -1) {
            var min = Math.floor(s/60)
            var sec = initTime % 60
            if (min < 10) {
                time = "0"
                time += min + ":"
            } else {
                time = min + ":"
            }
            if (sec < 10) {
                time += "0"
            }
            time += sec.toFixed(0)
        }
        return time
    }

    Component.onCompleted: {
        initTime = 0
        timer.start()
    }

    Rectangle {
        width: 375
        height: 812
        Image {
            id: background
            anchors.fill: parent
            source: "qrc:/image/Dog.jpg"
            fillMode: Image.PreserveAspectCrop
        }
        GaussianBlur {
            id: gaussianBlur
            source: background
            radius: 100
            samples: 50
            anchors.fill: parent
        }

        Rectangle {
            anchors.fill: parent
            color: "#000000"
            opacity: 0.7
            z: 1
        }

        Column {
            anchors.top: parent.top
            anchors.topMargin: 120
            anchors.left: parent.left
            anchors.leftMargin: 128
            z: 2
            Image {
                horizontalAlignment: Image.AlignHCenter
                source: "qrc:/image/Dog.jpg"
                width: 120
                height: 120
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Caster")
                color: "#FFFFFF"
                font.pixelSize: 32
                topPadding: 48
                font.family: "Segoe UI Semibold"
            }

            Timer {
                id: timer
                interval: 1000
                repeat: true
                triggeredOnStart: true
                onTriggered: {
                    initTime++
                    timeTex.text = toTime(initTime)
                }
            }

            Text {
                id: timeTex
                font.pixelSize: 16
                topPadding: 48
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#FFFFFF"
                font.family: "Segoe UI Semibold"
            }

            Text {
                text: qsTr("In a call")
                font.pixelSize: 16
                topPadding: 8
                leftPadding: 33
                color: "#FFFFFF"
                opacity: 0.5
                font.family: "Segoe UI Semibold"
            }
        }

        Image {
            id: cancel
            z: 2
            width: 64
            height: 64
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 76
            source: "qrc:/image/Group.png"
            fillMode: Image.PreserveAspectFit
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    voip.hangup()
                    stackView.pop()
                }
            }
        }

        Text {
            z: 2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 48
            text: qsTr("Cancel")
            font.pixelSize: 16
            font.family: "Segoe UI Semibold"
            color: "#FFFFFF"
        }

        Image {
            id: mute
            z: 2
            width: 32
            height: 32
            anchors.left: parent.left
            anchors.leftMargin: 58
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 92
            source: "qrc:/image/mute.png"
            fillMode: Image.PreserveAspectFit
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    voip.setVolume(0)
                }
            }
        }

        Text {
            z: 2
            anchors.top: mute.bottom
            anchors.topMargin: 24
            anchors.left: parent.left
            anchors.leftMargin: 56
            text: qsTr("Mute")
            font.pixelSize: 16
            font.family: "Segoe UI Semibold"
            color: "#FFFFFF"
        }

        Image {
            id: volume
            z: 2
            width: 32
            height: 32
            anchors.right: parent.right
            anchors.rightMargin: 56
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 92
            source: "qrc:/image/volume.png"
            fillMode: Image.PreserveAspectFit
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    volumeBar.visible = true
                }
                onClicked: {
                    if (volumeBar.visible) {
                        volumeBar.visible = false
                        return
                    }

                    if (!volumeBar.visible) {
                        volumeBar.visible = true
                    }
                }
            }
        }

        Text {
            z: 2
            anchors.top: volume.bottom
            anchors.topMargin: 24
            anchors.right: parent.right
            anchors.rightMargin: 56
            text: qsTr("Volume")
            font.pixelSize: 16
            font.family: "Segoe UI Semibold"
            color: "#FFFFFF"
        }

        Slider {
            z: 2
            id: volumeBar
            anchors.bottom: volume.top
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 72
            width: 20
            height: 100
            orientation: Qt.Vertical
            visible: false
            minimumValue: 0
            maximumValue: 1
            value: 1 - 0.2
            property bool hoverTrigger: true
            onValueChanged: {
                voip.setVolume(value)
            }
            style: SliderStyle {
                handle: Rectangle {
                    width: 13
                    height: 13
                    radius: width/2
                }
            }
        }
    }
}
