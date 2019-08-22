import QtQuick 2.11
import QtGraphicalEffects 1.0

Item {
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
                text: qsTr("Ashley")
                color: "#FFFFFF"
                font.pixelSize: 32
                topPadding: 48
                font.family: "Segoe UI Semibold"
            }

        }

        Image {
            z: 2
            id: cancel
            width: 64
            height: 64
            anchors.left: parent.left
            anchors.leftMargin: 74
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
            anchors.horizontalCenter: cancel.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 48
            text: qsTr("Cancel")
            font.pixelSize: 16
            font.family: "Segoe UI Semibold"
            color: "#FFFFFF"
        }

        Image {
            z: 2
            id: answer
            width: 64
            height: 64
            anchors.right: parent.right
            anchors.rightMargin: 74
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 76
            source: "qrc:/image/Pickup.png"
            fillMode: Image.PreserveAspectFit
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    voip.answer()
                }
            }
        }

        Text {
            z: 2
            anchors.horizontalCenter: answer.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 48
            text: qsTr("Answer")
            font.pixelSize: 16
            font.family: "Segoe UI Semibold"
            color: "#FFFFFF"
        }
    }
}
