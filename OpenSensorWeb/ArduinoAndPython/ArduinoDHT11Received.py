import serial
import time
import traceback
import pyodbc
import datetime

ser = serial.Serial('COM6', 9600, timeout=60)
connection = pyodbc.connect('Driver={SQL Server};Server=LENOVOZ50-70;Database=OpenMonitor;uid=OpenMonitor;pwd=0penm0nit0r')
cursor = connection.cursor()

while 1:
    try:
        lineReceived = ser.readline().decode().strip()
        now = datetime.datetime.now()
        lineReceived = "%s:::Datetime=%s" % (lineReceived , now.strftime("%Y-%m-%d %H:%M:%S"))
        split = lineReceived.split(":::")
        temperature = split[0].split("=")[1]
        humidity = split[1].split("=")[1]
        sound = split[2].split("=")[1]
        print("--------------------------")
        print(now)
        print("Temperature: %s" % temperature) #Temperature
        print("Humidité : %s%%" % humidity) #Humidity
        print("Sound : %s" % sound ) #Sound
        sql = "INSERT INTO [OpenMonitor].[dbo].[OpenMonitorValue](ModuleId , Value , CreatedDate) VALUES (? , ? , ? )" #Base INSERT
        cursor.execute(sql, 1, temperature, now)
        cursor.execute(sql, 2, humidity, now)
        cursor.execute(sql, 3, sound, now)
        connection.commit()
    except :
        traceback.print_exc()
    #time.sleep(1)
cursor.close()
connection.close()


