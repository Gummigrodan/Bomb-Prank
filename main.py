import serial
import time

arduino = serial.Serial('COM3', 9600)
time.sleep(2)

while True:
    seconds = input("Ange sekunder för nedräkning: ")

    if seconds.lower() == "exit":
        break

    if seconds.isdigit():
        arduino.write((seconds + "\n").encode())
    else:
        print("Skriv bara siffror!")

arduino.close()