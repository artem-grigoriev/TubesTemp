import os
import time

cmd = 'mysqldump -u root -pKvantorium33 TubesTemp > /home/pi/tt_dump.sql'
os.system(cmd)
time(600)