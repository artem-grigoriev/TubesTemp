from __future__ import print_function
import time
import mysql.connector
import serial

while 1:
    user = 'root'
    db = 'TubesTemp'
    passwrd = 'Kvantorium33'
    cnx = mysql.connector.connect(user=user,
                                  database=db,
                                  password=passwrd,
                                  host='127.0.0.1')
    cursor = cnx.cursor()
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout = 3)
    line = ser.readline().decode("utf-8").strip()
    print(">> ", line)
    data = line.split(" ")
    if (len(data) == 4) and (data[0] != 'Kvantorium-33'):
        id = data[1]
        id = id[:-1]
        idcheck = id.split()
        if(idcheck[0] == '2') and (idcheck[1] == '8'):
            print(data)
            temp = data[len(data) - 1]

            add_sensor = ("INSERT INTO TubesTemp"
                            "(date_add, temp, id)"
                            "VALUES (%s, %s, %s)")
            data_sensor = (time.time(), temp, id)

            # Insert sensor
            cursor.execute(add_sensor, data_sensor)
            emp_no = cursor.lastrowid
            # Make sure data is committed to the database
            cnx.commit()

            cursor.close()
            cnx.close()
