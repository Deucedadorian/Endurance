/*** BeginHeader  ********************************************/
#ifndef __UDPDNLD_LIB
#define __UDPDNLD_LIB
#ifdef CUSTOM1
#define DNLD_UDP_PORT	8000	// arbitrary
#else
#define DNLD_UDP_PORT	2000	// arbitrary
#endif
typedef unsigned char ubyte;
typedef unsigned short int ushort;
typedef unsigned long int ulong;
#ifndef ETH_MTU
#define ETH_MTU 1500
#endif

typedef struct {
	ubyte cmd,status;
	ushort length;	// data size
	ulong address;	// write address
	ubyte data[ETH_MTU-8];  // can be up to 512 bytes.
} UDP_DBG_HEADER;

#define UDP_DBG_HEADER_SIZE (sizeof(UDP_DBG_HEADER)-ETH_MTU+8)
#define FRAG_MASK 0xff20

// command definitions
#define UDPDNLD_QUERY 1	// query for all boards (broadcast)
#define UDPDNLD_DOWNLOAD_RAM 2	// download RAM code
#define UDPDNLD_XMEM_SIZE 3		// xmem size needed for RAM code
#define UDPDNLD_DOWNLOAD_FLASH 4	// download FLASH code (data len=0 when done)
#define UDPDNLD_RUN 5		// run download RAM code
#define UDPDNLD_REBOOT 6	// restart with new code
#define UDPDNLD_SET_IP 7	// set the board to diff IP
#define UDPDNLD_SET_SPECIFIC_IP 8	// set the board to diff IP
#define UDPDNLD_GET_USERBLOCK 9
#define UDPDNLD_READ 10
#define UDPDNLD_NULL 127	// do nothing command to resolve ARP

// query status
#define UDPDNLD_STATUS_NULL 0 // not set
#define UDPDNLD_STATUS_NEED_CODE 1 // board needs code downloaded to RAM
#define UDPDNLD_STATUS_HAS_CODE 2 // board has co
#define UDPDNLD_STATUS_RAM_CODE 3	// ram code already running
#define UDPDNLD_STATUS_NOMEM 4 // no xmem available
#define UDPDNLD_STATUS_REBOOT 5 // rebooting

// download status
#define UDPDNLD_STATUS_ACK 6 // download acknowledge
#define UDPDNLD_STATUS_NACK 7 // download fail acknowledge
#define UDPDNLD_STATUS_SEQUENCE 8 // dld sequence error
#define UDPDNLD_STATUS_RAM_CODE_IN_XMEM 9 // RAM loader in flash
#define UDPDNLD_STATUS_FRAG 10	// fragmented packet received
#endif
/*** EndHeader ***********************************************/
