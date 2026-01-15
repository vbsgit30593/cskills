# Intro
* This project is trying to build a TCP/IP stack.
* The main goal is to learn the protocol in a hands own manner

# Knowledge gain ## TUN/TAP
https://www.kernel.org/doc/Documentation/networking/tuntap.txt
https://www.youtube.com/watch?v=NZlbyoHgYjk&list=PL2TXDotVKyDCuM7-MShb_9y2g6LQjVDxw

* In case of tap, a virtual bridge is created such that packets arriving on the
actual hardware NIC and passed via the virtual bridge to the tap interface.
* We can read or write packets from and to userspace.
* A tap helps in intercepting low level network traffic from the linux kernel.
* For L2, we need TAP and for L3 we need TUN.
* TUN/TAP provides packet reception and transmission for user space programs.
It can be seen as a simple Point-to-Point or Ethernet device, which, instead of
receiving packets from physical media, receives them from user space program
and instead of sending packets via physical media writes them to the user space
program. 
