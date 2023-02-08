Enclosed is the demo for the SHDesigns Ethernet Download Manager.

Demo works for most Rabbit boards:

Softools:
Use the Flashit to program an rabbit board with the dlm-demo.bin file. Remove
the programming cable and reset the board. Note: if you don't have flashit, you can
use the RFU from Dynamic C.

Dynamic C:
Use the RFU program an rabbit board with the dlm-demo.bin file. Remove
the programming cable and reset the board.

Note: if your board does not use the clock doubler, use the DLMDemo-ND.bin file.

The board will come up with a DHCP IP address. If this fails, it wil have an address
of 10.1.100.88. If this is not compatable with your network, that will not be a problem.

Run the UDPDownload.exe program. It should find the board.

If not, do a "Search" and it should find a board with an id of:
 "SHDesigns DC/Softools Demo V1.2 Wed Jan  4 2006".

If the IP address is not valid for your LAN, then use the "Set Board IP" command
from the "Ping" menu. Enter an unused local IP address to use.

Click on the "..." button to the right of the "User Program" field. Select
one of your .bin files compatable with the board you use.

Select the board running the demo then Click on download. The program will then
download and run your program. However, since your program does not have the
DLM included it will not be able to be updated with the utility.

If you connect the programming cable with the "Diag" connector to the board you can
capture the debug output. Use something like HyperTerm at 115200 baud, no parity
and no handshaking.

For more information, check the web Page: 

http://shdesigns.org/rabbit/st-download.html	- Softools version
http://shdesigns.org/rabbit/download.html	- Dyanic C version

Thanks for trying the demo; hope your impressed ;)

Scott Henion
SHDesigns
