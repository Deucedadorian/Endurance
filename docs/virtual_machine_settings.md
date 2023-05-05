# How to Create a Babbit Board-to-Computer Connection

### Prerequisites:
1. 2x [TRENDnet TEW-430APB](https://www.trendnet.com/products/product-detail?prod=145_TEW-430APB)s or equivalent
2. 2x ethernet cables
3. computer running [Oracle VM VirtualBox](https://www.virtualbox.org/) with a Windows XP or Vista VM

step 1: configure wifi for vm. (probably not necessary but possibly useful)
1. inside of VirtualBox select settings for your Virtual Machine.
2. go to the network tab.
3. select Adapter 1
4. Ensure 'Enable Network Adapter' is checked
5. set 'Attached to' to NAT
6. adapter type set to Intel Pro/1000 MT Desktop(82540EM)

![configuration of adapter 1](/images/network_adapter1.jpg)

step 2: configure ethernet port for connecting to TRENDnet Access Point
1. next to where you selected Adapter 1, select Adapter 2 
2. Ensure 'Enable Network Adapter' is checked
3. for Name, select your ethernet port. I don't know if it's different for 
different computers but if it is, you'll have to figure out which option corresponds with your ethernet port.
4. in Advanced, set adapter type to Intel Pro/1000 MT Desktop(82540EM)  
5. you can set Promiscuous Mode to Allow All if you're feeling frisky

![configuration of adapter 2](/images/network_adapter2.jpg)

\* you'll have to figure out which option is your ethernet, either research or trial and error to figure it out!.. unless it's the same as mine lol

step 3: configure your virtual machine for communication with Rabbit

1. open control panel in your vm and click 'Network and Internet Connections'

![open control panel in your vm and click 'Network and Internet Connections'](/images/winXPNetworkSetup1.jpg)

2. select Network Connections

![select Network Connections](/images/winXPNetworkSetup2.jpg)

3. inside of network connections, select the Local Area Connection corresponding to your ethernet port, in my case LAC 4

![inside of network connections, select the Local Area Connection corresponding to your ethernet port, in my case LAC 4](/images/winXPNetworkSetup3.jpg)

4. next, Select Properties

![Select Properties](/images/winXPNetworkSetup4.jpg)

5. highlight Internet Protocol(TCP/IP) (or Internet Protocol Version 4 if there is the option)
6. click Properties

![steps 5. and 6.](/images/winXPNetworkSetup5.jpg)

7. check use the following IP address
8. input the IP address '192.168.0.50'
9. input the Subnet mask '255.255.255.0'
10. click OK and close the rest of the windows that were opened during this process
![steps 7., 8., and 9.,](/images/winXPNetworkSetup6.jpg)

follow Complete Communication Re-Configuration Procedure.pdf in /docs to complete configuration.
