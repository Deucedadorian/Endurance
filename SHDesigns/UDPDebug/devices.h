/*** BeginHeader  */
#ifndef __DEVICES_H
#define __DEVICES_H

/*** EndHeader */

/*** BeginHeader  */
// Define the supported device types
#define EMPTY_SLOT			0
#define TYPE_UNKNOWN_DEVICE	1
#define TYPE_BAROMETER		2
#define TYPE_HUMIDITY		3
#define TYPE_LIGHTNING		4
#define TYPE_WIND_SPEED		5
#define TYPE_WIND_DIRECTION	6
#define TYPE_RAIN_GAUGE		7
#define TYPE_SOLAR			8
#define TYPE_HUMIDITY_SOLAR	9
#define TYPE_TEMP			10
#define TYPE_LEAF_WETNESS	11
#define TYPE_SOIL_MOISTURE	12

#ifndef MAX_DEVICE_NAME
#define MAX_DEVICE_NAME 20
#endif

#define SERIAL_NUM_SIZE 8
#define SERIAL_NUM_STRING_SIZE (SERIAL_NUM_SIZE * 2) + 1
typedef struct
	{
	unsigned char serialNum[SERIAL_NUM_SIZE];
	char serialStr[SERIAL_NUM_STRING_SIZE];
	char name[MAX_DEVICE_NAME];
    int type;
    int interval;
	} Device;

/*** EndHeader */

/*** BeginHeader  */
#endif
/*** EndHeader */

