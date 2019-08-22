import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 375
    height: 852
    title: qsTr("Hello World")

    header: ToolBar {
        height: 40
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("<")
                onClicked: stackView.pop()
            }
            Label {
                text: qsTr("Voip Call")
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }
    }

    StackView {
        id: stackView
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            top: header.bottom
        }
        initialItem: startingPage
    }

    Component {
        id: startingPage
        StartingPage {}
    }

    Component {
        id: audioCallingPage
        AudioCalling {}
    }

    Component {
        id: incomingCallPage
        IncomingCall {}
    }

    Component {
        id: audioCallConfirmedPage
        AudioCallConfirmed {}
    }

    function load_page(page) {
        switch(page) {
        case 'page 1':
            stackView.push(startingPage);
            break;
        case 'audioCallingPage':
            stackView.push(audioCallingPage);
            break;
        case 'incomingCallPage':
            stackView.push(incomingCallPage);
            break
        case 'audioCallConfirmedPage':
            stackView.push(audioCallConfirmedPage)
            break
        }
    }
}
