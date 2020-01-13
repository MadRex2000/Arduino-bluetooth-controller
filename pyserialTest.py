import serial.tools.list_ports

ports = list(serial.tools.list_ports.comports())
print(ports)
for i in ports:
    print(i)
