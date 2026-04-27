import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 800
    height: 500
    title: "EdgeWatch Dashboard"

    property real cpu: 0
    property real temp: 0

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        // Title
        Text {
            text: "EdgeWatch Monitoring"
            font.pixelSize: 28
            Layout.alignment: Qt.AlignHCenter
        }

        // Device Card
        Rectangle {
            Layout.fillWidth: true
            height: 200
            radius: 12
            color: "#2c2c2c"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 10

                Text {
                    text: "Device 1"
                    font.pixelSize: 20
                    color: "white"
                }

                // CPU
                Text {
                    text: "CPU Usage: " + cpu.toFixed(1) + " %"
                    color: "lightgray"
                }

                ProgressBar {
                    value: cpu / 100
                }

                // Temperature
                Text {
                    text: "Temperature: " + temp.toFixed(1) + " °C"
                    color: "lightgray"
                }

                ProgressBar {
                    value: temp / 100
                }
            }
        }

        // Alert Box
        Rectangle {
            Layout.fillWidth: true
            height: 80
            radius: 10
            color: temp > 80 ? "#8b0000" : "#1e7e34"

            Text {
                anchors.centerIn: parent
                text: temp > 80 ? "🔥 ALERT: High Temperature!" : "✅ System Stable"
                color: "white"
                font.pixelSize: 18
            }
        }

        // Manual Refresh Button
        Button {
            text: "Refresh Now"
            Layout.alignment: Qt.AlignHCenter
            onClicked: fetchData()
        }
    }

    // 🔁 Auto refresh every second
    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: fetchData()
    }

    // 🌐 API Call
    function fetchData() {
        var xhr = new XMLHttpRequest()
        xhr.open("GET", "http://localhost:5038/devices/1")

        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
                try {
                    var response = JSON.parse(xhr.responseText)

                    if (response.length > 0) {
                        cpu = response[0].cpu
                        temp = response[0].temperature
                    }
                } catch (e) {
                    console.log("JSON error:", e)
                }
            }
        }

        xhr.send()
    }

    Component.onCompleted: fetchData()
}
