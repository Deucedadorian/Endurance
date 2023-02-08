#define UDP_SOCKETS 4	// allow enough for downloader and DHCP
#define MAX_UDP_SOCKET_BUFFERS 4


#define DISABLE_TCP // this sample does not use TCP, this saves code space

// this is required for 9.x and 8.5 or later.
#define TCPCONFIG 7

// this is for 7.x compilers
//#define MY_IP_ADDRESS "10.1.1.89"
//#define MY_NETMASK "255.255.255.0"
//#define USE_DHCP 1 // use this for earlier versions


#use dcrtcp.lib

// define this string to inlcude the RAM loader in FLASH,
// RAM loader must be unencrypted.
// use the full path to the file and use forward slashes.
#define UDPDL_LOADER "c:/dcrabbit_9.62/Loaders/pdl-generic-D.bin"
// this allows the new code to show th MAC address even through subnets or routers.
#define SHOW_MAC_ADDR

//
// this will output debug info on serial port a at 115200 baud
//
#ifdef DEBUG_RST // only include if compiling with debugging on.
#define	STDIO_DEBUG_SERIAL	SADR
#define	STDIO_DEBUG_BAUD		115200l
#define	STDIO_DEBUG_ADDCR
#endif

// include the library

#use UDPDOWNL.lib

// the following is for a combined etherenet/serial demo
#ifdef INC_SERLOAD
#define DIRECT_SERIAL
#define BAUD_RATE 57600
#use SERDOWNL.LIB
#endif
//
// Define the board ID. this will appear in the board list in the PC app.
//
const char my_id[]="Demo app using Generic loader " __DATE__;

root void main()
{
	printf(my_id);
	printf("\nNetwork init\n");
	sock_init();

   // Wait for default LAN interface to come up.
	// otherwise sockets may fail as they have no IP
	while (ifpending(IF_DEFAULT) == 1)
		tcp_tick(NULL);

  	ip_print_ifs();

#ifdef INC_SERLOAD
	SerDL_Init(my_id);
#endif
	//
	// Initialize the DLM
	//
	UDPDL_Init(my_id);

	// lots of useless debug info.
	printf("SEGSIZE=%x\n",RdPortI(SEGSIZE));
	printf("MMIDR=%x\n",RdPortI(MMIDR));
	printf("MECR=%x\n",RdPortI(MECR));
	printf("MTCR=%x\n",RdPortI(MTCR));
	printf("MB0CR=%x\n",MB0CRShadow);
	printf("MB1CR=%x\n",MB1CRShadow);
	printf("MB2CR=%x\n",MB2CRShadow);
	printf("MB3CR=%x\n",MB3CRShadow);
	printf("GCSR=%x\n",GCSRShadow);
	printf("GCSRIO=%x\n",RdPortI(GCSR));
	printf("STACKSEG=%x\n",RdPortI(STACKSEG));
	printf("DATASEG=%x\n",RdPortI(DATASEG));
	printf("RAMCS=%x\n",CS_RAM);
	printf("Ready to download over me!\n");
	//
	// sample main loop
	//
	while(1)
	{
#ifdef INC_SERLOAD
		SerDL_Tick();
#endif
		tcp_tick(NULL); // usually in user's main loop somewhere
		// call the tick at least twoce a second for best results.
		// this can be in its own costate if needed
		if (UDPDL_Tick()) // this should be called at least twice a second.
		{
			printf("Download request pending!\n");
			// if you need to shut things down before the download, do it here.
		}
		//
		// regular user main loop would follow
		//
	}
}