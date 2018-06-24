import canlib.canlib as canlib
import sys

print("Initializing Canlib")
cl = canlib.canlib()

chan = 0
if len(sys.argv) == 2:
    chan = int(sys.argv[1])

print("Opening channel %d" % (chan))
ch = cl.openChannel(chan, canlib.canOPEN_ACCEPT_VIRTUAL)

print("%d. %s (%s / %s) " % (chan, ch.getChannelData_Name(),
                                        ch.getChannelData_EAN(),
                                        ch.getChannelData_Serial()))

if ch.getChannelData_Cust_Name() != '':
    print("Customized Channel Name: %s " % (ch.getChannelData_Cust_Name()))
print("Setting bitrate to 250 kb/s")
ch.setBusParams(canlib.canBITRATE_250K)

print("Going on bus")
ch.busOn()

print("Sending a message")
msgId = 123
data = [1, 2, 3, 4, 5, 6, 7, 8]
dlc = len(data)
flags = 0
ch.write(msgId, data, flags, dlc)
print("Going off bus")
ch.busOff()

print("Closing channel")
ch.close()
