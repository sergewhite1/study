Print all awailable interfaces:
tcpdump --list-interface
1.wlp6s0b1 [Up, Running]
2.any (Pseudo-device that captures on all interfaces) [Up, Running]
3.lo [Up, Running, Loopback]
4.enp7s0 [Up]
5.nflog (Linux netfilter log (NFLOG) interface)
6.nfqueue (Linux netfilter queue (NFQUEUE) interface)
7.usbmon1 (USB bus number 1)
8.usbmon2 (USB bus number 2)

Run capture:
tcpdump -vv -i lo tcp port 4040 -w dump.pcap

Run server:
./tcpdump-demo-server

Run client:
tcpdump-demo-client

Stop capture and analyze captured pcap.