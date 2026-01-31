import serial
import tkinter as tk

PORT = "COM4"     
BAUD = 9600       

prozor = tk.Tk()
prozor.title("KTM")
prozor.geometry("410x300")

ser = serial.Serial(
    PORT,
    BAUD,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    timeout=1
)

def map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min


def pali(text):
    #text = 'p'
    ser.write(text.encode())
    print("Poslano: pali ledicu")
    data = ser.read(50)
    print("Primljeno: ", data.decode(errors="ignore"))
    if text == 'a':
        mode = 'p'
        jacinaP.set(10)
    elif text == 'c':
        mode = 'c'
        jacinaC.set(20)
    elif text == 'e':
        mode = 'z'
        jacinaZ.set(30)

def gasi(text):
    #text = 'g'
    ser.write(text.encode())
    print("Poslano: gasi ledicu")
    data = ser.read(50)
    print("Primljeno: ", data.decode(errors="ignore"))
    if text == 'b':
        jacinaP.set(1)
    elif text == 'd':
        jacinaC.set(11)
    elif text == 'f':
        jacinaZ.set(21)

def vrijednostP(vr):
    val = int(vr)
    ser.write(bytes([val]))


def vrijednostZ(vr):
    val = int(vr)
    ser.write(bytes([val]))

def vrijednostC(vr):
    val = int(vr)
    ser.write(bytes([val]))

paliP = tk.Button(prozor, text = "Pali", width = 10, command = lambda: pali("a"))
paliP.place(x = 10, y = 50)
gasiP = tk.Button(prozor, text = "Gasi", width = 10, command = lambda: gasi("b"))
gasiP.place(x = 10, y = 150)
jacinaP = tk.Scale(prozor, from_ = 1, to = 10, orient = tk.HORIZONTAL, command = vrijednostP)
jacinaP.place(x = 10, y = 250)


paliC = tk.Button(prozor, text = "Pali", width = 10, command = lambda: pali("c"))
paliC.place(x = 150, y = 50)
gasiC = tk.Button(prozor, text = "Gasi", width = 10, command = lambda: gasi("d"))
gasiC.place(x = 150, y = 150)
jacinaC = tk.Scale(prozor, from_ = 11, to = 20, orient = tk.HORIZONTAL, command = vrijednostC)
jacinaC.place(x = 150, y = 250)


paliZ = tk.Button(prozor, text = "Pali", width = 10, command = lambda: pali("e"))
paliZ.place(x = 300, y = 50)
gasiZ = tk.Button(prozor, text = "Gasi", width = 10, command = lambda: gasi("f"))
gasiZ.place(x = 300, y = 150)
jacinaZ = tk.Scale(prozor, from_ = 21, to = 30, orient = tk.HORIZONTAL, command = vrijednostZ)
jacinaZ.place(x = 300, y = 250)


prozor.mainloop()
