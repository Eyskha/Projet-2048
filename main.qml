import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: window
    width: 640
    height: 600
    visible: true
    color: "#eaeaea"
    title: qsTr("Jeu du 2048")

    Grid {
        id: grid
        x: 120
        y: 40
        columns: grille.largeur
        width: 100*grille.largeur
        height: 100*grille.hauteur
        anchors.verticalCenter: parent.verticalCenter
        z: 1
        anchors.horizontalCenter: parent.horizontalCenter

        Repeater{
            model: grille.hauteur*grille.largeur
            Rectangle{
                color: grille.couleurs[index]
                radius: 15
                border.color: "#7c7369"
                border.width: 5
                width: 100
                height: 100

                Text {
                    id: text2
                    text: grille.cases[index]
                    color: (grille.cases[index]==="0" ? "#9d968f" : "#eaeaea")
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 30
                    font.bold: true
                    font.family: "Verdana"
                    anchors.horizontalCenter: parent.horizontalCenter
                    focus: true
                }
            }
        }

        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_Up:
                grille.mouvUp();
                break;
            case Qt.Key_Down:
                grille.mouvDown();
                break;
            case Qt.Key_Left:
                grille.mouvLeft();
                break;
            case Qt.Key_Right:
                grille.mouvRight();
                break;
            case Qt.Key_Space:
                grille.newgame();
                break
            }
        }
    }

    Rectangle {
        id: fond
        x: 79
        y: 137
        width: 100*grille.largeur+10
        height: 100*grille.hauteur+10
        color: "#7c7369"
        radius: 10
        border.color: "#7c7369"
        border.width: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        x: 135
        y: 46
        width: 152
        height: 79
        color: "#7c7369"
        text: "2048"
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 65
        anchors.verticalCenterOffset: -50*(grille.hauteur+1)
        anchors.horizontalCenterOffset: -110
        anchors.horizontalCenter: parent.horizontalCenter
        font.family: "Verdana"
    }

    Rectangle {
        id: rectangle
        x: 342
        y: 56
        width: 161
        height: 59
        visible: true
        color: "#7c7369"
        radius: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -50*(grille.hauteur+1)
        anchors.horizontalCenterOffset: 106
        anchors.horizontalCenter: parent.horizontalCenter
        clip: false
        layer.smooth: true

        Text {
            id: text17
            y: 31
            color: "#eae8e6"
            text: qsTr("Score : ")+grille.score
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Verdana"
        }
    }

    Text {
        id: text19
        x: 8
        y: 8
        text: grille.fin
        font.pixelSize: 20
    }

    Rectangle {
        id: rectangle1
        x: 170
        y: 275
        width: 300
        height: 150
        opacity: grille.opacite
        color: "#f1eaeaea"
        radius: 30
        border.width: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        z: 2

        Text {
            id: text20
            x: 0
            width: 302
            height: 24
            color: "#645b4e"
            text: qsTr("Partie terminée")
            anchors.top: parent.top
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            font.family: "Verdana"
            font.bold: true
            anchors.topMargin: 15
        }

        Text {
            id: text21
            x: 0
            width: 302
            height: 24
            color: "#46433d"
            text: qsTr("Ton score est de :")
            anchors.top: text20.bottom
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            font.family: "Verdana"
            anchors.topMargin: 5
        }

        Text {
            id: text22
            x: 0
            width: 302
            color: "#46433d"
            text: grille.score
            anchors.top: text21.bottom
            anchors.bottom: parent.bottom
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            font.family: "Verdana"
            anchors.bottomMargin: 34
            anchors.topMargin: 5
        }
        Text {
            color: "#46433d"
            text: qsTr("Pour rejouer, appuyer sur la barre espace")
            anchors.top: parent.top
            font.pixelSize: 13
            font.family: "Verdana"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 110
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:10}
}
##^##*/
