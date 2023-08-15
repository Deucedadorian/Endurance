#define UDP_SOCKETS 4	// allow enough for debugger and DHCP
#define MAX_UDP_SOCKET_BUFFERS 4

// undefine this if you don't want dhcp
//#define USE_DHCP 1

// if you use hardcoded addresses
// edit these defines
#define DISABLE_DNS
#define MY_IP_ADDRESS   "10.1.1.200"
#define MY_NETMASK      "255.255.255.0"
// default is 600, speed up but less then 1500
#define ETH_MTU 700
#define FULL_DUPLEX

#use dcrtcp.lib

//
// remember to add udpdebug.lib to your lib.dir in the compiler directory!
//
#use UDPDebug.lib

//
// These defines reroute stdio to the debug calls.
// as an alternative you can just use the calls directly
// reroute printf to debug_printf
#define printf dbg_printf
//#define putchar(c) dbg_printf("%c",c)
#define kbhit dbg_kbhit
#define getchar dbg_getchar
#define puts(x) dbg_printf("%s",x)

typedef struct {
	float random;
	long int counter; // HEX
	char string[80];
	int bitmask;	// BINARY
	int edit_me;
} demostruct;

//
// this define tells the debugger to stop looking for stucture,
// typedef, enums and #defines. It can't handle 'c' code, only
// what would normally be in a ".h" file.
//
#define NO_DEBUG_PARSE

demostruct demo;
int count;
xmem void main()
{
// disable by default, otherwise any printfs will hang if they happen before
// sock_init()/debug_init(1)
	dbg_init(0);
	demo.counter=0l;
	demo.edit_me=count=0;
	pd_resetinterface();	// this seems to fix some hub problems
	sock_init();

// this fixes an init bug of the realtek chip
#asm
	ld hl, 500 ;500 ms delay
	call tickwait
#endasm
// everything ready now enable the debugger
	dbg_init(1);
	printf("Ready to debug!\n");
	while(1)
	{
		costate
		{
			tcp_tick(NULL);
			// poll this from time to time......
			debug_tick();
			// 
			demo.counter++;
		}
		costate
		{
			waitfor(DelayMs(1000));	
			sprintf(demo.string,"Count is now %d\n",++count);
			puts(demo.string);
			demo.bitmask=1<<(count%16);
			demo.random=rand();
		}
	}
}
