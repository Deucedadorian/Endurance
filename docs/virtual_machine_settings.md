# How to create a rabbit board to computer connection

### prerequisites:
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

![configuration of adapter 1](network_adapte1.png)

step 2: configure ethernet port for connecting to TRENDnet Access Point
1. 
