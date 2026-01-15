# Packet captures in Scapy
```
from scapy.all import *

packets = rdpcap("something.pcap")
packets.show()
packets[0].show()
```
