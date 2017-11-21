
TCP/IP Demo Library
===================
This fully working demonstration library is made for testing purposes only. You 
need to run the included dynmac.exe program on your PC before you start a DSP 
application. When the DSP program starts, a BOOTP request is performed and the 
dynmac.exe server is responding with an essential code part for the DSP. 

IT IS NOT ALLOWED TO RUN MORE THAN ONE DSK DEMO APPLICATION IN ONE LOCAL AREA
NETWORK.

The test program for the TCP/IP library (\Example\Misc\NetTest\) implements a 
ICMP socket to reply to 'pings', an UDP echo server and a TCP server which
sends a message in response to any incoming request on port 1061. The DSP's IP 
address setting (default mydemo) can be changed in file netconfig.c. 
You may have to recompile the program with an IP address or Host name that 
matches your network.

To verify operation, use the NetCat utility from the tools subdirectory 
\util\netcat\. The following examples use the DSP IP address mydemo, 
change this according to your network.

To test ICMP, type:
  >ping mydemo

To test the UDP echo server, run NetCat with
  >nc -u mydemo 7

  Any characters you type in the console window will be returned. NetCat doesn't
  send the characters immediately, it will send the entire string following a 
  terminating CR. Please note that the maximum length of the character string
  is limited by the size of the buffer used for UDP echo (1024). You may also 
  transmit a file by re-directing it to stdin:

  >nc -u mydemo 7 < hello.txt

To test the TCP server, run NetCat with
  >nc mydemo 1061

  Type a CR, the DSP will respond with it's message
