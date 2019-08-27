import QtQuick 2.11
import QtGraphicalEffects 1.0

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
            source: "qrc:/image/QQ图片20190322171359.jpg"
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
                source: "qrc:/image/QQ图片20190322171359.jpg"
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
                text: qsTr("Calling …")
                font.pixelSize: 16
                topPadding: 8
                leftPadding: 33
                color: "#FFFFFF"
                opacity: 0.5
                font.family: "Segoe UI Semibold"
            }
        }

        Image {
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
                    timer.stop()
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
    }
}
