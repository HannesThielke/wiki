# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'opendrop_gui.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
import os, subprocess, time, platform

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(581, 439)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.layoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.layoutWidget.setGeometry(QtCore.QRect(20, 15, 545, 378))
        self.layoutWidget.setObjectName("layoutWidget")
        self.gridLayout_5 = QtWidgets.QGridLayout(self.layoutWidget)
        self.gridLayout_5.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_5.setObjectName("gridLayout_5")
        self.gridLayout = QtWidgets.QGridLayout()
        self.gridLayout.setObjectName("gridLayout")
        self.nrOfDroplets_label = QtWidgets.QLabel(self.layoutWidget)
        self.nrOfDroplets_label.setObjectName("nrOfDroplets_label")
        self.gridLayout.addWidget(self.nrOfDroplets_label, 0, 0, 1, 1)
        self.nrOfDroplets = QtWidgets.QSpinBox(self.layoutWidget)
        self.nrOfDroplets.setEnabled(False)
        self.nrOfDroplets.setProperty("value", 1)
        self.nrOfDroplets.setObjectName("nrOfDroplets")
        self.gridLayout.addWidget(self.nrOfDroplets, 0, 1, 1, 1)
        self.droplet_label = QtWidgets.QLabel(self.layoutWidget)
        self.droplet_label.setObjectName("droplet_label")
        self.gridLayout.addWidget(self.droplet_label, 0, 2, 1, 1)
        self.droplet_dropdown = QtWidgets.QComboBox(self.layoutWidget)
        self.droplet_dropdown.setObjectName("droplet_dropdown")
        self.gridLayout.addWidget(self.droplet_dropdown, 0, 3, 1, 1)
        self.droplet_x_label = QtWidgets.QLabel(self.layoutWidget)
        self.droplet_x_label.setObjectName("droplet_x_label")
        self.gridLayout.addWidget(self.droplet_x_label, 0, 4, 1, 1)
        self.droplet_x_position = QtWidgets.QComboBox(self.layoutWidget)
        self.droplet_x_position.setCurrentText("")
        self.droplet_x_position.setObjectName("droplet_x_position")
        self.droplet_x_position.addItems(['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16'])
        self.gridLayout.addWidget(self.droplet_x_position, 0, 5, 1, 1)
        self.refreshRate_label = QtWidgets.QLabel(self.layoutWidget)
        self.refreshRate_label.setObjectName("refreshRate_label")
        self.gridLayout.addWidget(self.refreshRate_label, 1, 0, 1, 1)
        self.refreshRate = QtWidgets.QSpinBox(self.layoutWidget)
        self.refreshRate.setMaximum(1000)
        self.refreshRate.setProperty("value", 101)
        self.refreshRate.setObjectName("refreshRate")
        self.gridLayout.addWidget(self.refreshRate, 1, 1, 1, 1)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout.addItem(spacerItem, 1, 2, 1, 1)
        self.droplet_y_label = QtWidgets.QLabel(self.layoutWidget)
        self.droplet_y_label.setObjectName("droplet_y_label")
        self.gridLayout.addWidget(self.droplet_y_label, 1, 4, 1, 1)
        self.droplet_y_position = QtWidgets.QComboBox(self.layoutWidget)
        self.droplet_y_position.setObjectName("droplet_y_position")
        self.droplet_y_position.addItems(['1', '2', '3', '4', '5', '6', '7', '8'])
        self.gridLayout.addWidget(self.droplet_y_position, 1, 5, 1, 1)
        self.gridLayout_5.addLayout(self.gridLayout, 0, 0, 1, 1)
        self.line = QtWidgets.QFrame(self.layoutWidget)
        self.line.setFrameShape(QtWidgets.QFrame.HLine)
        self.line.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line.setObjectName("line")
        self.gridLayout_5.addWidget(self.line, 1, 0, 1, 1)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.protocol_steps = QtWidgets.QListWidget(self.layoutWidget)
        self.protocol_steps.setObjectName("protocol_steps")
        self.horizontalLayout.addWidget(self.protocol_steps)
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.btn_del_selected_item = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_del_selected_item.setObjectName("btn_del_selected_item")
        self.verticalLayout.addWidget(self.btn_del_selected_item)
        spacerItem1 = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
        self.verticalLayout.addItem(spacerItem1)
        self.horizontalLayout.addLayout(self.verticalLayout)
        self.horizontalLayout_2.addLayout(self.horizontalLayout)
        self.gridLayout_2 = QtWidgets.QGridLayout()
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.btn_up = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_up.setObjectName("btn_up")
        self.gridLayout_2.addWidget(self.btn_up, 0, 1, 1, 1)
        self.btn_left = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_left.setObjectName("btn_left")
        self.gridLayout_2.addWidget(self.btn_left, 1, 0, 1, 1)
        self.btn_step = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_step.setObjectName("btn_step")
        self.gridLayout_2.addWidget(self.btn_step, 1, 1, 1, 1)
        self.btn_right = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_right.setObjectName("btn_right")
        self.gridLayout_2.addWidget(self.btn_right, 1, 2, 1, 1)
        self.btn_down = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_down.setObjectName("btn_down")
        self.gridLayout_2.addWidget(self.btn_down, 2, 1, 1, 1)
        self.horizontalLayout_2.addLayout(self.gridLayout_2)
        self.gridLayout_5.addLayout(self.horizontalLayout_2, 2, 0, 1, 1)
        self.line_2 = QtWidgets.QFrame(self.layoutWidget)
        self.line_2.setFrameShape(QtWidgets.QFrame.HLine)
        self.line_2.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line_2.setObjectName("line_2")
        self.gridLayout_5.addWidget(self.line_2, 3, 0, 1, 1)
        self.gridLayout_4 = QtWidgets.QGridLayout()
        self.gridLayout_4.setObjectName("gridLayout_4")
        self.btn_generate_arduino_code = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_generate_arduino_code.setObjectName("btn_generate_arduino_code")
        self.gridLayout_4.addWidget(self.btn_generate_arduino_code, 0, 0, 1, 1)
        self.btn_open_arduino_code = QtWidgets.QPushButton(self.layoutWidget)
        self.btn_open_arduino_code.setObjectName("btn_open_arduino_code")
        self.gridLayout_4.addWidget(self.btn_open_arduino_code, 1, 0, 1, 1)
        self.gridLayout_3 = QtWidgets.QGridLayout()
        self.gridLayout_3.setObjectName("gridLayout_3")
        spacerItem2 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_3.addItem(spacerItem2, 0, 0, 1, 1)
        self.status_label = QtWidgets.QLabel(self.layoutWidget)
        self.status_label.setObjectName("status_label")
        self.gridLayout_3.addWidget(self.status_label, 1, 0, 1, 1)
        self.status_value_label = QtWidgets.QLabel(self.layoutWidget)
        self.status_value_label.setObjectName("status_value_label")
        self.gridLayout_3.addWidget(self.status_value_label, 1, 1, 1, 1)
        spacerItem3 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_3.addItem(spacerItem3, 0, 1, 1, 1)
        self.gridLayout_4.addLayout(self.gridLayout_3, 0, 1, 2, 1)
        self.gridLayout_5.addLayout(self.gridLayout_4, 4, 0, 1, 1)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 581, 22))
        self.menubar.setObjectName("menubar")
        self.menuFile = QtWidgets.QMenu(self.menubar)
        self.menuFile.setObjectName("menuFile")
        self.menuEdit = QtWidgets.QMenu(self.menubar)
        self.menuEdit.setObjectName("menuEdit")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionOpen = QtWidgets.QAction(MainWindow)
        self.actionOpen.setObjectName("actionOpen")
        self.actionClose = QtWidgets.QAction(MainWindow)
        self.actionClose.setObjectName("actionClose")
        self.actionClear = QtWidgets.QAction(MainWindow)
        self.actionClear.setObjectName("actionClear")
        self.menuFile.addAction(self.actionOpen)
        self.menuFile.addAction(self.actionClose)
        self.menuEdit.addAction(self.actionClear)
        self.menubar.addAction(self.menuFile.menuAction())
        self.menubar.addAction(self.menuEdit.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.nrOfDroplets_label.setText(_translate("MainWindow", "Number of Droplets:"))
        self.droplet_label.setText(_translate("MainWindow", "Droplet:"))
        self.droplet_x_label.setText(_translate("MainWindow", "x:"))
        self.refreshRate_label.setText(_translate("MainWindow", "Refresh Rate:"))
        self.droplet_y_label.setText(_translate("MainWindow", "y:"))
        self.btn_del_selected_item.setText(_translate("MainWindow", "X"))
        self.btn_up.setText(_translate("MainWindow", "up"))
        self.btn_left.setText(_translate("MainWindow", "left"))
        self.btn_step.setText(_translate("MainWindow", "step"))
        self.btn_right.setText(_translate("MainWindow", "right"))
        self.btn_down.setText(_translate("MainWindow", "down"))
        self.btn_generate_arduino_code.setText(_translate("MainWindow", "generate Arduino Code"))
        self.btn_open_arduino_code.setText(_translate("MainWindow", "open Arduino Code"))
        self.status_label.setText(_translate("MainWindow", "Status: "))
        self.status_value_label.setText(_translate("MainWindow", "-"))
        self.menuFile.setTitle(_translate("MainWindow", "File"))
        self.menuEdit.setTitle(_translate("MainWindow", "Edit"))
        self.actionOpen.setText(_translate("MainWindow", "Open"))
        self.actionClose.setText(_translate("MainWindow", "Exit"))
        self.actionClear.setText(_translate("MainWindow", "Clear"))

        self.btn_left.clicked.connect(self.moveLeft)
        self.btn_right.clicked.connect(self.moveRight)
        self.btn_up.clicked.connect(self.moveUp)
        self.btn_down.clicked.connect(self.moveDown)
        self.btn_del_selected_item.clicked.connect(self.removeSelectedItems)
        self.btn_generate_arduino_code.clicked.connect(self.generateArduinoCode)
        self.btn_open_arduino_code.clicked.connect(self.openArduinoCode)
        self.btn_step.clicked.connect(self.nextStep)
        self.droplet_dropdown.addItem('Droplet 1')
        
    def removeSelectedItems(self):
        self.status_value_label.setText('removed last item.')
        listItems = self.protocol_steps.selectedItems()
        if not listItems: return
        for item in listItems:
                self.protocol_steps.takeItem(self.protocol_steps.row(item))
        
    def moveLeft(self):
        self.status_value_label.setText('added "left" item.')
        self.protocol_steps.addItem(QtWidgets.QListWidgetItem('left \t(' + str(self.droplet_dropdown.currentText()) + ")"))
        
    def moveRight(self):
        self.status_value_label.setText('added "right" item.')
        self.protocol_steps.addItem(QtWidgets.QListWidgetItem('right \t(' + str(self.droplet_dropdown.currentText()) + ")"))
        
    def moveUp(self):
        self.status_value_label.setText('added "up" item.')
        self.protocol_steps.addItem(QtWidgets.QListWidgetItem('up \t(' + str(self.droplet_dropdown.currentText()) + ")"))
        
    def moveDown(self):
        self.status_value_label.setText('added "down" item.')
        self.protocol_steps.addItem(QtWidgets.QListWidgetItem('down \t(' + str(self.droplet_dropdown.currentText()) + ")"))

    def nextStep(self):
        self.status_value_label.setText('added "step" item.')
        self.protocol_steps.addItem(QtWidgets.QListWidgetItem('wait \t(' + str(self.refreshRate.value()) + ' ms)'))
        self.refreshRate.setEnabled(False)
        
    def generateArduinoCode(self):
        # Read the protocol list
        items = []
        for index in range(self.protocol_steps.count()):
            items.append(self.protocol_steps.item(index))
        labels = [i.text() for i in items]
        
        # Open Output File
        outputFile = open('OpenDropCode/OpenDropCode.ino', 'w')
        
        # Load the basic code from template file
        with open('OpenDropCode_Template/OpenDropCode_Template.ino', 'r') as template:
            outputFile.writelines(template.readlines())
        
        # Write things in the Setup function
        outputFile.write("\tmyDrop->begin(" + str(self.droplet_x_position.currentText()) + "," + str(self.droplet_y_position.currentText()) + ");\n")
        outputFile.write("\tOpenDropDevice.update();\n")

        # Start the loop function
        outputFile.writelines("}\n\n"
        "void loop(){\n"
        "\tSW2_value = digitalRead(SW2_pin);\n\n"
        "\t// Wait for button 2 to be pressed\n"
        "\twhile(SW2_value) SW2_value = digitalRead(SW2_pin);\n"
        "\trun_protocol();\n"
        "}\n\n"
        )

        self.refreshRate.update()
        outputFile.write("int del_time={};".format(self.refreshRate.value()))
        outputFile.write("\n\nvoid run_protocol(){")
        
        for item in labels:
            if item[:4] == 'left':
                outputFile.write("\n\tmyDrop->move_left();")
                outputFile.write("\n\tOpenDropDevice.run();")
            if item[:5] == 'right':
                outputFile.write("\n\tmyDrop->move_right();")
                outputFile.write("\n\tOpenDropDevice.run();")
            if item[:2] == 'up':
                outputFile.write("\n\tmyDrop->move_up();")
                outputFile.write("\n\tOpenDropDevice.run();")
            if item[:4] == 'down':
                outputFile.write("\n\tmyDrop->move_down();")
                outputFile.write("\n\tOpenDropDevice.run();")
            if item[:4] == 'step':
                outputFile.write("\n\tdelay(del_time);")
        
        outputFile.write("\n}")
        self.status_value_label.setText('output file generated.')
    
    def openArduinoCode(self):
        self.status_value_label.setText('opening Arduino file ...')
        if platform.system() == 'Windows':
            os.system('start OpenDropCode/OpenDropCode.ino', shell=True)
        elif platform.system() == 'Darwin':
            subprocess.call('open OpenDropCode/OpenDropCode.ino', shell=True)


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

