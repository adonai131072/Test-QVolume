import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 360
    height: 60
    minimumWidth: 360
    maximumWidth: 360
    minimumHeight: 60
    maximumHeight: 60

    Binding {
        target: volumeChanger
        property: "volume"
        value: mainForm.sliderHorizontal1.value
    }

    Binding {
        target: volumeChanger
        property: "mute"
        value: mainForm.checkBox1.checked
    }

    Binding {
        target: mainForm.sliderHorizontal1
        property: "value"
        value: volumeChanger.volume
    }

    Binding {
        target: mainForm.checkBox1
        property: "checked"
        value: volumeChanger.mute
    }

    MainForm {
        id: mainForm
        anchors.fill: parent
        sliderHorizontal1.enabled: !checkBox1.checked
        sliderHorizontal1.opacity: checkBox1.checked ? 0.5 : 1
    }

}
