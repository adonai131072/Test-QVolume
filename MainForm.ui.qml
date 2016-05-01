import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Window 2.2

Rectangle {

    property alias sliderHorizontal1: sliderHorizontal1
    property alias checkBox1: checkBox1

    width: 360
    height: 60

    Slider {
        id: sliderHorizontal1
        x: 8
        y: 8
        width: 344
        height: 22
        enabled: true
        value: 1
        updateValueWhileDragging: false
    }

    CheckBox {
        id: checkBox1
        x: 259
        y: 36
        width: 93
        height: 16
        text: qsTr("Mute")
    }
}
