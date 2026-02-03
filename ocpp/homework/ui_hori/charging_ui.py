#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr 21 21:11:05 2025

@author: amin
"""

# main_window.py
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QMainWindow, QStackedWidget, QApplication, QGraphicsOpacityEffect, QLabel, QPushButton
from PyQt5.QtCore import Qt, QPropertyAnimation, QEasingCurve, QTimer, pyqtSignal, QDateTime, QObject
from PyQt5 import QtGui
from home import Ui_Form as home
from step1 import Ui_Form as step1
from step2 import Ui_Form as step2
from step3 import Ui_Form as step3
from step4 import Ui_Form as step4
from step5 import Ui_Form as step5
from step5_2 import Ui_Form as step5_2
from step6 import Ui_Form as step6
from step7_1 import Ui_Form as step7_1
from step7_2 import Ui_Form as step7_2
from step8 import Ui_Form as step8
from step9 import Ui_Form as step9
from step9_new import Ui_Form as step9_new
from step10 import Ui_Form as step10
from thankyou import Ui_Form as thankyou
from PyQt5.QtWidgets import QWidget
from PyQt5.QtCore import QThread
import sys
import datetime
import random
import charge_point
import asyncio
import time
from language_manager import language_manager

try:
    import websockets
except ModuleNotFoundError:
    print("This example relies on the 'websockets' package.")
    print("Please install it by running: ")
    print()
    print(" $ pip install websockets")
    sys.exit(1)

from smartcard.System import readers
from smartcard.util import toHexString


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        parent_width = 1024
        parent_height = 600
        
        self.UID = ""
        
        self.setWindowTitle("Charging Station")
        self.setGeometry(0, 0, 1024, 600)
        self.showFullScreen()

        self.stack = QStackedWidget()
        self.setCentralWidget(self.stack)

        # 初始化每個畫面
        self.welcome = QWidget()
        self.step1 = QWidget()
        self.step2 = QWidget()
        self.step3 = QWidget()
        self.step4 = QWidget()
        self.step5 = QWidget()
        self.step5_2 = QWidget()
        self.step6 = QWidget()
        self.step7_1 = QWidget()
        self.step7_2 = QWidget()
        self.step8 = QWidget()
        self.step9 = QWidget()
        self.step9_new = QWidget()
        self.step10 = QWidget()
        self.thankyou = QWidget()

        self.ui_welcome = home()
        self.ui_welcome.setupUi(self.welcome)
        # self.ui_welcome.label_2.
        # center_x = (parent_width - self.ui_welcome.label_2.width()) // 2
        # center_y = self.ui_welcome.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_welcome.label_2.move(center_x, center_y)
        # self.fit_text_to_label(self.ui_welcome.label_2)
        # center_x = (parent_width - self.ui_welcome.label_4.width()) // 2
        # center_y = self.ui_welcome.label_4.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_welcome.label_4.move(center_x, center_y)
        # self.fit_text_to_label(self.ui_welcome.label_4)
        # self.ui_welcome.pushButton_start.pressed.connect(lambda: self.ui_welcome.pushButton_start.setIcon(QtGui.QIcon("image/btn_start_act.png")))
        # self.ui_welcome.pushButton_start.released.connect(lambda: self.ui_welcome.pushButton_start.setIcon(QtGui.QIcon("image/btn_start_def.png")))
        
        
        
        self.ui_step1 = step1()
        self.ui_step1.setupUi(self.step1)
        # self.ui_step1.label_2.adjustSize()
        # center_x = (parent_width - self.ui_step1.label_2.width()) // 2
        # center_y = self.ui_step1.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_step1.label_2.move(center_x, center_y)
        # self.fit_text_to_label(self.ui_step1.label_2, "Open the charging cover", bold=False)

        self.ui_step2 = step2()
        self.ui_step2.setupUi(self.step2)
        # center_x = (parent_width - self.ui_step2.label_2.width()) // 2
        # center_y = self.ui_step2.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_step2.label_2.move(center_x, center_y)
        # self.fit_richtext_to_label(self.ui_step2.label_2, "<html><head/><body><p align=\"center\">Choose the charging interface is</p><p align=\"center\">compatible with the vehicle</p></body></html>", bold=False)


        self.ui_step3 = step3()
        self.ui_step3.setupUi(self.step3)
        # center_x = (parent_width - self.ui_step3.label_2.width()) // 2
        # center_y = self.ui_step3.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_step3.label_2.move(center_x, center_y)
        # self.fit_richtext_to_label(self.ui_step3.label_2, "<html><head/><body><p align=\"center\">Remove the charging gun and insert it into</p><p align=\"center\">the vehicle’s charging interface</p></body></html>", bold=False)


        self.ui_step4 = step4()
        self.ui_step4.setupUi(self.step4)
        # center_x = (parent_width - self.ui_step4.label_2.width()) // 2
        # center_y = self.ui_step4.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_step4.label_2.move(center_x, center_y)
        # self.fit_text_to_label(self.ui_step4.label_2, "Choose one to start charging", bold=False)
        
        
        self.ui_step5 = step5()
        self.ui_step5.setupUi(self.step5)
        # center_x = (parent_width - self.ui_step5.label_2.width()) // 2
        # center_y = self.ui_step5.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_step5.label_2.move(center_x, center_y)
        # self.fit_text_to_label(self.ui_step5.label_2, "Use APP to Scan the QR code", bold=False)
        
        
        self.ui_step5_2 = step5_2()
        self.ui_step5_2.setupUi(self.step5_2)
        # center_x = (parent_width - self.ui_step5_2.label_2.width()) // 2
        # center_y = self.ui_step5_2.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_step5_2.label_2.move(center_x, center_y)
        # self.fit_richtext_to_label(self.ui_step5_2.label_2, "<html><head/><body><p align=\"center\">Place the RFID card close to the card</p><p align=\"center\">sensing zone on the pile</p></body></html>", bold=False)


        self.ui_step6 = step6()
        self.ui_step6.setupUi(self.step6)
        # center_x = (parent_width - self.ui_step6.label_2.width()) // 2
        # center_y = self.ui_step6.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_step6.label_2.move(center_x, center_y)
        # self.fit_text_to_label(self.ui_step6.label_2, "Access granted", bold=False)
        # self.fit_text_to_label(self.ui_step6.label_3, "Card ID:", bold=False)


        self.ui_step7_1 = step7_1()
        self.ui_step7_1.setupUi(self.step7_1)
        # center_x = (parent_width - self.ui_step7_1.label_2.width()) // 2
        # center_y = self.ui_step7_1.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_step7_1.label_2.move(center_x, center_y)
        # self.fit_text_to_label(self.ui_step7_1.label_2, "Battery Charging")
        # self.fit_text_to_label(self.ui_step7_1.battery_num, "100%")
        # self.fit_text_to_label(self.ui_step7_1.label_3, "Voltage")
        # self.fit_text_to_label(self.ui_step7_1.label_4, "V")
        # self.fit_text_to_label(self.ui_step7_1.label_5, "Charging Time")
        # self.fit_text_to_label(self.ui_step7_1.label_6, "H")
        # self.fit_text_to_label(self.ui_step7_1.label_7, "Min")
        # self.fit_text_to_label(self.ui_step7_1.label_8, "Current")
        # self.fit_text_to_label(self.ui_step7_1.label_9, "A")
        # self.fit_text_to_label(self.ui_step7_1.label_10, "CO2 Saved")
        # self.fit_text_to_label(self.ui_step7_1.label_11, "Kg")
        # self.fit_text_to_label(self.ui_step7_1.label_12, "Power")
        # self.fit_text_to_label(self.ui_step7_1.label_13, "Kw")
        # self.fit_text_to_label(self.ui_step7_1.label_14, "Charging Cost")
        # self.fit_text_to_label(self.ui_step7_1.label_15, "NT$")
        # self.fit_text_to_label(self.ui_step7_1.voltage, "200.0")
        # self.fit_text_to_label(self.ui_step7_1.hour, "00")
        # self.fit_text_to_label(self.ui_step7_1.min, "00")
        # self.fit_text_to_label(self.ui_step7_1.kg, "100.0")
        # self.fit_text_to_label(self.ui_step7_1.power, "100.0")
        # self.fit_text_to_label(self.ui_step7_1.amp, "100.0")
        # self.fit_text_to_label(self.ui_step7_1.nt, "2000$")
        

        self.ui_step7_2 = step7_2()
        self.ui_step7_2.setupUi(self.step7_2)
        # center_x = (parent_width - self.ui_step7_2.label_2.width()) // 2
        # center_y = self.ui_step7_2.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_step7_2.label_2.move(center_x, center_y)
        # self.fit_text_to_label(self.ui_step7_2.label_2, "Battery Charging")
        # self.fit_text_to_label(self.ui_step7_2.label_2, "Battery Charging")
        # self.fit_text_to_label(self.ui_step7_2.battery_num, "100%")
        # self.fit_text_to_label(self.ui_step7_2.label_3, "Voltage")
        # self.fit_text_to_label(self.ui_step7_2.label_4, "V")
        # self.fit_text_to_label(self.ui_step7_2.label_5, "Charging Time")
        # self.fit_text_to_label(self.ui_step7_2.label_6, "H")
        # self.fit_text_to_label(self.ui_step7_2.label_7, "Min")
        # self.fit_text_to_label(self.ui_step7_2.label_8, "Current")
        # self.fit_text_to_label(self.ui_step7_2.label_9, "A")
        # self.fit_text_to_label(self.ui_step7_2.label_10, "CO2 Saved")
        # self.fit_text_to_label(self.ui_step7_2.label_11, "Kg")
        # self.fit_text_to_label(self.ui_step7_2.label_12, "Power")
        # self.fit_text_to_label(self.ui_step7_2.label_13, "Kw")
        # self.fit_text_to_label(self.ui_step7_2.label_14, "Charging Cost")
        # self.fit_text_to_label(self.ui_step7_2.label_15, "NT$")
        # self.fit_text_to_label(self.ui_step7_2.voltage, "200.0")
        # self.fit_text_to_label(self.ui_step7_2.hour, "00")
        # self.fit_text_to_label(self.ui_step7_2.min, "00")
        # self.fit_text_to_label(self.ui_step7_2.kg, "100.0")
        # self.fit_text_to_label(self.ui_step7_2.power, "100.0")
        # self.fit_text_to_label(self.ui_step7_2.amp, "100.0")
        # self.fit_text_to_label(self.ui_step7_2.nt, "2000$")
        
        
        self.ui_step8 = step8()
        self.ui_step8.setupUi(self.step8)
        # center_x = (parent_width - self.ui_step8.label_2.width()) // 2
        # center_y = self.ui_step8.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_step8.label_2.move(center_x, center_y)
        # self.fit_text_to_label(self.ui_step8.label_2, "Billing Details")
        # self.fit_text_to_label(self.ui_step8.label_3, "Charging Date / Time")
        # self.fit_text_to_label(self.ui_step8.label_4, "Charging power")
        # self.fit_text_to_label(self.ui_step8.label_5, "Charging Cost")
        # self.fit_text_to_label(self.ui_step8.label_6, "Payment Method")
        # self.fit_text_to_label(self.ui_step8.label_datetime, "2025/05/31 02:00~2025/05/31 02:15")
        # self.fit_text_to_label(self.ui_step8.label_power, "7.16000 Kw")
        # self.fit_text_to_label(self.ui_step8.label_creditcard, "Credit Card (****1111)")
        # self.fit_text_to_label(self.ui_step8.label_nt, "53100 NT$")
        # self.fit_text_to_label(self.ui_step8.label_11, "Cost Calculation")
        # self.fit_text_to_label(self.ui_step8.label_12, "Payment Information")
        
        
        self.ui_step9 = step9()
        self.ui_step9.setupUi(self.step9)
        
        self.ui_step9_new = step9_new()
        self.ui_step9_new.setupUi(self.step9_new)
        # center_x = (parent_width - self.ui_step9.label_2.width()) // 2
        # center_y = self.ui_step9.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_step9.label_2.move(center_x, center_y)
        # self.fit_richtext_to_label(self.ui_step9.label_2, "<html><head/><body><p>Remove the charging</p><p>gun and return it to the</p><p>designated position on</p><p>the charging station</p></body></html>")

        
        self.ui_step10 = step10()
        self.ui_step10.setupUi(self.step10)
        # center_x = (parent_width - self.ui_step10.label_2.width()) // 2
        # center_y = self.ui_step10.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_step10.label_2.move(center_x, center_y)
        # self.fit_richtext_to_label(self.ui_step10.label_2, "<html><head/><body><p align=\"center\">Confirm that the charging port cover</p><p align=\"center\">on the vehicle is  securely closed</p></body></html>")


        self.ui_thankyou = thankyou()
        self.ui_thankyou.setupUi(self.thankyou)
        # center_x = (parent_width - self.ui_thankyou.label_2.width()) // 2
        # center_y = self.ui_thankyou.label_2.y()  # 保留原來的 y，如果你想垂直置中可一併處理
        # self.ui_thankyou.label_2.move(center_x, center_y)
        # self.fit_richtext_to_label(self.ui_thankyou.label_2, "<html><head/><body><p align=\"center\">Ensure that there are no items left around</p><p align=\"center\">the vehicle and charging station</p></body></html>")


        # 加入 QStackedWidget
        self.stack.addWidget(self.welcome)      # index 0
        self.stack.addWidget(self.step1)   # index 1
        self.stack.addWidget(self.step2)    # index 2
        self.stack.addWidget(self.step3)     # index 3
        self.stack.addWidget(self.step4)      # index 4
        self.stack.addWidget(self.step5)   # index 5
        self.stack.addWidget(self.step5_2)   # index 6
        self.stack.addWidget(self.step6)    # index 7
        self.stack.addWidget(self.step7_1)     # index 8
        self.stack.addWidget(self.step7_2)      # index 9
        self.stack.addWidget(self.step8)     # index 10
        self.stack.addWidget(self.step9)      # index 11
        self.stack.addWidget(self.step9_new)  # index 12
        self.stack.addWidget(self.step10)   # index 13
        self.stack.addWidget(self.thankyou)    # index 14

        # 預設載入歡迎畫面
        self.stack.setCurrentIndex(0)

        # Language selection
        self.ui_welcome.language_combo.currentTextChanged.connect(self.on_language_changed)
        
        # Initialize with default language
        self.update_all_texts()
        
        # 例如從歡迎畫面點擊按鈕跳轉
        self.ui_welcome.pushButton_start.clicked.connect(self.goto_step1)
        
        self.ui_step1.pushButton_next.clicked.connect(self.goto_step2)
        
        self.ui_step2.pushButton_ccs1.clicked.connect(self.goto_step3)
        self.ui_step2.pushButton_ccs2.clicked.connect(self.goto_step3)
        self.ui_step2.pushButton_previous.clicked.connect(self.goto_step1)
        self.ui_step2.pushButton_exit.clicked.connect(self.goto_step0)
        
        self.ui_step3.pushButton_next.clicked.connect(self.goto_step4)
        self.ui_step3.pushButton_previous.clicked.connect(self.goto_step2)
        
        self.ui_step4.pushButton_qrcode.clicked.connect(self.goto_step5)
        self.ui_step4.pushButton_card.clicked.connect(self.goto_step5_2)
        self.ui_step4.pushButton_previous.clicked.connect(self.goto_step3)
        self.ui_step4.pushButton_exit.clicked.connect(self.goto_step0)
        
        self.ui_step5.pushButton_exit.clicked.connect(self.goto_step0)
        self.ui_step5.pushButton_previous.clicked.connect(self.goto_step4)
        
        self.ui_step5_2.pushButton_exit.clicked.connect(self.goto_step0)
        self.ui_step5_2.pushButton_previous.clicked.connect(self.goto_step4)
        
        self.rfid_timer = QTimer()
        self.rfid_timer.timeout.connect(self.rfid_read)
        
        self.ui_step6.pushButton_previous.clicked.connect(lambda: self.goto_step5_2)
        self.ui_step6.pushButton_startcharging.clicked.connect(lambda: self.goto_step7_1(True))
        
        # self.ui_step7_1.pushButton_stop.clicked.connect(self.goto_step7_2)
        self.ui_step7_1.pushButton_stop.clicked.connect(lambda: self.goto_step9_new(True))
        
        # 對應 figma 上沒有這個步驟了，拿掉
        self.ui_step7_2.pushButton_stop.clicked.connect(lambda: self.goto_step9_new(True))
        self.ui_step7_2.pushButton_continue.clicked.connect(lambda: self.goto_step7_1(False))
        
        self.ui_step8.pushButton_ok.clicked.connect(self.goto_step9)
        
        self.ui_step9.pushButton_next.clicked.connect(self.goto_step10)
        self.ui_step9.pushButton_previous.clicked.connect(lambda: self.goto_step8(False))
        
        self.ui_step9_new.pushButton_next.clicked.connect(self.goto_step10)
        
        self.ui_step10.pushButton_next.clicked.connect(self.goto_thankyou)
        self.ui_step10.pushButton_previous.clicked.connect(self.goto_step9)
        
        # battery 的閃爍效果
        self.battery_opacity = QGraphicsOpacityEffect()
        self.ui_step7_1.battery.setGraphicsEffect(self.battery_opacity)
        
        self.battery_animation = QPropertyAnimation(self.battery_opacity, b"opacity")
        self.battery_animation.setDuration(1000)
        self.battery_animation.setStartValue(1.0)
        self.battery_animation.setEndValue(0.0)
        self.battery_animation.setEasingCurve(QEasingCurve.InOutQuad)
        self.battery_animation.setLoopCount(-1)
        self.battery_animation.start()
        
        # battery_num 的閃爍效果
        self.battery_num_opacity = QGraphicsOpacityEffect()
        self.ui_step7_1.battery_num.setGraphicsEffect(self.battery_num_opacity)
        
        self.battery_num_animation = QPropertyAnimation(self.battery_num_opacity, b"opacity")
        self.battery_num_animation.setDuration(1000)
        self.battery_num_animation.setStartValue(1.0)
        self.battery_num_animation.setEndValue(0.0)
        self.battery_num_animation.setEasingCurve(QEasingCurve.InOutQuad)
        self.battery_num_animation.setLoopCount(-1)
        self.battery_num_animation.start()
        
        self.timer = QTimer()        # 加入定時器
        self.timer.timeout.connect(self.update_value)   # 設定定時要執行的 function
        self.timer.timeout.connect(self.total_count)
        # self.timer.start(1000)               # 啟用定時器，設定間隔時間為 500 毫秒
        
        
        self.idle_timer = QTimer()
        self.idle_timer.setInterval(30 * 1000)  # 30 秒
        self.idle_timer.timeout.connect(self.goto_step0)

        # 用來偵測滑鼠點擊的透明遮罩
        self.thankyou_click_mask = QWidget(self)
        self.thankyou_click_mask.setStyleSheet("background: transparent;")
        self.thankyou_click_mask.setGeometry(self.rect())
        self.thankyou_click_mask.mousePressEvent = self.on_thankyou_clicked
        self.thankyou_click_mask.hide()
        
        self.fullscreen = True
        
        # Store reference to worker thread for RFID communication
        self.worker_thread = None
        
        # 調整所有 label
        # self.adjust_all_labels(self)
    
    def on_language_changed(self, language_display_name):
        """Handle language change from dropdown"""
        # Map display names to internal names (now includes flags)
        language_map = {
            "🇹🇼 繁體中文": "Traditional Chinese",
            "🇨🇳 简体中文": "Simplified Chinese",
            "🇺🇸 English": "English",
            "🇯🇵 日本語": "Japanese",
            "🇹🇭 ภาษาไทย": "Thai",
            "🇻🇳 Tiếng Việt": "Vietnamese",
            "🇪🇸 Español": "Spanish"
        }
        
        internal_name = language_map.get(language_display_name, "English")
        language_manager.set_language(internal_name)
        self.update_all_texts()
    
    def update_all_texts(self):
        """Update all UI texts based on current language"""
        # Update welcome page
        self.ui_welcome.label_2.setText(language_manager.get_text("welcome"))
        self.ui_welcome.label_4.setText(language_manager.get_text("charging_station"))
        self.ui_welcome.pushButton_start.setText(language_manager.get_text("start"))
        
        # Update step1
        self.ui_step1.label_2.setText(language_manager.get_text("open_charging_cover"))
        self.ui_step1.pushButton_next.setText(language_manager.get_text("next"))
        
        # Update step2
        self.ui_step2.label_2.setText(language_manager.get_text("choose_charging_interface"))
        self.ui_step2.pushButton_previous.setText(language_manager.get_text("previous"))
        self.ui_step2.pushButton_exit.setText(language_manager.get_text("exit"))
        
        # Update step3
        self.ui_step3.label_2.setText(language_manager.get_text("remove_charging_gun"))
        self.ui_step3.pushButton_next.setText(language_manager.get_text("next"))
        self.ui_step3.pushButton_previous.setText(language_manager.get_text("previous"))
        
        # Update step4
        self.ui_step4.label_2.setText(language_manager.get_text("choose_start_charging"))
        self.ui_step4.pushButton_previous.setText(language_manager.get_text("previous"))
        self.ui_step4.pushButton_exit.setText(language_manager.get_text("exit"))
        
        # Update step5
        self.ui_step5.label_2.setText(language_manager.get_text("use_app_scan_qr"))
        self.ui_step5.pushButton_exit.setText(language_manager.get_text("exit"))
        self.ui_step5.pushButton_previous.setText(language_manager.get_text("previous"))
        
        # Update step5_2
        self.ui_step5_2.label_2.setText(language_manager.get_text("place_rfid_card"))
        self.ui_step5_2.pushButton_exit.setText(language_manager.get_text("exit"))
        self.ui_step5_2.pushButton_previous.setText(language_manager.get_text("previous"))
        
        # Update step6
        self.ui_step6.label_2.setText(language_manager.get_text("access_granted"))
        self.ui_step6.label_3.setText(language_manager.get_text("card_id"))
        self.ui_step6.pushButton_previous.setText(language_manager.get_text("previous"))
        self.ui_step6.pushButton_startcharging.setText(language_manager.get_text("start_charging"))
        # Update timestamp with current language
        self.ui_step6.label_timestamp.setText(f"{language_manager.get_text('timestamp')}: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        
        # Update step7_1
        self.ui_step7_1.label_2.setText(language_manager.get_text("battery_charging"))
        self.ui_step7_1.label_3.setText(language_manager.get_text("voltage"))
        self.ui_step7_1.label_5.setText(language_manager.get_text("charging_time"))
        self.ui_step7_1.label_8.setText(language_manager.get_text("current"))
        self.ui_step7_1.label_10.setText(language_manager.get_text("co2_saved"))
        self.ui_step7_1.label_12.setText(language_manager.get_text("power"))
        self.ui_step7_1.label_14.setText(language_manager.get_text("charging_cost"))
        self.ui_step7_1.pushButton_stop.setText(language_manager.get_text("stop"))
        
        # Update step7_2
        self.ui_step7_2.label_2.setText(language_manager.get_text("battery_charging"))
        self.ui_step7_2.label_3.setText(language_manager.get_text("voltage"))
        self.ui_step7_2.label_5.setText(language_manager.get_text("charging_time"))
        self.ui_step7_2.label_8.setText(language_manager.get_text("current"))
        self.ui_step7_2.label_10.setText(language_manager.get_text("co2_saved"))
        self.ui_step7_2.label_12.setText(language_manager.get_text("power"))
        self.ui_step7_2.label_14.setText(language_manager.get_text("charging_cost"))
        self.ui_step7_2.pushButton_stop.setText(language_manager.get_text("stop"))
        self.ui_step7_2.pushButton_continue.setText(language_manager.get_text("continue"))
        
        # Update step8
        self.ui_step8.label_2.setText(language_manager.get_text("billing_details"))
        self.ui_step8.label_3.setText(language_manager.get_text("charging_date_time"))
        self.ui_step8.label_4.setText(language_manager.get_text("charging_power"))
        self.ui_step8.label_5.setText(language_manager.get_text("charging_cost"))
        self.ui_step8.label_6.setText(language_manager.get_text("payment_method"))
        self.ui_step8.label_11.setText(language_manager.get_text("cost_calculation"))
        self.ui_step8.label_12.setText(language_manager.get_text("payment_information"))
        self.ui_step8.pushButton_ok.setText(language_manager.get_text("ok"))
        
        # Update step9
        self.ui_step9.label_2.setText(language_manager.get_text("remove_gun_return"))
        self.ui_step9.pushButton_next.setText(language_manager.get_text("next"))
        self.ui_step9.pushButton_previous.setText(language_manager.get_text("previous"))
        
        # Update step9_new
        self.ui_step9_new.label_instruction.setText(language_manager.get_text("remove_gun_return"))
        self.ui_step9_new.pushButton_next.setText(language_manager.get_text("next"))
        
        # Update step10
        self.ui_step10.label_2.setText(language_manager.get_text("confirm_port_cover"))
        self.ui_step10.pushButton_next.setText(language_manager.get_text("next"))
        self.ui_step10.pushButton_previous.setText(language_manager.get_text("previous"))
        
        # Update thankyou
        self.ui_thankyou.label_2.setText(language_manager.get_text("ensure_no_items"))
    
    def goto_step0(self):
        self.stack.setCurrentIndex(0)
        self.thankyou_click_mask.hide()
        self.idle_timer.stop()
        self.UID = ""
    
    def goto_step1(self):
        self.stack.setCurrentIndex(1)
    
    def goto_step2(self):
        self.stack.setCurrentIndex(2)
    
    def goto_step3(self):
        self.stack.setCurrentIndex(3)
    
    def goto_step4(self):
        self.rfid_timer.stop()
        self.stack.setCurrentIndex(4)
         
    def goto_step5(self):
        self.stack.setCurrentIndex(5)
        
    def goto_step5_2(self):
        self.stack.setCurrentIndex(6)
        self.rfid_timer.stop()
        self.UID = ""
        self.rfid_timer.start(1000)
    
    def goto_step6(self):
        
        self.ui_step6.pushButton_startcharging.clicked.disconnect()
        self.ui_step6.pushButton_previous.clicked.disconnect()
        if self.UID:
            # self.fit_text_to_label(self.ui_step6.label_uid, self.UID)
            # self.fit_text_to_label(self.ui_step6.label_4, "")
            img = './image/ico_ok.png'
            self.ui_step6.label_6.setPixmap(QtGui.QPixmap(img))
            self.ui_step6.label_uid.setText(self.UID)
            self.ui_step6.label_4.setText("")
            self.ui_step6.pushButton_previous.setText(language_manager.get_text("previous"))
            self.ui_step6.pushButton_previous.clicked.connect(self.goto_step5_2)
            self.ui_step6.pushButton_startcharging.setText(language_manager.get_text("start_charging"))
            self.ui_step6.pushButton_startcharging.clicked.connect(lambda: self.goto_step7_1(True))
            # self.ui_step6.label_5.setText("Connected to central system ✅")
            self.ui_step6.label_5.setText(self.UID)
        else:
            # self.fit_text_to_label(self.ui_step6.label_4, "RFID format error, please try again!")
            img = './image/ico_error.png'
            self.ui_step6.label_6.setPixmap(QtGui.QPixmap(img))
            self.ui_step6.label_uid.setText("")
            self.ui_step6.label_4.setText("RFID format error, please try again!")
            self.ui_step6.pushButton_previous.setText(language_manager.get_text("retry"))
            self.ui_step6.pushButton_previous.clicked.connect(self.goto_step5_2)
            self.ui_step6.pushButton_startcharging.setText(language_manager.get_text("exit"))
            self.ui_step6.pushButton_startcharging.clicked.connect(self.goto_step0)
            
        # self.fit_text_to_label(self.ui_step6.label_timestamp, f"Timestamp: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        self.ui_step6.label_timestamp.setText(f"{language_manager.get_text('timestamp')}: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        self.stack.setCurrentIndex(7)
    
    def goto_step7_1(self, first=True):
        # if first:
            # print("this is first")
        ChargingValue.battery_num = 0
        ChargingValue.battery_stage = 0
        ChargingValue.power = 0
        ChargingValue.end_power = 0
        ChargingValue.charging_start_datetime = datetime.datetime.now()
        self.update_value()
        self.timer.start(1000)
        self.stack.setCurrentIndex(8)
        # self.ui_step7_1.amp.setText("200")
        
    
    def goto_step7_2(self):
        self.timer.stop()
        
        hours, minutes = ChargingValue.get_charging_time()
        
        self.ui_step7_1.battery_num.setText(f"{ChargingValue.battery_num}%")
        self.ui_step7_1.voltage.setText(f"{ChargingValue.voltage}")
        self.ui_step7_1.hour.setText(f"{hours}")
        self.ui_step7_1.min.setText(f"{minutes}")
        self.ui_step7_1.amp.setText(f"{ChargingValue.amp}")
        self.ui_step7_1.kg.setText(f"{ChargingValue.kg}")
        self.ui_step7_1.power.setText(f"{ChargingValue.end_power:.2f}")
        self.ui_step7_1.nt.setText(f"{ChargingValue.nt}")
        
        self.ui_step7_2.battery_num.setText(f"{ChargingValue.battery_num}%")
        self.ui_step7_2.voltage.setText(f"{ChargingValue.voltage}")
        self.ui_step7_2.hour.setText(f"{hours}")
        self.ui_step7_2.min.setText(f"{minutes}")
        self.ui_step7_2.amp.setText(f"{ChargingValue.amp}")
        self.ui_step7_2.kg.setText(f"{ChargingValue.kg}")
        self.ui_step7_2.power.setText(f"{ChargingValue.end_power:.2f}")
        self.ui_step7_2.nt.setText(f"{ChargingValue.nt}")
        self.stack.setCurrentIndex(9)
        
    def goto_step8(self, first=True):
        self.timer.stop()
        
        hours, minutes = ChargingValue.get_charging_time()
        start_dateime = ChargingValue.charging_start_datetime.strftime("%Y-%m-%d %H:%M")
        if first:
            ChargingValue.charging_end_datetime = datetime.datetime.now()
        end_datetime = ChargingValue.charging_end_datetime.strftime("%Y-%m-%d %H:%M")
        total_power = ChargingValue.end_power - ChargingValue.power
        nt = total_power * 100

        # 使用自動調整字體大小
        # self.fit_text_to_label(self.ui_step8.label_datetime, f"{start_dateime}~{end_datetime}")
        # self.fit_text_to_label(self.ui_step8.label_power, f"{total_power:.2f} Kw")
        # self.fit_text_to_label(self.ui_step8.label_nt, f"{int(nt)} NT$")
        
        self.ui_step8.label_datetime.setText(f"{start_dateime}~{end_datetime}")
        self.ui_step8.label_power.setText(f"{total_power:.2f} Kw")
        self.ui_step8.label_nt.setText(f"{int(nt)} NT$")
        self.stack.setCurrentIndex(10)
    
    def goto_step9(self):
        self.stack.setCurrentIndex(11)
    
    def goto_step9_new(self, first=True):
        self.stack.setCurrentIndex(12)
        # Start countdown timer
        self.countdown_timer = QTimer()
        self.countdown_timer.timeout.connect(self.update_countdown)
        self.countdown_seconds = 119  # 01:59 = 119 seconds
        self.update_countdown()
        self.countdown_timer.start(1000)
    
    def update_countdown(self):
        """Update the countdown timer display"""
        if self.countdown_seconds > 0:
            minutes = self.countdown_seconds // 60
            seconds = self.countdown_seconds % 60
            time_str = f"{minutes:02d}:{seconds:02d}"
            self.ui_step9_new.label_timer.setText(time_str)
            self.countdown_seconds -= 1
        else:
            # Timer finished, stop the timer
            self.countdown_timer.stop()
            # Auto-advance to next step
            self.goto_step10()
    
    def goto_step10(self):
        self.stack.setCurrentIndex(13)
    
    def goto_thankyou(self):
        self.stack.setCurrentIndex(14)
        self.idle_timer.start()  # 開始 30 秒計時
        self.thankyou_click_mask.show()  # 顯示全畫面點擊偵測
    
    def on_thankyou_clicked(self, event):
        self.goto_step0()
    
    def rfid_read(self):
        # self.UID = '92345678901234567890'
        # self.rfid_timer.stop()
        # self.goto_step6()
        '''
        r = readers()
        if r:
            conn = r[0].createConnection()
            try:
                conn.connect()
                get_uid = [0xFF, 0xCA, 0x00, 0x00, 0x00]
                data, sw1, sw2 = conn.transmit(get_uid)
        
                if sw1 == 0x90:
                    print("UID: ", toHexString(data))
                    uid_hex = toHexString(data)
                    uid_dec = f'{int(uid_hex.replace(" ", ""), 16)}'
                    self.UID = uid_dec
                    self.rfid_timer.stop()
                    print(self.UID)
                else:
                    print(f"Error: SW={sw1:x}{sw2:x}")
                self.goto_step6()
            except Exception as e:
                print(e)
        else:
            pass
        '''
        card_ids = [
            "7A4C91E2F5B3",
            "D19F73C5A28B",
            "3F7A1E9C84D2",
            "9B62C4D7A1E8",
            "5E1C8A3F9D47",
            "B2D47F8C31E9",
            "4A9F2C7E5D13",
            "E1B47D9C3A52",
            "8C2F5B7A1E49",
            "F73D29E1C84B"
        ]
        # random card_id
        time.sleep(8)
        self.UID = random.choice(card_ids)
        # self.UID = '92345678901234567890'
        self.rfid_timer.stop()
        print(f"RFID read: {self.UID}")
        
        # Send RFID data to server if worker thread is available
        if self.worker_thread and hasattr(self.worker_thread, 'send_rfid_to_server'):
            self.worker_thread.send_rfid_to_server(self.UID)
            print(f"RFID data sent to server: {self.UID}")
        
        self.goto_step6()
    
    def update_value(self):
        hours, minutes = ChargingValue.get_charging_time()
        
    
        self.ui_step7_1.battery_num.setText(f"{ChargingValue.battery_num}")
        self.ui_step7_1.voltage.setText(f"{ChargingValue.voltage}")
        self.ui_step7_1.hour.setText(f"{hours}")
        self.ui_step7_1.min.setText(f"{minutes}")
        self.ui_step7_1.amp.setText(f"{ChargingValue.amp}")
        self.ui_step7_1.kg.setText(f"{ChargingValue.kg}")
        self.ui_step7_1.power.setText(f"{ChargingValue.end_power:.2f}")
        self.ui_step7_1.nt.setText(f"{ChargingValue.nt}")
        
        
    def total_count(self):
        if ChargingValue.battery_num < 100:
            ChargingValue.battery_num += 1
            if ChargingValue.battery_num > 100:
                ChargingValue.battery_num = 100
            if ChargingValue.battery_num <= 10 and ChargingValue.battery_stage < 10:
                img = "./image/battery-0.png"
                self.ui_step7_1.battery.setPixmap(QtGui.QPixmap(img))
                self.ui_step7_2.battery.setPixmap(QtGui.QPixmap(img))
                ChargingValue.battery_stage = 10
            
            elif 11 <= ChargingValue.battery_num <= 20 and ChargingValue.battery_stage < 20:
                img = "./image/battery-10.png"
                self.ui_step7_1.battery.setPixmap(QtGui.QPixmap(img))
                self.ui_step7_2.battery.setPixmap(QtGui.QPixmap(img))
                ChargingValue.battery_stage = 20
        
            elif 21 <= ChargingValue.battery_num <= 30 and ChargingValue.battery_stage < 30:
                img = "./image/battery-20.png"
                self.ui_step7_1.battery.setPixmap(QtGui.QPixmap(img))
                self.ui_step7_2.battery.setPixmap(QtGui.QPixmap(img))
                ChargingValue.battery_stage = 30
            
            elif 31 <= ChargingValue.battery_num <= 40 and ChargingValue.battery_stage < 40:
                img = "./image/battery-30.png"
                self.ui_step7_1.battery.setPixmap(QtGui.QPixmap(img))
                self.ui_step7_2.battery.setPixmap(QtGui.QPixmap(img))
                ChargingValue.battery_stage = 40
        
            elif 41 <= ChargingValue.battery_num <= 50 and ChargingValue.battery_stage < 50:
                img = "./image/battery-40.png"
                self.ui_step7_1.battery.setPixmap(QtGui.QPixmap(img))
                self.ui_step7_2.battery.setPixmap(QtGui.QPixmap(img))
                ChargingValue.battery_stage = 50
                
            elif 51 <= ChargingValue.battery_num <= 60 and ChargingValue.battery_stage < 60:
                img = "./image/battery-50.png"
                self.ui_step7_1.battery.setPixmap(QtGui.QPixmap(img))
                self.ui_step7_2.battery.setPixmap(QtGui.QPixmap(img))
                ChargingValue.battery_stage = 60
        
            elif 61 <= ChargingValue.battery_num <= 70 and ChargingValue.battery_stage < 70:
                img = "./image/battery-60.png"
                self.ui_step7_1.battery.setPixmap(QtGui.QPixmap(img))
                self.ui_step7_2.battery.setPixmap(QtGui.QPixmap(img))
                ChargingValue.battery_stage = 70
            
            elif 71 <= ChargingValue.battery_num <= 80 and ChargingValue.battery_stage < 80:
                img = "./image/battery-70.png"
                self.ui_step7_1.battery.setPixmap(QtGui.QPixmap(img))
                self.ui_step7_2.battery.setPixmap(QtGui.QPixmap(img))
                ChargingValue.battery_stage = 80
        
            elif 81 <= ChargingValue.battery_num <= 90 and ChargingValue.battery_stage < 90:
                img = "./image/battery-80.png"
                self.ui_step7_1.battery.setPixmap(QtGui.QPixmap(img))
                self.ui_step7_2.battery.setPixmap(QtGui.QPixmap(img))
                ChargingValue.battery_stage = 90
            
            elif 91 <= ChargingValue.battery_num <= 100 and ChargingValue.battery_stage < 100:
                img = "./image/battery-90.png"
                self.ui_step7_1.battery.setPixmap(QtGui.QPixmap(img))
                self.ui_step7_2.battery.setPixmap(QtGui.QPixmap(img))
                ChargingValue.battery_stage = 100
            
            # print(ChargingValue.battery_num)
            # print(ChargingValue.battery_stage)
            
            end_power = round(ChargingValue.end_power + random.random(), 2)
            ChargingValue.end_power = end_power
            total_power = round(ChargingValue.end_power - ChargingValue.power, 2)
            nt = int(round(total_power * 100, 0))
            ChargingValue.nt = nt
            if self.battery_animation.state() != QPropertyAnimation.Running:
                self.battery_num_animation.start()
            if self.battery_animation.state() != QPropertyAnimation.Running:
                self.battery_animation.start()
            # print(ChargingValue.end_power)
            # print(QPropertyAnimation.Running)
        else:
            if self.battery_animation.state() == QPropertyAnimation.Running:
                self.battery_num_animation.stop()
            if self.battery_animation.state() == QPropertyAnimation.Running:
                self.battery_animation.stop()
            self.battery_opacity.setOpacity(1.0)
            self.battery_num_opacity.setOpacity(1.0)
            img = "./image/battery-100.png"
            self.ui_step7_1.battery.setPixmap(QtGui.QPixmap(img))
            self.ui_step7_2.battery.setPixmap(QtGui.QPixmap(img))
            self.timer.stop()
            
    def adjust_all_labels(self, parent: QWidget):
        """遞迴遍歷整個父 widget，對所有 QLabel 呼叫 adjustSize()"""
        for label in parent.findChildren(QLabel):
            label.adjustSize()
            
    def fit_text_to_label(self, label: QLabel):
        text = label.text()
        if not text:
            return
    
        # 先取得 label 原本的字型 (會包含字體、粗細、樣式)
        base_font = label.font()
        
        for size in range(100, 5, -1):
            font = QtGui.QFont("Arial", size)
            # font = QtGui.QFont(base_font)
            # font.setBold(bold)  # 設定粗體
            label.setFont(font)
            # font.setPointSize(size)         # 只改大小
            fm = QtGui.QFontMetrics(font)
            if fm.horizontalAdvance(text) <= label.width() and fm.height() <= label.height():
                label.setText(text)
                return
    def fit_richtext_to_label(self, label: QLabel, html_text: str, font_family="Arial", line_spacing=120, bold=False):
        for size in range(100, 5, -1):  # 由大到小試每種字體大小
            font = QtGui.QFont(font_family, size)
            font.setBold(bold)  # 設定粗體
            label.setFont(font)
            
            doc = QtGui.QTextDocument()
            doc.setDefaultFont(font)
            doc.setHtml(html_text)
            
            # 設定行距
            # cursor = QtGui.QTextCursor(doc)
            # block_fmt = QtGui.QTextBlockFormat()
            # # block_fmt.setLineHeight(line_spacing, QtGui.QTextBlockFormat.ProportionalHeight)  
            # block_fmt.setLineHeight(43, QtGui.QTextBlockFormat.FixedHeight)  # 固定 20px
            # cursor.select(QtGui.QTextCursor.Document)
            # cursor.setBlockFormat(block_fmt)
            
            doc.setTextWidth(label.width())
            
            if doc.size().height() <= label.height():
                label.setText(html_text)
                return

    def update_rfid_server_response(self, server_response_data):
        """Update UI with server response data from RFID communication"""
        print(f"Received server response: {server_response_data}")
        # Update label_5 in step6 with the server response
        if hasattr(self, 'ui_step6') and hasattr(self.ui_step6, 'label_5'):
            text_messag =f"{language_manager.get_text('welcome_to_system')}: {server_response_data} !!"
            self.ui_step6.label_5.setText(text_messag)
            print(f"Updated UI with server response: {server_response_data}")

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_Escape:
            if self.fullscreen:
                self.showNormal()
                self.fullscreen = False
            else:
                self.close()
        elif event.key() == Qt.Key_F12:
            if not self.fullscreen:
                self.showFullScreen()
                self.fullscreen = True

class ChargingValue:
    voltage = 200.9
    charging_start_datetime = datetime.datetime.now()
    charging_end_datetime = datetime.datetime.now()
    amp = 500
    kg = 300
    power = 0
    end_power = 0
    nt = 531
    battery_num = 10
    battery_stage = 0

    @classmethod
    def get_charging_time(cls):
        delta = datetime.datetime.now() - cls.charging_start_datetime
        total_seconds = delta.total_seconds()
        hours = int(total_seconds // 3600)
        minutes = int((total_seconds % 3600) // 60)
        return hours, minutes
    



class WorkerThread(QThread):
    rfid_data_signal = pyqtSignal(str)  # Signal to send RFID data
    
    def __init__(self):
        super().__init__()
        self.charge_point_instance = None
        self.event_loop = None
        self.rfid_queue = asyncio.Queue()
        
    def run(self):
        # Run asyncio loop inside this thread
        asyncio.run(self.main_with_rfid())
    
    async def main_with_rfid(self):
        """Modified main function that keeps reference to charge point instance"""
        self.event_loop = asyncio.get_running_loop()
        
        async with websockets.connect(
            "ws://localhost:9000/CP_1", subprotocols=["ocpp2.1"]
        ) as ws:
            print("WebSocket connection established.")
            self.charge_point_instance = charge_point.ChargePoint("CP_1", ws)
            
            # Start both the charge point and RFID processing
            await asyncio.gather(
                self.charge_point_instance.start(), 
                self.charge_point_instance.send_boot_notification(),
                self.process_rfid_queue()
            )
    
    async def process_rfid_queue(self):
        """Process RFID data from the queue"""
        while True:
            try:
                rfid_uid = await self.rfid_queue.get()
                if self.charge_point_instance:
                    response = await self.charge_point_instance.send_rfid_data(rfid_uid)
                    if response and response.data:
                        # Send server response data to UI thread
                        self.rfid_data_signal.emit(response.data)
                    self.rfid_queue.task_done()
            except Exception as e:
                print(f"Error processing RFID: {e}")
    
    def send_rfid_to_server(self, rfid_uid):
        """Method to send RFID data to server - thread safe"""
        if self.event_loop and not self.event_loop.is_closed():
            # Schedule the RFID to be added to the queue
            asyncio.run_coroutine_threadsafe(
                self.rfid_queue.put(rfid_uid), 
                self.event_loop
            )

if __name__ == "__main__":
    QApplication.setAttribute(Qt.AA_EnableHighDpiScaling, True)
    QApplication.setAttribute(Qt.AA_UseHighDpiPixmaps, True)
    app = QApplication(sys.argv)

    screen = app.primaryScreen()
    dpi = screen.logicalDotsPerInch()
    scale = dpi / 96.0
    print(dpi, scale)

    win = MainWindow()   # keep a reference!
    win.show()           # actually show it!

    # Start thread and store reference in MainWindow
    thread_a = WorkerThread()
    win.worker_thread = thread_a  # Store reference for RFID communication
    # Connect signal to update UI with server response
    thread_a.rfid_data_signal.connect(win.update_rfid_server_response)
    thread_a.start()

    sys.exit(app.exec_())