import serial
import time
import sys
from tkinter import *
from tkinter import messagebox

root = Tk()
root.title("PowerTech")
root.geometry("480x180")

titleLabel = Label(root, text = "PowerTech控制器藍牙設定程式")
firstLabel = Label(root, text = "序列埠：")
secondLabel = Label(root, text = "mac位址：")

port = Entry(root, text = "comPort")
addr = Entry(root, text = "macAddr")

def clickHelp():
    messagebox.showinfo("設定說明","1.將遙控器連接至電腦\n2.輸入序列埠後 點擊確認\n3.輸入mac位址後 點擊確認\nmac位址的格式為「12:34:56」")

def clickPort():
    try:
        global ser
        comPort = port.get()
        baudRates = 9600
        ser = serial.Serial(comPort.upper(),baudRates)
    except:
        messagebox.showwarning("序列埠錯誤","請確認開發板是否正確連接至電腦 並重新輸入")


def clickAddr():
    try:
        global ser
        macAddr = addr.get()
        addrList = macAddr.split(':')
        addrFin = str(addrList[0]+addrList[1]+addrList[2]+ \
        addrList[3]+addrList[4]+addrList[5])

        print(addrFin)

        ser.write(b'AT+BAND%s\n' % addrFin.encode())


        time.sleep(0.5)

        while ser.in_waiting:
                feedback = ser.readline().decode()
                print(feedback)
                messagebox.showinfo("完成","已成功設定藍芽晶片")
        else:
            print("00")
    except:
        messagebox.showwarning("錯誤","請重新輸入mac位址")

buttonPort = Button(root, text = "確認序列埠", command = clickPort)
buttonAddr = Button(root, text = "確認mac位址", command = clickAddr)
buttonHelp = Button(root, text = "設定說明", command = clickHelp)

titleLabel.place(x = 140, y = 10)
firstLabel.place(x = 100, y = 50)
secondLabel.place(x = 100, y = 80)
port.place(x = 170, y = 50)
addr.place(x = 170, y = 80)
buttonPort.place(x = 170, y = 110)
buttonAddr.place(x = 260, y = 110)
buttonHelp.place(x = 100, y = 110)

mainloop()
