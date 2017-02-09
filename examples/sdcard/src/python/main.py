import machine, sdcard, os, time

sd = sdcard.SDCard(machine.SPI(1), machine.Pin(15))

os.umount()
os.VfsFat(sd, "")
os.listdir()


time.sleep(2)

f = open('test.txt', 'w')
f.write('hello world')
f.close()
os.listdir()

time.sleep(1)

f = open('text.txt', 'r')
f.read()
f.close()
