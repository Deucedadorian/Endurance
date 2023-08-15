// defines for Engineering Test version
// NOTE: these are HEX numbers
#define VERSION_MAJOR 9
#define VERSION_MINOR 2
#define VERSION_BUILD 6

///////////////////////////////////////////////////////////////////////////////
//
// Engineering Test Software
//
// P R O P R I E T A R Y
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// I M P L E M E N T A T I O N  N O T E S
//
// **********F I N A L  C H E C K  N O T E S****************
// There are a number of items that should be checked before
//   use on a turbine.  These include items useful for debug
//   or bench test such as modified setpoints, rpm sensor
//   over-ride, etc.  Search this file for the string
//   "final check" (no quotes) to find these items
// *********************************************************
//
// C O M P I L E R  N O T E S :
//
// In Dynamic C Integrated Debugging Environment, set the
//   Options:Environment Options:Editor:Block Indent to 2
//
// C O M M U N I C A T I O N S  P R O T O C O L  N O T E S:
//
// Need to change the following line in the Dynamic C RabbitBios.c file in the
// Bios folder (or Lib/BIOSLIB/memconfig.lib file in v9.52):
//
// Old: #define XMEM_RESERVE_SIZE 0x0000L // Amount of space ...
// New: #define XMEM_RESERVE_SIZE 0x4000L // Amount of space ...
//
// Old:
// seq#,mph,rpm,tailstat,amps
// "@!C%05d,%6.2f,%d,%1d,%6.2f#\r\n"
//
// New:
// seq#,MPSx100,MaxMPSx100,WATTSx100,MaxWATTSx100,RPMLSS,MaxRPMLSS,Starts,Stops,
//   Total Hours, Service Hours,Status
// "@!S%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld#\r\n"
// sysstat: UINT : bit fields:
// Convert all floats into ULONGS: ulTemp = (ULONG) (100 * fFloat) to make
// parsing easier
//
// Note that if the client (OP6810) sets the HALT bit in the communications
// packet and then communications is lost, the tower controller (BL2510)
// will stay in the HALT state until power is cycled or until communications
// are restored with the in-home client unit.
//
// H A R D W A R E  N O T E S:
//
// I / O  M A P:
//
// Inputs:
//   IN00    J11:1   PE1    INT1A  Shaft Encoder for RPMLSS
//   IN01    J11:2   PE3           Anemometer
//   IN02    J11:3   PE6           Pulse counter for RPMHSS  // 20050505 ACH
//   IN03    J11:4   PE7           Grid status input //20060628 ACH
//   AD0     J1:2    Analog Input  Generator Current {0.0 V .. 3.3V} not used...
//   AD0 removed.  Using rpm to get power 20050506 ACH
//
// Outputs:
//   OUT0    J3:1    PA0           Neutral
//   OUT1    J3:2    PA1           HOT2
//   OUT2    J3:3    PA2           MOTOR
//   OUT3    J3:4    PA3           Normal Run
//   OUT3    J3:4    PA4           Resistor Off
//   OUT3    J3:4    PA5           Resistor On
//   OUT3    J3:4    PA6           Run Capacitor
//   OUT3    J3:4    PA7           Brake Contactor Actuator
//
// On-board LEDs:
//   DS1                           Startup
//   DS2                           Startup
//   DS3                           Startup, Flash FSM state code at 1 Hz rate
//   DS4                           Startup, Flash on each good message
//
// Serial Port Connections:
//   TXE     J6 pin 3              Serial Port E TX to AeroComm DE9 pin 3 (TD)
//   RXE     J6 pin 5              Serial Port E RX to AeroComm DE9 pin 2 (RD)
//   GND     J6 pin 9              Serial Port E GND to AeroComm DE9 pin 5 (SG)
//
// Serial Interface Header J6 (male) pinout (top view):
//
//     2  4  6  8  10      ribbon cable direction
//     1  3  5  7  9                ||
//        |  |     |                ||
//   TXE -+  |     +- GND          \  /
//   RXE ----+                      \/
//
// NRG #40 Anemometer Transfer Function (see AnemometerCountsToMPS):
//   MPH = 1.711 (Hz) + 0.78 (MPH)
//   M/S = 0.765 (Hz) + 0.35 (M/S)
//   inverting gives:
//   Hz = (MPH - 0.78) / 1.711
//   Hz = (M/S - 0.35) / 0.765
//   representative limit values:
//   100 MPH => 58 Hz
//
// LSS Shaft Encoder:   (see RotorCountsToRPM)
//   2048 pulses per shaft rev => RPM = 0.029297*Frequency in Hz
//   nominal rotor speed = 170 RPMLSS = 5803 Hz
//   Max readable RPM ~ 9000*.029297 = 264 rpm
//
// HSS shaft encoder:   (see RPMHSSCountsToRPM)
//   18 pulses per shaft rev and gear ratio = 10.82 => RPM = 0.3466*Frequency in Hz
//   nominal rotor speed = 170 RPMLSS = 490.5 Hz
//   Note that HSS RPM is always expressed as LSS equivalent ( = true HSS rpm / gear ratio)
//
// Connect tail microswitch to J11:3 and install a jumper at R58 to
//   pull up all digital inputs to +3.3V via a 100K Ohm resistor. (not used)
//
// Digital Output lines require pull-up resistors since they're open collector.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Master Update List:
//
// 20040213 RSF - created windmain.c and Version 1.0.0
// 20040325 RSF - added status task to flash LEDs
// 20040401 RSF - documentation cleanup
// 20040406 RSF - test code cleanup
// 20040407 RSF - release preliminary test version 1.0.0
// 20041025 RSF - updated jumper documentation
// 20041027 RSF - fix RotorBrake() output bit selection per CH
// 20041028 RSF - change counts per second conversion routines to use float
//                arguments to allow easier integration time changes
//              - change TaskMeasureSpeeds() to do 0.5 Sec. rotor sample time
//                and 5.0 Sec. anemometer sample time per CH
//              - include input limit checking with conversion routines
// 20041029 RSF - release preliminary test version 1.1.0
// 20041115 RSF - Created windmain_120.c and Version 1.2.0
// 20041128 RSF - Revamp commo structure to match OP6810
//              - Include message parser for incoming client commands
// 20041217 RSF - Update program documentation
// 20050107 RSF - Code cleanup
// 20050421 ACH - Change RPM sampling time to 0.1 sec
// 20050426 ACH - Version 1.3.0 windmain_130.c  Comment out all tail magnet and position
//                I/O.  Change RPM to RPMLSS in preparation for adding RPMHSS (each change
//                not marked with individual comment, search for RPMLSS).
// 20050427 ACH - Added FaultMonitor task (with no content yet)
// 20050505 ACH - Added counter for RPMHSS, use MS_TIMER to get count intervals
// 20050506 ACH - Remove analog current input, now get gen power from
//                RPMHSS using GenPowerGet()
// 20050510 ACH - Version 1.4.0 windmain_140.c Many changes in FSMWindspeed
//                to match flowchart of May, 2005
//                also change definition and values of set-point constants
// 20050511 ACH - Add fault detection: overspeed and RPM sensor error
//                Put overspeed detect in TaskMeasureSpeeds for quickest response
//                Other faults will be found in TaskFaultMonitor
//                Changed rotor rpm function and variables to float.  Needed
//                decimal precision for values around 160-180 RPM.
// 20050525 ACH - Write STATE to flash memory if FAULT or HALT.  Read memory
//                on cold start and return to appropriate state.
// 20050708 ACH - Reversed definitions of ON and OFF in digOut calls v1.43
// 20050804 ACH - Added time delay for going offline at low rpm,
//                to avoid contact chatter at rpm near synch,
//                new parameter to set is kulMinTimeGenOn, v1.44
// 20051020 ACH - Make control parameters adjustable 'on the fly' by storing
//                params in arrays, then selecting the elements we want during
//                run time.  Program starts with zeroeth elements, then
//                index is changed by command from OP6810 keypad.  v1.50.
// 20051025 ACH - Removed most of code related to Tail latch and status (they
//                were already commented out).  Added test for STATE_FAULT
//                in several fault checking locations, so blocks of code
//                including Flash Memory update won't repeat after fault is
//                first detected. v1.51
// 20051118 ACH - Minor changes while debugging in SF. v1.52
// 20051128 ACH - Changed ISR_ExternalInterrupt by removing ASM code and
//                replacing with simple increment counting.  Now works up to
//                > 8kHz with 0-5V square wave input from 'output pulse' of
//                function generator.  Removed uneeded reset from ISR_Anemometer
//                v1.53
// 20051130 ACH - Change HSS rpm sampling to 1 second rate and added averaging
//                to get ~ 5s average value also. v1.54
// 20051212 ACH - Went back to assembly version of ISR_ExternalInterrupt
//                after finding out it runs much faster.  Added comments
//                explaining the use of interrupts.  Shouldn't be
//                any functional change. v1.55.
// 20060104 ACH - Changed to startup/reboot in HALT mode instead of CALM
//                so we'll know if it has rebooted.  v1.56  (didn't work)
// 20060313 ACH - Error code now written to flash memory so we'll know what error
//                was if system restarts after a fault   v1.58
// 20060314 ACH - Changed logic for going offline in light winds.  Now uses
//                integrated speed slip value plus time plus rpm setpoint v1.59
// 20060315 DJL - Added floor to speed slip value to avoid overflow.  Also added
//                reset of speed slip value for Freewheel - Genereating transition.
// 20060328 ACH - Changed use of giParameterID so the array elements are
//                accessed using giParameterID instead of giParameterID-1 to
//                save a bit of calc time.  Removed giParameterID from flash
//                structure since we weren't really using it for anything. 1.63
// 20060403 DJL - Changed code to operate with new gearbox (8.98:1).  Also changed
//                code to use 2048 LSS encoder. v2.00
// 20060403 DJL - Switched back to 1024 LSS encoder. It's safer since it won't
//                lead to overspeeding if the 2048 encoder is actually used.  v2.00
//
// 20060406 DJL - Started to add the voltage switching logic.  v3.00
// 20060417 DJL - Attempt to add the motoring logic and actual SSR switching. v3.01
// 20060418 DJL - Changed the time delays in voltage switching to use OSTimeDly
//                and a number of clock ticks instead of seconds. v3.02
// 20060425 DJL - Changed logic in CUTIN state to better handle motoring.
//                Also switched HIGHWINDS to revert to CUTIN, not FREEWHEEL
//                and rearranged logic for going to CALM from FREEWHEEL. v3.03
// 20060425 DJL/ACH - Added motoring error to detect brake drag. Now uses
//                OS_TICKS_PER statements for up- and down-switching.  v3.04
// 20060426 DJL - Changed downswitch rpm to 201.83.
// 20060427 DJL - Storing Upswitches in ulReserved[2] for now. v3.06
// 20060503 DJL - Update Falsh on START command.  Reduce RPM_Lo to 2 RPM.
//                Reduce SpeedSlipSum for going offline. v3.07
// 20060503 DJL - Added #ifdef BENCH_TEST. v3.08
// 20060503 DJL - removed ulDownSwitches.  Freed ulReserved[2].  Activated
//                ulUpSwitches.  Must use OPMAIN 118 now. v3.09
// 20060524 DJL - Added power calculations.  Increased cut-out wind speed to
//                ~24.5 m/s.  Changed kf70pct_WSCutOut to kf80pct_WSCutOut.
//                Increased anemometer error tolerance to 15%.
// 20060628 ACH - Added input of grid status (digital input 03).  Fault monitoring
//                now includes this grid status input with GridFault function.
//                When fault is detected (over or under voltage, frequency error) then turbine
//                is shut down with GRID FAULT error.  The turbine will restart
//                automatically (returns to CALM state) 30s after the fault clears. v3.20
// 20060807 DJL - Added IFDEF DYNO_TEST for one-line change to use dynomometer test with
//                higher gera ratio. Added IFDEF BENCH_TEST to gridfault function.  v3.22
// 20060831 DJL - Altered recovery wait period from grid fault to 5-minutes.
//                Changed parameters to model specific test cases for commissioning.
//                Changed MOTOR_ERR parameters to better detect error.
//                Increased maximum time in CUTIN to 2 hours.
//                Added additional motoring error check.  Now checks for reaching
//                minimum RPM in kulRPMTimeMotor and total motoring time.
//                When RPM drops below kfRPM_Lo in FREEWHEEL, now reverts back
//                to CUTIN.  This should reduce cycling brakes during variable
//                wind days and allow more time freewheeling.
//                Added variable kulGridTimeOut as wait time after grid fault.
//                Corrected power estimate equations to work with dyno.
//                Forced power estimate to use 120V during first second of
//                operation at 240V to allow rpm to stabilize and avoid
//                erroneously high power estimate.
//                Redefined parameter sets for use in commissioning tests.  Set
//                1 has a normal anemometer parameter; other sets use 0 to bypass
//                anemometer setpoints.  Set 2 has a low overspeed setpoint (125rpm
//                on dyno; 155 rpm on turbine) to cause overspeed after motoring.
//                Set 3 has a low rpm error tolerance (3rpm) which should force an
//                rpm error. Set 4 sets a low cut-out speed to test HIGHWIND state.
//                Set 5 test the anemometer error with a high (30 m/s) value that must
//                be reached if rpm reaches synchronous.
//                Reactivated update of flash memory on Halt command
//                to prevent turbine start after Halt command and power interrupt.
//                Broke BENCH_TEST into 3 other ifdef functions: HSSRPM_BYPASS,
//                NO_ANEM, and GRID_BYPASS, to make HSS rpm = LSS rpm, set
//                anemometer check values to meaningless low numbers, and to
//                force the grid fault to never occur, repectively.  Each can
//                be chosen independently for specific testing conditions.
//                Added ifdef FLASH_RESET to reset flash memory on boot. v3.30
// 20060917 DJL - Changed motor error parameters to 2 sec and 9 seconds. v3.32
// 20060920 DJL - Added variables ulTimeHighWind and kulTimeHighWind to keep
//                turbine in HIGHWINDS state for mininum time.  Currently set to
//                1/2 hour. v3.33
// 20061011 DJL - Added LSSRPMErr when LSS RPM drops more than kfMaxRPMDec
//                (currently 25 RPM) in one time step (~0.1 sec) in generating
//                state or when freewheeling faster than kf25pctRPM_Synch
//                (currently 25 rpm).  Changed back to switching to CALM from
//                FREEWHEEL if RPM is below kfRPM_Lo (3 rpm).  Changed logic
//                in STATE_CUTIN to go to motoring regardless of wind speed.
//                Reduced time to go to motor from CUT-IN (kulMinTimeCutIn) to
//                40 seconds.  Increased cut-in wind speed (kfWS_Cutin) to
//                3.8 m/s.  Changed threshold for CUT-IN to FREEWHEEL to be
//                twice kfRPM_Lo to build in hysteresis.  v3.34
// 20061012 DJL - Retracted changes made in v3.34.  Hardware solution found.
//                Increased cut-in wind speed (kfWS_Cutin) to 3.8 m/s. v3.35
// 20061012 DJL - Added DI-04 (INPUT_RESTART) to handle reset from FAULT at
//                control panel.  Requires a switch normally open that shorts
//                to digital ground.  When this circuit is closed the controller
//                is put in a HALT state.  When the circuit is closed, the
//                controller switches from HALT to CALM. v3.36
// 20061016 DJL - Added state history to track previous two states.  Added code
//                version to aerocomm send packet.  Added ability to clear max
//                values and events on remote unit. Now sends code version number
//                to remote unit along with history.  Changed gucTowerCOmmand to
//                guiTowerCommand to handle commands better from remote.
//                Must use OpMain v1.21 in remote.  v3.40
// 20061017 DJL - Upgraded timers to only count time while spinning.  v3.41
// 20061017 DJL - Made DI-03 to turn ON when turbine is unavailable.  v3.42
// 20061018 DJL - CHANGED DI-03 to turn ON when turbine is available.  Reduced
//                cut-in to 3.5 m/s.  v3.43
// 20061020 DJL - Reversed KeySwitchHalted logic.  Now DI-04 requires a normally closed
//                switch that must be opened to HALT the turbine.  v3.44
// 20061026 DJL - Converted anemometer error to a resetting fault similar to
//                the grid fault logic.  Converted STATE_GRIDFAULT to STATE_WARN
//                to reflect it handles all automatic reset faults.  Must use
//                OPMAIN v1.22.  v3.45
// 20061101 DJL - Reduced O-speed test setting to 152 RPM.  v3.46
// 20061104 DJL - Reduced O-speed test setting to 151 RPM.  Increased kulRPMTimeMotor
//                to 12 seconds.  v3.47
// 20061127 DJL - Added kfRPMOnlineMin to drop offline instantly when below this value
//                to prevent a motoring problem with the brakes on.  Increased
//                kulMaxTimeMotor to 30 seconds.  Added parameter kulMotorTimeOut which
//                sets the minimum time between motor events at 10 minutes.  Increased
//                time delay on up- and down-switch from 16 to 31 ms.  v3.48
// 20061128 DJL - Fixed bug in reading state history from flash.  v3.49
// 20061130 DJL - Fixed bug in kfRPMOnlineMin check.  Now uses RotorRPMGet for
//                comparison.  Reduced kfRPMOnlineMin to 150 rpm as well.  v3.50
// 20061201 DJL - Shelved kfRPMOnlineMin and kulMotorTimeOut.  v3.51
// 20061201 DJL - Increased kulRPMTimeMotor to 5 seconds.  v3.52
// 20061201 DJL - Repaired bug that could lead to auto restart from HALT by initializing
//                gbRemoteHalt to TRUE if HALT is stored in flash.  Also improved history
//                initialization.  Fixed integrator for downswitch.  Increased slip sums
//                for downswitch and offline.  v3.53
// 20061207 DJL - Reactivated kfRPMOnlineMin and kulMotorTimeOut.  Changed parameters
//                in cut-out and anemometer test to require normal wind speed values
//                for the turbine to operate.  Set kulMotorTimeOut to 5 minutes.
//                Reduced slip sums for downswitch and offline to -15 and -30.  v3.54
// 20061208 DJL - Decreased kfHiSpeedSlipSetpoint to -15.  Added resistor options for
//                motoring and going online.  Cleaned up OS_TICKS.  v3.55
// 20061212 DJL - Decreased kfHiSpeedSlipSetpoint to -10.  Added parameter kfRPM_HiNeut
//                to define downswitch RPM separate from slip sum threshold.  Made
//                kfRPM_Synch a constant variable instead of an array (we were not
//                using the array).  Changed downswitch parameters to switch at ~500W,
//                with a neutral point of ~1355W.  v3.56
// 20061216 DJL - Eliminated resistor options for start-up and motoring.  Added
//                run-cap option for start-up.  v3.57
// 20061228 DJL - Added fRotorRPM_prev in TaskMeasureSpeeds to keep track of rotor
//                rpm from previous time step.  This is used in a new overspeed logic
//                that checks if the current and previous rpm values exceed overspeed
//                and that the current rpm is >= the previous.  This is an attempt to
//                reduce possible nuisance overspeeds.  Moved all switching events
//                (motor, online, up and down) after history update but before state
//                update to make it more evident if a fault occurs during a switch.  v3.58
// 20070102 DJL - Improved start-up parsing of states read from flash by adding
//                warning reset and clearing any residual error codes that might be
//                in the code when the state is not FAULT or WARN.  Also changed the
//                timer for the run cap to 6 ticks (~100ms).  v3.59
// 20070102 DJL - Updates max LSS rpm immediately on overspeed error.  Immediately
//                updates flash when warning clears to prevent waking up again in
//                warning state.  Also changed the timer for the run cap to 16 ticks
//                (~250ms)v3.60
// 20070110 DJL - Reduced the timer for the run cap to 6 ticks (~100ms)  v3.61
// 20070110 DJL - Added wait time on power up with kulCnctWaitTime (300s)  v3.62
// 20070115 DJL - Reduced wait time on power up to 0s.  v3.63
// 20070115 DJL - Reduced o-speed test to 150.2 rpm.  Increased motoring to 45s.  v3.64
// 20070118 DJL - Forced error code to 0 for all non-error state switches.  v3.65
// 20070127 DJL - Added scheme to hide and prevent comissioning test options
//                unless DI-05 (INPUT_TESTSWITCH) is opened.  Must use
//                OPMAIN 1.30.  v3.70
// 20070130 DJL - Moved commissioning test input to DI-15 to use jumper.  v3.71
// 20070130 DJL - Increased motor time-out to 15 minutes and connection wait
//                time-out to 5 minutes.  Added resistor options for going
//                   online (as per 3.55).  v3.72
// 20070203 DJL - Added virtual watchdogs to TaskMeasureSpeeds and TaskFaultMonitor.
//                Named watchdog timers giWDT_main, giWDT_measure, and giWDT_fault,
//                and set them to 2.31s, 0.25s and 1.0625s respectively.  Changed
//                WatchdogHit to accept WDT ID as input argument.  v3.73
// 20070205 DJL - Increased watchdog times to prevent nuisances.  v3.74
// 20070315 DJL - Increased RPM error window to 45 rpm.  v3.76
// 20070320 DJL - Added motoring time-out check in Cut-in (it was missing).
//                Added initialization of ulTimeMotorStart to prevent
//                unwanted wait periods after boot-up.  Allowed bypass of
//                connection time-out on boot-up during commissioning tests
//                (DI-15 jumper removed).  v3.77
// 20070330 DJL - Eliminated write to flash on warnings.  Reduced grid warning
//                time out to 5 minutes.  v3.78
// 20070414 DJL - Restrict motoring time-out to periods when wind speed is below
//                120% of cut-in.  v3.79
// 20070810 DJL - Increased motoring time-out limiting to 150% of cut-in.  v3.80
// 20071021 DJL - Decreased min generating time to 10s.  v3.81
// 20071106 DJL - Decreased min generating time to 1s.  Reduced kfSpeedSlipSetpoint
//                to -7.0.  v3.82
// 20071106 DJL - Increased time to calculate 120V power to 3s.  Set gfSpeedSlipSum
//                ceiling to zero (no counting up).  Increased min generating time
//                to 4s.  Increased kfSpeedSlipSetpoint to -8.0.  v3.83
// 20071108 DJL - Switch to GEN-LO below synchronous.  v3.84
// 20071109 DJL - Reverted to v3.83.  Increased kfHiSpeedSlipSetpoint to -12.0.
//                Set gfHiSpeedSlipSum ceiling to zero (no counting up) v3.85djl
// 20071123 DAD - Added STATE_FREEWHEEL as an ignored state for GridFault
//                checking.  v3.85dad
// 20071127 DJL - Limited grid fault check to only gen-lo and gen-hi states.
//                Reset ceiling for gfHiSpeedSlipSum to -kfHiSpeedSlipSetpoint.
//                Added logic to sum by the square of the difference for
//                gfHiSpeedSlipSum.  v3.86
// 20071130 DJL - Changed logic to sum by the cube of the difference for
//                gfHiSpeedSlipSum.  v3.87
// 20071130 DJL - Reduced RESERVED_ULONGS to 2 from 3 for memory file size
//                reasons. Removed immediate flash write after recovery from
//                grid fault (grid faults are not written to flash anyway).  v3.88
// 20080123 DJL - Increased kulMinTimeCutIn to 5 minutes to delay motoring (if the
//                rotor does not spin).  v3.89
// 20080211 DJL - Increased kfWS_Cutin to 4.0m/s to reduce energy consumption.  v3.90
// 20080220 DJL - Changed motoring errors to warnings, with 3 hour time out.  Added
//                time stamp info to communication string.  Requires remote
//                firmware v1.40.  v3.91
// 20080221 DJL - Eliminated writes to flash on start and clearing of all warnings.
//                Eliminated waking up in warning state.  v 3.92
// 20080221 DJL - Decreased kulMinTimeCutIn to 1 minutes to start motoring (if the
//                rotor does not spin).  v3.93
// 20090204 JRM - Decreased the maximum motoring RPM to 75 to reduce the duration
//						that the start capacitor is in the circuit. v8.05
// 20090204 JRM - Added the run capacitor in parallel with the start cap during
//						motoring to reduce current in start cap by approx 12%. v8.06
// 20090204 DJL - Reduced kulMaxTimeMotor to 15sec and made it kick to FREEWHEEL
//                instead of a motor error.  Reduced kulMotorTimeOut from 15min
//                to 10min and changed logic to force the time out in all
//                situations (no override for higher wind speeds).  v8.08
// 20090204 DJL - Changed kfRPM_OverSpeed parameter set 2 (overspeed test) to 75.2
//                to reflect new maximum motor speed changed in v8.05.  Also
//                changed kfRPM_OverSpeed and kf75pctRPM_Synch to 60.2 and 60,
//                respectively for DYNO_TEST to be consistent with max motor speed
//                changes already made.  v8.09-djl
// 20090211 JRM - Field testing has shown that 75rpm could be insufficient torque
//				  in new and/or cold applicaitons at certain windspeeds.  Moving
//				  the new max motoring RPM to 100 from 75.  I skipped v8.10 as
//				  it was used as diagnostic code that wasn't shipped.  v8.11
// 20090212 DJL - Added bypass of motoring time out during commissioning tests. v8.12
// 20090212 DJL - Same as v8.12, just different logic test. v8.13
// 20090303 DJL - Changed resistor settings in UpSwitch and DownSwitch routines.
//            Increased kulMinTime240V to 15 seconds. v8.15
// 20090303 DJL - Increased kulMinTime240V to 15 seconds (for real this time). v8.16
// 20090320 DJL - Changed wind speed in comm to 1-min avg. v8.18
// 20090401 DJL - Changed Power equations to use LSS rpm.  Added 1-min. power average
//            variable gfWattsPwrAvg.  Working from v8.30. v8.32
// 20090428 DJL - Same as 8.18, but DYNO_TEST flag is on and gbTesting is NOT set to
//            true. v8.19-DYNO
// 20090708 BAC - Merged in Gorman's final firmware changes (what they called v9.20)
//            These changes include password protection, datalogging, a new flash task
// 20090710 BAC - Issue #15 - Removed kfRPMOnlineMin to prevent the turbine from
//            going on/offline too quickly - can be dangerous.
// 20090717 BAC - Issues #33 & #57 - Removed watchdog reprogramming on firmware update.
//            Now programs once on startup, and sets timeout and overspeed (NEW) config
// 20090717 BAC - Issue #23 - Replaced appropriate calls to CommissionTest()
//            with new funcion TestActive(), which checks is a test is actually active.
// 20090717 BAC - Issue #21 - Added logic to bypass utility timeout after HALT and RUN
// 20090720 BAC - Issues #33 & #57 - All (appropriate) watchdog params are now
//            explicitly set on rabbit startup programmed.
// 20090721 BAC - Merged in code from 8.19 for production 343 firmware
// 20090723 BAC - Issue #10 - Improved windspeed datalogging to log either one, ten or
//             sixty minute averages, with recording intervals starting at the top of the
//             minute/hour. Also removed power logging (will be improved and added later)
// 20090724 BAC - Issue #8 - Implemented factory reset
// 20090724 BAC - Issue #6 - Displayed power is now calculated as the 1s (true) average
//             using 100ms LSS samples
// 20090820 BAC - Issue #30 - Added feature to set turbine model at run-time. Includes
//             some fairly significant refactoring of existing logic, specifically for
//             the definition of RPM limits/thresholds.
// 20090827 BAC - Issue #33 - Removed watchdog commands which repeatedly set constant
//             values. Watchdog now only sends values which depend on model type
//             (overspeeds).
// 20090831 BAC - Fixed following code review with DJL - Includes: addition of 
//             2s delay in Calm; power calculations now use model-independant 
//             constants and gearbox ratio.
// 20090901 BAC - Moved the initialization of gbSemaphoreFlashUpdate flags to
//             ReadFlashData to resolve a bug in which the flags are initialized
//             after some of them are set.
// 20090925 BAC - Changed default logging interval to 10 minutes.
// 20091005 BAC - Issue #61 - State information is always loaded from flash structure on start-up.
//             Refactored code to read/write this info from the flash struct.
//             (Re)Added writes to flash when entering Fault state.
// 20100803 BAC - Integrated Gorman's changes for v1.4.6 - Addition of HSS to ERI 
//             serial string and calculation of new Max HSS value for said string
// 20100804 BAC - Integrated Gorman's fixes for v1.4.6 (Gorman Rev 2)
// 20100804 BAC - Tidied up changes for HSS Maximum detection
// 20100820 BAC - Model info retains previous value on a firmware upgrade, 
//             defaults to S-343 on clean install.


///////////////////////////////////////////////////////////////////////////////
/*                                                                            /
 * Pick the predefined TCP/IP configuration for this sample.  See             /
 * LIB\TCPIP\TCP_CONFIG.LIB for instructions on how to set the                /
 * configuration.                                                             /
                                                                             */
#define TCPCONFIG 1
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//For implementing the download manager                                      //
#define	UDP_SOCKETS 1                                                        //
#define  MAX_UDP_SOCKET_BUFFERS 1                                            //
                                                                             //
// define this string to inlcude the RAM loader in FLASH,                    //
// RAM loader must be unencrypted.                                           //
// use the full path to the file and use forward slashes.                    //
#define UDPDL_LOADER "c:/dcrabbit_9.62/Loaders/pdl-generic-D.bin"            //
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//For testing only:                                                          //
#define	STDIO_DEBUG_SERIAL	SADR                                             //
#define	STDIO_DEBUG_BAUD		57600                                        //
                                                                             //
// Add this line to add carriage returns ('\r') to each newline              //
// char ('\n') when sending printf output to a serial port.                  //
                                                                             //
#define	STDIO_DEBUG_ADDCR                                                    //
///////////////////////////////////////////////////////////////////////////////

typedef unsigned long ULONG;
typedef unsigned int  UINT;
typedef unsigned char UCHAR;
typedef unsigned char BOOL;


// Flash Memory interface structure ...
// All of the floats will be scaled by 100 to get 2 fraction digits
#define RESERVED_ULONGS 2 /* reserve this many ULONGS in Flash struct        */

struct FlashStruct
{
  ULONG ulPowerMaxX100; // Maximum Power output (/= 100.0 to convert to float)
  ULONG ulMPSMaxX100;   // Maximum MPS (/= 100.0 to convert to float)
  ULONG ulRPMLSSMax;    // Maximum RPMLSS
  ULONG ulMotorStarts;  // Number of motor start ups
  ULONG ulUpSwitches;   // Number of upswitches (120v - 240V)
  ULONG ulBrakeStops;   // Number of brake stops of turbine
  ULONG ulTotalHours;   // Total number of hours of operation
  ULONG ulServiceHours; // Number of hours into service interval
  ULONG ulReserved[RESERVED_ULONGS]; // reserve this many ULONG locations
  // ulReserved[0] is number of flash writes
  // ulReserved[1] is 1000 * gucStateHistory[1]
  //                 + 100 * gucStateHistory[0]
  //                  + 10 * gucStateWindSpeed
  //                       + gucFaultCode to save these values

  char	Saved[6]; //Used to determine if the structure has been written
  					    //To Flash.

};

typedef struct FlashStruct FlashStruct;

#define  SAVED_STRING_LENGTH  (6)
const char gcSaved[]="saved";
const char gcNotSaved[]="xxxxx";

const FlashStruct gFlashDefaults =
{0,0,0,0,0,0,0,0,{0,0},"00000"};


///////////////////////////////////////////////////////////////////////////////
//
// System Configuration Settings
// NOTE: Check Carefully!
//
///////////////////////////////////////////////////////////////////////////////


// Hardware configuration settings ...
// NOTE: Check these settings CAREFULLY before software version releases!


// Characteristics of turbine components

// Synchronous RPM of generator
#define RPM_HSS_SYNCHRONOUS   (1800)
// Sensor encoding rates
#define HSS_TICKS_PER_REV     (18)
#define LSS_TICKS_PER_REV     (1024)


#define SERVICE_INTERVAL 10000 /* service interval in hours                  */

// Transition wind speeds, RPMLSSs and times for control FSM ...
// ACH 20050510 removed many variables, added and redefined others
// Wind speeds (WS) in m/s.  Shaft speeds in LSS RPM.

#define NUMBER_SSR_OUTS 7  // 20060417 DJL added this for dimensioning number of dig outs for SSR's


// Parameter Sets
// Constants defining multiple parameter sets to facilitate dynamically
// configuring the controller to use different operation parameters
// (The current application of these parameter sets is commisioning tests)

// Number of parameter sets
#define NUMBER_PARAM_SETS (5)

// Definition of different parameter sets
typedef enum
{
	eNormal           = 0,
	eOverSpeedTest    = 1,
   eRpmErrorTest     = 2,
   eCutOutTest       = 3,
   eAnemometerTest   = 4,
} ParameterSet;


    // Use lines below to control the RESISTOR during motoring and online sequences
const int OS_TICKS_GENLO_RUNCAP = 6; /* Set number of ticks run-cap will be delayed during online transition; 64 ticks per sec; 0.1sec */
#define GENLO_RESISTOR  /* DL - uncomment to use resistor during online transition  */
const int OS_TICKS_GENLO_RESISTOR = 0; /* Set number of ticks resistor will be on during online transtion; 64 ticks per sec */
                                       /* Note that the resistor ticks is added to the runcap ticks for total resistor time */

    // use lines below only for bench or dyno testing - final check */
//#define HSSRPM_BYPASS    /* DL - uncomment to force HSS rpm = LSS rpm; for bench testing only */
//#define NO_ANEM          /* DL - uncomment for testing without anemometer (use for bench and dyno tests) */
//#define GRID_BYPASS      /* DL - uncomment to bypass grid fault monitoring */

//final check - comment out the next line for normal operation
//#define FLASH_RESET      /* DL - uncomment to reset flash memory on boot up - do not use for normal operation. */

// final check.  Make sure correct values used for all setpoints
#ifdef NO_ANEM
const static float kfWS_AnemCheck[NUMBER_PARAM_SETS]  =
                       {0.0, 0.0, 0.0, 0.0, 30.0}; // anemometer error override values
const static float kfWS_Cutin[NUMBER_PARAM_SETS] =
                       {0.0, 0.0, 0.0, 0.0, 0.0}; // override minimum WS
#else
const static float kfWS_AnemCheck[NUMBER_PARAM_SETS]  =   // anemometer error if HSS RPM>Synch and WSAvg < this value
                       {1.0, 0.0, 0.0, 1.0, 30.0}; // anemometer error override values; should be < 1 m/s
const static float kfWS_Cutin[NUMBER_PARAM_SETS] =
                       {4.0, 0.0, 0.0, 4.0, 4.0}; // calm->cutin when WSAvg < this value.  highwinds->calm when WS < this value
#endif

    // these controller parameters are not arrays, values do not change
    // with keypad entry
const static float kfRPM_Lo = 3.0;               // switch from freewheel -> calm if HSS RPM below this value, and
                                                 // Motoring error if RPM is not > this value after [kulRPMTimeMotor] sec of motoring

// RPM above which a brake fault is detected (when additional conditions are met)
const static float kfRPM_BrakeCheck = 50.0;
                                                 
// the next three parameters control switching from GENERATING -> FREEWHEEL in light winds
const static ULONG kulMinTimeCutIn = 60;           // must be in Cut-in this long before can switch to freewheel, sec
const static ULONG kulMaxTimeCutIn = 7200;         // must leave cut-in state after this long, sec
const static ULONG kulTimeHighWind = 1800;         // must stay in HIGHWIND state this long, sec
const static ULONG kulMinTimeGenOn = 4;            // must be in Generating state this long before can switch offline, sec
const static ULONG kulMinTime240V = 15;            // must be in 240V Generating state this long before can switch down to 120V, sec
const static ULONG kulMinTime240VWithBrakes = 1;   // this parameter is used in lieu of kulMinTime240V when the brakes have just been applied, sec
const static ULONG kul240VBrakeResponseDelay = 4;  // Delay after brakes applied during which kulMinTime240VWithBrakes is used versus kulMinTime240V, sec
const static ULONG kulRPMTimeMotor = 5;            // fault if we motor longer than this time without reaching minimum RPM, sec
const static ULONG kulMaxTimeMotor = 15;           // return to FREEEWHEEL after we motor longer than this time, sec
const static ULONG kulMotorTimeOut = 600;          // minimum time between motoring events, sec
const static ULONG kulGridTimeOut = 300;           // wait before restart on grid fault, sec
const static ULONG kulAnemTimeOut = 60;            // wait before restart on anemometer fault, sec
const static ULONG kulMotErrTimeOut = 10800;       // wait before restart on motoring fault, sec
const static ULONG kulCnctWaitTime = 300;          // wait before starting turbine on power up, sec
const static ULONG kulMinTimeCalm = 2;             // must be in Calm this long before can switch to cut-in, sec
const static ULONG kulFaultBrakeResponseDelay = 20;// Delay after brakes applied during which the brake failure fault is inactive, sec

// Number of seconds to wait after power up before setting the external
// watchdog timeout.
const static ULONG kulWDPwrUpDelay = 5;

// Number of seconds to wait after ERI disabled the watchdog before resetting it
const static ULONG kulWDERIUpDelay = 7200;

// these parameters are selected by keypad entry, see NUMBER_PARAM_SETS above
// Program uses first column (zeroeth elements) when initialized
const static float kfSpeedSlipSetpoint = -8.0; // SpeedSlipSum must be less than this setpoint to switch offline
                                                 // Note floor is set at -1.0E4, so setpoint can't be below that
const static float kfHiSpeedSlipSetpoint = -12.0; // HiSpeedSlipSum must be less than this setpoint to switch down to 120V
                                                 // Note floor is set at -1.0E4, so setpoint can't be below that


///////////////////////////////////////////////////////////////////////////////
// Relative RPM parameters
// These constants, given as a ratio of the synchronous RPM (which is the same
// ratio for both LSS and HSS RPM), define RPM setpoints at which certain
// state-change events occur
///////////////////////////////////////////////////////////////////////////////

// RPM below which a sufficient slip-sum can bring turbine offline
#define RPM_RATIO_OFFLINE                 (0.99781)
// RPM below which a sufficient slip-sum can trigger downswitch.
// Corresponds to approximately 500W power production
#define RPM_RATIO_DOWNSWITCH              (1.00462)
// RPM above which an upswitch is triggerred
#define RPM_RATIO_UPSWITCH                (1.03055)
// RPM threshold for slip-sum accumulation in GenHi
// Corresponds to approximately 1355W power production
#define RPM_RATIO_GENHI_SLIP_SUM_THRESH   (1.009)
// Maximum RPM at which motoring can start
#define RPM_RATIO_MOTOR_START_MAX         (0.25)
// Target RPM to motor to, above which motoring ceases.
#define RPM_RATIO_MOTOR_STOP              (0.5)
// RPM above which an overspeed is triggerred
#define RPM_RATIO_OVERSPEED               (1.10)
// Overspeed RPM for an overspeed test
#define RPM_RATIO_OVERSPEED_TEST          (0.501)


///////////////////////////////////////////////////////////////////////////////
// Model specific parameters
// These are the parameters which differ between turbine models
///////////////////////////////////////////////////////////////////////////////

//
// Typedefs
//

// Model specific parameters
typedef struct
{
   // The gear ratio (between HSS and LSS)
   float fGearRatio;
} ModelParamStruct;

// Enumerator of different model types
typedef enum
{
   // S-250
	eS250 = 0,

   // S-343
	eS343 = 1
} ModelEnum;

// Enumerator of different generator states
typedef enum
{
   // Disconnected
	eDisconnected = 0,

   // Connected to 120v
	eConnected120V = 1,
   
   // Connected to 240v
	eConnected240V = 2,
   
   // Connected for motoring
	eConnectedMotor = 3   
   
} GenStateEnum;

 // Global generator state
GenStateEnum gGenState;

//
// Constants
//

// Gearbox Ratios
#define S250_GEARBOX_RATIO (8.98)
#define S343_GEARBOX_RATIO (10.82)

//
// Declarations of parameter sets for individual models
//

// Parameters for S250 Turbines
const ModelParamStruct kS250Params =
{
   S250_GEARBOX_RATIO,
};

// Parameters for S343 Turbines
const ModelParamStruct kS343Params =
{
   S343_GEARBOX_RATIO,
};

//
// Global variables to hold the current model
//
ModelParamStruct gModelParams;



const static float kf80pct_WSCutout[NUMBER_PARAM_SETS] =
                       {19.5, 19.5, 19.5, 5.0, 19.5};    // 80% of WS_Cutout.  Cutout->Freewheel when WSAvg < this value
const static float kf90pct_WSCutout[NUMBER_PARAM_SETS] =
                       {22.0, 22.0, 22.0, 6.0, 22.0};    // Switch to cutout when WSAvg > this value
const static float kf110pct_WSCutout[NUMBER_PARAM_SETS] =
                       {27.0, 27.0, 27.0, 7.0, 27.0};   // Switch to cutout when WS > this value
const static float kfRPM_ErrorTolerance[NUMBER_PARAM_SETS] =
                       {45.0, 45.0, 3.0, 45.0, 45.0};  // should be ~15% of RPM_Synch = 30 rpm

// Generator output voltage ...
//const static float gkfGeneratorVoltage = 220.0;      20050506 ACH remove

// Limits for Flash File System read parameter checking ...
const static float gkfPowerMax = 20000.0; // 20 kW upper limit
const static float gkfMPSMax = 100.0;     // 100 m/s upper limit
const static float gkfRPMLSSMax = 400.0;  // 400 RPMLSS upper limit

// include the following define for debugging only ...
// Comment out for normal operation ...
// final check.  Are all defines set for normal operation?
//#define DEBUG_PRINT      /* CH uncommented do serial output of diagnostics */

// Include the following to use stdin keys to adjust measured parameters ...
// Comment out for normal operation ...
//#define TESTING          /* include to allow stdio keypad commands         */

//#define	TEST_PRINT	//define for various printf to stdio

// Include the following to use testing hardware configuration ...
// Comment out for normal operation ...
//#define TEST_HARDWARE    /* include to allow bench testing of system       */


	#ifdef FLASH_RESET
   	#define TEST_FOUND
	#endif


	#ifdef HSSRPM_BYPASS
   	#define TEST_FOUND
	#endif

	#ifdef NO_ANEM
   	#define TEST_FOUND
	#endif

	#ifdef GRID_BYPASS
   	#define TEST_FOUND
	#endif


   #ifdef DEBUG_PRINT
   	#define TEST_FOUND
   #endif

   #ifdef TEST_PRINT
   	#define TEST_FOUND
   #endif

	#ifdef TEST_HARDWARE
   	#define TEST_FOUND
	#endif

	#ifdef TESTING
   	#define TEST_FOUND
	#endif

// Include the following define for debugging only ...
// Comment out for normal operation ...
// Use in conjunction with DEBUG_PRINT (above).  If DEBUG_PRINT is defined and
// DIAGNOSTIC_RS232 is not defined, output will go to stdio.
//#define DIAGNOSTIC_RS232       /* CH uncommented will send diagnostics to serial port     */

// miscellaneous constants ...
#define TRUE                 1 /* for Boolean operations                     */
#define FALSE                0 /* for Boolean operations                     */
#define ON                   1 /* for control operations                     */
#define OFF                  0 /* for control operations                     */

// Serial interface definitions ...
// Selects serial port:
//   Port A = CMOS level programming / diagnostic port [for test only]
//   Port E = RS232 level serial interface [normal operation]
// Comment out for normal operation ...
//#define SERIAL_PORTA           /* use the programming port for RF commo    */
#ifdef SERIAL_PORTA

#define SerialGetC    serAgetc /* build serNget function                     */
#define SerialOpen    serAopen /* build serNopen function                    */
#define SerialPuts    serAputs /* build serNputs function                    */
#define SerialRdFlush serArdFlush /* build serNrdFlush                       */
#define SerialWrFlush serAwrFlush /* build serNwrFlush                       */
// serial interface buffers ...
#define AINBUFSIZE        1023 /* serial input interrupt buffer size         */
#define AOUTBUFSIZE       2047 /* serial output interrupt buffer size        */

#else // #ifdef SERIAL_PORTA

#define SerialGetC    serEgetc /* build serNget function                     */
#define SerialOpen    serEopen /* build serNopen function                    */
#define SerialPuts    serEputs /* build serNputs function                    */
#define SerialRdFlush serErdFlush /* build serNrdFlush                       */
#define SerialWrFlush serEwrFlush /* build serNwrFlush                       */
// serial interface buffers ...
#define EINBUFSIZE        1023 /* serial input interrupt buffer size         */
#define EOUTBUFSIZE       2047 /* serial output interrupt buffer size        */
#endif // #ifdef SERIAL_PORTA

#define SERIAL_BAUD      57600 /* use 57600 baud, 8N1 for AeroComm serial    */
#define CHAR_CR           '\r' /* to delimit incoming AeroComm messages      */
#define CHAR_LF           '\n' /* to delimit incoming AeroComm messages      */
#define CHAR_START0        '@' /* first character of message start sequence  */
#define CHAR_START1        '!' /* second character of message start sequence */

//Using serial port F for connection to the external watchdog board.
#define FINBUFSIZE 	127
#define FOUTBUFSIZE  127




// Digital Output Port Definitions ...
#define OUTPUT_NEU          0 /* Connect to SSRN                             */
#define OUTPUT_HOT2         1 /* Connect to SSRL2                            */
#define OUTPUT_MOTOR        2 /* Connect to Motor (R9)                       */
#define OUTPUT_WATCHDOG     3 /* Connect to Pulse                            */
#define OUTPUT_RESISTOFF    4 /* Connect to SSR-L1                           */
#define OUTPUT_RESISTON     5 /* Connect to Resistor                         */
#define OUTPUT_RUNCAP       6 /* Connect to Run Cap                          */
#define OUTPUT_BRAKE        7 /* Connect to Brake relay, 1 = released        */


// Digital Input Port Definitions ...
#define INPUT_ROTORSPEED     0 /* rotor speed tachometer, nominal 200 RPM    */
#define INPUT_WINDSPEED      1 /* anemometer tachometer                      */
// DI-02 is HSS sensor
#define INPUT_GRIDSTATUS     3 /* Grid status monitors, 0 = okay, 1 = fault  */
#define INPUT_RESTART        4 /* Reset button, 0 = RUN, 1 = HALT            */
#define INPUT_TESTSWITCH    15 /* Test jumper, 0 = Normal Op, 1 = Test Op    */
// Analog Input Port Definitions ...
//#define INPUT_CURRENT          /* output of generator in Amps 20050506 ACH */

// #defines for function return values ...
#define RET_OK            0x00 /* return value is OK                         */

// uC-OSII RTK configuration defines ...
#define OS_MAX_EVENTS        22 /* max # of semaphores, queues, mailboxes    */
#define OS_MAX_TASKS         12 /* max # of tasks that system can create     */  // 20050427 ACH add 1
#define OS_TASK_CREATE_EN     0 /* disable normal task creation              */
#define OS_TASK_CREATE_EXT_EN 1 /* enable extended task creation             */
#define OS_TIME_DLY_HMSM_EN   1 /* enable OSTimeDlyHMSM                      */
#define OS_SEM_EN             1 /* enable semaphore handling                 */
#define OS_SEM_ACCEPT_EN      1 /* enable semaphore accept handling          */
#define STACK_CNT_512         3 /* stat task + prog stack +flash write       */  // 20050427 ACH add 1
#define STACK_CNT_2K          1 /* application tasks */
#define STACK_CNT_1K		  9 /* 2K stack for tcp/ip socket                */
#define OS_TICKS_PER_SEC     64 /* default is 64 ticks per second // 20050422 ACH           */

// the following constants are based upon the uC-OSII tick frequency ...
const int OS_TICKS_PER_16th_SEC  = OS_TICKS_PER_SEC / 16;  //= 4 ticks
const int OS_TICKS_PER_TENTH_SEC = OS_TICKS_PER_SEC / 10;  //= 6 ticks
const int OS_TICKS_PER_31_mSEC   = OS_TICKS_PER_SEC / 32;  //= 2 ticks
const int OS_TICKS_PER_8th_SEC   = OS_TICKS_PER_SEC / 8;   //= 8 ticks
const int OS_TICKS_PER_4th_SEC   = OS_TICKS_PER_SEC / 4;   //=16 ticks
const int OS_TICKS_PER_HALF_SEC  = OS_TICKS_PER_SEC / 2;   //=32 ticks

#define TASK_STK_SIZE      1024 /* size of each task's stack (# of bytes)    */

#define TASK_ID_START         0 /* ID of task to start up all other tasks    */
#define TASK_ID_AEROCOMM      1 /* process incoming AeroComm serial messages */
#define TASK_ID_MEASURE       2 /* measure rotor and wind speeds             */
#define TASK_ID_FAULTMONITOR  3 /* Check for sensor or system faults         */
#define TASK_ID_STATUS        4 /* Flash DS2 and DS3 LEDs to indicate status */
#define TASK_ID_MAINTHREAD    5 /* main processing loop                      */
#define TASK_ID_TCPIP			6 /* TCP/IP processing                         */
#define TASK_ID_TIMERS        7 /* Tasks that need to be timed               */
#define TASK_ID_FLASH			8 /* Task for writing to Flash memory	        */

#define TASK_PRIO_START      10 /* startup task priority (highest priority)  */
#define TASK_PRIO_AEROCOMM   11 /* process incoming AeroComm serial messages */
#define TASK_PRIO_MEASURE    12 /* measure rotor and wind speed task priority*/
#define TASK_PRIO_FAULT      13 /* Fault monitoring task priority */
#define TASK_PRIO_STATUS     14 /* Flash DS2 and DS3 LEDs to indicate status */
#define TASK_PRIO_TCPIP      15 /* TCP/IP task                               */
#define TASK_PRIO_TIMERS     16 /* TCP/IP processing                         */
#define TASK_PRIO_MAINTHREAD 17 /* normal processing loop priority           */
#define TASK_PRIO_FLASH	     18 /* Writing to Flash (lowest priority)        */

#define LED0	0
#define LED1	1
#define LED2	2
#define LED3	3

//
// for State Machines ...

// Command bit structure to Tower Controller ...
// Used as bit masks for guiTowerCommand
enum{
CMD_NULL			=   0,
CMD_RUN            	=   1,
CMD_HALT           	=   2,
CMD_CLEARSVC       	=   3,
CMD_CLEARMAX       	=   4,
CMD_CLEAREVNT      	=   5,
CMD_TESTON			=   6,
CMD_TESTOFF			=   7,
CMD_SetDate			=   8,
CMD_SetTime			=   9,


CMD_ReqIPinfo     	= 51,
CMD_ReqDigIO		= 52,
CMD_CancelDigIO	  	= 53,
CMD_RequestPassKey	= 54,

CMD_SetIPAdd		= 61,
CMD_SetNetmask	  	= 62,
CMD_SetNameServer 	= 63,
CMD_SetGateway	  	= 64,
CMD_SetIPPort 	  	= 65,
CMD_ApplyIPSettings	= 66,
CMD_Motor			= 67,
CMD_ApplyBrake		= 68,
CMD_StackReport		= 69,
CMD_RequestSiteInfo	= 71,
CMD_SetSiteInfo		= 72,
CMD_RequestFlashInfo= 73,
CMD_QueryTestMode	= 74,
CMD_RequestRecInfo  = 75,
CMD_RequestMainRec  = 76,
CMD_CancelRecords	= 77,
CMD_Hello		    = 78,
CMD_SetRecInterval  = 79,
CMD_RequestDate		= 81,
CMD_RequestTime		= 82,
CMD_RequestTriggers = 83,
CMD_SetTriggers		= 84,
CMD_ReqRecInterval  = 85,
CMD_Password		= 86,
CMD_NewPassword		= 87,
CMD_SetNewPassword	= 88,
CMD_FwUpgrade		= 89,

CMD_ParamSet1      	= 10,
CMD_ParamSet2      	= 20,
CMD_ParamSet3      	= 30,
CMD_ParamSet4      	= 40,
CMD_ParamSet5      	= 50
};

enum{//Event codes for recorded events)
EV_PowerDown		=	0,
EV_PowerUp		  	=	1,
EV_RecordsInit		=	2,
EV_ERIconnect		=	3,
EV_ERIterminated	=	4,

EV_HaltState		=	5,
EV_CalmState		=	6,
EV_CutinState	  	=	7,
EV_FreeWheelState	=	8,
EV_MotorState       =	9,
EV_GenLowState      = 	10,
EV_GenHighState     =	11,
EV_HighWindState    =	12,
EV_FaultState       =	13,  //13,14,15
EV_WarningState     =	16,  //16,17,18,19

EV_Trigger		   =  25, //Diagnostic trigger occured
EV_TriggerERI	   =	26, //Diagnostic trigger (via ERI)
EV_TriggerCleared =	27, //Diagnostic trigger cleared (via ERI)
EV_ExtWDSetShort  =  28, //Programing external watch dog to standard delay
EV_ExtWDSetLong   =  29, //ERI is disabling external watchdog


//20 through 108 are for codes that represent states
//and the logical paths that are followed through the
//state machine.  To calculate the code number use the
//following Code# = EV_StateWithPath + 10*State + ucStatePath
//This allows for a maximum of 10 paths for each state
EV_StateWithPath	= 	20,

EV_Halt				=	120, //
EV_Run				=	121, //
EV_ClrService  	    =   122, //
EV_ClrMax 		    =	123, //
EV_ClrEvents    	=   124, //
EV_OldTime       	=	125, //
EV_NewTime       	=	126, //
EV_OldDate       	=	127, //
EV_NewDate       	=	128, //
EV_IPChange      	=	129, //
EV_TestModes		=	130  // 130 to 134 for test modes Normal run to Anemom test

};

// FSM states
#define STATE_HALT      (0)
#define STATE_CALM      (1)
#define STATE_CUTIN     (2)
#define STATE_FREEWHEEL (3)
#define STATE_MOTOR     (4)
#define STATE_GENLO     (5)
#define STATE_GENHI     (6)
#define STATE_HIGHWINDS (7)
#define STATE_FAULT     (8)
#define STATE_WARN      (9)
                          
// Define fault message codes
#define ERR_NoError           (0)
#define ERR_LSSOspeed         (1)   //Fault LSS overspeed
#define ERR_HSSOspeed         (2)   //Fault HSS Overspeed
#define ERR_RPMError          (3)   //Fault LSS != HSS
#define ERR_WSLowError        (4)   //Warning Anemometer error
#define ERR_Motoring          (5)   //Warning Motor error
#define ERR_GridFault         (6)   //Warning Grid fault
#define ERR_UndefinedState    (7)   //Fault
// Fault Brake Failure: this is aliased to ERR_UndefinedState because there 
// is no support in the ERI for a new code
#define ERR_BrakeFailure      (ERR_UndefinedState) 

// Define which digits represent which state parameters saved in flash 
// (in gFlashStruct.ulReserved[1]).
// These are all perfect powers of ten, as one digit represents one parameter
// value, where the values can be (0-9).
#define FLASH_FAULT_CODE_DIGIT      (1)
#define FLASH_CURRENT_STATE_DIGIT   (10)
#define FLASH_PAST_STATE_1_DIGIT    (100)
#define FLASH_PAST_STATE_2_DIGIT    (1000)


///////////////////////////////////////////////////////////////////////////////
// Included Libraries:
// NOTE: These must appear after the RTK configuration defines
///////////////////////////////////////////////////////////////////////////////

#class auto         //Place local vars on the stack






#memmap xmem        //Place c functions in extended memory unless declared as
				    //root

#use ucos2.lib
//#use "fs2.lib"
#use "dcrtcp.lib"  // For tcp/ip
#use udpdownl.lib  // For download manager


BOOL gbSendDigIO;      			//True if remote interface wants I/O status.
int gbDigitalOutTesting;		//True if bench testing dig outputs.

int giOutputTest[8];		   //Dig outputs are set by checking the
						   	   //values in this array when digitalOutTesting
                           //is TRUE.

int giOutputs[8];				//This holds the values that were written to the
									//actual output channels.


enum { maxCommParse = 20 };
//const char TestString[]="@#,1.56,78.9,8,#\0";
float command[maxCommParse+1];





enum { rb_size = 400 };
struct ring_buffer
        {
        char buffer[rb_size];
        int head, tail, count;
        };
typedef struct ring_buffer ring_buffer;


struct IPConfig
{
	char	IPAddress[16];
   char	Netmask[16];
   char  NameServer[16];
   char	Gateway[16];
   int	Port;
   char	Saved[SAVED_STRING_LENGTH];

};
typedef struct IPConfig IPConfig;
const IPConfig DefaultIPSettings=
	{"192.168.0.61",  //Default IP address
    "255.255.255.0",	//Default Netmask
    "192.168.0.1",   //Default name server
    "192.168.0.1",   //Default gateway
    3500,            //Default TCP/IP port
    "XXXXX"          //Not saved to user block
   };
IPConfig IPSettings;


struct SiteInfo
{
	char	Name[100];
   char  Saved[SAVED_STRING_LENGTH];
};

typedef struct SiteInfo SiteInfo;
const SiteInfo gSiteDefaults={"Endurance control panel","00000"};
SiteInfo	gSite;

char gcPasswordKey[20];			//Sent to remote interface to encrypt password
char gcPassword[20];
char gcEncryptedPassword[20];
char gcPendingPassword[20];
BOOL gbPasswordAccepted;

unsigned char gucWatchDogIN[100];
unsigned char gucWatchDogOut[50];


struct PasswordFlash
{
	char	cPassword[30];
   char  cSaved[SAVED_STRING_LENGTH];
};

typedef struct PasswordFlash PasswordFlash;
const PasswordFlash structDefaultPassword={"admin","00000"};
PasswordFlash structPassword;

///////////////////////////////////////////////////////////////////////////////
// Structures for turbine model information, stored in flash
///////////////////////////////////////////////////////////////////////////////

// Default turbine model
#define MODEL_TYPE_DEFAULT (eS343)

// Model Info structure definition
typedef struct
{
   ModelEnum   model;
   ModelEnum   defaultModel;
   char        Saved[SAVED_STRING_LENGTH];
} ModelInfoStruct;

// Default model info
const ModelInfoStruct gModelInfoDefaults =
{
   MODEL_TYPE_DEFAULT,
   MODEL_TYPE_DEFAULT,
   "00000"
};

// Global (SRAM) model info struct
ModelInfoStruct gModelInfo;


struct WindRecord
{
	long lTimeStamp;
   int iRPM;   // Can be rpm or power
   int iWindSpeed;
};
typedef struct WindRecord WindRecord;

struct EventRecord
{
	long lTimeStamp;
   char cEvent;
};
typedef struct EventRecord EventRecord;

struct RecordBuffer
{
	unsigned long 	ulBase;    		  //Base address of buffer
   unsigned long 	ulWrap;          //Largest address before wrap around
   unsigned long	ulRecordLast;    //Address of last stored record
   unsigned long	ulRecordNext;    //Address to store next record
   unsigned long	ulOldestRecord;  //Address of oldest record
   unsigned long	ulBufferSize;	  //Total size of buffer
   unsigned int  	uiRecordSize;    //Size of each record
   unsigned int	uiRecordCount;   //Number of records
   unsigned	int	uiRecordMax;     //Max number of records
	unsigned long	ulNextRecToSend; //Address of next record to send
	unsigned int	uiRecsToSend;	  //Number of records to send
	//Function that converts record to a string to be transmitted to ERI
   char* 			(*pfnConvert)();
};
typedef struct RecordBuffer RecordBuffer;

RecordBuffer gWindRPM;
RecordBuffer gEvents;
RecordBuffer gWindRPMDiag;
RecordBuffer gEventsDiag;
BOOL bRecordsInitalized;

//Points to the structure that is transmitting records, NULL if none
//are being sent.
RecordBuffer*	pRecXmitter;

//Indexable array of pointers to RecordBuffers, pRecXmitter will
//be set to one of these:
RecordBuffer* const	pRecXmitters[4]=
		{&gWindRPM,&gEvents,&gWindRPMDiag,&gEventsDiag};


//Strings sent to ERI will have the following as prefix and suffix
const  char gcCommandHeader[]="@*CMD,";    //ERI strings starts with this
const  char gcCommandTerminator[]="#\r\n";  //ERI string ends with this


//ring_buffer	grbTCPincomming;	//Buffers for getting data between tasks.

ring_buffer	grbTCPoutgoing;
tcp_Socket 	gsSocket; //Our socket that listens for connections
int 			giSocketInitStatus; //0 if socket initialized OK.
BOOL 			gbTCPConnected;

long			glFreeMemory;

char			 gcWindRecInterval;	 //Interval that data is recorded

unsigned long			 glRecRequestDate;	 //Send records newer than this date


//long			glNextRecToSend;		//Address of next record to send
//int			guiRecsToSend;		   //Number of records to send

int			giERIversion;			//Software version of Endurance Remote Interface

///////////////////////////////////////////////////////////////////////////////
// Global Variables:
///////////////////////////////////////////////////////////////////////////////

// Global command for tower controller (see CMD_* bit maps above) ...
UINT guiTowerCommand;

// Flag for remote HALT command
BOOL gbRemoteHalt;

// Flag to indicate that the turbine has been HALTED since
// starting up (does not include starting up in HALT)
BOOL gbHaltedSinceStart;

// Flag for current state of the brake digital output 
BOOL gbBrakeState;

// Persisted storage for keeping track of time since last power up ...
ULONG gulSecondsSinceStart;
ULONG gulTimeHistory;      //value of SEC_TIMER when program starts, seconds
ULONG ulGenSwitchOnTime;   //latest time generator is switched on, seconds
ULONG ulGenSwitchHiTime;   //latest time generator is switched to 240V, seconds
ULONG ulTimeBrakeStop;     //latest time brakes were applied
ULONG ulTimeCutIn;         //latest time CUTIN state began, seconds
ULONG ulTimeMotorStart;    //latest time MOTOR state began, seconds
ULONG ulTimeHighWind;      //latest time HIGHWIND state began, seconds
ULONG gulWarnTime;         //latest time at which there was a warning, seconds
ULONG gulTimeCutInOk;      //time after which it is OK for the turbine to cut-in

// Storage for ISR_ExternalInterrupt used to sample rotor speed ...
shared UINT guiShaftEncoderCount; // encoder counts, consumer should clear

// Storage for ISR_Anemometer used to sample wind speed ...
shared UINT guiAnemometerCount; // positive edges, consumer should clear
BOOL gbAnemometerPolarity;      // 1 => anemometer output signal was HIGH

// Storage for ISR_Anemometer used to sample HSS RPM ... 20050505 ACH
shared UINT guiRPMHSSCount; // positive edges, consumer should clear
BOOL gbRPMHSSPolarity;      // 1 => encoder output signal was HIGH

// Storage for computed speeds ...
shared float gfRPMLSS; // computed rotor RPM, access via function
shared float gfRPMPrev; // previously computed rotor RPM
shared float gfRPMLSSAvg; // computed time-averaged rotor RPM
shared float gfRPMHSS; // computed HSS speed as LSS equivalent, access via function
shared float gfRPMHSSAvg; // computed time-averaged HSS RPM  as LSS equivalent
shared float gfWSmps; // computed wind speed, access via function
shared float gfWSmpsAvg; // computed time-average wind speed
shared float gfSpeedSlip; //HSS avg slip in rpm = gfRPMHSSAvg - RpmMotorStartMaxGet()
shared float gfSpeedSlipSum; //running total (integral) of gfSpeedSlip
shared float gfHiSpeedSlipSum; //running total (integral) of gfSpeedSlip
shared float gfPowerAvgDisplay; // computed average power for display purposes
shared float gfMaxRPMHSS; // maximum observed value of HSS rpm

// Counters for windspeed logging synchronization
shared ULONG gulLastRecordPending; // The most recent pending record
shared ULONG gulLastRecordComplete; // The most recent record which is complete

// Storage for computed generator power ACH 20050506
shared float gfGenPowerWatts;

// Storage for outbound message counter ...
shared UINT guiSequenceNumber;

// Storage for Finite State Machine state ...
UCHAR gucStateWindSpeed; 	// Current state
UCHAR gucFaultCode; 		 	// store fault message code (see "Define fault message codes")
UCHAR gucLastRecEvent;   	// Last recorded event code
UCHAR gucLastERIRec;	      // Last recorded Command from ERI.
UCHAR gucLastRecDiagEvent;	// Last recorded diagnostic event
UCHAR gucStateHistory[2]; 	// store previous 2 states

// Storage for SSR swtich settings
BOOL gbSSR_On[7];      // array of 7 SSR switch settings (ON of OFF)

// Storage for virtual watchdog timers (initialized in StateInitialize) ...
int giWDT_main;    // MainTask wachtdog timer
int giWDT_measure; // TaskMeasureSpeeds wachtdog timer
int giWDT_fault  ; // TaskFaultMonitor wachtdog timer

// Index of control parameter arrays, the Parameter ID
int giParameterID;              // 20051020 ACH  added for param adjustment on the fly

// Global serial input and output buffers ...
#define BUFFER_RECEIVE_SIZE  200 /* allow incoming messages of this size     */
UCHAR gucBufferIn[BUFFER_RECEIVE_SIZE];
UCHAR gucBufferParse[BUFFER_RECEIVE_SIZE];
UCHAR gucIndexInput; // point into buffers

// Flash structures
#define NUM_FLASH_STRUCTS  (5)
enum FlashSemaphoreEnum
{
   eFlashStruct   = 0,
   eIPSettings    = 1,
   eSiteInfo      = 2,
   ePassword      = 3,
   eModelInfo     = 4,
};

// Global semaphore to allow coordination of Flash Memory writes ...
//set gbSemaphoreFlashUpdate[eFlashStruct] = TRUE to to save gFlashStruct to Flash
//set gbSemaphoreFlashUpdate[eIPSettings] = TRUE to to save ip settings to Flash
//set gbSemaphoreFlashUpdate[eSiteInfo] = TRUE to to save site info to Flash
//set gbSemaphoreFlashUpdate[ePassword] = TRUE to to save password to Flash
//set gbSemaphoreFlashUpdate[eModelInfo] = TRUE to to save model info to Flash
BOOL gbSemaphoreFlashUpdate[NUM_FLASH_STRUCTS];


// Global Flash Memory file transfer structure ...
struct 	FlashStruct gFlashStruct;
unsigned long	gulTimeClock;					// Time clock is read into this
unsigned long 	gulTimeClockOffset;			//Difference between SEC_TIMER
														//and gulTimeClock - set at power up


// For testing only ...
#ifdef TESTING
UINT guiTestingRotorRPM;
float gfTestingWSMPS;
float gfTestingRPMHSS;
#endif // #ifdef TESTING


///////////////////////////////////////////////////////////////////////////////
// Function Prototypes:
///////////////////////////////////////////////////////////////////////////////

// interrupt service routines ...
void ISR_Anemometer( void );
void ISR_ExternalInterrupt( void );

// functions ...
float AnemometerCountsToMPS( float fCountsPerSecond ); // 20041028 RSF
float RPMHSSCountsToRPM( float fCountsPerSecond ); // 20050505 ACH
void  ClearReceiveBuffer( void );
void  DiagnosticPrint( char *pString );

#ifdef	TEST_PRINT
void  FileParameterDump( void );
#endif

void  FSMWindSpeed( void );
void  HandleHalt( void );
float GenPowerGet( void );            // 20050506 ACH
float RpmToPower( float rpm, UCHAR state );
BOOL  GridFault( void );              // 20060628 ACH
BOOL  KeySwitchHalted( void );
BOOL  CommissionTest( void );         // 20070127 DJL
BOOL  TestActive( void );
void  HandleTimers( void );
void  MotorStart( void );
void  MotorSwitch( void );
void  GenLoSwitch( void );
void  UpSwitch( void );
void  DownSwitch( void );
void  SSR_Switch( void );
void  UpdateGenerator( void );
void  UpdateGenState( void );
void  SetGenSSRs( void );
BOOL  MemoryTest(void);
void  ReadFlashData(BOOL);
void  FactoryReset(void);
void  CountSwitchToggles(void);
BOOL  MessageParse(char* pToParse );
void  RotorBrake( BOOL bOn );
BOOL  GetBrakeState( void );
BOOL  CheckBrakeFailureCondition( void );
float RotorCountsToRPM( float fCountsPerSecond ); // 20041028 RSF
float RotorRPMGet( void );
void  RotorRPMSet( float fRPMLSS );
float RPMHSSGet( void );
void  RPMHSSSet( float fRPMHSS );
void 	rb_addChar(ring_buffer  *b,char  c);
char 	rb_getChar(ring_buffer *b);
void rb_reset(ring_buffer *b);
//void  SendIO (void){};
UINT  SequenceNumberGet( void );
void  SequenceNumberSet( UINT uiSequenceNumber );
int	SerialGetChar(void);
BOOL  SerialReceiveAeroComm( void );
void  SerialSendAeroComm( char *pOutgoingMessage );
void  StateInitialize(BOOL bNewFirmware);
void  TaskAeroCommReceive( void *pData );
void  TaskMainThread( void *pData );
void  TaskMeasureSpeeds( void *pData );
void  TaskStart( void *pData );
void  TaskStatus( void *pData );
void  TaskFaultMonitor( void *pData );
void  TaskTCPIP(void *pData);
void  TaskTimers(void *pData);
void 	TaskFlashWrite(void *pData);
void  TestingParseKeypress( void );
void  TestOutput( BOOL bOn );
void	RecordsInit(BOOL bFullReset);
void  RecordStructInit(RecordBuffer* R);
void  CheckRecordInterval(struct tm *theTime);
char  GetRecordInterval(void);
void  UpdateWindSpeedRecord(float currentWindSpeed,  UINT samplePeriodSecs);
void 	CheckTriggers(void);
void	ExecuteTowerCommand(char *pToParse );
void  ExtWDCheck(); //Called once per second

#ifdef TEST_PRINT
void ShowBuffer (RecordBuffer* R);
#endif



#ifdef TEST_FOUND
void 	CompileCheck(void);
#endif

//Functions prototypes for commands received from ERI
void	TC_Null(void);
void	TC_Run(void);
void	TC_Halt(void);
void	TC_ClearSVC(void);
void	TC_ClearMax(void);
void	TC_ClearEvent(void);
void	TC_TestOn(void);
void	TC_TestOff(void);
BOOL	TC_SetDate(char* pToParse);
BOOL  TC_SetTime(char* pToParse);
void	TC_SetIPAdd(char* pToParse);
void  TC_ReqIPinfo(void);
void  TC_SetNetmask(char* pToParse);
void  TC_SetNameServer(char* pToParse);
void  TC_SetGateway(char* pToParse);
void  TC_SetIPPort(char* pToParse);
void  TC_SendDefaultString (void);
void  TC_ApplyIPSettings(void);
void  TC_Motor(void);
void  TC_Brake(void);
void  TC_StackReport (void);
void	TC_RequestSiteInfo (void);
void  TC_SetSiteInfo(char* pToParse);
void	TC_RequestFlashInfo(void);
void  TC_QueryTestMode(void);
void  TC_RequestRecInfo(char* pToParse);
void	TC_RequestMainRec(char* pToParse);
void	TC_CancelRecords(void);
void	TC_Hello(char* pToParse);
void  TC_SetRecInterval(char* pToParse);
void  TC_RequestRecInterval();
void	TC_RequestDate(void);
void  TC_RequestTime(void);
void	TC_RequestTriggers(void);
BOOL	TC_SetTriggers(char* pToParse);
void  TC_RequestPassKey(void);
void 	TC_Password(char* pToParse);
void 	TC_NewPassword(char* pToParse);
void 	TC_SetNewPassword(char* pToParse);
void  TC_FwUpgrade(char* pToParse);




//Tower response codes
enum {
		TR_IPInfo 				=	1,
	   TR_IPConfirm 			= 	2,
    	TR_RecIPApplied 		=	3,
    	TR_PasswordKey 		=	4,
    	TR_StackInfo 			=	5,
    	TR_SiteInfo 			=	6,
    	TR_FlashInfo 			=	7,
      TR_QueryTestMode 		=	8,
      TR_RequestRecInfo 	= 	9,
      TR_RecordsStarted 	= 	10,
      TR_RecordsCanceled 	= 	11,
      TR_MainRecord		 	=  12,
      TR_RecInterval 		=  13,
      TR_DateTime 			=	14,
      TR_RecordsComplete 	=	15,
      TR_Triggers 			=	16,
      TR_PasswordResponse	=	17,
      TR_NewPasswordEcho	=	18,
      TR_NewPasswordSet		=	19,
      TR_WatchDogDisabled	=  20
										     };


void  EncryptPassword();
void 	SendMainRecords(void);
void  ApplyIPSettings(void);
void  ToggleOutput( int output );
// ULONG ValidatePersistent( void );
void  WatchdogHit( int iWDT );
float WindSpeedMPSGet( void );
void  WindSpeedMPSSet( float fMPS );
void  digitalOutput(int channel,int value);
void  TwicePerSecond(void);
void  OncePerSecond(void);
void  OncePerMinute(void);
void  OncePerDay(void);

void  DigitalTest(void);

void AddRecord(void* pRecord, RecordBuffer* R);
unsigned long RecAddInc (unsigned long Address,RecordBuffer* R);
void RecordMoveNext(RecordBuffer* R);
void SendMoveNext(RecordBuffer* R);
void RecordWind(float windSpeed);
void RecordWindDiag(void);
void RecordEvent(char EventNumber);
void RecordDiagnosticEvent(char EventNumber);
void RecordDoubleEvent(char EventNumber);
void RecordTestMode(UCHAR ucTestMode);
void RecordStateIfChanged(void);
BOOL RecordPath(unsigned char ucPath);
void SetState(UCHAR ucNewState);
void ModelParamsSet(void);
void ToggleModel(void);
float RpmLssSynchronousGet(void);
float RpmOfflineGet(void);
float RpmDownSwitchGet(void);
float RpmUpSwitchGet(void);
float RpmGenHiSlipSumThreshGet(void);
float RpmMotorStartMaxGet(void);
float RpmMotorStopGet(void);
float RpmOverSpeedGet(void);
ULONG VersionDisplayNumberGet(void);

char* xTimeString(char* pBuff, long lTime);
char* PlaceHeader(char* pBuff, unsigned int CommandNumber);
char* EventToString(char*pBuff,unsigned long pE);
char* WindRPMToString(char*pBuff,unsigned long pW);


char* ultoh(char* str,unsigned long* N );  //Unsigned long to hex string
char* uitoh (char* str, unsigned int* N);  //Unsigned integer to hex string
char* btoh (char* str, char C);            //Byte to hex string
char* ntoh (char* str, char C);				 //Nibble to hex


void FindNewMax(void);


//Set diagnostic trigger on halt if 					gbTriggers[0] ==TRUE
// 								 calm if 					gbTriggers[1] ==TRUE
// 								 cutin if 					gbTriggers[2] ==TRUE
// 								 free-wheel if 			gbTriggers[3] ==TRUE
// 								 motor if 					gbTriggers[4] ==TRUE
// 								 generate low if 			gbTriggers[5] ==TRUE
// 								 generate high if 		gbTriggers[6] ==TRUE
// 								 high wind if 				gbTriggers[7] ==TRUE
// 								 fault LSS overspeed if gbTriggers[8] ==TRUE
//									 fault HSS if 				gbTriggers[9] ==TRUE
//									 fault RPM error if 		gbTriggers[10]==TRUE
//									 warn anem error if 		gbTriggers[11]==TRUE
//									 warn motor error if 	gbTriggers[12]==TRUE
//									 warn grid fault if 		gbTriggers[13]==TRUE
//									 unknown error if 		gbTriggers[14]==TRUE
//									 power down if    		gbTriggers[15]==TRUE

//gbTriggers[16] is TRUE if any trigger has occured and no more
//records will be added to the diagnostic buffers until gbTriggers[16]
//has been reset to FALSE;
BOOL gbTriggers[17];

const BOOL gbDefaultTriggers[]=
{
		FALSE, // Halt                  0
      FALSE, // Calm                  1
   	FALSE, // Cutin                 2
      FALSE, // Free-wheel            3
      FALSE, // Motor                 4
      FALSE, // Generate low          5
      FALSE, // Generate hi           6
      FALSE, // High wind             7
    TRUE,    // LSS overspeed         8
    TRUE,    // HSS overspeed         9
    TRUE,    // RPM error             10
    	FALSE, // Anemometer error      11
      FALSE, // Motor error           12
      FALSE, // Grid fault            13
    TRUE,    // Unknown error         14
      FALSE, // Power down            15
      FALSE	 // Trigger activated	  16
};

BOOL  gbExtWatchDogSet;   		//True after external watch dog has been enabled
ULONG gulExtWDConfigTimeout; 		//Number of secs before enabling the external watchdog

// main routine ...
void  main( void );


///////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines:
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Rabbit 3000 Timer B Interrupt Service Routine
// Used to count pulses from the anemometer and HSS pulse.
// Note: The consumer is responsible for clearing the count
//
// Input Args:     none
// Output Args:    none
// Input Globals:  guiAnemometerCount, gbAnemometerPolarity
//                 guiRPMHSSCount,     gbRPMHSSPolarity
// Output Globals: guiAnemometerCount, gbAnemometerPolarity
//                 guiRPMHSSCount,     gbRPMHSSPolarity
// Returns:        none
// Processing:     measure anemometer speed by counting positive edges
// Updates:
//   20040224 RSF - original version
//   20050505 ACH - add second channel for HSS RPM


#asm
ISR_Anemometer::
        push     hl                 ; save affected registers ...
        push     af
        ioi      ld      a,(TBCSR)  ; load B1, B2 interrupt flags (clears them)
        ; sample Anemometer Input (PE3) to look for rising edges ...
        ld       hl,PEDR            ; point at Port E input bits ...
        ioi      bit      3,(hl)    ; Z flag set if PE3 was zero
        jr       z,AnemometerLow    ; ++ iff rising edge ...
        ld       a,(gbAnemometerPolarity) ; check old polarity ...
        or       a
        jr       nz,RPMHSSCount  ; old polarity was already high, get RPM counts
        ld       hl,(guiAnemometerCount) ; increment Anemometer counter ...
        inc      hl
        ld       (guiAnemometerCount),hl
        ld       a,0x01             ; "old" polarity becomes one ...
        ld       (gbAnemometerPolarity),a
        jr       RPMHSSCount        ; move to RPM counter
AnemometerLow:
        xor      a                  ; "old" polarity becomes zero ...
        ld       (gbAnemometerPolarity),a
RPMHSSCount:        ; sample encoder Input (PE6) to look for rising edges ...
        ld       hl,PEDR            ; point at Port E input bits ...
        ioi      bit      6,(hl)    ; Z flag set if PE6 was zero
        jr       z,RPMHSSLow        ; ++ iff rising edge ...
        ld       a,(gbRPMHSSPolarity) ; check old polarity ...
        or       a
        jr       nz,AnemometerExit  ; old polarity was already high
        ld       hl,(guiRPMHSSCount) ; increment RPM counter ...
        inc      hl
        ld       (guiRPMHSSCount),hl
        ld       a,0x01             ; "old" polarity becomes one ...
        ld       (gbRPMHSSPolarity),a
        jr       AnemometerExit
RPMHSSLow:
        xor      a                  ; "old" polarity becomes zero ...
        ld       (gbRPMHSSPolarity),a
AnemometerExit:
        ld       a,00h              ; reload timer B match register
        ioi      ld       (TBL1R),a ; LS
        ioi      ld       (TBM1R),a ; MS
        pop      af                 ; restore affected registers ...
        pop      hl
        ipres
        ret
#endasm
// end of ISR_Anemometer

///////////////////////////////////////////////////////////////////////////////
// Rabbit 3000 External Interrupt Service Routine
// Used to count pulses from the shaft encoder.
// Note: The consumer is responsible for clearing the count
//
// Input Args:     none
// Output Args:    none
// Input Globals:  guiShaftEncoderCount
// Output Globals: guiShaftEncoderCount
// Returns:        none
// Processing:     measure rotor speed by counting encoder pulses
//                 the pulse count is incremented by 1 each time
//                 this routine is called (each interrupt or pulse on input INT1a)
// Updates:
//   20040218 RSF - original version
// this asm routine is the equivalent of guiShaftEncoder++  (increment value by 1)
// but runs much faster in assembly than in C (perhaps 10x faster)
//nodebug root interrupt void ISR_ExternalInterrupt()
//{
//   guiShaftEncoderCount++;
//}
#asm
ISR_ExternalInterrupt::
        push     hl                 ; save affected registers ...
        push     af
        ld       hl,(guiShaftEncoderCount)
        inc      hl
        ld       (guiShaftEncoderCount),hl
        pop      af                 ; restore affected registers ...
        pop      hl
        ipres
        ret
#endasm
// end of ISR_ExternalInterrupt


///////////////////////////////////////////////////////////////////////////////
// Support Functions:
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Compute wind speed in MPS from counts per second
// NOTE: We'll limit input counts to 100 to prevent numerical overflow
//
// NRG #40 Anemometer Transfer Function:
//   MPH = 1.711 (Hz) + 0.78 (MPH)
//   M/S = 0.765 (Hz) + 0.35 (M/S)
//   inverting gives:
//   Hz = (MPH - 0.78) / 1.711
//   Hz = (M/S - 0.35) / 0.765
//   representative limit values:
//   100 MPH => 58 Hz
//
// Input Args:     counts per second
// Output Args:    none
// Input Globals:  none
// Output Globals: none
// Returns:        wind speed in MPS (float)
// Processing:     units conversion from Hertz to MPS for NRG #40 Anemometer
// Updates:
//   20040224 RSF - original version
//   20041028 RSF - use float arg to allow easier integration time changes
float AnemometerCountsToMPS( float fCountsPerSecond )
{
   // perform input range limiting (about 200 MPS) ...
   if (fCountsPerSecond > 1500.0) // too high ...     // 20050427 ACH was 116
   {
     fCountsPerSecond = 1500.0;
   }
   else if (fCountsPerSecond < 0.0) // too low ...
   {
     fCountsPerSecond = 0.0;
   }
   // final check.  check calibration const for anemom. (Hz -> m/s)
   return 0.35 + 0.765 * fCountsPerSecond;
   //return fCountsPerSecond;     // 20050427 ACH  to output freq instead of wind speed
} // end of AnemometerCountsToMPS


// Compute LSS RPM from HSS sensor pulses per second
// Limit input counts to prevent numerical overflow
//
// Inputs:
//    fCountsPerSecond -   HSS sensor pulses, per second
// Returns:
//    LSS speed in RPM (float)
float RPMHSSCountsToRPM( float fCountsPerSecond )
{
   float fLimitedFrequency;
   float fConvertedRPM;

   #define MAX_HSS_FREQUENCY (1500.0)
   #define MIN_HSS_FREQUENCY (0.0)

   // Limit inputs: must be between 0 and 1500 Hz

   // Check upper limit
   if (fCountsPerSecond > MAX_HSS_FREQUENCY)
   {
     fLimitedFrequency = MAX_HSS_FREQUENCY;
   }
   // Check lower limit
   else if (fCountsPerSecond < MIN_HSS_FREQUENCY)
   {
     fLimitedFrequency = MIN_HSS_FREQUENCY;
   }
   // Within limits, so use the input value
   else
   {
      fLimitedFrequency = fCountsPerSecond;
   }

   // Convert the frequency [pulses/s] to LSS RPM according to the formula:
   //
   // LSS RPM =             (Freq [pulses / s] * 60 [s / min])
   //            ---------------------------------------------------------
   //            (18 [pulses / HSS Rev] * GearRatio [HSS Revs / LSS Revs])
   //
   fConvertedRPM = (fCountsPerSecond * 60) /
                     (HSS_TICKS_PER_REV * gModelParams.fGearRatio);

   // Return the converted value
   return fConvertedRPM;

} // end of RPMHSSCountsToRPM

///////////////////////////////////////////////////////////////////////////////
// Empty serial receive buffer by performing reads until no characters left
//
// Input Args:     none
// Output Args:    none
// Input Globals:  none
// Output Globals: none
// Returns:        none
// Processing:     read until we see "-1"s coming from serial interface
// Updates:
//   20050107 RSF - original version
void ClearReceiveBuffer( void )
{
  int iChar; // character destination

	  do
	  {
   	 iChar = SerialGetC();
	  }
  	  while (iChar != -1);
} // end of ClearReceiveBuffer

///////////////////////////////////////////////////////////////////////////////
// If DEBUG_PRINT is defined, print out diagnostic string to:
//   RS232 serial port if DIAGNOSTIC_RS232 is defined,
//   else, Dynamic C stdio if DIAGNOSTIC_RS232 is not defined
//
// Input Args:     pointer to null-terminated string to be printed
// Output Args:    none
// Input Globals:  none
// Output Globals: none
// Returns:        none
// Processing:
// Updates:
//   20040218 RSF - original version
void DiagnosticPrint( char *pString )
{
   #ifdef DEBUG_PRINT
     WatchdogHit(giWDT_main); // always hit watchdog when printing enabled
     #ifdef DIAGNOSTIC_RS232
       SerialPuts( pString );
     #else // #ifdef DIAGNOSTIC_RS232
       printf( "%s", pString );
     #endif // #ifdef DIAGNOSTIC_RS232
   #endif // #ifdef DEBUG_PRINT
} // end of DiagnosticPrint


///////////////////////////////////////////////////////////////////////////////
// Dump the contents of the Flash File struct (for diagnostics).
//
// Input Args:     none
// Output Args:    none
// Input Globals:  gFlashStruct
// Output Globals: none
// Returns:        none
// Processing:     Dump the parameters in the gFlashStruct struct
// Updates:
//   20041209 RSF - original version
//   20041210 RSF - clean up formatting
#ifdef	TEST_PRINT
void FileParameterDump( void )
{
  int ii; // loop index
  char strTemp[80]; // to build output strings

  DiagnosticPrint( "File Parameter Storage:\r\n" );
  sprintf( strTemp, "  Maximum Power (Watts):          %8.2f\r\n",
    gFlashStruct.ulPowerMaxX100 / 100.0 );
  DiagnosticPrint( strTemp );
  sprintf( strTemp, "  Maximum Wind Speed (MPS):       %8.2f\r\n",
    gFlashStruct.ulMPSMaxX100 / 100.0 );
  DiagnosticPrint( strTemp );
  sprintf( strTemp, "  Maximum Shaft Speed (RPM):      %08ld\r\n",
    gFlashStruct.ulRPMLSSMax );
  DiagnosticPrint( strTemp );
  sprintf( strTemp, "  Number of Motor Starts:         %08ld\r\n",
    gFlashStruct.ulMotorStarts );
  DiagnosticPrint( strTemp );
  sprintf( strTemp, "  Number of Brake Stops:          %08ld\r\n",
    gFlashStruct.ulBrakeStops );
  DiagnosticPrint( strTemp );
  sprintf( strTemp, "  Total Hours of Operation:       %08ld\r\n",
    gFlashStruct.ulTotalHours );
  DiagnosticPrint( strTemp );
  sprintf( strTemp, "  Hours Into Service Interval:    %08ld\r\n",
    gFlashStruct.ulServiceHours );
  DiagnosticPrint( strTemp );
  sprintf( strTemp, "  Number of DVS Upswitches:       %08ld\r\n",
    gFlashStruct.ulUpSwitches );
  DiagnosticPrint( strTemp );
  sprintf( strTemp, "  Saved                   :       %s\r\n",
    gFlashStruct.Saved );
  DiagnosticPrint( strTemp );

  // print out reserved fields ...
  for (ii = 0; ii < RESERVED_ULONGS; ii++)
  {
    sprintf( strTemp, "  Reserved ULONG # %d:             %08lx\r\n", ii,
      gFlashStruct.ulReserved[ii] );
    DiagnosticPrint( strTemp );
  }
} // end of FileParameterDump
#endif



///////////////////////////////////////////////////////////////////////////////
// State Machine responsible for actions based upon wind speed
//
// Input Args:     none
// Output Args:    none
// Input Globals:  gucTowerCommand, gucStateWindSpeed, gFlashStruct
// Output Globals: gucTowerCommand, gucStateWindSpeed, gFlashStruct
// Returns:        none
// Processing:     perform actions based upon wind speed & RPM
// There are four RPM values and two wind speed values available for the
//  state control logic:
//    RotorRPMGet() is the 0.1s average of the LSS encoder speed
//    gfRPMLSSAvg is the filtered average of the LSS speed (~5s avg)
//    RPMHSSGet() is the 1s average of the HSS speed (in LSS equivalent)
//    gfRPMHSSAvg is the filtered average of the HSS speed (~5s avg)
//    fMPS = WindSpeedMPSGet() is the 5s average wind speed
//    gfWSmpsAvg is the filtered (averaged) value of wind speed (same as fMPS in current version)
//
// Updates:
//   20040216 RSF - original version
//   20040325 RSF - make state variable global for status task access
//   20041201 RSF - handle client requests to HALT (hold in HALT state)
//   20050510 ACH - extensive changes to logic
void FSMWindSpeed( void )
{
   #define PARAM_1    10      // 20051020 ACH use for parameter switching
   #define PARAM_2    20
   #define PARAM_3    30
   #define PARAM_4    40
   #define PARAM_5    50

   // local variables ...
   int i;

	giParameterID *=CommissionTest();

   HandleHalt();

   FindNewMax(); //Look for new max values for power etc.

   // Process state transitions and actions for this pass of FSM ...
   switch (gucStateWindSpeed)
   {
     case STATE_HALT: // Client is requesting system HALT ...
       // Handle state actions ...
       RotorBrake( ON ); // apply rotor brake
       UpdateGenerator();

       // Handle state transitions and exit actions ...

      if ( ! KeySwitchHalted() && ! gbRemoteHalt )  // RUN command at tower AND NOT HALT from remote
      {
         // If user issued both a HALT and RUN command, set the cut-in OK time
         // to now + kulMinTimeCalm. This forces the turbine to wait in calm
         // for kulMinTimeCalm seconds before going to cut-in.
         // This also serves to bypass kulCnctWaitTime as forcing a HALT & RUN
         // is the "back-door" command to force the turbine to cut-in.
         if (gbHaltedSinceStart == TRUE)
         {
            gulTimeCutInOk = SEC_TIMER + kulMinTimeCalm;
         }

         SetState(STATE_CALM);
         gucFaultCode = ERR_NoError;
         DiagnosticPrint( "FSMWindSpeed: [HALT->CALM] ...\r\n" );
      }
      break;

     case STATE_CALM: // waiting for wind
       // Handle state actions ...
       RotorBrake( ON ); // apply rotor brake
       UpdateGenerator();

       // Go to generator cut in state if wind speed > kfWS_Cutin MPS
       if (gfWSmpsAvg > kfWS_Cutin[giParameterID]           // There is enough wind...
       && (SEC_TIMER >= gulTimeCutInOk                      // and it's been long enough since power-up.
       ||  TestActive() ) )                                 // or we're actively in a test mode.
       {
         SetState(STATE_CUTIN); //
         gucFaultCode = ERR_NoError;
         ulTimeCutIn = SEC_TIMER; // Record time CUTIN started
         DiagnosticPrint( "FSMWindSpeed: [CALM->CUTIN] ...\r\n" );
       }

       break;

     case STATE_CUTIN: // for winds above kfWS_Cutin after CALM or HIGHWINDS
       // Handle state actions ...
       RotorBrake( OFF ); // release rotor brake
       UpdateGenerator();

       // Handle state transitions and exit actions ...

       // Switch to FREEWHEEL state if RPM reaches minimum
       if ( RPMHSSGet() > kfRPM_Lo )
       {
         SetState(STATE_FREEWHEEL);
         gucFaultCode = ERR_NoError;

         DiagnosticPrint( "FSMWindSpeed: [CUTIN->FREEWHEEL] ...\r\n" );
       }
       else if ( SEC_TIMER - ulTimeCutIn > kulMinTimeCutIn       // We've been here for a minimum time
         && gfWSmpsAvg > kfWS_Cutin[giParameterID]               // and we've got wind
         && (SEC_TIMER - ulTimeMotorStart > kulMotorTimeOut      // and (it's been long enough since last motor event,
         || TestActive() ) )                                     // or we're actively in a test mode).
       {
         SetState(STATE_MOTOR);
         gucFaultCode = ERR_NoError;
         ulTimeMotorStart = SEC_TIMER;
         DiagnosticPrint( "FSMWindSpeed: [CUTIN->MOTOR] ...\r\n" );
         MotorStart(); // log the number of motor starts
       }
       else if ( SEC_TIMER - ulTimeCutIn > kulMaxTimeCutIn )  // We've been stuck here long enough
       {
         SetState(STATE_CALM);
         gucFaultCode = ERR_NoError;
         DiagnosticPrint( "FSMWindSpeed: [CUTIN->CALM] ...\r\n" );
       }
       break;

     case STATE_FREEWHEEL: // after wind dies and we're offline, wait for wind
       // Handle state actions ...
       RotorBrake( OFF ); // release rotor brake
       UpdateGenerator();

       // Handle state transitions and exit actions ...
       if (RPMHSSGet() < kfRPM_Lo)  // very low rpm, prepare to save energy req'd to hold brakes off
       {
         SetState(STATE_CUTIN);
         gucFaultCode = ERR_NoError;
         ulTimeCutIn = SEC_TIMER; // Record time CUTIN started
         DiagnosticPrint( "FSMWindSpeed: [CALM->CUTIN] ...\r\n" );
       }
       // If the generator has connected, update the state to the appropriate generating state
       else if (( gGenState == eConnected120V ) || ( gGenState == eConnected240V ))
       {
         SetState(STATE_GENLO);
         gucFaultCode = ERR_NoError;

         #ifdef TEST_PRINT
	         DiagnosticPrint( "FSMWindSpeed: [FREEWHEEL->GENERATING] ...\r\n" );
         #endif
       }
       else if ( gfWSmpsAvg > kfWS_Cutin[giParameterID]       // sufficient wind,
       && RotorRPMGet() < RpmMotorStartMaxGet()               // but not wind starting,
       && ( SEC_TIMER - ulTimeMotorStart > kulMotorTimeOut    // and (it's been long enough since last motor event;
       ||   TestActive() ) )                                  // or we're actively in a test mode).
       {
         SetState(STATE_MOTOR);
         gucFaultCode = ERR_NoError;
         ulTimeMotorStart  = SEC_TIMER;
         DiagnosticPrint( "FSMWindSpeed: [FREEWHEEL->MOTOR] ...\r\n" );
         MotorStart(); // log the number of motor starts
       }
       break;

     case STATE_MOTOR: // motor up to speed when wind comes up ...
       // Handle state actions ...
       RotorBrake( OFF ); // release rotor brake
       UpdateGenerator();

       if (RotorRPMGet() > RpmMotorStopGet() // rotor up to speed
        ||  (SEC_TIMER - ulTimeMotorStart > kulMaxTimeMotor) )  // or we've motored long enough
       {
         SetState(STATE_FREEWHEEL);
         gucFaultCode = ERR_NoError;
         DiagnosticPrint( "FSMWindSpeed: [MOTOR->FREEWHEEL] ...\r\n" );
       }
       else if ( (SEC_TIMER - ulTimeMotorStart > kulRPMTimeMotor
        && RotorRPMGet() < kfRPM_Lo ) ) // Do not have any RPM after 5 sec
       {
         SetState(STATE_WARN); // force halt
         gulWarnTime = SEC_TIMER;
         gucFaultCode = ERR_Motoring;
         DiagnosticPrint( "Fault while motoring ...\r\n" );
       }

       break;

     case STATE_FAULT: // come here for fault conditions ...
       // Handle state actions ...
       RotorBrake( ON ); // apply rotor brake
       UpdateGenerator();
       break;

     case STATE_GENLO: // normal operation in 120V power-producing winds
       // Handle state actions ...
       RotorBrake( OFF ); // release rotor brake
       UpdateGenerator();

       // If the generator has disconnected, go back down to freewheel
       if ( gGenState == eDisconnected )
       {
         SetState(STATE_FREEWHEEL);
         gucFaultCode = ERR_NoError;
         DiagnosticPrint( "FSMWindSpeed: [GENERATING->FREEWHEEL] ...\r\n" );
       }
       // If the generator has upswitched to 240V, go into gen hi
       else if ( gGenState == eConnected240V )
       {
         SetState(STATE_GENHI);
         gucFaultCode = ERR_NoError;
         DiagnosticPrint( "FSMWindSpeed: [GENLO->GENHI] ...\r\n" );
       }

       break;

     case STATE_GENHI: // normal operation in 240V power-producing winds
       // Handle state actions ...
       RotorBrake( OFF ); // release rotor brake
       UpdateGenerator();

       // If the generator has downswitched to 120V, go into gen low
       if (( gGenState == eConnected120V ) || ( gGenState == eDisconnected ))
       {
         SetState(STATE_GENLO);
         gucFaultCode = ERR_NoError;
         DiagnosticPrint( "FSMWindSpeed: [GENHI->GENLO] ...\r\n" );
       }

       break;

     case STATE_HIGHWINDS: // > parked and waiting for winds to decrease
       // Handle state actions ...
       RotorBrake( ON ); // engage rotor brake
       UpdateGenerator();

       if (SEC_TIMER - ulTimeHighWind > kulTimeHighWind)  // We have been here long enough
       {
       // Handle state transitions and exit actions ...
         if (gfWSmpsAvg < kfWS_Cutin[giParameterID])
         {
           SetState(STATE_CALM);
           gucFaultCode = ERR_NoError;
           DiagnosticPrint( "FSMWindSpeed: [HIGHWINDS->CALM] ...\r\n" );
         }
         else if (gfWSmpsAvg < kf80pct_WSCutout[giParameterID] )
         {
           SetState(STATE_CUTIN);
           gucFaultCode = ERR_NoError;
           ulTimeCutIn = SEC_TIMER; // Record time CUTIN started
           DiagnosticPrint( "FSMWindSpeed: [HIGHWINDS->FREEWHEEL] ...\r\n" );
         }
       }
       break;

     case STATE_WARN: // warning detected
       RotorBrake( ON );    // apply brake
       UpdateGenerator();

       switch (gucFaultCode)
       {
       case ERR_GridFault: // Grid fault detected
         if ( GridFault() )      // fault continues
           {
           gulWarnTime = SEC_TIMER;   //keep updating time at which there was a grid fault, seconds
           }
         else if ( (SEC_TIMER - gulWarnTime) > kulGridTimeOut ) // fault has cleared, return to calm state and restart after delay
           {
           SetState(STATE_CALM);
           gucFaultCode = ERR_NoError;
           DiagnosticPrint( "FSMWindSpeed: [GRIDFAULT -> CALM] ...\r\n" );
           }
         break;

       case ERR_WSLowError: // Anemometer Error detected
         if ( gfWSmpsAvg < kfWS_AnemCheck[giParameterID] )      // fault continues
           {
           gulWarnTime = SEC_TIMER;   //keep updating time at which there was an anemometer error, seconds
           }
         else if ( (SEC_TIMER - gulWarnTime) > kulAnemTimeOut ) // fault has cleared, return to calm state and restart after delay
           {
           SetState(STATE_CALM);
           gucFaultCode = ERR_NoError;
           DiagnosticPrint( "FSMWindSpeed: [Anem Error -> CALM] ...\r\n" );
           }
         break;

       case ERR_Motoring: // Motoring Error detected
         if ( (SEC_TIMER - gulWarnTime) > kulMotErrTimeOut ) // fault has cleared, return to calm state and restart after delay
           {
           SetState(STATE_CALM);
           gucFaultCode = ERR_NoError;
           DiagnosticPrint( "FSMWindSpeed: [Anem Error -> CALM] ...\r\n" );
           }
         break;
       }
       break;

     default: // unknown state - we shouldn't get here, shutdown on Fault
       // Handle state actions ...
       RotorBrake( ON ); // apply rotor brake
       UpdateGenerator();

       gucFaultCode = ERR_UndefinedState;
       SetState(STATE_FAULT);
       DiagnosticPrint( "FSMWindSpeed: [DEFAULT->FAULT] ...\r\n" );
       break;
   } // end of switch (gucStateWindSpeed)

   // Record state change (if one occurred)
   RecordStateIfChanged();

   //RecordPath() tests the current state and path against the last recorded
   //state and path and adds a new diagnostic record if there was a change.
   //If the state has changed RecordPath would have been called already.
   //If the state has NOT changed the path may have changed so ...
//	if(!bPathRecorded)
//   	RecordPath(ucStatePath);

	//See if the current state and fault code has been selected as a trigger
   //to stop recording diagnostic records.
	CheckTriggers();


} // end of FSMWindSpeed


void HandleHalt( void )
{
   // Flags for recording info on the current halt request
   BOOL haltRequested;
   BOOL haltRequestedNew;
   BOOL haltRequired;
   
   // Variables to remember the current halt positions
   BOOL currentKeySwitch;
   BOOL currentRemoteHalt;
   
   // Static variables to remember the last halt positions
   static BOOL lastKeySwitch;
   static BOOL lastRemoteHalt;

   #GLOBAL_INIT
   {
      // Initialize these to true so that the only way we
      // get a rising edge is to actually force the halt
      lastKeySwitch = TRUE;
      lastRemoteHalt = TRUE;      
   }
   
   // Initialize all of the halt request flags to false
   haltRequested = FALSE;
   haltRequestedNew = FALSE;
   haltRequired = FALSE;
  
   //
   // Read and record the current halt positions
   //
   currentKeySwitch = KeySwitchHalted();
   currentRemoteHalt = gbRemoteHalt;

   //
   // Detect halt requests and set all flags accordingly
   //
   
   // Check if keyswitch is in HALT position
   if (currentKeySwitch == TRUE)
   {
      // Flag halt request
      haltRequested = TRUE;
      
      // Check if this is a new halt request and flag it accordingly
      if (lastKeySwitch == FALSE)
      {
         haltRequestedNew = TRUE;
      }

      // A keyswitch halt clears an ERI halt
      gbRemoteHalt = FALSE;
   }

   // Otherwise check if the ERI has sent a halt command
   if (currentRemoteHalt == TRUE)
   {
      // Flag halt request
      haltRequested = TRUE;
      
      // Check if this is a new halt request and flag it accordingly
      if (lastRemoteHalt == FALSE)
      {
         haltRequestedNew = TRUE;
      }
   }
   
   //
   // Handle requests based on flags
   //
   
   // Only proceed if a halt is requested
   if (haltRequested == TRUE)
   {
      // Default to halt, overriding if necessary (this is the safest approach)
      haltRequired = TRUE;
      
      switch (gucStateWindSpeed)
      {
         // If in HALT already there is no need to change states
         case STATE_HALT:
            haltRequired = FALSE;
            break;
         
         // Some faults override halt, so check for those
         case STATE_FAULT:
            // Brake failure fault overrides halt as long as the brake failure
            // condition persists
            if (gucFaultCode == ERR_BrakeFailure)
            {
               // Can only halt if the brake failure condition has cleared and
               // a new halt request (i.e. an "edge") has just occurred
               if ((CheckBrakeFailureCondition() == FALSE) && 
                     (haltRequestedNew == TRUE))
               {
                  haltRequired = TRUE;
               }
               // Otherwise override the halt
               else
               {
                  haltRequired = FALSE;
               }
            }
            break;
            
         // Any state other than halt or fault will unconditionally go into halt
         default:
            // Do nothing - default is to halt
            break;
   
      }
      
      // Proess the halt only if it is required
      if (haltRequired == TRUE)
      {
         SetState(STATE_HALT);
         gucFaultCode = ERR_NoError;
         DiagnosticPrint( "FSMWindSpeed: [HALT] ...\r\n" );

         // Has gone from a state other than HALT into HALT
         gbHaltedSinceStart = TRUE;
      }      
   }
   
   // Clear remote flag if we didn't halt
   if ((gucStateWindSpeed != STATE_HALT) && (currentRemoteHalt == TRUE))
   {
      gbRemoteHalt = FALSE;         
   }

   
   //
   // Remember the last halt positions
   //
   lastKeySwitch = currentKeySwitch;
   lastRemoteHalt = currentRemoteHalt;

}

void HandleTimers( void )
{
  static ULONG ulOldSecondTimer; // keep history to see if time has changed
  static ULONG ulRunTime;        // time spent running
  static BOOL bFirstPass;        // Let's us know if this is the first pass since updating the count
  #GLOBAL_INIT
  {
    ulRunTime = 0L;
    bFirstPass = TRUE;
    ulOldSecondTimer = SEC_TIMER;
  }

  if ( gucStateWindSpeed == STATE_FREEWHEEL
    || gucStateWindSpeed == STATE_MOTOR
    || gucStateWindSpeed == STATE_GENLO
    || gucStateWindSpeed == STATE_GENHI )  //Count time spent spinning
  {
    if (bFirstPass)  // Is this the first time here since updating hours?
    {
      ulOldSecondTimer = SEC_TIMER;
      bFirstPass = FALSE;   //Set the first pass flag false
    }
    ulRunTime += (SEC_TIMER - ulOldSecondTimer);
    ulOldSecondTimer = SEC_TIMER;
  }
  else //Don't update the run time, just the old time
  {
    ulOldSecondTimer = SEC_TIMER;
  }

  // if sufficient time has elapsed to update hours ...
  if (ulRunTime > 3600L)
  {
    DiagnosticPrint( "HandleTimers: Hours updating ...\r\n" );

    bFirstPass = TRUE;  // Reset the first pass flag
    ulRunTime = 0L;      // Reset the second counter

    // Update the total hrs and service interval hrs in Flash xfer struct ...
    gFlashStruct.ulTotalHours++;
    gFlashStruct.ulServiceHours++;

    // For diagnostics, display the Flash File structure ...
    #ifdef TEST_PRINT
    FileParameterDump();
    #endif

  }
} // end of HandleTimers




///////////////////////////////////////////////////////////////////////////////
// Switch sequence when going from Freewheel to GenLo state
//
// Input Args:     none
// Output Args:    none
// Returns:        none
// Processing:     act as a HAL for digOut()
// Updates:
//   20060718 CH - created GenLoSwitch
void GenLoSwitch( void )
{
   char strTemp[80]; // for diagnostic printout

// Set diagnositc outputs in case we are using them
   sprintf( strTemp, "GenLoSwitch( %d )\r\n" );
   DiagnosticPrint( strTemp );

// update the appropriate ports ...
   digitalOutput( OUTPUT_NEU, 0 ); // open collector => SSR will be ON
  #ifdef GENLO_RESISTOR
   digitalOutput( OUTPUT_RESISTON, 0 );  // open collector => SSR will be ON
  #else
   digitalOutput( OUTPUT_RESISTOFF, 0 ); // open collector => SSR will be ON
  #endif
   OSTimeDly(OS_TICKS_GENLO_RUNCAP);  // wait at least 0.1s
   digitalOutput( OUTPUT_RUNCAP, 0 );       // open collector => SSR will be ON
  #ifdef GENLO_RESISTOR
   OSTimeDly(OS_TICKS_GENLO_RESISTOR);      // wait specified time delay
   digitalOutput( OUTPUT_RESISTOFF, 0 ); // open collector => SSR will be ON
   digitalOutput( OUTPUT_RESISTON, 1 );  // open collector => SSR will be OFF
  #endif

} // end of GenLoSwitch

///////////////////////////////////////////////////////////////////////////////
// Switch motoring relays with time delay
//
// Input Args:     none
// Output Args:    none
// Returns:        none
// Processing:     act as a HAL for digOut()
// Updates:
//   20060718 CH - created Motor Switch
void MotorSwitch( void )
{
   char strTemp[80]; // for diagnostic printout

// Set diagnositc outputs in case we are using them
   sprintf( strTemp, "MotorSwitch( %d )\r\n" );
   DiagnosticPrint( strTemp );

// update the appropriate ports ...
   digitalOutput( OUTPUT_MOTOR, 0 );       // open collector => SSR will be ON
   digitalOutput( OUTPUT_RUNCAP, 0 );       // open collector => SSR will be ON
   OSTimeDly(OS_TICKS_PER_TENTH_SEC);  // wait 100ms
   digitalOutput( OUTPUT_NEU, 0 ); // open collector => SSR will be ON
   digitalOutput( OUTPUT_RESISTOFF, 0 ); // open collector => SSR will be ON

} // end of MotorSwitch

///////////////////////////////////////////////////////////////////////////////
// Upswitch from 120V to 240V
//
// Input Args:     none
// Output Args:    none
// Input Globals:  gFlashStruct
// Returns:        none
// Processing:     act as a HAL for digOut()
// Updates:
//   20060417 DJL - created UpSwitch for going from 120V to 240V
void UpSwitch( void )
{
   char strTemp[80]; // for diagnostic printout

   #ifdef TEST_PRINT
		// Set diagnositc outputs in case we are using them
	   sprintf( strTemp, "UpSwitch( %d )\r\n" );
   	DiagnosticPrint( strTemp );
   #endif

	// log the event to Flash File System ...
   gFlashStruct.ulUpSwitches++; // increment total # Upswitches

   #ifdef TEST_PRINT
		// For diagnostics, display the Flash File structure ...
	   DiagnosticPrint( "Updated UpSwitches ...\r\n" );
   	FileParameterDump();
   #endif

// update the appropriate ports ...
   digitalOutput( OUTPUT_NEU, 1 );       // open collector => SSR will be OFF
   digitalOutput( OUTPUT_RESISTOFF, 1 ); // open collector => SSR will be OFF
   digitalOutput( OUTPUT_RESISTON, 0 );  // open collector => SSR will be ON
   OSTimeDly(OS_TICKS_PER_31_mSEC);  // wait ~31ms
   digitalOutput( OUTPUT_HOT2, 0 );      // open collector => SSR will be ON
   OSTimeDly(OS_TICKS_PER_4th_SEC);      // wait specified time delay
   digitalOutput( OUTPUT_RESISTOFF, 0 ); // open collector => SSR will be ON
   digitalOutput( OUTPUT_RESISTON, 1 );  // open collector => SSR will be OFF

} // end of UpSwitch

///////////////////////////////////////////////////////////////////////////////
// Downswitch from 240V to 120V
//
// Input Args:     none
// Output Args:    none
// Input Globals:  gFlashStruct
// Returns:        none
// Processing:     act as a HAL for digOut()
// Updates:
//   20060417 DJL - created DownSwitch for going from 240V to 120V
void DownSwitch( void )
{
   char strTemp[80]; // for diagnostic printout

// Set diagnositc outputs in case we are using them
   sprintf( strTemp, "DownSwitch( %d )\r\n" );
   DiagnosticPrint( strTemp );

// do the SSR switching sequence ...
   digitalOutput( OUTPUT_RUNCAP, 1 );    // open collector => SSR will be OFF
   digitalOutput( OUTPUT_RESISTOFF, 1 ); // open collector => SSR will be OFF
   digitalOutput( OUTPUT_RESISTON, 0 );  // open collector => SSR will be ON
   OSTimeDly(OS_TICKS_PER_16th_SEC);     // wait specified time delay
   digitalOutput( OUTPUT_HOT2, 1 );      // open collector => SSR will be OFF
   digitalOutput( OUTPUT_RESISTOFF, 0 ); // open collector => SSR will be ON
   digitalOutput( OUTPUT_RESISTON, 1 );  // open collector => SSR will be OFF
   OSTimeDly(OS_TICKS_PER_31_mSEC);      // wait ~31ms
   digitalOutput( OUTPUT_NEU, 0 );       // open collector => SSR will be ON
   OSTimeDly(OS_TICKS_PER_8th_SEC);      // wait specified time delay
   digitalOutput( OUTPUT_RUNCAP, 0 );    // open collector => SSR will be ON

} // end of DownSwitch

///////////////////////////////////////////////////////////////////////////////
//
// Input Args:     none
// Output Args:    none
// Input Globals:  gFlashStruct
// Returns:        none
// Processing:     count number of motor starts
// Updates:
//   20060417 DJL - created for counting motor starts
void MotorStart( void )
{
   char strTemp[80]; // for diagnostic printout

   sprintf( strTemp, "MotorStart( %d )\r\n" );
   DiagnosticPrint( strTemp );

   gFlashStruct.ulMotorStarts++; // increment total # Motor Starts

   #ifdef TEST_PRINT
	   // For diagnostics, display the Flash File structure ...
   	DiagnosticPrint( "Updated MotorStarts ...\r\n" );
	   FileParameterDump();
   #endif

} // end of MotorStart

///////////////////////////////////////////////////////////////////////////////
// Set SSR switch according to input
// 0 ==> SSR is activated (contactor is closed)
// NOTE: digOut() accounts for polarity inversion in open collector output
//
// Input Args:     {OFF, ON}
// Output Args:    none
// Input Globals:  gFlashStruct
// Returns:        none
// Processing:     act as a HAL for digOut()
// Updates:
//   20060417 DJL - created for handling motor starts
void SSR_Switch( void )
{
   char strTemp[80]; // for diagnostic printout
   int i;

   // update the appropriate ports ...
   for( i = 0; i < 7; i++ )
   {
     if (gbSSR_On[i] != 0)
     {
       digitalOutput( i, 0 );       // close connector => SSR will be ON
     }
     else
     {
       digitalOutput( i, 1 );       // open connector => SSR will be OFF
     }
   }
} // end of SSR_Switch


// Updates the generator control, setting the proper state and controlling 
// the SSRs which connect the generator and it's auxillary components
//
// Inputs:
//    None
// Returns:
//    void
void UpdateGenerator( void )
{
   // Update the generator's finite state machine
   UpdateGenState();
   
   // Set the generator SSRs based on the current state
   SetGenSSRs();
}

// Updates the generator finite state machine, based primarily on the current rotor speed
//
// Inputs:
//    None
// Returns:
//    void
void UpdateGenState( void )
{
   // Temp variable for the selected minimum 240V generation time
   ULONG ulMinTime240V;

   // Update the FSM 
   switch(gGenState)
   {
      // Generator is disconnected 
      case (eDisconnected):
         
         // If freewheeling at or above synchronous, connect the generator.
         // Use either sensor for this decision
         if ( (RotorRPMGet() > RpmLssSynchronousGet()) || 
               (RPMHSSGet() > RpmLssSynchronousGet()) ) 
         {
            // Switching sequence to go from disconnected to 120V state
            GenLoSwitch();
            
            // reset timer and slip sum
            ulGenSwitchOnTime = SEC_TIMER;
            gfSpeedSlipSum = 0.0;
            
            // Set the new state
            gGenState = eConnected120V;            
         }
         
         // If freewheeling and the main controller state goes into motoring
         // state, the generator should be connected as a motor
         else if (gucStateWindSpeed == STATE_MOTOR)
         {
            // Switching sequence to go from disconnected to motor
            MotorSwitch();
            
            // Set the new state
            gGenState = eConnectedMotor;
         }
         break;
       
      // Generator is connected at 120V
      case (eConnected120V):
      
         // Disconnect if we meet three criteria: the averaged RPM is well
         // below sycnhronous, the slipsum exceeds the negative limit, and we 
         // have satisified the minumum time required connected
         if ( (gfRPMHSSAvg < RpmOfflineGet()) && 
               (gfSpeedSlipSum < kfSpeedSlipSetpoint) && 
               ((SEC_TIMER - ulGenSwitchOnTime) > kulMinTimeGenOn) )
         {
            // Set the new state
            gGenState = eDisconnected;            
         }
         
         // Upswitch to 240V if either LSS or HSS RPMs are above the upswitch
         // threshold RPM
         else if ((RotorRPMGet() > RpmUpSwitchGet()) || 
                  (RPMHSSGet() > RpmUpSwitchGet()) )
         {
            // Switching sequence for upswitching
            UpSwitch();
            
            // Reset timer and slip sum
            ulGenSwitchHiTime = SEC_TIMER;
            gfHiSpeedSlipSum = 0.0;
            
            // Set the new state
            gGenState = eConnected240V;            
         }      
         break;
               
      // Generator is connected at 240V
      case (eConnected240V):

         // Choose the minimum 240V generation time: use the standard value 
         // unless the brakes have just been applied
         if ((SEC_TIMER - ulTimeBrakeStop) < kul240VBrakeResponseDelay)
         {
            ulMinTime240V = kulMinTime240VWithBrakes;
         }
         else
         {
            ulMinTime240V = kulMinTime240V;
         }

         // Downswitch if we meet three criteria: the averaged RPM is below
         // the downswitch threshold, the slipsum exceeds the negative limit,
         // and we have satisified the minumum time required connected at 240V
         if ( (gfRPMHSSAvg < RpmDownSwitchGet()) &&  
               (gfHiSpeedSlipSum < kfHiSpeedSlipSetpoint) &&
               ((SEC_TIMER - ulGenSwitchHiTime) > ulMinTime240V) )
         {
            // Switching sequence for downswitching
            DownSwitch();

            // Set the new state
            gGenState = eConnected120V;
         }      
         break;
         
      // Generator is connected as a motor
      case (eConnectedMotor):
         if (gucStateWindSpeed != STATE_MOTOR)
         {
            gGenState = eDisconnected;
         }
         break;   
   }

}

// Sets the SSRs, which connect the generator and it's auxillary components,
// according to the current generator state machine state
//
// Inputs:
//    None
// Returns:
//    void
void SetGenSSRs( void )
{
   int i;

   // Start by turning off all SSRs
   for ( i = 0; i < 7; i++ )
   {
      // Turn off all SSR's except for the watchdog
      if (i != OUTPUT_WATCHDOG)
      {
         gbSSR_On[i] = OFF;
      }
   }

   // Now turn on the ones we want based on the generator state
   switch(gGenState)
   {
      case (eDisconnected):      
         // Leave all SSRs disconnected
         break;

      case (eConnected120V):
         // Connect across L1 and Neutral, with the run cap
         gbSSR_On[OUTPUT_NEU]= ON;
         gbSSR_On[OUTPUT_RESISTOFF]= ON;
         gbSSR_On[OUTPUT_RUNCAP]= ON;
         break;

      case (eConnected240V):
         // Connect across L1 and L2, with the run cap
         gbSSR_On[OUTPUT_HOT2]= ON;
         gbSSR_On[OUTPUT_RESISTOFF]= ON;
         gbSSR_On[OUTPUT_RUNCAP]= ON;
         break;
         
      case (eConnectedMotor):
         // Connect across L1 and L2, with the run cap and with the motor
         // relay (which switches the windings and adds the start cap 
         // by controlling other relays)
         gbSSR_On[OUTPUT_MOTOR]= ON;
         gbSSR_On[OUTPUT_RUNCAP] = ON;
         gbSSR_On[OUTPUT_NEU]= ON;
         gbSSR_On[OUTPUT_RESISTOFF]= ON;
         break;   
   }
   
   // Now propogate these settings to the SSRs
   SSR_Switch();
}


///////////////////////////////////////////////////////////////////////////////
// Parse the incoming client commands.  Return TRUE iff message was OK.
//
// Input Args:     none
// Output Args:    none
// Input Globals:  gucBufferParse
// Output Globals: gucTowerCommand
// Returns:        TRUE iff message parsed OK
// Processing:     scan through fields in parse buffer
// Updates:
//   20041128 RSF - original version
//   20041203 RSF - handle service hours reset here
BOOL MessageParse( char *pToParse )
{


   //All valid commands received must begin with this sequence
	const static char cCommandHeader[]="@!C";

  	char 					*pNext;  // pointer into gucBufferParse
	int 					i;			//Loop counter
   int					iLength; //Length of the string to be parsed


   iLength = strlen(pToParse);

   //Make sure we have enough characters for the minimum length
   //of valid string.
   if(iLength < sizeof(cCommandHeader)+2) return FALSE;

   //The last character of all valid strings is "#"
	if(*(pToParse+ iLength-1) != '#') return FALSE;


   //Make sure the begining of the string matches the
   //expected header
   for(i=0;i<sizeof(cCommandHeader)-1;i++)
   	if(*(pToParse+i) != cCommandHeader[i]) return FALSE;

	//The first character after the header must be a digit
  	if (!isdigit((int)( *(pToParse + sizeof(cCommandHeader) - 1 ))) ) return FALSE;


   //Convert the command number from ASCII to UINT
   guiTowerCommand = (UINT) (ULONG) atol( pToParse+sizeof(cCommandHeader)-1 );

   #ifdef TEST_PRINT
   	if(guiTowerCommand != 0)
      {
      	printf("Tower command=%d\r\n",guiTowerCommand);
      }

   #endif

   //Before the password is accepted only the following commands will be
   //processed.
   if(gbPasswordAccepted         			||
   	guiTowerCommand==CMD_Hello 			||
		guiTowerCommand==CMD_Password 		||
		guiTowerCommand==CMD_RequestPassKey )
   {
		ExecuteTowerCommand(pToParse);
   }

  return TRUE;
} // end of MessageParse

///////////////////////////////////////////////////////////////////////////////
// Set the Rotor Brake Output line according to the argument
// 0 ==> rotor brake is released (contactor is closed)
// 1 ==> rotor brake is applied (contactor is open)
// NOTE: Polarity is inverted
// NOTE: digOut() accounts for polarity inversion in open collector output
//
// Input Args:     {OFF, ON}
// Output Args:    none
// Input Globals:  gFlashStruct
// Returns:        none
// Processing:     act as a HAL for digOut()
// Updates:
//   20040224 RSF - original version
//   20041027 RSF - fix output bit selection per CH
//   20041209 RSF - if state has changed to ON, log to Flash File System
void RotorBrake( BOOL bOn )
{

   char strTemp[80]; // for diagnostic printout

   #GLOBAL_INIT
   {
     gbBrakeState = 2; // to force display update on 1st pass
   }

   if (bOn != gbBrakeState)
   {
     sprintf( strTemp, "RotorBrake( %d )\r\n", bOn );
     DiagnosticPrint( strTemp );

     // 20041209 RSF - if state has changed to ON, log to Flash File System ...
     if ((bOn == ON) && (gbBrakeState == OFF))
     {
       gFlashStruct.ulBrakeStops++; // increment total # brake stops
       
       // Record the time of the last brake stop
       ulTimeBrakeStop = SEC_TIMER;

		 #ifdef TEST_PRINT
	       // For diagnostics, display the Flash File structure ...
   	    DiagnosticPrint( "Updated Brake Stops ...\r\n" );
      	 FileParameterDump();
		 #endif
     }

     // Update history ...
     gbBrakeState = bOn;
   }

   // update the appropriate port ...
   if (bOn != 0)
   {
     digitalOutput( OUTPUT_BRAKE, 1 ); // open collector => SSR will be OFF
          // 20050708 ACH changed 0 to 1 here, 1 to 0 in next call
  }
   else
   {
     digitalOutput( OUTPUT_BRAKE, 0 ); // open collector => SSR will be ON
   }
} // end of RotorBrake

// Returns the state of the brake digital output
//
// Inputs:
//    None
// Returns:
//    The current state of the brakes (BOOL, either ON or OFF)
BOOL GetBrakeState( void )
{
   return gbBrakeState;
}

// Checks for the brake failure condition
//
// Inputs:
//    None
// Returns:
//    BOOL indicating if the brake failure condition is met (TRUE) or not (FALSE)
BOOL CheckBrakeFailureCondition( void )
{
   // A brake failure is when either sensor reports RPMs above the brake-check
   // RPM while the brakes are on
   return ((gfRPMLSSAvg > kfRPM_BrakeCheck || RPMHSSGet() > kfRPM_BrakeCheck) && 
            (GetBrakeState() ==  ON));
}

///////////////////////////////////////////////////////////////////////////////
// Compute rotor RPM from counts per second
// NOTE: We'll limit input counts to 6000 to prevent numerical overflow
//
//
// Input Args:     counts per second
// Output Args:    none
// Input Globals:  none
// Output Globals: none
// Returns:        rotor RPM
// Processing:     units conversion from Hertz to RPM for H20 shaft encoder
// Updates:
//   20040224 RSF - original version
//   20041028 RSF - use float arg to allow easier integration time changes
float RotorCountsToRPM( float fCountsPerSecond )
{
   float fCounts; // 20041028 RSF - do conversion from float to UINT here

   // perform input range limiting ...
   // 20041028 RSF - handle float argument ...
   if (fCountsPerSecond < 0) // too low ...
   {
     fCountsPerSecond = 0.0;
   }
   else if (fCountsPerSecond > 10000.0) // too high ...  20050831 ACH increased
   {
     fCountsPerSecond = 10000.0;
   }
   // final check--conversion constant for LSS RPM
   // RPM = [counts per sec]/[2048 counts per rev]*[60 sec/min]
   // 170 rpm = 5802.6 Hz from 2048 encoder     (use 0.058594 for 1024, 0.029297 for 2048)
   fCounts = 0.058594 * fCountsPerSecond;  // conversion to RPM here  1024 pulses/rev

   return fCounts;
} // end of RotorCountsToRPM

///////////////////////////////////////////////////////////////////////////////
// Accessor function for global rotor RPM storage
//
// Input Args:     none
// Output Args:    none
// Input Globals:  gfRPMLSS
// Output Globals: none
// Returns:        none
// Processing:     retrieve value from global
// Updates:
//   20040224 RSF - original version
float RotorRPMGet( void )
{
   #ifdef TESTING
   #GLOBAL_INIT
   {
     guiTestingRotorRPM = 190;
   }
   return guiTestingRotorRPM;
   #else // #ifdef TESTING
   return  gfRPMLSS;
   #endif // #ifdef TESTING
} // end of RotorRPMGet

///////////////////////////////////////////////////////////////////////////////
// Mutator function for global rotor RPM storage
// NOTE: may want to perform input argument limiting
//
// Input Args:     rotor RPM
// Output Args:    none
// Input Globals:  none
// Output Globals: gfRPMLSS
// Returns:        none
// Processing:     store argument to global
// Updates:
//   20040224 RSF - original version
void RotorRPMSet( float fRPMLSS )
{
   gfRPMPrev = gfRPMLSS;   // Save previous value
   gfRPMLSS = fRPMLSS;
} // end of RotorRPMSet

///////////////////////////////////////////////////////////////////////////////
// Accessor function for global AeroComm message counter
//
// Input Args:     none
// Output Args:    none
// Input Globals:  guiSequenceNumber
// Output Globals: none
// Returns:        none
// Processing:     retrieve value from global
// Updates:
//   20040308 RSF - original version
UINT SequenceNumberGet( void )
{
   return guiSequenceNumber;
} // end of SequenceNumberGet

///////////////////////////////////////////////////////////////////////////////
// Accessor function for global AeroComm message counter
//
// Input Args:     new sequence number
// Output Args:    none
// Input Globals:  none
// Output Globals: guiSequenceNumber
// Returns:        none
// Processing:     set global value
// Updates:
//   20040308 RSF - original version
void SequenceNumberSet( UINT uiSequenceNumber )
{
   guiSequenceNumber = uiSequenceNumber;
} // end of SequenceNumberSet

///////////////////////////////////////////////////////////////////////////////
// Receive the AeroComm characters in the global buffer gucBufferIn[]
// Return FALSE until a complete and validated message arrives.
// If an invalid message is received, reset the input pointer and start again.
//
// Input Args:     none
// Output Args:    none
// Input Globals:  gucBufferIn[], gucIndexInput
// Output Globals: gucBufferIn[], gucIndexInput
// Returns:        FALSE until a complete, validated message arrives
// Processing:
// Updates:
//   20040308 RSF - original version
BOOL SerialReceiveAeroComm( void )
{
   char strTemp[80]; // for diagnostic printouts
   int iChar; // (possible) input characters go here

   iChar = SerialGetChar(); // returns -1 if a new character is not ready

   // loop, continuing to process characters until none are left, or a CR
   // is seen, indicating a complete line ...
   while (iChar != -1)
   {
     // CH sprintf( strTemp, "RF in = %c (%02x)\r\n", iChar, iChar );
     // CH DiagnosticPrint( strTemp );

     // if we see a start char sequence, restart ...
     if (iChar == CHAR_START0) // restart the sequence, stored below ...
     {
       memset( gucBufferIn, 0x00, sizeof( gucBufferIn ));
       memset( gucBufferParse, 0x00, sizeof( gucBufferParse ) );
       gucIndexInput = 0; // restart at buffer beginning
     }

     // only store if not a terminator character (CR or LF) ...
     if ((iChar != CHAR_CR) && (iChar != CHAR_LF))
     {
       gucBufferIn[gucIndexInput] = (UCHAR) iChar;
       gucIndexInput++;
     }

     // if message is longer than BUFFER_RECEIVE_SIZE, restart
     if (gucIndexInput >= (BUFFER_RECEIVE_SIZE - 20)) // overflow!
     {
       memset( gucBufferIn, 0x00, sizeof( gucBufferIn ));
       memset( gucBufferParse, 0x00, sizeof( gucBufferParse ) );
       gucIndexInput = 0; // restart at buffer beginning
       // <<< could increment rejected messages count here >>>
       return FALSE; // indicate failure to caller
     }

     // if the last character was a CR and we had a complete start sequence,
     // "seal" the string and return a TRUE to the caller ...
     if ((iChar == CHAR_CR) && (gucBufferIn[1] == CHAR_START1))
     {
       gucBufferIn[gucIndexInput] = '\0'; // null-terminate the string

       // copy message to working buffer ...
       memset( gucBufferParse, 0x00, sizeof( gucBufferParse ) );
       memcpy( gucBufferParse, gucBufferIn, strlen( gucBufferIn ) );
       memset( gucBufferIn, 0x00, sizeof( gucBufferIn )); // clear for restart
       gucIndexInput = 0; // to restart filling of buffer

       // empty any remaining characters from receive buffer ...
       // ClearReceiveBuffer();
       return TRUE; // only when we get a complete message, return TRUE
     }

     // get next character ...
     iChar = SerialGetC(); // returns -1 if a new character is not ready
   } // end while (iChar != -1)

   // if we get here, must not have a complete message or no new characters ...
   return FALSE;
} // end of SerialReceiveAeroComm

///////////////////////////////////////////////////////////////////////////////
// Transmit a null-terminated string to the AeroComm.
//
// Input Args:     pointer to null-terminated string
// Output Args:    none
// Input Globals:  none
// Output Globals: none
// Returns:        none
// Processing:
// Updates:
//   20040308 RSF - original version
void SerialSendAeroComm( char * pOutgoingMessage )
{
   int 	length;
	int 	toSend;


   if( gbTCPConnected )
   {
   	toSend=length=strlen(pOutgoingMessage);
      while(toSend>0)
      {
      	rb_addChar(&grbTCPoutgoing,pOutgoingMessage[length-toSend]);
         toSend--;
      }
   }
   else
   {
   	//make sure there is room in the buffer
   	while ( serEwrFree() < strlen(pOutgoingMessage) );

   	SerialPuts( pOutgoingMessage );
   }

} // end of SerialSendAeroComm


void SerialSendWatchDog( char * pOutgoingMessage )
{
   	//make sure there is room in the buffer
   	while ( serFwrFree() < strlen(pOutgoingMessage) );
   	serFputs( pOutgoingMessage );
      #ifdef TEST_PRINT
      	printf("SerF->%s",pOutgoingMessage);
      #endif

} // end of SerialSendWatchDog



///////////////////////////////////////////////////////////////////////////////
// Initialize all hardware and variables
//
// Input Args:     BOOL bNewFirmware - indicates new firmware has been 
//                   installed (or SRAM needs to be re-initialized)
// Output Args:    none
// Input Globals:  all persisted variables
// Output Globals: all persisted variables
// Returns:        none
// Processing:
// Updates:
//   20040219 RSF - original version
//   20041202 RSF - initialize communications structures
//   20041203 RSF - initialize Flash Memory structures
debug void StateInitialize(BOOL bNewFirmware)
{
   char strTemp[80]; // for diagnostic printouts
   int iRet; // to capture initialization function return values
   int i;

   DiagnosticPrint( "Entering StateInitialize ...\r\n" ); // diagnostic


   //
   // Hardware Initialization:

   // Initialize controller digital i/o hardware ...

   // Turn off all diagnostic LEDs ...
   ledOut( LED0, 0 ); // DS1
   ledOut( LED1, 0 ); // DS2
   ledOut( LED2, 0 ); // DS3
   ledOut( LED3, 0 ); // DS4

   //
   // Global Variable Initialization ...


   guiShaftEncoderCount = 0;  // for rotor speed measurements
   guiAnemometerCount = 0;    // positive edges, consumer should clear
   gbAnemometerPolarity = 0;  // 1 => anemometer output signal was HIGH
   guiRPMHSSCount = 0;        // positive edges, consumer should clear
   gbRPMHSSPolarity = 0;      // 1 => HSS endcoder output signal was HIGH

   giParameterID = eNormal;   // start with normal controller parameters
                              // 20051020 ACH added this variable

   gulTimeHistory = SEC_TIMER;  // program start time, sec

   ulTimeMotorStart = SEC_TIMER - kulMotorTimeOut;  // set to initial value, sec

   // Wait kulCnctWaitTime to satisfy utility timeout requirements
   gulTimeCutInOk = SEC_TIMER + kulCnctWaitTime;

   // Initialize flag to indicate we have not HALTED yet
   gbHaltedSinceStart = FALSE;

   // Error status
   gucFaultCode = ERR_NoError;

   // Communications parameters ...
   guiTowerCommand = CMD_NULL; // set RUN mode

   // Initialize the time of the last brake stop to now
   ulTimeBrakeStop = SEC_TIMER;
   
   // Place system actuators in known states ...
   RotorBrake( ON ); // rotor brake is APPLIED
   gGenState = eDisconnected;
   SetGenSSRs();

   // Initialize Model Parameters
   ModelParamsSet();

   // Initialize rotor RPM and Anemometer values ...
   RotorRPMSet( 0.0 );
   gfRPMPrev = 0.0; //Set previous RPM value to zero
   WindSpeedMPSSet( 0.0 ); // TaskMeasureSpeed() will update to non-zero value
   RPMHSSSet( 0.0 ); // TaskMeasureSpeed() will update to non-zero value
   gfSpeedSlipSum = 0.0;  // integrated speed slip value
   gfHiSpeedSlipSum = 0.0;  // integrated Hi speed slip value

   // Initialize wind speed record synchronization data
   gulLastRecordPending = 0;
   gulLastRecordComplete = 0;

   // Initialize outbound message counter ...
   SequenceNumberSet( 0 );

   //

   // hex to binary table used in many statements below:
   //  hex    binary              hex    binary
   // 0x00 =  00 00 00 00         0x01 = 00 00 00 01
   // 0x02    00 00 00 10         0x03   00 00 00 11
   // 0x04    00 00 01 00         0x05   00 00 01 01
   // 0x06    00 00 01 10         0x07   00 00 01 11
   // 0x08    00 00 10 00         0x09   00 00 10 01
   // 0x0a    00 00 10 10         0x0b   00 00 10 11
   // 0x0c    00 00 11 00         0x0d   00 00 11 01
   // 0x0e    00 00 11 10         0x0f   00 00 11 11

   // for example
   // 0xb5    10 11 01 01  (Here bits 1, 3 and 6 are zero--first bit is bit 0)
   // 0x35    00 11 01 01  (Now using four inputs, bits 1, 3, 6, and 7)

   // Initialize interrupt handlers ...
   // Use Help I/O Registers for info on the acronyms like PEDDR, I1CR, etc.

   // Set Port E pin directions (1 = output, 0 = input) see help for I/O registers
   // see online BL2500 docs for table relating PI numbers to IN numbers
//   WrPortI( PEDDR, &PEDDRShadow, 0xb5 ); // E1 = int1a = j11:1 = IN00 = encoder
   WrPortI( PEDDR, &PEDDRShadow, 0x35 ); // E1 = int1a = j11:1 = IN00 = encoder
                                         // E3 = j11:2 = IN01 = anemometer
                                         // E6 = j11:3 = IN02 = HSS encoder pulses
                                         // E7 = j11:4 = IN03 = Grid status relays

   // Initialize external interrupt (to monitor shaft speed) ...
   SetVectExtern3000( 1, ISR_ExternalInterrupt ); // point vector to ISR
   WrPortI( I1CR, NULL, 0x09 ); // int1a at port E1, rising edge, en prio 1
   // can replace previous line with one of these to change settings:
//  WrPortI( I1CR, NULL, 0x0a ); // int1a at port E1, rising edge, en prio 2
//  WrPortI( I1CR, NULL, 0x06 ); // int1a at port E1, falling edge, en prio 2
// might try falling edge (bits 3 and 2 = 01) or higher priority (larger value)
// e.g. 0x06 = 01 10 = falling edge, priority 2)

   // Initialize periodic interrupt (to sample Anemometer & HSS lines)
   //   at a fixed rate that is > the incoming pulse rates
   SetVectIntern( 0x0b, ISR_Anemometer );  //calls ISR_Anemometer routine on each
   //   Timer B interrupt
   // NOTE: may want level 2 or 3 interrupt here ...
//  WrPortI( TBCR, &TBCRShadow, 0x01 ); // perclk / 2 interrupt level = 1
   WrPortI( TBCR, &TBCRShadow, 0x09 ); // perclk / 16 interrupt level = 1
   // match registers are reset to 0x00 by ISR_Anemometer.  This means
   // there will be a match (interrupt) at TimerB Clock/1024 interval.
   // perclk/16 is approx. 29.4 MHz/(16*1024) = 1.79 kHz.  If HSS pulse at
   // 220 RPM/0.30807 = 714 Hz then 1.79/0.714= 2.5 interrupts
   // per HSS pulse, should be okay.
   WrPortI( TBL1R, NULL, 0x00 ); // initial match register
   WrPortI( TBM1R, NULL, 0x00 ); // initial match register
   WrPortI( TBCSR, &TBCSRShadow, 0x03 ); // en timer B and B1 match interrupts


   // Initialize RS232 Serial Interface ...

   rb_reset(&grbTCPoutgoing);	//Reset the tcp outgoing ringbuffer



   iRet = SerialOpen( SERIAL_BAUD ); // default mode is 3-wire RS232
   sprintf( strTemp, "StateInitialize: serEopen() returns: %d\r\n", iRet );
   DiagnosticPrint( strTemp );
   SerialWrFlush();
   SerialRdFlush();


 	serFopen(9600); 		  	//Serial port F for external watch dog
	serFwrFlush();				//Flush the write buffer
 	serFrdFlush();   			//Flush the read buffer

   //External watch dog has not been programed yet. We will wait a few seconds
   //before we attempt to program it, in case it needs time to power up.
   //After we program it we will set gbExtWatchDogSet to TRUE.
	gbExtWatchDogSet=FALSE;
	gulExtWDConfigTimeout=kulWDPwrUpDelay;

   
   //
   // State-machine initialization
   //
   
   // If there's new firmware (or if the SRAM is being re-initialized), set
   // the "remote halt" flag to true so the system starts up in the halt state.
   if (bNewFirmware == TRUE)
   {
      gbRemoteHalt = TRUE;
   }
       
   // Extract state information from flash struct
   gucFaultCode         = (UINT) ((gFlashStruct.ulReserved[1] / FLASH_FAULT_CODE_DIGIT) % 10L);
   gucStateWindSpeed    = (UINT) ((gFlashStruct.ulReserved[1] / FLASH_CURRENT_STATE_DIGIT) % 10L);
   gucStateHistory[0]   = (UINT) ((gFlashStruct.ulReserved[1] / FLASH_PAST_STATE_1_DIGIT) % 10L);
   gucStateHistory[1]   = (UINT) ((gFlashStruct.ulReserved[1] / FLASH_PAST_STATE_2_DIGIT) % 10L);   

	// Ensure the controller can only start in Fault, Halt, or Calm.
   // Any prior state other than Fault or Halt should result in the controller
   // starting in Calm.
	switch(gucStateWindSpeed)
   {
      // If Fault or Halt, leave the state alone
   	case	STATE_FAULT:
      case	STATE_HALT:
      	break;

      // Otherwise, force the state to Calm
      default:
	    	SetState(STATE_CALM);
         
         // Clear any previous falut code
   	   gucFaultCode = ERR_NoError;
         break;
   }

} // end of StateInitialize

///////////////////////////////////////////////////////////////////////////////
// Return the status of the grid monitoring relays
// 1 ==> grid fault is present  (high voltage on dig input 03)
// 0 ==> no grid fault detected
//
// Input Args:     none
// Output Args:    none
// Input Globals:  none
// Output Globals: none
// Returns:        grid status (see above)
// Updates:
//   20060628 ACH - original version
BOOL GridFault( void )
{

#ifdef GRID_BYPASS
  return 0;
#else
  return digIn( INPUT_GRIDSTATUS );
#endif

  } // end of GridFault


///////////////////////////////////////////////////////////////////////////////
// Return the status of the RESTART button
// 1 ==> Put turbine in normal operation
// 0 ==> Put turbine in HALT state
//
// Input Args:     none
// Output Args:    none
// Input Globals:  none
// Output Globals: none
// Returns:        RESTART button status (see above)
// Updates:
//   20060912 DJL - original version
BOOL KeySwitchHalted( void )
{

  return digIn( INPUT_RESTART );

}

///////////////////////////////////////////////////////////////////////////////
// Return the status of the TESTSWITCH button
// 1 ==> Put turbine in normal operation
// 0 ==> Put turbine in Commissioning Test ready
//
// Input Args:     none
// Output Args:    none
// Input Globals:  none
// Output Globals: none
// Returns:        TESTSWITCH button status (see above)
// Updates:
//   20070127 DJL - original version
BOOL CommissionTest( void )
{

  return digIn( INPUT_TESTSWITCH );

} // end of CommissionTest

// Indicates if a test is currently active
BOOL TestActive( void )
{
  return giParameterID != eNormal;
}

///////////////////////////////////////////////////////////////////////////////
// Task to communicate via AeroComm RF modem
//
// Input Args:     pointer to data (ignored)
// Output Args:    none
// Input Globals:  none
// Output Globals: none
// Returns:        none
// Processing:     wait for incoming message and then send status
// Updates:
//   20040308 RSF - original version
//   20041222 RSF - update output string format
//   20050106 RSF - include FSM state in status
void TaskAeroCommReceive( void *pData )
{
   pData = pData; // to prevent compiler warning
   DiagnosticPrint( "Entering TaskAeroCommReceive ...\r\n" ); // diagnostic

   // State processing ...
   while (TRUE)
   {
     // handle new messages from the OP6810 Home Unit ...
     if (SerialReceiveAeroComm() == TRUE) // complete and valid message ...
     {

     		if( MessageParse(gucBufferParse) == TRUE)
         {
      		ledOut( 3, 1 ); // DS4 ON
		   	OSTimeDly( OS_TICKS_PER_TENTH_SEC/2 ); // keep DS4 LED on for 100 ms
   			ledOut( 3, 0 ); // DS4 OFF
         }
     } // end of if (SerialReceiveAeroComm() == TRUE)

//     else if(pRecXmitter!=NULL)
//     		SendMainRecords();

     OSTimeDly( OS_TICKS_PER_TENTH_SEC*2 ); // run at a 20 Hz rate
   } // end of while (TRUE)
} // end of TaskAeroCommReceive




///////////////////////////////////////////////////////////////////////////////
// Main Thread processing task.  This loop executes continuously.
//
// Input Args:     data pointer (unused)
// Output Args:    none
// Input Globals:  none
// Output Globals: none
// Returns:        never returns
// Processing:
// Updates:
//   20040219 RSF - original version
//   20041203 RSF - include service interval and total hour timer updates
//   20041210 RSF - update Flash if required
//   20041214 RSF - move Flash updates to separate routine
void TaskMainThread( void *pData )
{
   UINT uiLED; // for LED pattern on startup
//   UINT uiVer; // for LED pattern indicating version number

   // State Entry Actions ...
   pData = pData; // prevent compiler warning
   DiagnosticPrint( "Entering TaskMainThread ...\r\n" ); // diagnostic


   // Produce startup pattern on LEDs ...
   for (uiLED = 0; uiLED < 4; uiLED++)
   {
     ledOut( uiLED, 1 ); // ON
     OSTimeDly( OS_TICKS_PER_TENTH_SEC ); // keep LED on for 100 ms
     ledOut( uiLED, 0 ); // OFF
   }

   // State Processing ...

      // Start virtual watchdog timer for Main Thread...
   giWDT_main = VdGetFreeWd( 38 ); // (38 - 1) / 16 ==> 2.31 sec



   // infinite processing loop ...
   while (TRUE)
   {
     // Handle total run time and service interval timers ...
     HandleTimers();

     // For testing only, parse keypresses ...
     #ifdef TESTING
     TestingParseKeypress();
     #endif // #ifdef TESTING

     // Perform passes through the Finite State Machines ...
     // NOTE: FSMWindSpeed() includes internal delays and watchdog hits ...
     FSMWindSpeed();

     // Count HALT-switch toggles (for factory reset)
     CountSwitchToggles();

     // Handle Flash Memory updates ...
//     HandleFlashUpdates();

     WatchdogHit(giWDT_main); // this is the main thread, hit watchdog here
     OSTimeDly( OS_TICKS_PER_TENTH_SEC ); // run at 10 Hz rate
   } // end of while (TRUE)
} // end of TaskMainThread

///////////////////////////////////////////////////////////////////////////////
// Task to measure rotor and anemometer speeds
//
// Input Args:     pointer to data (ignored)
// Output Args:    none
// Input Globals:  guiShaftEncoderCount, guiAnemometerCount, guiRPMHSSCount
// Output Globals: guiShaftEncoderCount, guiAnemometerCount, guiRPMHSSCount
// Returns:        none
// Processing:     capture counts, perform unit conversions, store results
// Updates:
//   20040224 RSF - original version
//   20041028 RSF - use 0.5S rotor sample and 5.0S anemometer sample per CH
//   20050421 ACH - changed rotor sample time to 0.2s
//   20050505 ACH - Added HSS RPM calcs at 5s sampling rate
//   20050510 ACH - Added time averaging of RPMLSS and WS using first order filter
void TaskMeasureSpeeds( void *pData )
{

   char strTemp[80];
   int i;

   UINT uiShaftEncoder; // temp for computation
   UINT uiAnemometer;   // temp for computation
   UINT uiRPMHSS;       // temp for computation
   UINT uiPass1s;   // 20051130 ACH - count passes for HSS speed timing
   UINT uiPass5s;   // 20041028 RSF - count passes for anemometer timing
   float fFreq;   // 20050506 ACH counter frequency in Hz
   UINT uiRPMLSSSampPerSec;  // 20050421 ACH - Number of RPMLSS measurements per sec
   ULONG ulOldTime_RPMLSS;   // 20050505 ACH - last time (ms) we got RPMLSS counts
   ULONG ulOldTime_RPMHSS;   // 20050505 ACH - last time (ms) we got RPMHSS counts
   ULONG ulOldTime_WS    ;   // 20051130 ACH - last time (ms) we got wind speed counts
   float fPower1s;  // temp variable for accumulating current 1s power average

   float fDTime_RPMHSS;      // 20050505 ACH -  inverse of elapsed time (1/sec) for RPMHSS counts
   float fDTime_RPMLSS;      // 20050505 ACH - inverse elapsed time (1/sec) for RPMLSS counts
   float fDTime_WS;          // 20051130 ACH - inverse elapsed time (1/sec) for wind speed counts

   static float fRotorRPM_prev;     // 20061228 DJL - previous rotor RPM

   // final check.  are filter factors set?
   const static float kfAvgFactor_WS = 0.9;  //filter factor for average wind speed (0=no filter) avg T ~ 5s/(1-f)
   const static float kfAvgFactor_LSSRPM = 0.9;  //filter factor for avg RPMLSS, avg=f*avg+(1-f)*new, avg T~0.1s/(1-f)
   const static float kfAvgFactor_HSSRPM = 0.7;  //filter factor for avg RPMHSS, avg=f*avg+(1-f)*new, avg T~1s/(1-f)

   ULONG	ulTicks;


   #GLOBAL_INIT
   {
     fRotorRPM_prev = 0.0;  //Initialize previous value to zero.
   }

   // State entry actions ...
   pData = pData; // to prevent compiler warning
   DiagnosticPrint( "Entering TaskMeasureSpeeds ...\r\n" ); // diagnostic

  	sprintf( strTemp, " TICK_TIMER = %d\r\n", TICK_TIMER );
	DiagnosticPrint( strTemp );
  	sprintf( strTemp, "OS_TICKS_PER_SEC = %d\r\n", OS_TICKS_PER_SEC );
	DiagnosticPrint( strTemp );





   // State processing ...

   // 20041028 RSF - increase loop speed to uiRPMLSSSampPerSec Hz to accomodate rotor per CH
   uiPass5s = 0;
   uiRPMLSSSampPerSec = 10;    // 20050421 ACH

   // zero out Rotor and Anemometer counts for first pass ...
   guiShaftEncoderCount = 0;
   guiAnemometerCount = 0;
   guiRPMHSSCount = 0;
   gfRPMLSSAvg = 0;  //initialize average values
   gfRPMHSSAvg = 0;  //initialize average values
   gfWSmpsAvg = kfWS_AnemCheck[giParameterID];      // initialize at setpoint to avoid startup problems  ACH 20060328
   ulOldTime_RPMLSS = TICK_TIMER;    //initialize "old" times  20050505 ACH
   ulOldTime_RPMHSS = TICK_TIMER;    //TICK_TIMER has 1024 ticks/sec

   // Initialize power values to zero
   gfPowerAvgDisplay = 0.0;
   fPower1s = 0.0;

      // Start virtual watchdog timer for TaskMeasureSpeeds...
   giWDT_measure = VdGetFreeWd( 9 ); // (9 - 1) / 16 ==> 0.5 sec reset interval

   while (TRUE)
   {
     // Delay approx 1/uiRPMLSSSampPerSec sec between passes ... //20050422 ACH
     OSTimeDly( OS_TICKS_PER_SEC / uiRPMLSSSampPerSec );

     // 20041028 RSF - Capture rotor counts at rate = uiRPMLSSSampPerSec //20050421 ACH
     uiShaftEncoder = guiShaftEncoderCount; // capture count


     // 20050505 ACH - get inverse of elapsed time since count was started
     // TICK_TIMER counts 1024 ticks per sec
     fDTime_RPMLSS = (float) 1024.0 / (TICK_TIMER - ulOldTime_RPMLSS);
     ulOldTime_RPMLSS = TICK_TIMER;

     // 20041028 RSF - Scale rotor counts to Hz ...

     fFreq = uiShaftEncoder * fDTime_RPMLSS;
     RotorRPMSet( RotorCountsToRPM( fFreq ) ); //20050505 ACH

     // 20050511 ACH - Check for overspeed.  Shutdown ASAP when detected.
     // but don't repeat this code if overspeed continues
     if ( RotorRPMGet() > RpmOverSpeedGet()
       && fRotorRPM_prev > RpmOverSpeedGet()
       && RotorRPMGet() >= fRotorRPM_prev
       && gucStateWindSpeed != STATE_FAULT )
     {
       gucFaultCode = ERR_LSSOspeed;
       SetState(STATE_FAULT);

       RotorBrake(ON);
       UpdateGenerator();
       DiagnosticPrint("Overspeed detected on LSSRPM\r\n");
       sprintf( strTemp, " Fault %d:, LSSRPM = %6.1f\r\n", gucFaultCode, RotorRPMGet() );
       DiagnosticPrint( strTemp );

     }

     // 20050510 ACH get time-average RPMLSS
     gfRPMLSSAvg = kfAvgFactor_LSSRPM * gfRPMLSSAvg +
                     ( 1.0 - kfAvgFactor_LSSRPM ) * RotorRPMGet();

     // 20041028 RSF - Zero out Rotor count before next sample ...
     guiShaftEncoderCount = 0;

     // 20061228 DJL Update the previous value for RPM
     fRotorRPM_prev = RotorRPMGet();

     // Accumulate average power
     fPower1s += (GenPowerGet() / uiRPMLSSSampPerSec);

     // 20041028 RSF - Only capture Anemometer counts every 5 seconds
     // and HSS counts every 1 second ...
     uiPass1s++;
     uiPass5s++;
     if (uiPass1s > uiRPMLSSSampPerSec) //  1 sec. integration ...   //20050421 ACH
     {
       uiPass1s = 0; // keep count for 1 seconds

       // 20050505 ACH - capture RPMHSS counts each 1 sec.
       uiRPMHSS = guiRPMHSSCount; // capture count

       // 20050505 ACH - get inverse elapsed time since count was started
       fDTime_RPMHSS = (float) 1024. / (TICK_TIMER - ulOldTime_RPMHSS);
       ulOldTime_RPMHSS = TICK_TIMER;

       // Scale HSS counts to Hz
       fFreq = (float) (uiRPMHSS * fDTime_RPMHSS);
       RPMHSSSet( RPMHSSCountsToRPM( fFreq ) );

       // 20051130 ACH get time-average HSS speed
       gfRPMHSSAvg = kfAvgFactor_HSSRPM * gfRPMHSSAvg +
                     ( 1.0 - kfAvgFactor_HSSRPM ) * RPMHSSGet();

      // We've accumulated a second's worth of average power.
      // Set the global average and reset the accumulated average
      gfPowerAvgDisplay = fPower1s;
      fPower1s = 0.0;

       // 20050511 ACH - Check for overspeed.  Shutdown ASAP when detected.
       if ( RPMHSSGet() > RpmOverSpeedGet()
         && gucStateWindSpeed != STATE_FAULT )
       {
         gucFaultCode = ERR_HSSOspeed;
       	SetState(STATE_FAULT);
         RotorBrake(ON);
         UpdateGenerator();
         sprintf( strTemp, "Fault %d:, HSSRPM = %6.1f\r\n", gucFaultCode, RPMHSSGet() );
         DiagnosticPrint( strTemp );

       }

       // 20041028 RSF - Zero out anemometer count before next sample ...
       guiRPMHSSCount = 0;

       // Accumulate speed slip value for generating->freewheeling logic
       // Keep sum below the ceiling for anti-windup and above floor
       // to avoid possible numeric overflow
       if (gfSpeedSlipSum <= -1.0E4 )  // don't waste time calculating if at the floor
       {
          gfSpeedSlipSum = -1.0E4;
       }
       else
       {
          gfSpeedSlipSum += gfRPMHSSAvg - RpmLssSynchronousGet();
          if (gfSpeedSlipSum > 0 )  // ceiling
          {
             gfSpeedSlipSum = 0;
          }
       }

       // Accumulate speed slip value for genHI->genLO logic
       // Keep sum below the ceiling for anti-windup and above floor
       // to avoid possible numeric overflow
       if (gfHiSpeedSlipSum <= -1.0E4 )  // don't waste time calculating if at the floor
       {
          gfHiSpeedSlipSum = -1.0E4;
       }
       else
       {
          gfHiSpeedSlipSum += (gfRPMHSSAvg - RpmGenHiSlipSumThreshGet())
                             *(gfRPMHSSAvg - RpmGenHiSlipSumThreshGet())
                             *(gfRPMHSSAvg - RpmGenHiSlipSumThreshGet());
          if (gfHiSpeedSlipSum > -kfHiSpeedSlipSetpoint )  // ceiling
          {
             gfHiSpeedSlipSum = -kfHiSpeedSlipSetpoint;
          }
       }

       // for screen output of LSS RPM
       //sprintf( strTemp, " LSSRPM = %6.1f\r\n", RotorRPMGet() );
       //DiagnosticPrint( strTemp );
}

     if (uiPass5s > 5*uiRPMLSSSampPerSec) //  5 sec. integration ...   //20050421 ACH
     {
       uiPass5s = 0; // keep count for 5 seconds

       // 20041028 RSF - capture anemometer counts each 5 sec.
       uiAnemometer = guiAnemometerCount; // capture count

       // 20050505 ACH - get inverse elapsed time since count was started
       fDTime_WS = (float) 1024. / (TICK_TIMER - ulOldTime_WS);
       ulOldTime_WS = TICK_TIMER;

       // 20041028 RSF - Scale anemometer counts to Hz ...
       fFreq = (float) (uiAnemometer * fDTime_WS);
       WindSpeedMPSSet( AnemometerCountsToMPS( fFreq ) );

       // Update the current wind speed record with current data
       UpdateWindSpeedRecord(WindSpeedMPSGet(), 5);

       // 20050510 ACH get time-average wind speed
       gfWSmpsAvg = kfAvgFactor_WS * gfWSmpsAvg + (1.0 - kfAvgFactor_WS) * WindSpeedMPSGet();

       // 20041028 RSF - Zero out anemometer count before next sample ...
       guiAnemometerCount = 0;
     }

     WatchdogHit(giWDT_measure); // this is the measure speeds task, hit watchdog here

     RecordWindDiag();

   } // end of while(TRUE)


} // end of TaskMeasureSpeeds

///////////////////////////////////////////////////////////////////////////////
// Start up all uC-OSII tasks
//
// Input Args:     pointer to data (ignored)
// Output Args:    none
// Input Globals:  none
// Output Globals: none
// Returns:        none
// Processing:     begin all other tasks in the system
// Updates:
//   20040219 RSF - original version
//   20040325 RSF - add task to display status on LEDs
void TaskStart( void *pData )
{
   // State entry actions ...
   pData = pData; // prevent compiler warning
   DiagnosticPrint( "Entering TaskStart ...\r\n" ); // diagnostic printout



   //
   // Start Windward Engineering Controller tasks ...
   OSTaskCreateExt // Serial communications update task
   (
     TaskAeroCommReceive,
     (void *) 0,
     TASK_PRIO_AEROCOMM,
     TASK_ID_AEROCOMM,
     TASK_STK_SIZE,
     (void *) 0,
     OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR
   );

   OSTaskCreateExt // rotor and wind speed measurement task
   (
     TaskMeasureSpeeds,
     (void *) 0,
     TASK_PRIO_MEASURE,
     TASK_ID_MEASURE,
     TASK_STK_SIZE,
     (void *) 0,
     OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR
   );

   OSTaskCreateExt // Fault monitoring task  // 20050427 ACH
   (
     TaskFaultMonitor,
     (void *) 0,
     TASK_PRIO_FAULT,
     TASK_ID_FAULTMONITOR,
     TASK_STK_SIZE,
     (void *) 0,
     OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR
   );

   OSTaskCreateExt // LED status display task
   (
     TaskStatus,
     (void *) 0,
     TASK_PRIO_STATUS,
     TASK_ID_STATUS,
     TASK_STK_SIZE,
     (void *) 0,
     OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR
   );

   OSTaskCreateExt // main processing loop task
   (
     TaskMainThread,
     (void *) 0,
     TASK_PRIO_MAINTHREAD,
     TASK_ID_MAINTHREAD,
     TASK_STK_SIZE,
     (void *) 0,
     OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR
   );



   OSTaskCreateExt // TCP/IP task
   (
     TaskTCPIP,
     (void *) 0,
     TASK_PRIO_TCPIP,
     TASK_ID_TCPIP,
     2048,
     (void *) 0,
     OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR
   );

   OSTaskCreateExt // Timed tasks
   (
     TaskTimers,
     (void *) 0,
     TASK_PRIO_TIMERS,
     TASK_ID_TIMERS,
     TASK_STK_SIZE,
     (void *) 0,
     OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR
   );

   OSTaskCreateExt // Flash write task
   (
     TaskFlashWrite,
     (void *) 0,
     TASK_PRIO_FLASH,
     TASK_ID_FLASH,
     TASK_STK_SIZE,
     (void *) 0,
     OS_TASK_OPT_STK_CHK + OS_TASK_OPT_STK_CLR
   );

   while (TRUE)
   {
   	if( UDPDL_Tick() )
      {
      	//Shut down code
         //A new program is about to be loaded
         //Release all the watchdogs so that a reset doesn't during download
         VdReleaseWd(giWDT_main);
         VdReleaseWd(giWDT_measure);
         VdReleaseWd(giWDT_fault);

			printf("Download request pending!\n");

      }

     	OSTimeDly( OS_TICKS_PER_SEC/2 ); // wake up once per second (and do nothing)
   }
} // end of TaskStart

///////////////////////////////////////////////////////////////////////////////
// Task to monitor for faults in sensors
//
// Input Args:     pointer to data (ignored)
// Output Args:    none
// Input Globals:
// Output Globals: none
// Returns:        none
// Processing:
// Updates:
//   20050511 ACH - original version
void TaskFaultMonitor( void *pData )
{
   char strTemp[80]; // for DiagnosticPrint calls
   ULONG ulElapsedTime;   //time since program start, seconds

   // State entry actions ...
   pData = pData; // to prevent compiler warning
   DiagnosticPrint( "Entering TaskFaultMonitor ...\r\n" ); // diagnostic

   // Start virtual watchdog timer for TaskFaultMonitor...
   giWDT_fault = VdGetFreeWd( 33 ); // (33 - 1) / 16 ==> 2.0 sec reset interval

   // State processing ...
   while (TRUE)
   {
     // get elapsed time since program start, sec
     ulElapsedTime = SEC_TIMER - gulTimeHistory;

     // Don't check for some faults until 20 sec have elapsed since program start
     if( ulElapsedTime > 20L )
     {
       // check for RPM sensor error using absolute value of speed difference
       // Averaged LSS value is used to have comparable time averaging of the two RPMs
       // Only do this in states where the brake is not applied
       if( fabs(gfRPMLSSAvg - RPMHSSGet() ) > kfRPM_ErrorTolerance[giParameterID]
         && ( gucStateWindSpeed == STATE_CUTIN
           || gucStateWindSpeed == STATE_FREEWHEEL
           || gucStateWindSpeed == STATE_GENLO
           || gucStateWindSpeed == STATE_GENHI ) )
       {
         if( RPMHSSGet() < RpmOverSpeedGet() )    //Did we also have overspeed?
         {

           gucFaultCode = ERR_RPMError;
           SetState(STATE_FAULT);
           DiagnosticPrint( "RPM sensor error detected\r\n" );
           sprintf(strTemp, "Fault %d: Avg LSS RPM = %5.1f, HSS RPM = %5.1f\r\n",
                     gucFaultCode, gfRPMLSSAvg, RPMHSSGet());
           DiagnosticPrint( strTemp );
         }
         else
         {
           gucFaultCode = ERR_HSSOspeed;
           SetState(STATE_FAULT);
           DiagnosticPrint( "HSS overspeed detected\r\n" );
           sprintf(strTemp, "Fault %d: HSS RPM = %5.1f\r\n",
                     gucFaultCode, RPMHSSGet());
           DiagnosticPrint( strTemp );
         }     //overspeed or RPM error?

       }

       // Check for anemometer reading too low
       if( gfWSmpsAvg < kfWS_AnemCheck[giParameterID]
          && RPMHSSGet() > RpmLssSynchronousGet()
          && gucStateWindSpeed != STATE_FAULT
          && gucStateWindSpeed != STATE_WARN)
       {
         SetState(STATE_WARN);
         gucFaultCode      = ERR_WSLowError;
         gulWarnTime       = SEC_TIMER;
         DiagnosticPrint( "Anemometer error detected--low reading\r\n" );
         sprintf(strTemp, "Fault %d: Avg HSS RPM = %5.1f, Avg WS = %5.1f\r\n",
                   gucFaultCode, RPMHSSGet(), gfWSmpsAvg);
         DiagnosticPrint( strTemp );

       }
     }  //elapsed time > 20?

     // Watch for high winds and switch to HIGHWINDS state.
     // This is not a fault, but we want to detect it if we're not in FAULT or HALT state.
     if( gucStateWindSpeed != STATE_FAULT && gucStateWindSpeed != STATE_HALT)
     {
       if (WindSpeedMPSGet() > kf110pct_WSCutout[giParameterID]
        || gfWSmpsAvg > kf90pct_WSCutout[giParameterID] )
       {
         SetState(STATE_HIGHWINDS);
         gucFaultCode = ERR_NoError;
         ulTimeHighWind = SEC_TIMER; // Record time HIGHWINDS started
         DiagnosticPrint( "TaskFaultMonitor: [State->HIGHWINDS] ...\r\n" );
       }
     }

     // Watch utility grid status and switch to GRIDFAULT state
     //  only when in a generating state
    if( gucStateWindSpeed == STATE_GENLO
     || gucStateWindSpeed == STATE_GENHI)
     {
       if ( GridFault() )
       {
         SetState(STATE_WARN);
         gucFaultCode      = ERR_GridFault;
         gulWarnTime       = SEC_TIMER;
         DiagnosticPrint( "TaskFaultMonitor: [State->GRIDFAULT] ...\r\n" );

       }
     }
     
      // Check for a brake failure, compensating for any delay in the physical 
      // system (pneumatics, deceleration of rotor, etc) by waiting a fixed
      // amount of time after a brake stop 
      if ((CheckBrakeFailureCondition() == TRUE) &&
            ((SEC_TIMER - ulTimeBrakeStop) > kulFaultBrakeResponseDelay))
      {
         // Go into a fault state with a brake failure fault code
         gucFaultCode = ERR_BrakeFailure;
         SetState(STATE_FAULT);
         DiagnosticPrint( "Brake Failure detected\r\n" );
      }

     OSTimeDly( OS_TICKS_PER_SEC ); // run at 1 sec interval

     WatchdogHit(giWDT_fault); // this is the fault monitor task, hit watchdog here

   } // end of while(TRUE)
} // end of TaskFaultMonitor

///////////////////////////////////////////////////////////////////////////////
// Task to display FSM status on LEDs
//
// Input Args:     pointer to data (ignored)
// Output Args:    none
// Input Globals:  gucStateWindSpeed
// Output Globals: none
// Returns:        none
// Processing:     Flash DS3 according to FSM state, DS3 once per second
// Updates:
//   20040325 RSF - original version
//   20041026 CH  - include additional debug printf's
//   20041026 CH  - change LED on and off times
//   20041026 RSF - use DiagnosticPrint()s so that DEBUG_PRINT enables them
void TaskStatus( void *pData )
{
   char strTemp[80]; // 20041026 RSF - for DiagnosticPrint calls
   UINT uiCount; // temp for computation

   // State entry actions ...
   pData = pData; // to prevent compiler warning
   DiagnosticPrint( "Entering TaskStatus ...\r\n" ); // diagnostic

   // State processing ...
   while (TRUE)
   {
     // Flash FSM state code ...
     for (uiCount = 0; uiCount < gucStateWindSpeed; uiCount++)
     {
       ledOut( 2, 1 ); // DS3 ON
       OSTimeDly( OS_TICKS_PER_4th_SEC ); // keep LED on for 250 ms
       ledOut( 2, 0 ); // DS3 OFF
       OSTimeDly( OS_TICKS_PER_16th_SEC ); // keep LED off for 100 ms
     }

     // 20041026 RSF - use DiagnosticPrint()s to allow DEBUG_PRINT control ---

     // Run at a 1 Hz rate ...
     OSTimeDly( OS_TICKS_PER_SEC ); // wait for one second
   } // end of while(TRUE)
} // end of TaskStatus

///////////////////////////////////////////////////////////////////////////////
// For Testing Only: set measured parameters via stdin
//
// Input Args:     none
// Output Args:    none
// Input Globals:  see below
// Output Globals: see below
// Returns:        none
// Processing:     substitute keypresses for external measurements
// Updates:
//   20040226 RSF - original version

#ifdef TESTING
void TestingParseKeypress( void )
{

   char strTemp[80]; // to build output strings

   if (!kbhit()) // key has not been pressed, leave ...
   {
     return;
   }

   switch (getchar()) // parse incoming character ...
   {

     case 'r':
       if (guiTestingRotorRPM > 10) // decr
       {
         guiTestingRotorRPM -= 10;
       }
       else
       {
         guiTestingRotorRPM = 0;
       }
       break;

     case 'R':
       guiTestingRotorRPM += 10;
       break;

     case 'a':
       if (gfTestingWSMPS > 0.2) // decr
       {
         gfTestingWSMPS -= 0.2;
       }
       else
       {
         gfTestingWSMPS = 0.0;
       }
       break;

     case 'A':
       gfTestingWSMPS += 0.2;
       break;

     case '-':
       if (gfTestingWSMPS > 2.0) // decr
       {
         gfTestingWSMPS -= 2.0;
       }
       else
       {
         gfTestingWSMPS = 0.0;
       }
       break;

     case '+':
       gfTestingWSMPS += 2.0;
       break;

     default:
       break;
   } // end of switch (getchar())

   // update stdio with current state ...
   WatchdogHit(giWDT_main); // always hit watchdog when printing enabled
   sprintf( strTemp, "uSW = %1d, RPMLSS = %04d (gen = %5d), MPS = %6.2f\r\n",
     guiTestingRotorRPM, guiTestingRotorRPM, gfTestingWSMPS );
   DiagnosticPrint( strTemp );
} // end of TestingParseKeypress
#endif // #ifdef TESTING

void WatchdogHit( int iWDT )
{
   VdHitWd( iWDT ); // hit virtual watchdog timer
} // end of WatchdogHit

///////////////////////////////////////////////////////////////////////////////
// Accessor function for global wind speed storage
//
// Input Args:     none
// Output Args:    none
// Input Globals:  gfWSmps
// Output Globals: none
// Returns:        wind speed in MPS (float)
// Processing:     retrieve value from global
// Updates:
//   20040224 RSF - original version
float WindSpeedMPSGet( void )
{
   #ifdef TESTING
   #GLOBAL_INIT
   {
     gfTestingWSMPS = 6.0;
   }
   return gfTestingWSMPS;
   #else // #ifdef TESTING
   return gfWSmps;
   #endif // #ifdef TESTING
} // end of WindSpeedMPSGet

///////////////////////////////////////////////////////////////////////////////
// Mutator function for global wind speed storage
// NOTE: may want to perform input argument limiting
//
// Input Args:     wind speed in MPS (float)
// Output Args:    none
// Input Globals:  none
// Output Globals: gfWSmps
// Returns:        none
// Processing:     store argument to global
// Updates:
//   20040224 RSF - original version
void WindSpeedMPSSet( float fMPS )
{
   gfWSmps = fMPS;
} // end of WindSpeedMPSSet

///////////////////////////////////////////////////////////////////////////////
// Accessor function for global RPMHSS storage
//
// Input Args:     none
// Output Args:    none
// Input Globals:  gfRPMHSS
// Output Globals: none
// Returns:        HSS speed in RPM (float)
// Processing:     retrieve value from global
// Updates:
//   20050505 ACH - original version
float RPMHSSGet( void )
{
   #ifdef TESTING
   #GLOBAL_INIT
   {
     gfTestingRPMHSS = 160.0;
   }
   return gfTestingRPMHSS;
   #else // #ifdef TESTING

   #ifdef HSSRPM_BYPASS // Use over-ride for testing only (not for actual turbine)
   gfRPMHSS = RotorRPMGet();//************* note over-ride to force two RPMs to match
                            // remove previous line to remove over-ride and get true RPMHSS
   #endif
   return gfRPMHSS;
// ************* note over-ride to force two RPMs to match
//   return guiRPMHSSCount;       //temporary output of counts instead of RPM
   #endif // #ifdef TESTING
} // end of RPMHSSGet

///////////////////////////////////////////////////////////////////////////////
// Mutator function for global HSS RPM storage
// NOTE: may want to perform input argument limiting
//
// Input Args:     HSS speed in RPM (float)
// Output Args:    none
// Input Globals:  none
// Output Globals: gfRPMHSS
// Returns:        none
// Processing:     store argument to global
// Updates:
//   20040224 RSF - original version
void RPMHSSSet( float fRPMHSS )
{
   gfRPMHSS = fRPMHSS;
} // end of WindSpeedMPSSet

// Gets the current power being generated, in Watts
// Inputs:
//    None
// Returns:
//    The current power being generated, in Watts
float GenPowerGet( void )
{
   UCHAR state;

   // Determine what state's RPM-to-power curve to use

   // For first 3s in GenHi use GenLo curve until RPM stabilizes
   if ((gucStateWindSpeed == STATE_GENHI) && (SEC_TIMER - ulGenSwitchHiTime < 3))
   {
      state = STATE_GENLO;
   }
   // Otherwise, use the current state
   else
   {
      state = gucStateWindSpeed;
   }

   // Convert the instantaneous RPM to power, based on the state
   return RpmToPower(RotorRPMGet(), state);
}

// Converts an RPM to power in Watts, based on the state of the system
// Inputs:
//    rpm   - The RPM to convert to power
//    state - The state of the system
// Returns:
//    The genrated power, in Watts
float RpmToPower(float rpm, UCHAR state)
{
   // RPM-to-power linear equation coefficients
   #define POWER_SLOPE              (27.4)
   #define POWER_INTERCEPT          (-49400)
   #define POWER_GENHI_GENLO_RATIO  (3.9216)

   float fCalculatedPower;
   float fHssRpm;
   float fScalingFactor;

   // Convert the LSS (Rotor) RPM to an HSS (Generator) RPM using the gearbox ratio.
   fHssRpm = (gModelParams.fGearRatio * rpm);

   // Calculate the power using the HSS (Generator) RPM
   fCalculatedPower = (POWER_SLOPE * fHssRpm) + POWER_INTERCEPT;

   // The power varies based on the state:
   // GenLo and GenHi have directly proportionate power equations; all other
   // states would correspond to zero power being generated.
   switch (state)
   {
      case STATE_GENLO:
         // The slope & intercept are defined for GenLo,
         // so the scaling factor should be 1 (i.e. don't scale)
         fScalingFactor = 1;
         break;

      case STATE_GENHI:
         // Scale by the GenHi:GenLo ratio
         fScalingFactor = POWER_GENHI_GENLO_RATIO;
         break;

      default:
         // No power being generated: scale by 0 to force power = 0
			fScalingFactor = 0;
         break;
   }

   // Scale the calculated power by the appropriate scaling factor
   fCalculatedPower = fScalingFactor * fCalculatedPower;

   return fCalculatedPower;
}

///////////////////////////////////////////////////////////////////////////////
// Main processing loop
//
// Input Args:     none
// Output Args:    none
// Input Globals:  none
// Output Globals: none
// Returns:        none
// Processing:     initialize, start multitasking,
//                   enter background loop processing
// Updates:
//   20040216 RSF - original version
//   20041205 RSF - include Flash Memory support
debug void main( void )
{
  //
  // local variable declarations ...
  int iCode; // return codes go here
  long dataStorage;
  long dataStorage2;
  BOOL bNewFirmware;

	//Check the SRAM for valid data and reset if needed.
   //Also check for IPconfig in FLASH and use defaults
   //if nothing was stored in flash yet.
  	bNewFirmware = MemoryTest();

   // Read data from flash
   ReadFlashData(bNewFirmware);

#ifdef TEST_FOUND
   CompileCheck();	//Set warning flag for test versions
#endif

  	OSInit(); // initialize uC-OSII
   brdInit();
	giSocketInitStatus=sock_init();
   ApplyIPSettings();

   //Init the download manager
   //UDPDL_Init needs to be called each time the IP address changes
   UDPDL_Init("Endurance Wind Power");


   //Perform hardware and data initialization
   StateInitialize(bNewFirmware);

		 #ifdef TEST_PRINT
	       // For diagnostics, display the Flash File structure ...
      	 FileParameterDump();
		 #endif

   RecordsInit(bNewFirmware);		 //Setup record buffers
   										 //if bNewFirmware is TRUE then all counters
                                  //etc are reset otherwise the memory is just
                                  //marked as used.




   RecordDoubleEvent(EV_PowerUp);       //Record the power up event.


   OSTaskCreateExt // Start up task will start all other tasks
   (
     TaskStart,
     (void *) 0,
     TASK_PRIO_START,
     TASK_ID_START,
     TASK_STK_SIZE,
     (void *) 0,
     OS_TASK_OPT_STK_CHK+OS_TASK_OPT_STK_CLR
   );


   OSStart(); // begin multitasking

   // if we get here a serious error must have occurred ...
   // a watchdog timeout will occur and reset the processor
   while (TRUE) // fail safe ...
   {
     OSTimeDly( OS_TICKS_PER_SEC );
   }
} // end of main

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
#ifdef TEST_PRINT
void PrintTime(unsigned long theTime)
{

	struct tm	ptime;

   mktm(&ptime, theTime);   //Takes theTime and fills the struct ptime

	printf("Year=%04d\n",1900+ptime.tm_year);
	printf("Month=%02d\n",ptime.tm_mon);
	printf("Day=%02d\n",ptime.tm_mday);
	printf("Hour=%02d\n",ptime.tm_hour);
	printf("Min=%02d\n",ptime.tm_min);
	printf("Sec%02d\n",ptime.tm_sec);


//	printf("%02d/%02d/%04d %02d:%02d:%02d\n\n",
//	ptime.tm_mon, ptime.tm_mday, 1900+ptime.tm_year,
//	ptime.tm_hour, ptime.tm_min, ptime.tm_sec);

}
#endif

///////////////////////////////////////////////////////////////////////////////
void  TaskTCPIP(void *pData)
{

#define SK_BUFF_SIZE 400

#define NETTIMEOUT 300   // Timeout in tengths of a second.

	static INT8U	error;
	char	socketIn[SK_BUFF_SIZE];
   char 	socketOut[SK_BUFF_SIZE];
   int 	toSend;
   int 	sent;
	int   i,j;
	int	ulTimeOutCount;

   #ifdef TEST_PRINT
   	DiagnosticPrint( "Entering TaskTCPIP ...\r\n" ); // diagnostic
   #endif


	while(1)
   {
		gbTCPConnected = FALSE;

   	//In case the socket didn't initalize OK when the program started
      //we will sit here until it does.  We also may be stuck in this loop
      //for a short time when
		while(giSocketInitStatus != 0)
      {
			giSocketInitStatus=sock_init(); //Returns 0 if socket initalizes OK.
     		OSTimeDly( OS_TICKS_PER_SEC ); // wait

      } // end while

   	sock_mode(&gsSocket,TCP_MODE_ASCII);	 //Put the socket into ASCII mode

      while(1 != tcp_listen(&gsSocket, IPSettings.Port, 0, 0, NULL, 0) )
      {
     		OSTimeDly( OS_TICKS_PER_SEC/2 ); // wait

      } // end while

   	DiagnosticPrint("tcp_listen returned 1\r\n");


		/* wait for a connection to be made */
		while(!sock_established((sock_type *)&gsSocket))
	   {
   	  	tcp_tick((sock_type *)&gsSocket);
     		OSTimeDly( OS_TICKS_PER_SEC/10 ); // wait

	   } // end while

      EncryptPassword();
      ulTimeOutCount=NETTIMEOUT;			//Tenths of seconds
		gbTCPConnected = TRUE;
   	DiagnosticPrint("Connection established\r\n");
		RecordEvent(EV_ERIconnect);

      while( sock_established((sock_type *)&gsSocket) && (ulTimeOutCount>0))
		{
			if(sock_bytesready(&gsSocket) !=-1 ) // Test with nonblocking function
         {
				switch( sock_gets(&gsSocket,socketIn,sizeof(socketIn)))
   		   {
      			case -1:
         	   	//An error occured
         			break;
		         case 0:
   	         	//No string received yet
   		      	break;
      		   default:
						// Received a CR or LF terminated string
	      			ulTimeOutCount=NETTIMEOUT;			//Reset timeout counter
			     		if( MessageParse(socketIn) == TRUE)
         			{
			      		ledOut( 3, 1 ); // DS4 ON
		   				OSTimeDly( OS_TICKS_PER_TENTH_SEC ); // keep DS4 LED on for 100 ms
			   			ledOut( 3, 0 ); // DS4 OFF
         			}

   	      }// end switch ( sock_gets(&gsSocket,socketIn,sizeof(socketIn)))
          } // end if(sock_bytesready() !=-1 )

         i=0;
         while( grbTCPoutgoing.count>0  && (i<=SK_BUFF_SIZE) )
         {
            socketOut[i++]=rb_getChar(&grbTCPoutgoing);

         } // end while

         if(i>0)
         {
         	socketOut[i]=0;
         	sock_puts(&gsSocket,socketOut);
         } // end if

   	  	tcp_tick((sock_type *)&gsSocket);
     		OSTimeDly( OS_TICKS_PER_TENTH_SEC/2  ); // wait
			ulTimeOutCount--;

      } // end while( sock_established((sock_type *)&gsSocket) )
		DiagnosticPrint("Connection terminated\r\n");
      RecordEvent(EV_ERIterminated);
    } // end while(1)


} //end TaskTCPIP(void *pData) ////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////////////////
int SerialGetChar(void)
{
	if(gbTCPConnected)
   	return -1;
   else
   	return SerialGetC();
}



///////////////////////////////////////////////////////////////////////////////
void rb_addChar(ring_buffer  *b,char  c)
{
	if ( b->count < rb_size)
   {
		b->buffer[b->head]=c;
		if( ++b->head>=rb_size ) b->head=0;
		b->count++;
   }
}



///////////////////////////////////////////////////////////////////////////////
char rb_getChar(ring_buffer *b)
{
	char retChar;
	if ( b->count > 0)
	{
		b->count--;

		retChar=b->buffer[b->tail++];

		if( b->tail>=rb_size ) b->tail=0;

		return retChar;
	}
	else
		return 0;

}
///////////////////////////////////////////////////////////////////////////////
void rb_reset(ring_buffer *b)
{
	b->head=0;
	b->tail=0;
	b->count=0;
}
///////////////////////////////////////////////////////////////////////////////
void 	TaskFlashWrite(void *pData)
{
	#define fFlashStruct 0
   #define fIPSettings  fFlashStruct+sizeof(FlashStruct)
   #define fSiteInfo    fIPSettings+sizeof(IPSettings)
   #define fPassword    fSiteInfo+sizeof(SiteInfo)
   #define fModelInfo   fPassword+sizeof(PasswordFlash)

	unsigned char i;
	BOOL	   ExtWDState;

	while(1)
	{
   	if(gbExtWatchDogSet) //No writes to flash until the external watchdog has been set
      {
			for(i=0;i<sizeof(gbSemaphoreFlashUpdate);i++)
      	{


   	   	//Check the semaphors for each of the structures that may be written to flash.
   			if(gbSemaphoreFlashUpdate[i])
      		{
               ledOut( LED1, 1 ); 					//Turn on LED
   				OSTimeDly(OS_TICKS_PER_TENTH_SEC/2);	   //Wait before enabling the external watchdog
               ledOut( LED1, 0 ); 					//Turn on LED

					ToggleOutput(OUTPUT_WATCHDOG);    // Hit the external watch dog timer

	      	   //A semaphore was set to true - write the matching structure to flash
      	      switch(i)
   	         {
	            	case eFlashStruct:
      					//Indicate saved so the defaults won't be used on next power up
         	      	strcpy(gFlashStruct.Saved,gcSaved);
						   writeUserBlock(fFlashStruct,&gFlashStruct,sizeof(gFlashStruct));
   	            	break;

                  case eIPSettings:
      					//Indicate saved so the default IP settings won't be used on next power up
   						strcpy(IPSettings.Saved,gcSaved);
         	      	writeUserBlock(fIPSettings,&IPSettings,sizeof(IPSettings));
      	         	break;

                  case eSiteInfo:
	      				//Indicate saved so the default site name won't be used on next power up
				   	   strcpy(gSite.Saved,gcSaved);
            	   	writeUserBlock(fSiteInfo,&gSite,sizeof(gSite));
         	      	break;

                  case ePassword:
   	   				//Indicate saved so the default password won't be used on next power up
					   	strcpy(structPassword.cSaved,gcSaved);
               		writeUserBlock(fPassword,&structPassword,sizeof(structPassword));
            	   	break;

                  case eModelInfo:
                     //Indicate saved so the default won't be used on next power up
					   	strcpy(gModelInfo.Saved, gcSaved);
               		writeUserBlock(fModelInfo, &gModelInfo, sizeof(gModelInfo));
            	   	break;

                  default:
                     break;
         	   } //end switch

					ToggleOutput(OUTPUT_WATCHDOG);    // Hit the external watch dog timer

      		   gbSemaphoreFlashUpdate[i]=FALSE; 	//Indicate flash write job done

               ledOut( LED1, 0 ); 					   //Turn off LED

		      } //end if(gbSemaphoreFlashUpdate[i])

	      }//end for(i=0;i<sizeof(gbSemaphoreFlashUpdate);i++)

      } //end if(gbExtWatchDogSet=TRUE)

   	OSTimeDly(OS_TICKS_PER_SEC/5);	//Alow other tasks time to operate

	}//end while
}
///////////////////////////////////////////////////////////////////////////////
void  TaskTimers(void *pData)
{
	while (1)
   {
   	OSTimeDly( OS_TICKS_PER_SEC/2 );  // wait
		TwicePerSecond();
   	OSTimeDly( OS_TICKS_PER_SEC/2 );  // wait
     	OncePerSecond();
		TwicePerSecond();
   }
}
void OncePerMinute(void)
{//Called every minute on the minute
}

void OncePerDay(void)
{
	//schedual a flash write
	gbSemaphoreFlashUpdate[eFlashStruct]=TRUE;
}

///////////////////////////////////////////////////////////////////////////////
void OncePerSecond(void)
{


	struct tm			theTime;
	static struct tm 	theLastTime;
   static char 		cLastDay;


   gulTimeClock=read_rtc();
   //theTm now has time in seconds since January 1, 1980.

   mktm(&theTime,gulTimeClock);
   //mktm converts gulTimeClock to a tm structure format

	CheckRecordInterval(&theTime); //See if its time to record data.

   DigitalTest();

   //See if the external watchdog needs to be enabled
   ExtWDCheck();

   if(cLastDay != theTime.tm_wday)
   {
   	cLastDay = theTime.tm_wday;	//Day of the week
      OncePerDay();
   }

}
///////////////////////////////////////////////////////////////////////////////
void TwicePerSecond(void)
{

	ToggleOutput(OUTPUT_WATCHDOG);    				// Hit the external watch dog timer
   ledOut( LED0, gbSSR_On[OUTPUT_WATCHDOG] ); 	//Set LED0 to match the state of the watchdog output

}


///////////////////////////////////////////////////////////////////////////////
void DigitalTest(void)
{
		static int	testSequence;
      int 	i;

      #GLOBAL_INIT {
      	testSequence=0;
      }

      if(CommissionTest()==0)
      {
      	gbDigitalOutTesting=FALSE;
      }//end if(CommisionTest==0)

      if(!gbDigitalOutTesting) return;

      for(i=0;i<8;i++)
      	{giOutputTest[i]=0;}

      switch(testSequence){
      	case 0:
				giOutputTest[OUTPUT_BRAKE]=ON;
         	break;
      	case 1:
				giOutputTest[OUTPUT_MOTOR]=ON;
         	break;
      	case 2:
				giOutputTest[OUTPUT_RESISTON]=ON;
         	break;
      	case 3:
				giOutputTest[OUTPUT_RUNCAP]=ON;
         	break;
      	case 4:
				giOutputTest[OUTPUT_RESISTOFF]=ON;
         	break;
      	case 5:
				giOutputTest[OUTPUT_NEU]=ON;
         	break;
      	case 6:
				giOutputTest[OUTPUT_HOT2]=ON;
         	break;
      }

   	if( giOutputTest[OUTPUT_WATCHDOG]=ON )
			giOutputTest[OUTPUT_WATCHDOG]=OFF;
      else
      	giOutputTest[OUTPUT_WATCHDOG]=ON;


      testSequence++;

      if( testSequence>6 ) testSequence=0;

		digitalOutput(0,giOutputTest[0]);
}
///////////////////////////////////////////////////////////////////////////////
void  ToggleOutput( int output )
{
     if (gbSSR_On[output] != OFF)
     {
       gbSSR_On[output] = OFF;
       digitalOutput( output, 1 );
     }
     else
     {
       gbSSR_On[output] = ON;
       digitalOutput( output, 0 );
     }

}




///////////////////////////////////////////////////////////////////////////////
void digitalOutput(int channel,int value)
{

   int i;
   static BOOL testingLastTime;

	#GLOBAL_INIT {
   testingLastTime=FALSE;
   gbDigitalOutTesting=FALSE;

   } // end GLOBAL_INIT



   if(!gbDigitalOutTesting)
   {
   	if(testingLastTime)
      { //Need to restore the outputs
/*	   	for(i=0;i<8;i++)
   	   {
      	 if( giOutputTest[i]=OFF)
       		digOut(i,1);
	       else
   	    	digOut(i,0);
      	 }
*/
      } // end if
      else
      {//Not testing last time
			digOut(channel,value);
         giOutputs[channel]=value;
      }// end else

     	testingLastTime=FALSE;
   } // end if(!gbDigitalOutTesting)
   else
	{ //Testing digital outputs


   	for(i=0;i<8;i++)
      {
	      if(i != OUTPUT_WATCHDOG)
   	   {
	      	 if( giOutputTest[i]==OFF)
             {
   	    		digOut(i,1);
               giOutputs[i]=1;
             } // end if
	      	 else
             {
   	    		digOut(i,0);
               giOutputs[i]=0;
             } // end else
      	 } // end if
          else
          {
	      	 if( gbSSR_On[i]==OFF)
             {
   	    		digOut(i,1);
               giOutputs[i]=1;
             } // end if
	      	 else
             {
   	    		digOut(i,0);
               giOutputs[i]=0;
             } // end else
          } // end for
      }// end else

       testingLastTime=TRUE;

   }
}

///////////////////////////////////////////////////////////////////////////////
void	TC_Null(void){}
///////////////////////////////////////////////////////////////////////////////
void	TC_Run(void)
{
 	gbRemoteHalt = FALSE;
   if(gucLastERIRec != EV_Run)
   {
     	RecordDoubleEvent(EV_Run);
      gucLastERIRec=EV_Run;
   }

}
///////////////////////////////////////////////////////////////////////////////
void	TC_Halt(void)
{
	gbRemoteHalt = TRUE;
   if(gucLastERIRec != EV_Halt)
   {
	 	RecordDoubleEvent(EV_Halt);
      gucLastERIRec=EV_Halt;
   }
}
///////////////////////////////////////////////////////////////////////////////
void	TC_ClearSVC(void)
{
	gFlashStruct.ulServiceHours = 0L;

   if(gucLastERIRec != EV_ClrService)
   {
	 	RecordDoubleEvent(EV_ClrService);
      gucLastERIRec=EV_Halt;
   }
}

///////////////////////////////////////////////////////////////////////////////
void  TC_Motor(void){}
///////////////////////////////////////////////////////////////////////////////
void  TC_Brake(void){}

///////////////////////////////////////////////////////////////////////////////
void	TC_TestOn(void)
{
	if(CommissionTest()==1) gbDigitalOutTesting=TRUE;
   else gbDigitalOutTesting=FALSE;
}

///////////////////////////////////////////////////////////////////////////////
void	TC_TestOff(void){gbDigitalOutTesting=FALSE;}

///////////////////////////////////////////////////////////////////////////////
void	TC_ClearMax(void)
{
  	gFlashStruct.ulPowerMaxX100 = 0L;
   gFlashStruct.ulMPSMaxX100 = 0L;
   gFlashStruct.ulRPMLSSMax = 0L;
   gfMaxRPMHSS = 0;

   if(gucLastERIRec != EV_ClrMax)
   {
	 	RecordDoubleEvent(EV_ClrMax);
      gucLastERIRec=EV_ClrMax;
   }
}

///////////////////////////////////////////////////////////////////////////////
void	TC_ClearEvent(void)
{
	gFlashStruct.ulMotorStarts = 0L;
   gFlashStruct.ulUpSwitches = 0L;
   gFlashStruct.ulBrakeStops = 0L;

   if(gucLastERIRec != EV_ClrEvents)
   {
 		RecordDoubleEvent(EV_ClrEvents);
      gucLastERIRec=EV_ClrEvents;
   }
}

///////////////////////////////////////////////////////////////////////////////
BOOL TC_SetDate(char* pToParse)
{
	struct tm		theTm;

   unsigned int 	yy;
   unsigned int	mm;
   unsigned int	dd;

	//															 "0123456789 1234567"
	//At this point gucBufferParse should contain "@!C08Date=yy-mm-dd#"
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   //More validation:
	if(strlen(pToParse) != 19  ) return FALSE;
   if( *(pToParse+12)  != '-' ) return FALSE;
   if( *(pToParse+15)  != '-' ) return FALSE;

   gulTimeClock=read_rtc();
   //gulTimeClock now has time in seconds since January 1, 1980.


   //mktm converts gulTimeClock to a tm structure format
   mktm(&theTm,gulTimeClock);

   dd=(UINT) (ULONG) atol(pToParse+16); //ASCII to long conversion for day
   mm=(UINT) (ULONG) atol(pToParse+13); //ASCII to long conversion for month
   yy=(UINT) (ULONG) atol(pToParse+10); //ASCII to long conversion for year

   if(dd>31) return FALSE;
   if(mm>12) return FALSE;
   if(yy>99) return FALSE;

   if(yy<80) yy +=100;

	theTm.tm_mday = dd;
	theTm.tm_mon = mm;
	theTm.tm_year = yy;        //tm_year is 80 to 147 to for 1980 to 2047

   RecordDoubleEvent(EV_OldDate);

	if( tm_wr(&theTm) == 0)
   {
      TC_RequestDate();
   	return TRUE;	//Writes the structure directly to the time clock.
   	RecordDoubleEvent(EV_NewDate);

   }
   else
   	return FALSE;


}

///////////////////////////////////////////////////////////////////////////////
BOOL TC_SetTime(char* pToParse)
{
	struct tm	theTm;

	//															 "0123456789 1234567"
	//At this point gucBufferParse should contain "@!C08Time=hh:mm:ss#"
   //24 hour time format is assumed.
   //The calling routine has verified that the header is OK and that
   //the last char is '#"


	if(strlen(pToParse) != 19) return FALSE;
	if(*(pToParse+12) != ':' ) return FALSE;
	if(*(pToParse+15) != ':' ) return FALSE;

   gulTimeClock=read_rtc();
   //gulTimeClock now has time in seconds since January 1, 1980.

   mktm(&theTm,gulTimeClock);
   //mktm converts gulTimeClock to a tm structure format

	theTm.tm_hour = (UINT) (ULONG) atol(pToParse+10 );
	theTm.tm_min = (UINT) (ULONG) atol( pToParse+13 );
	theTm.tm_sec = (UINT) (ULONG) atol( pToParse+16 );

   RecordDoubleEvent(EV_OldTime);

	if( tm_wr(&theTm) == 0)
   {
      TC_RequestDate();
   	RecordDoubleEvent(EV_NewTime);
   	return TRUE;	//Writes the structure directly to the time clock
   }
   else
   	return FALSE;

#ifdef TEST_PRINT
   PrintTime(read_rtc());
#endif

}




///////////////////////////////////////////////////////////////////////////////
void  TC_ReqIPinfo(void)
{
	// Send all IP settings

	char  sTemp[100];
   char	*p; //points to the location in the outgoing string that
         	 //is under construction

	p=PlaceHeader(sTemp,TR_IPInfo);

   strcpy(p,IPSettings.IPAddress);
   p=p+strlen(IPSettings.IPAddress);
   *(p++)=',';    							//Delimiter
   strcpy(p,IPSettings.Netmask);
   p=p+strlen(IPSettings.Netmask);
   *(p++)=',';    							//Delimiter
   strcpy(p,IPSettings.NameServer);
   p=p+strlen(IPSettings.NameServer);
   *(p++)=',';    							//Delimiter
   strcpy(p,IPSettings.Gateway);
   p=p+strlen(IPSettings.Gateway);
   *(p++)=',';    							//Delimiter
   p=itoa(IPSettings.Port,p);				//Convert port number to ASCII
   strcpy(p,gcCommandTerminator);      //Add the terminator

   SerialSendAeroComm( sTemp );

}

BOOL  MemoryTest(void)
{
	//This function is only called when the program is started.
   //It checks and compares a section of SRAM with a corresponding
   //section of Flash memory. If they are the same it is assumed
   //That the battery backed SRAM is OK.  If different then it
   //is assumed that this is the first time the program was run
   //or the battery has failed.
   //
   //Also checks the RAM location glCompileTime against the constant
   //dc_timestamp.  dc_timestamp is a constant that is generated at compile
   //time, so if a difference is found we know that more than just a
   //power off and on cycle has occured - likely there's new firmware.
	//Returns TRUE if new firmware has been identified.

	BOOL					bNewFirmware;
	const static char gcFlashRAMCheck[]="31415926935895956";
			static char gcSRAMCheck[sizeof(gcFlashRAMCheck)];
			static long glCompileTime;

	//Define the relative address of each of the items stored in flash
   //It is important to keep these addresses constant from version to
   //version so that program upgrades will not lose parameters such
   //as service hours, password, IP settings, etc.  This also means that
   //the size of the structures should not be changed.

	if ((strcmp(gcFlashRAMCheck, gcSRAMCheck) != 0) ||
      (glCompileTime != dc_timestamp))
   {
   	#ifdef TEST_PRINT
	   	printf("%s\r\n","Memory test failed");
      #endif

   	strcpy(gcSRAMCheck,gcFlashRAMCheck);
      glCompileTime = dc_timestamp;

		bNewFirmware = TRUE;
   }
   else
   {
   	#ifdef TEST_PRINT
   		printf("%s\r\n","Memory test passed");
      #endif

      bNewFirmware = FALSE;
   }

   return bNewFirmware;
}


// Reads all flash data on startup. For each set of values stored in flash,
// the structure is first read from flash and the contents are validated.
// Validation is accomplished by checking for the string "saved" in a certain
// location of each struct, which indicates that the struct had previously
// been saved to flash (there are potential holes in this method, as the struct
// size/order could have changed since past firmware releases, and the "saved"
// string from another struct could coincidentally be in the exact spot we're
// checking). If the data is not valid, the defaults are used.
//
// Inputs:
//    bNewFirmware - boolean indicating that new firmware has been detected.
// Returns:
//    void
void ReadFlashData(BOOL bNewFirmware)
{
   int i;

   // Initialize flash update flags to false. We do this here because this
   // function is the first place in which the flags can be set, so we need
   // to initialize them before any setting of the flags occurs
   for (i = 0; i < NUM_FLASH_STRUCTS; i++)
   {
	   gbSemaphoreFlashUpdate[i] = FALSE;
   }

   //
   // Primary Flash Struct
   //

   // Only restore from flash if new firmware was detected. Otherwise, keep
   // SRAM data. This data is only written to flash once every 8 hours, so
   // we'd prefer to keep the SRAM data since it is likely more recent.
   if (bNewFirmware == TRUE)
   {
      // Read struct from flash
   	readUserBlock(&gFlashStruct, fFlashStruct, sizeof(gFlashStruct));

      // Check for the "saved" string: if not found, set to defaults
   	if(strcmp(gFlashStruct.Saved, gcSaved) != 0)
	   {
   		gFlashStruct = gFlashDefaults;
	   }

      // Maximum HSS RPM should be in flash, but for 9.2.6 development this 
      // was left out in order to speed up development and to minimize changes.
      // This value should behave like flash (except for actually being 
      // retained on a loss of SRAM). Thus we initialize it here when the 
      // flash structure is initialized.
      gfMaxRPMHSS = 0;
         
   }
   else
   {
      // Schedule a write to flash for gFlashStruct as this provides a means to
      // update the flash before a program upgrade is applied (cycle the power
      // before upgrading a program to write the data to flash.
   	gbSemaphoreFlashUpdate[eFlashStruct] = TRUE;
   }

   //
   // IP Settings
   //

   // Read struct from flash
   readUserBlock(&IPSettings, fIPSettings, sizeof(IPSettings));

   // Check for the "saved" string: if not found, set to defaults
   if(strcmp(IPSettings.Saved, gcSaved) != 0)
   {
      IPSettings = DefaultIPSettings;
   }

   //
   // Site Info
   //

	// Read struct from flash
   readUserBlock(&gSite, fSiteInfo, sizeof(gSite));

   // Check for the "saved" string: if not found, set to defaults
   if(strcmp(gSite.Saved, gcSaved) != 0)
   {
      gSite = gSiteDefaults;
   }

   //
   // Password
   //

	// Read struct from flash
   readUserBlock(&structPassword, fPassword, sizeof(structPassword));

   // Check for the "saved" string: if not found, set to defaults
   if(strcmp(structPassword.cSaved, gcSaved) != 0)
   {
      structPassword = structDefaultPassword;
   }

   //
   // Model Info
   //

   // Read struct from flash
   readUserBlock(&gModelInfo, fModelInfo, sizeof(gModelInfo));

   // Initialize the turbine model info to defaults if the "saved" string is
   // not found, indicating the struct had not been previously saved in flash,
   // which can be interperated as either an empty flash or an upgrade from a
   // previous version for which no model info was stored.
   if (strcmp(gModelInfo.Saved, gcSaved) != 0)
   {
      // Set entire struct to defaults
      gModelInfo = gModelInfoDefaults;
      
      // Save to flash as we always need to remember the model type
      gbSemaphoreFlashUpdate[eModelInfo] = TRUE;
   }
   // If model info was saved in flash, new firmware is detected and the 
   // default model does not match that in flash then update it to this firmware
   // program's default model
   else if ((bNewFirmware == TRUE) && 
            (gModelInfo.defaultModel != gModelInfoDefaults.defaultModel))
   {
      // Set the default model
      gModelInfo.defaultModel = gModelInfoDefaults.defaultModel;
      
      // Save to flash now
      gbSemaphoreFlashUpdate[eModelInfo] = TRUE;   
   }
}

// Reset critical configuration to factory default settings
void FactoryReset(void)
{
   // Reset IP Settings to defaults and apply them
   IPSettings = DefaultIPSettings;
   ApplyIPSettings();

   // Reset the site info
   gSite = gSiteDefaults;

   // Reset the password
   structPassword = structDefaultPassword;

   // Schedule Flash Update
	gbSemaphoreFlashUpdate[eIPSettings] = TRUE;
   gbSemaphoreFlashUpdate[eSiteInfo] = TRUE;
   gbSemaphoreFlashUpdate[ePassword] = TRUE;

   // Record events
   RecordDoubleEvent(EV_IPChange);
}

// Counts the number of consecutive HALT key-switch toggles within a fixed
// window of time. If one of the toggle sequences is recognized, the
// appropriate action is carried out.
void CountSwitchToggles(void)
{
   ////////////////////////////////////////////////////////////////////////////
   // Constants
   ////////////////////////////////////////////////////////////////////////////

   // Toggle switching event parameters: A fixed window period is defined
   // in which any sequence must be completed. Additionally, parameters are
   // defined such that if a period of inactivity occurs after a minimum
   // number of toggles, the window is reset. This provision is made because
   // normal HALT and RUN sequences should be excluded.
   #define TOGGLE_WINDOW               (10)
   #define TOGGLE_TIMEOUT_PERIOD       (2)
   #define TOGGLE_TIMEOUT_MAX_TOGGLES  (2)

   // Factory reset sequence parameters:
   // 5-7 toggles in 5 seconds, followed by 5 seconds of inactivity
   #define RESET_MIN_TOGGLES           (5)
   #define RESET_MAX_TOGGLES           (7)
   #define RESET_ACTIVE_WINDOW         (5)
   #define RESET_INACTIVE_WINDOW       (TOGGLE_WINDOW - RESET_ACTIVE_WINDOW)

   // Turbine Type change parameters:
   // 10+ toggles in 10 seconds.
   #define TYPE_CHANGE_MIN_TOGGLES     (10)


   ////////////////////////////////////////////////////////////////////////////
   // Static constants (preserved between iteration of this function)
   ////////////////////////////////////////////////////////////////////////////

   // Flag indicating if a toggling window is active
   static BOOL bTogglingActive;

   // The number of toggles in this window
   static UINT uiToggleCount;

   // The time of the first and last toggles
   static ULONG ulFirstToggle;
   static ULONG ulLastToggle;

   // The last keyswitch position
   static BOOL ulLastSwitchPosition;


   ////////////////////////////////////////////////////////////////////////////
   // Non-static constants
   ////////////////////////////////////////////////////////////////////////////

   // The current HALT keyswitch postion
   BOOL bCurrentSwitchPosition;

   // Flag indicating if the toggling window elapsed this iteration
   BOOL bToggleWindowElapsed;

   #GLOBAL_INIT
   {
      // Default to inactive, 0 toggles, set all timestamps to now, and
      // guess that initial switch state is HALT (since we will detect
      // transitions from RUN to HALT, this avoids artificial transitions
      // to HALT on startup due to an incorrect guess)
      bTogglingActive      = FALSE;
      uiToggleCount        = 0;
      ulFirstToggle        = SEC_TIMER;
      ulLastToggle         = SEC_TIMER;
      ulLastSwitchPosition = TRUE;
   }


   ////////////////////////////////////////////////////////////////////////////
   // Check Timers
   ////////////////////////////////////////////////////////////////////////////

   // Initialized elapsed window flag to false. It will be set if a window has elapsed
   bToggleWindowElapsed = FALSE;

   // If active, check for a completed window or for a timeout
   if ((bTogglingActive == TRUE))
   {
      // Check if the toggling sequence has timed out due to inactivity
      // (defined as TOGGLE_TIMEOUT_PERIOD since last toggle and
      // TOGGLE_TIMEOUT_MAX_TOGGLES or fewer toggles). If so, reset by
      // making inactive
      if (((SEC_TIMER - ulLastToggle) >= TOGGLE_TIMEOUT_PERIOD) &&
         (uiToggleCount <= TOGGLE_TIMEOUT_MAX_TOGGLES))
      {
         bTogglingActive = FALSE;
      }
      // Check if a toggling window has elapsed and if so, indicate
      // inactive and flag that the window has elapsed
      else if ((SEC_TIMER - ulFirstToggle) >= TOGGLE_WINDOW)
      {
         bTogglingActive = FALSE;
         bToggleWindowElapsed = TRUE;
      }
   }


   ////////////////////////////////////
   // Detect completed toggle sequence
   ////////////////////////////////////

   // Check if the current window has elapsed
   if (bToggleWindowElapsed == TRUE)
   {
      // Only continue with the actions if the test jumper is out
      if ((CommissionTest() == TRUE) && (giParameterID == eNormal))
      {
         // If it has been RESET_INACTIVE_WINDOW since the last toggle
         // and there were between RESET_MIN_TOGGLES and RESET_MAX_TOGGLES
         // before that, this was a factory reset toggle sequence
         if (((SEC_TIMER - ulLastToggle) >= RESET_INACTIVE_WINDOW) &&
            (uiToggleCount >= RESET_MIN_TOGGLES) && (uiToggleCount <= RESET_MAX_TOGGLES))
         {
            // Factory Reset
            FactoryReset();
         }
         // If more than TYPE_CHANGE_MIN_TOGGLES, this was a change turbine type sequence
         else if (uiToggleCount >= TYPE_CHANGE_MIN_TOGGLES)
         {
            // Change Type of turbine
            ToggleModel();
         }
      }
   }


   //////////////////////////////////
   // Detect and handle rising edge
   //////////////////////////////////

   // Get the current switch state
   bCurrentSwitchPosition = KeySwitchHalted();

   // If the state has just changed, check if it was a rising edge (indicating the
   // keyswitch has just been changed to the HALT position) and continue
   if ((ulLastSwitchPosition != bCurrentSwitchPosition) &&
      (bCurrentSwitchPosition == TRUE))
   {
      // If not actively counting switches, start doing so now as the
      // first toggle has been received
      if (bTogglingActive == FALSE)
      {
         // Set the active flag
         bTogglingActive = TRUE;

         // Initialize counter and start time
         uiToggleCount = 0;
         ulFirstToggle = SEC_TIMER;
      }

      // Add this toggle event to the count and remember its time
      uiToggleCount++;
      ulLastToggle = SEC_TIMER;
   }

   // Remember the current switch state
   ulLastSwitchPosition = bCurrentSwitchPosition;
}

///////////////////////////////////////////////////////////////////////////////
void  TC_SetIPAdd(char* pToParse)
{

	char	sTemp[16];
   int	iLength; 	//Length of string representing the IP address.
   int	i;

	//															 "0123456789 123456789 1"
	//At this point gucBufferParse should contain "@!C61 xxx.xxx.xxx.xxx#"
   //Where xxx.xxx.xxx.xxx is the new IP address
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   iLength=strlen(pToParse)-7; //Less header and '#'

   if(iLength<17)
   {
   	for(i=0;i<iLength;i++)
   		sTemp[i]=*(pToParse+i+6);

	   sTemp[i]=0;
   	strcpy(IPSettings.IPAddress,sTemp);

      //Send the new settings back for verification
		TC_ReqIPinfo();
   } // end (iLength<17)

}

///////////////////////////////////////////////////////////////////////////////
void  TC_SetNetmask(char* pToParse)
{
	char	sTemp[16];
   int	iLength;
   int	i;

	//															 "0123456789 123456789 1"
	//At this point gucBufferParse should contain "@!C62 xxx.xxx.xxx.xxx#"
   //Where xxx.xxx.xxx.xxx is the new Netmask
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   iLength=strlen(pToParse)-7; //Less header and '#'

   if(iLength<17)
   {
   	for(i=0;i<iLength;i++)
   		sTemp[i]=*(pToParse+i+6);

	   sTemp[i]=0;
   	strcpy(IPSettings.Netmask,sTemp);

      //Send the new settings back for verification
		TC_ReqIPinfo();

   } // end if(i<17)
}

///////////////////////////////////////////////////////////////////////////////
void  TC_SetNameServer(char* pToParse)
{
	char	sTemp[16];
   int	iLength;
   int	i;

	//															 "0123456789 123456789 1"
	//At this point gucBufferParse should contain "@!C63 xxx.xxx.xxx.xxx#"
   //Where xxx.xxx.xxx.xxx is the new name server address
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   iLength=strlen(pToParse)-7; //Less header and '#'

   if(iLength<17)
   {
   	for(i=0;i<iLength;i++)
   		sTemp[i]=*(pToParse+i+6);

	   sTemp[i]=0;
   	strcpy(IPSettings.NameServer,sTemp);

      //Send the new settings back for verification
		TC_ReqIPinfo();
   } // end if(i<17)
}

///////////////////////////////////////////////////////////////////////////////
void  TC_SetGateway(char* pToParse)
{
	char	sTemp[16];
   int	iLength;
   int	i;

	//															 "0123456789 123456789 1"
	//At this point gucBufferParse should contain "@!C64 xxx.xxx.xxx.xxx#"
   //Where xxx.xxx.xxx.xxx is the new Gateway address
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   iLength=strlen(pToParse)-7; //Less header and '#'

   if(iLength<17)
   {
   	for(i=0;i<iLength;i++)
   		sTemp[i]=*(pToParse+i+6);

	   sTemp[i]=0;
   	strcpy(IPSettings.Gateway,sTemp);

      //Send the new settings back for verification
		TC_ReqIPinfo();
   } // end if(i<17)
}

///////////////////////////////////////////////////////////////////////////////
void  TC_SetIPPort(char* pToParse)
{
	char	sTemp[16];
   int	iLength;
   int	i;

	//															 "0123456789 1"
	//At this point gucBufferParse should contain "@!C65 xxxxx#"
   //Where xxxxx new port number
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   iLength=strlen(pToParse)-7; //Less header and '#'

   if(iLength<6)
   {
   	for(i=0;i<iLength;i++)
   		sTemp[i]=*(pToParse+i+6);

	   sTemp[i]=0;
   	IPSettings.Port= (int) atol(sTemp);

   } // end if(iLength<6)

   //Send the new settings back for verification
	TC_ReqIPinfo();

}

///////////////////////////////////////////////////////////////////////////////
void TC_ApplyIPSettings(void)
{
	//All of the TCP Port settings have been received, sent back
   //and verified.  It is now time to apply them.

	const static char  sTemp1[]="@*CMD,3,#\r\n";

   SerialSendAeroComm( sTemp1 );

   // Allow 2 seconds for response to get sent before tearing down the socket.
   OSTimeDly( 2* OS_TICKS_PER_SEC );

   ApplyIPSettings(); //Apply the new IP settings

   //Schedule a flash update
	gbSemaphoreFlashUpdate[eIPSettings]=TRUE;

 	RecordDoubleEvent(EV_IPChange);

}

///////////////////////////////////////////////////////////////////////////////
void  ApplyIPSettings(void)
{
	ifconfig(IF_ETH0,
   	IFS_DOWN,
      IFS_IPADDR, aton(IPSettings.IPAddress),
      IFS_NETMASK, aton(IPSettings.Netmask),
      IFS_ROUTER_SET, aton(IPSettings.Gateway),
      IFS_NAMESERVER_SET, aton(IPSettings.NameServer),
      IFS_UP,
      IFS_END);

      #ifdef TEST_PRINT
      	printf("IP address = %s",IPSettings.IPAddress);
      #endif

}

///////////////////////////////////////////////////////////////////////////////
void  TC_SendDefaultString (void)
{
	//This function sends the standard string after a command that does
   //not require a specific response has been received.

   char strTemp[120]; // to build outbound messages
   ULONG ulTimeStamp; // Time stamp when packet sent

   char strTime[7];
	char* p;

   struct tm	tmDateTime;



	if(pRecXmitter==NULL)
   {
      mktm(&tmDateTime,read_rtc());
   	p=btoh(strTime,tmDateTime.tm_hour);
      p=btoh(p,tmDateTime.tm_min);
      p=btoh(p,tmDateTime.tm_sec);

      //	ulTimeStamp = SEC_TIMER;  // Set time stamp for packet
	   // Send Rotor Controller status string via AeroComm to the OP6810 ...
   	// seq#,MPSx100,MaxMPSx100,WATTSx100,MaxWATTSx100,RPMLSS,MaxRPMLSS,
	   //   Starts, Stops, Total Hours, Service Hours, Status
   	// "@!S%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld#\r\n"
      p=strTemp;
	   p+=sprintf( strTemp,
   	"@!S%ld,%s,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld#\r\n",
	   (ULONG) SequenceNumberGet(),
   	strTime,
	   (ULONG) (gfWSmpsAvg * 100L),
   	gFlashStruct.ulMPSMaxX100,
	   (ULONG) (100.0 * gfPowerAvgDisplay),// 20050506 ACH power from function
   	gFlashStruct.ulPowerMaxX100,
	   (ULONG) RotorRPMGet(),
   	gFlashStruct.ulRPMLSSMax,
	   gFlashStruct.ulMotorStarts,
   	gFlashStruct.ulBrakeStops,
	   gFlashStruct.ulTotalHours,
   	gFlashStruct.ulServiceHours,
	   gFlashStruct.ulUpSwitches,
   	(ULONG)( 10 * CommissionTest()
   		+ giParameterID + 1 ) ,
	      (ULONG)( 1000 * gucStateHistory[1]
   	   + 100 * gucStateHistory[0]
      	  + 10 * gucStateWindSpeed
         	 + gucFaultCode) ,
	   VersionDisplayNumberGet() );

      // ERI versions greater than 12.0.0 expect to have additional parameters.
      // Conditionally add them based on the ERI version in order to preserve
      // backwards compatibility with the home unit
      if(giERIversion>1200)
      {
	      p-=3; //Back up over CR LF and #
   	   sprintf(p,",%ld,%ld#\r\n",
         (ULONG)(RPMHSSGet()),
         (ULONG)(gfMaxRPMHSS)
         );
      }

   	SerialSendAeroComm( strTemp );
	   SequenceNumberSet( SequenceNumberGet() + 1 ); // bump outbound count
   }//end if(!gbSendingMainRec)
   else if(pRecXmitter!=NULL)
     		SendMainRecords();


}

///////////////////////////////////////////////////////////////////////////////
void  TC_StackReport (void)
{
// Send information about the stacks for all the OS tasks.
// Format of the string to be sent is:
// "@*CMD,5,u1,f1,u2,f2,...,#" + cr + lf
// Where ui is the maximum amount of stack used for the task with priority i
// and fi is the minimum amount of free stack space for the task with
// priority i.
//
   OS_STK_DATA			data;     //Data from OSTaskStkChk goes in this structure

   char  				sTemp[120];  //Build outgoing string here

   int					i;  //loop counter

   char					*p; //points to the location in the outgoing string that
                         //is under construction

	p=PlaceHeader(sTemp,TR_StackInfo);

   //Loop through all tasks:
   for(i=TASK_PRIO_START; i<=TASK_PRIO_MAINTHREAD; i++)
   {
	   //OSTaskStkChk is called to check the amount of free memory
      //left on the stack (the task with priority i).
	   OSTaskStkChk(i,&data);

      p = itoa( (int) data.OSUsed, p ) ;  //integer to ASCII conversion
      *(p++)=',';                     		//Delimiter
		p = itoa( (int) data.OSFree, p ) ;  //integer to ASCII conversion
      *(p++)=',';                         //Delimiter

   }

   p--; 										//Last delimiter is not needed
   strcpy(p,gcCommandTerminator); 	//Add the terminator
   SerialSendAeroComm( sTemp );  	//Send the completed string

}  //end TC_StackReport
///////////////////////////////////////////////////////////////////////////////
void  TC_SetSiteInfo(char* pToParse)
{

	char	sTemp[100];
   int	iLength;
   int	i;

	//															 "0123456789 1"
	//At this point gucBufferParse should contain "@!C72ccc...#"
   //Where ccc... is new site name
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   iLength=strlen(pToParse)-6; //Less header and '#'

   if(iLength<100) //Max size of site name is 100 characters
   {
   	for(i=0;i<iLength;i++)
   		gSite.Name[i]=*(pToParse+i+5);

      gSite.Name[i]=0; //Terminate the string

      //Schedule a flash update for Site info
		gbSemaphoreFlashUpdate[eSiteInfo]=TRUE;

      //Send the new name back for verification
		TC_RequestSiteInfo();
   } //end if(iLength<100)

}

///////////////////////////////////////////////////////////////////////////////
void TC_Hello(char* pToParse)
{
	char	sTemp[16];
   int	iLength;
   int	i;

	//															 "0123456789 "
	//At this point gucBufferParse should contain "@!C78 xxxx#"
   //Where xxxx ERI version number
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   iLength=strlen(pToParse)-7; //Less header and '#'

   if(iLength<6)
   {
   	for(i=0;i<iLength;i++)
   		sTemp[i]=*(pToParse+i+6);

	   sTemp[i]=0;	//Add the string terminator for the atol function

   	giERIversion= (int) atol(sTemp);

   } // end if(iLength<6)

	//"Hello" comand is sent as soon as ERI makes a connection
   //If we are sending records it must be from a previous connection
   //that was lost so stop sending now.
   pRecXmitter=NULL;

}
///////////////////////////////////////////////////////////////////////////////
void TC_RequestDate(void)
{
	char			sTemp[20];
   char*			p;


   p=PlaceHeader(sTemp,TR_DateTime);   //Construct the header

   //xTimeString converts the number of seconds since Jan 1, 1980  to an ASCII
   //coded string, puts it in sTemp and adjust the pointer p to point to
   //the next char in sTemp.
   p=xTimeString( p, read_rtc() );

   strcpy(p,gcCommandTerminator);      //Add the terminator

   SerialSendAeroComm( sTemp );       //Send the completed string

}
///////////////////////////////////////////////////////////////////////////////
void TC_RequestTime(void)
{
	TC_RequestDate();
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void  TC_SetRecInterval(char* pToParse)
{

	//Set the recording time interval

	char	sTemp[16];	//Temp buffer used to parse incomming message
   						//also to construct outgoing response

   int	iLength;
   int	i;
   char*	p;

	//															 "0123456789 "
	//At this point gucBufferParse should contain "@!C79 xx#"
   //Where xx is the new record interval
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   iLength=strlen(pToParse)-7; //Less header and '#'

   if(iLength<3)
   {
   	for(i=0;i<iLength;i++)
   		sTemp[i] = *(pToParse+i+6);

	   sTemp[i]=0;	//Add the string terminator for the atol function

   	gcWindRecInterval = (char) atol(sTemp);

		TC_RequestRecInterval(); //Send the same tower response as
      								 //a request for the record interval.

   } // end if(iLength<3)
}

///////////////////////////////////////////////////////////////////////////////
void  TC_RequestRecInterval()
{
	char	sTemp[50]; //Construct the outgoing string here

   char	*p; //points to the location in the outgoing string that
         	 //is under construction

	unsigned char i;	//Loop counter


	p=PlaceHeader(sTemp,TR_RecInterval);   //Construct the header

   p=itoa( (int)gcWindRecInterval, p );	//Convert gcWindRecInterval ASCII

   strcpy(p,gcCommandTerminator);         //Add the terminator

   SerialSendAeroComm( sTemp );       //Send the completed string
}

///////////////////////////////////////////////////////////////////////////////
void	TC_RequestSiteInfo (void)
{
	char	sTemp[120]; //Construct the outgoing string here

   char	*p; //points to the location in the outgoing string that
         	 //is under construction

	p=PlaceHeader(sTemp,TR_SiteInfo);   //Construct the header

   strcpy(p,gSite.Name); 					//Add the site name

   p=p+strlen(gSite.Name);             //Adjust the pointer

   *p++ = ',';									//Add the delimiter

   //dc_timestamp is a long representing the time that the
   //program was compiled, xTimeString converts it to a special
   //string format that can be sent to ERI.
   p=xTimeString(p,dc_timestamp);


   strcpy(p,gcCommandTerminator);      //Add the terminator

   SerialSendAeroComm( sTemp );       //Send the completed string

}


void	TC_RequestTriggers (void)
{
	char	sTemp[50]; //Construct the outgoing string here

   char	*p; //points to the location in the outgoing string that
         	 //is under construction

	unsigned char i;	//Loop counter


	p=PlaceHeader(sTemp,TR_Triggers);   //Construct the header


   for(i=0;i<sizeof(gbTriggers);i++)
   	if(gbTriggers[i])
			*(p++)='1';
      else
			*(p++)='0';


   strcpy(p,gcCommandTerminator);      //Add the terminator

   SerialSendAeroComm( sTemp );       //Send the completed string

}

BOOL TC_SetTriggers(char* pToParse)
{
	unsigned char i;	// Loop counter
	//															 "0123456789 123456789 12"
	//At this point gucBufferParse should contain "@!C84-xxxxxxxxxxxxxxxx#"
   //where xxxxxxxxxxxxxxxx has the new values for the trigger array
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   //More validation
	if(strlen(pToParse) != 24) return FALSE;
	if(*(pToParse+5) != '-' ) return FALSE;

   pToParse += 6;

   //Parse all but the last array element
   for(i=0;i<sizeof(gbTriggers)-2;i++)
   	if( *(pToParse+i)== '0' )
      	gbTriggers[i]=FALSE;
       else if ( *(pToParse+i)== '1' )
       	gbTriggers[i]=TRUE;
       		else
            	return FALSE;

	//The last element in the array is '1' if the trigger is to be active and '0'
   //if the trigger is not to be active.  We need to test for a change so it
   //can be recorded as an event...

   i++; //Point to the last array element

	if( *(pToParse+i)== '0' )
   {//ERI says trigger should be deactivated (Set to FALSE)
   	if (gbTriggers[sizeof(gbTriggers)-1])
		{//Changing from TRUE to FALSE
      	gbTriggers[i]=FALSE; //Deactivate first so this event can be recorded
      	RecordDiagnosticEvent(EV_TriggerCleared);
   	}
   }
   else if( *(pToParse+i)== '1' )
   {//ERI says trigger should be activated (Set to TRUE)
   	if ( !gbTriggers[sizeof(gbTriggers)-1] )
   	{//Changing from FALSE to TRUE
      	//Record the trigger event before the trigger is deactivated
      	RecordDiagnosticEvent(EV_TriggerERI);
      	gbTriggers[i]=TRUE;
	   }
   }

	TC_RequestTriggers();     //Send the new triggers back for the response

}


///////////////////////////////////////////////////////////////////////////////
void	TC_RequestFlashInfo(void)
{
	//Sends the number of flash writes

  	char sTemp[80]; // to build output strings

   sprintf(sTemp,"%s%d,%ld,%ld%s",
   	gcCommandHeader,  //
	   TR_FlashInfo,     //CommandNumber
	   gFlashStruct.ulReserved[0],
      glFreeMemory,
		gcCommandTerminator);

   SerialSendAeroComm( sTemp );       //Send the completed string

}

///////////////////////////////////////////////////////////////////////////////
void  TC_RequestRecInfo(char* pToParse)
{

	RecordBuffer* 	R; //Will point to record buffer that info is requested for

	char				sTemp[40];

   char				*p; //points to the location in the outgoing string that
         	 			 //is under construction

	unsigned long 	ulTimeStamp;

   unsigned char 	i;

   //The calling routine has verified that the header is OK and that
   //the last char is '#".
                                              //  01234567
   //At this point gucBufferParse should contain "@!C75-x#"
   //Where x specifies which record buffer is to be looked at:

   //'0' for gWindRPM
   //'1' for gEvents
   //'2' for gWindRPMDiag
   //'3' for gEventsDiag

   i=(*(pToParse+6))-'0';  //Convert from ASCII to unsigned char

	if( (i>=0) &&  ( i<sizeof(pRecXmitters) ) )
   {
		R=pRecXmitters[i]; //Get the address of the record structure

		//Construct the message header
   	p=PlaceHeader(sTemp,TR_RequestRecInfo);

	   //Add the record count and delimiter
   	p = itoa( R->uiRecordCount, p ) ; //integer to ASCII conversion
		*p++=',';

   	//Add the timestamp of the oldest record
	   xmem2root(&ulTimeStamp,R->ulOldestRecord,sizeof(ulTimeStamp));
		p=xTimeString(p,ulTimeStamp);
		*p++=',';

   	//Add the timestamp of the newest record
	   xmem2root(&ulTimeStamp,R->ulRecordLast,sizeof(ulTimeStamp));
		p=xTimeString(p,ulTimeStamp);
		*p++=',';

   	//Add the maximimum number of records that can be recorded
		p=itoa(R->uiRecordMax,p);
		*p++=',';

		//Add the record interval
   	p=itoa(gcWindRecInterval,p);

	   strcpy(p,gcCommandTerminator);      //Add the terminator

   	SerialSendAeroComm( sTemp );       //Send the completed string
   }

}
///////////////////////////////////////////////////////////////////////////////
void	TC_RequestMainRec(char* pToParse)
{
	char						sTemp[40];	//Construct outgoing response here
   char*						p;          //Used to index into sTemp

	struct tm				tmDateTime;
   char						yy;				//Year
   unsigned int			i;             //Counter and index for array
   int						iSearchRelief;
   RecordBuffer*			pR;


	//															 "0123456789 123456789 1234567"
	//At this point gucBufferParse should contain "@!C76,yyyy-mm-dd,hh:mm:ss-B#"
   //The calling routine has verified that the header is OK and that
   //the last char is '#"
   //yyyy-mm-dd,hh:mm:ss is the date and time of the last record on file on
   //the ERI PC. We we don't want to wast time sending records older than
   //that date.  B is the record buffer to be searched:
   //B = 1 for gWindRPM
   //B = 2 for gEvents
   //B = 3 for gWindRPMDiag
   //B = 4 for gEventsDaig

   //If we are already sending then we don't need to init vars again
	if(pRecXmitter==NULL)
   {
      #ifdef TEST_PRINT
      	printf("Search start -%lu\r\n",MS_TIMER);
      #endif

	   //Validate the format of the request
		if(strlen(pToParse) != 28  ) return;
	   if( *(pToParse+10)  != '-' ) return;
   	if( *(pToParse+13)  != '-' ) return;
	   if( *(pToParse+16)  != ',' ) return;
	   if( *(pToParse+19)  != ':' ) return;
	   if( *(pToParse+22)  != ':' ) return;
	   if( *(pToParse+25)  != '-' ) return;

      yy = atoi(pToParse+6) - 1900;

   	tmDateTime.tm_year =	yy;
	   tmDateTime.tm_mon  =	(char) atoi(pToParse+11);
  	 	tmDateTime.tm_mday = (char) atoi(pToParse+14);
	   tmDateTime.tm_hour = (char) atoi(pToParse+17);
   	tmDateTime.tm_min  = (char) atoi(pToParse+20);
	   tmDateTime.tm_sec  = (char) atoi(pToParse+23);

      //Find out which record buffer to use
      i=atoi(pToParse+26);

      //Make sure i refers to a valid record buffer
      if( i > sizeof(pRecXmitters) - 1 ) return;

      pR=(RecordBuffer*)pRecXmitters[i];	//Get a pointer to the RecordBuffer

      //Convert the date and time to a long for quick comparison with the
      //stored records.
   	glRecRequestDate = mktime(&tmDateTime);

      pR->uiRecsToSend=pR->uiRecordCount;     //Assume for now that all records
      pR->ulNextRecToSend=pR->ulOldestRecord; //are to be sent.


      //point pR->ulNextRecToSend to the oldest record that is newer
      //than glRecRequestDate
		i=0;
   	while(	(xgetlong(pR->ulNextRecToSend)<=glRecRequestDate) &&
      		   (i<pR->uiRecordCount)                           )
   	{
      	//SendMoveNext moves pR->ulNextRecToSend to the next record
         //and decreases pR->uiRecsToSend
         SendMoveNext(pR);
      	i++;
         iSearchRelief++;


         //If the whole buffer needs to be searched, it could take some time
         //so we will release the task and alow the higher priority tasks
         //to proceed
         if(iSearchRelief==1000)
         {
     			OSTimeDly(2*OS_TICKS_PER_TENTH_SEC); // wait
				iSearchRelief=0;
         }

		}

      #ifdef TEST_PRINT
      	printf("Search end -%lu\r\n",MS_TIMER);
      #endif



	   p=PlaceHeader(sTemp,TR_RecordsStarted);

		p=itoa(pR->uiRecsToSend,p);      //Tell ERI how many records to expect
   	strcpy(p,gcCommandTerminator);   //Add the terminator

	   SerialSendAeroComm( sTemp );     //Tell ERI message received

      if(pR->uiRecsToSend==0)
      		pRecXmitter=NULL;
      else
      		pRecXmitter=pR;




   } //end if(pRecXmitter=NULL)


}
void	TC_CancelRecords(void)
{
	pRecXmitter=NULL;
	gWindRPM.uiRecsToSend=0;
   SerialSendAeroComm( "@*CMD,11#" );       //Tell ERI message received
}

///////////////////////////////////////////////////////////////////////////////
void 	SendMainRecords(void)
{
   #define RecsPerXmission 20

   char	sTemp[400]; //Outgoing string is constructed here

   char	*p; //points to the location in the outgoing string that
         	 //is under construction

   int	i;  //Counts the number of records in each transmission

   //Construct the transmission header
   p=PlaceHeader(sTemp,TR_MainRecord);

	i=0;
	while(pRecXmitter->uiRecsToSend>0 && i<RecsPerXmission)
   {
   	p=(*pRecXmitter->pfnConvert)(p,pRecXmitter->ulNextRecToSend);

      //Calculate the address of the next record to send
		//and decrease the RecsToSend counter
      SendMoveNext(pRecXmitter);

		i++;             //Count how many records have been converted
   }

   strcpy(p,gcCommandTerminator);     //Add the terminator
   SerialSendAeroComm( sTemp );       //Send the completed string

   if(pRecXmitter->uiRecsToSend==0)
   {
   	pRecXmitter=NULL;
      p=PlaceHeader(sTemp,TR_RecordsComplete); //Tell ERI we are done
   	strcpy(p,gcCommandTerminator);     		  //Add the terminator
   	SerialSendAeroComm( sTemp );             //Send the completed string
   }

}

void  TC_QueryTestMode(void)
{
	//Tell ERI that the program was compiled for testing
   #ifdef TEST_FOUND
   	SerialSendAeroComm( "@*CMD,8,1#\r\n" );       //Send the completed string
   #else
   	SerialSendAeroComm( "@*CMD,8,0#\r\n" );       //Send the completed string
   #endif
}



#ifdef TEST_FOUND
void CompileCheck(void)
{
   	printf("%s\r\n","------------------------------------------------");
   	printf("%s\r\n","--------- Warning TEST VERSION ONLY ------------");
   	printf("%s\r\n\n\n","________________________________________________");
}
#endif

void	RecordsInit(BOOL bFullReset)
{
   unsigned char i; 				//Loop counter
	unsigned long	ulFreeMem;

   #GLOBAL_INIT {pRecXmitter=NULL;}
   #GLOBAL_INIT {gucLastERIRec=255;}

   //Allocate memory for Wind and rpm records
	gWindRPM.ulBufferSize = xavail((long *) &gWindRPM.ulBase); // get free xmem

	ulFreeMem=xavail(NULL); //Find out how much memory is left

	gEvents.ulBufferSize 		= (unsigned long)(.33 * ulFreeMem);
   gWindRPMDiag.ulBufferSize 	= (unsigned long)(.33 * ulFreeMem);

   gEvents.ulBase 		=  xalloc(gEvents.ulBufferSize);
   gWindRPMDiag.ulBase 	=  xalloc(gWindRPMDiag.ulBufferSize);

   //gEventsDiag buffer gets remaining free memory
	gEventsDiag.ulBufferSize = xavail((long *) &gEventsDiag.ulBase);

   gWindRPM.uiRecordSize		= sizeof(WindRecord);
   gEvents.uiRecordSize			= sizeof(EventRecord);
   gWindRPMDiag.uiRecordSize	= sizeof(WindRecord);
   gEventsDiag.uiRecordSize	= sizeof(EventRecord);

   //Set up the addresses of the functions that convert the record
   //data to strings to be transmitted to ERI:
   gWindRPM.pfnConvert				=	WindRPMToString;
   gEvents.pfnConvert				=	EventToString;
   gWindRPMDiag.pfnConvert			=	WindRPMToString;
   gEventsDiag.pfnConvert			=	EventToString;

	//Not sending records to ERI
   gWindRPM.uiRecsToSend				=	0;
   gEvents.uiRecsToSend					=	0;
   gWindRPMDiag.uiRecsToSend			=	0;
   gEventsDiag.uiRecsToSend			=	0;



	if(bFullReset)
	{  //Only get here on first run or when battery backed up memory failed
   	//or the program time stamp was changed.

	   //Init pointers and counters for all buffers
   	RecordStructInit(&gWindRPM);
	   RecordStructInit(&gEvents);
   	RecordStructInit(&gWindRPMDiag);
	   RecordStructInit(&gEventsDiag);

   	RecordDoubleEvent(EV_RecordsInit);

	   for(i=0;i<sizeof(gbTriggers);i++)
		   gbTriggers[i]=gbDefaultTriggers[i];

		bRecordsInitalized=TRUE;

   	gcWindRecInterval = 11; //Record wind and rpm every 10 minutes
	}
	else
	{
		//Battery backed memory was ok and the program time stamp did not change
	   //(this is not the first time this version of code was run) so we will
   	// know what time the power down occured.
   	RecordDoubleEvent(EV_PowerDown);

      //If power down was selected as a trigger event then activate the
		//trigger so diagnostic recording will stop.
	   if( gbTriggers[15] )
   		gbTriggers[sizeof(gbTriggers)-1]=TRUE;
	}

}


#ifdef TEST_PRINT
void ShowBuffer (RecordBuffer* R)
{
	char i;
	char pX[20];

	printf("Base address=%ld\r\n",R->ulBase);          	//Base address of record buffer
	printf("Wrap address=%ld\r\n",R->ulWrap);          	//Largest address before wrap around
	printf("Last rec address=%ld\r\n",R->ulRecordLast);   //Address of last stored record
	printf("Next rec adress=%ld\r\n",R->ulRecordNext);    //Address to store next record
	printf("Oldest rec address=%ld\r\n",R->ulOldestRecord);  //Address of oldest record
	printf("Buffer size=%ld\r\n",R->ulBufferSize);	  			//Total size of buffer
	printf("Each record size =%d\r\n",R->uiRecordSize);  //Size of each record
	printf("Number of records=%d\r\n",R->uiRecordCount); //Number of records
	printf("Max records=%d\r\n",R->uiRecordMax);     		//Max number of records
	printf("Address of next rec to send=%ld\r\n",R->ulNextRecToSend); //Address of next record to send
	printf("Number of records to send=%d\r\n",R->uiRecsToSend);	  	//Number of records to send

	xmem2root(pX,R->ulBase,10);
   pX[10]=0;

   for(i=0;i<10;i++)
   {
   	printf("%d ",pX[i]);
    }

   printf("\r\n");
   printf("\r\n");
}

int xxx(void)
{
	char sX[11];
	char i;

	xmem2root(sX,gEventsDiag.ulBase,10);

   printf("\r\n");
	printf("gEventsDiag.Base=%ld\r\n",gEventsDiag.ulBase);
   for(i=0;i<10;i++)
   {
   	printf("%d ",sX[i]);
    }

   printf("\r\n");

   return 1;

}


#endif




void RecordStructInit(RecordBuffer* R)
{
	//This function will set up the pointers and counters in a RecordBuffer
   //structure R. Before calling the following must be set up:
   //
   // R->ulBase 			= The base address of the buffer
   // R->uiRecordSize 	= The size of each record to be stored
	// R->ulBufferSize	= The total number of bytes available in the buffer

	//R.ulRecordNext is address of the location to store the next record
   R->ulRecordNext = R->ulBase;

   //R.uiRecordMax is the maximum number of records that can be stored
	R->uiRecordMax = (int)(R->ulBufferSize/R->uiRecordSize);

   //Address of the last record before wrap around is required
   R->ulWrap = R->ulBase + (((long)R->uiRecordMax-1) * R->uiRecordSize);

	R->uiRecordCount = 0; //Keep count of records with this

	R->ulOldestRecord = R->ulBase;  //Address of oldest record

	R->ulNextRecToSend = R->ulBase; //Address of next record to send
}

void AddRecord(void* pRecord, RecordBuffer* R)
{
	//Cant'record if records to send is at max because we will wipe
   //out the records before they are sent.  This would also cause
   //the records sent to out of cronalogical order.
	if(R->uiRecsToSend < R->uiRecordMax)
   {
   	root2xmem(R->ulRecordNext,pRecord,R->uiRecordSize);
		RecordMoveNext(R);
   }
   #ifdef TEST_PRINT
	else
   {
   	DiagnosticPrint("Missed record");
   }
   #endif
}



void RecordMoveNext(RecordBuffer* R)
{
	//This function is called after a record has been stored

   //Save the address of the newest record
	R->ulRecordLast=R->ulRecordNext;

   //Move the address of the next record ahead wrap around if needed
   R->ulRecordNext=RecAddInc(R->ulRecordNext,R);

	//Increase the count if not at max
	if(R->uiRecordCount < R->uiRecordMax)
   {
   	R->uiRecordCount++;
   	R->ulOldestRecord = R->ulBase;
   }
   else
   {
   	//Enough records have been recorded to wipe out the
      //very first record, untill now R->Base was the address
      //of the oldest record, from now on the oldest record
      //has the same address of the next record

		R->ulOldestRecord = R->ulRecordNext;

   }

}

//////////////////////////////////////////////////////////////////////////////

void SendMoveNext(RecordBuffer* R)
{
	//This function is called after a record has been sent

   //Move the address of the next record to send ahead, wrap around if needed
	R->ulNextRecToSend=RecAddInc(R->ulNextRecToSend,R);

	//Decrease the number of records to send
	if(R->uiRecsToSend>0) R->uiRecsToSend--;

}


//////////////////////////////////////////////////////////////////////////////
//Returns the address of the next record location after Address.
unsigned long RecAddInc (unsigned long Address,RecordBuffer* R)
{
  	if(Address<R->ulWrap)
		return Address+R->uiRecordSize;
	else
   	return R->ulBase;
}

//////////////////////////////////////////////////////////////////////////////

//Convert unsigned long to null terminated ASCII coded hex string
char* ultoh(char* str, unsigned long* N)
{
	unsigned int* I;

   I=(unsigned int*)(N);

	I++;
   str=uitoh(str,I); //Unsigned integer to ASCII coded hex

   I--;
   str=uitoh(str,I); //Unsigned integer to ASCII coded hex

   *(str)=0;    //Null terminator

   return str;

}
//////////////////////////////////////////////////////////////////////////////


//Convert an unsigned integer to a null terminated ASCII coded hex string
char* uitoh (char* str, unsigned int* N)
{
	char*	C;

   C=(char*)(N);

   C++;
   str=btoh(str,*(C)); //Byte to ASCII coded hex

   C--;
   str=btoh(str,*(C)); //Byte to ASCII coded hex

   *(str)=0;      //Null terminator

   return str;

}
//////////////////////////////////////////////////////////////////////////////

//Convert a byte to a null terminated ASCII coded hex string
char* btoh (char* str,char C)
{
	char cTemp;

   cTemp=C;	//Save to restore C later

   C >>= 4;	//Put MSN into LSN

   str=ntoh(str,C); //Converts low nibble to hex

   str=ntoh(str,cTemp); //Low nibble to ASCII coded hex

   *(str)=0;  //Null terminator

   return str;

}
//////////////////////////////////////////////////////////////////////////////

//Convert low nibble of C to ASCII coded hex character
char* ntoh (char* str,char C)
{
	C &= 0x0F;	//Get rid of most signifigant nibble
   if(C < 10)
   	*str++ = (C + '0');
   else
   	*str++ = (C + 'A'-10);

	*str = 0;	//Place the null terminator

   return str;

}

//////////////////////////////////////////////////////////////////////////////
// Record the current windspeed
// Inputs
//    windSpeed = the currentWindSpeed (m/s)
void RecordWind(float windSpeed)
{
   WindRecord	R;
   ULONG currentTimeInSeconds;
   ULONG logTimeInSeconds;
   struct tm currentTime;

   // Get the current time in whole minutes for the timestamp of the data log.

   // Get the system time in seconds
   currentTimeInSeconds = read_rtc();
   // Convert the seconds to a time structure, setting seconds to zero
   mktm(&currentTime, currentTimeInSeconds);
   currentTime.tm_sec = 0;
   // Convert the structure back into seconds, which is the data log timestamp format
   logTimeInSeconds = mktime(&currentTime);

   // Populate the record

   // Log the windspeed * 100 for added resolution
   R.iWindSpeed=(int)(windSpeed*100);
   // Log 0 for RPM/Power for the time being. TODO implement powerlogging.
   R.iRPM = 0;
   // Log the timestamp in whole minutes which we created
   R.lTimeStamp = logTimeInSeconds;

   // Add the record to the log buffer
   AddRecord(&R,&gWindRPM);

   #ifdef TEST_PRINT
      printf("Added wind and rpm record\r\n");
   #endif
}

void RecordWindDiag(void)
{
	WindRecord	R;

	if((!gbTriggers[sizeof(gbTriggers)-1])) //If trigger has not occured
	{
   	//RotorRPMGet() returns the LSS RPM and is updated 10 times/sec
	   R.iRPM=(int)(RotorRPMGet()*100);

		//WindSpeedMPSGet() returns the wind speed in meters/sec and
	   //it is updated every 5 seconds.
  		R.iWindSpeed=(int)(WindSpeedMPSGet()*100);

	   R.lTimeStamp=read_rtc();

  		AddRecord(&R,&gWindRPMDiag);
	}
}

//////////////////////////////////////////////////////////////////////////////
//char* xTimeString(char* pBuff, long lTime)
//
//DESCRIPTION: Converts lTime to a string 6 bytes in length for transmission
//             to ERI. The string is null terminated.
//
// 	PBuff+0 = second + 65
//		pBuff+1 = minute + 65
//	   pBuff+2 = hour + 65
//    pBuff+3 = day + 65
//		pBuff+4 = month + 65
//    pBuff+5 = year + 65
//
// 65 is added to each character, this is to avoid having the ASCII codes
// for "@", "!", "#", CR, and LF involved in the data part of a coded
//	transmission string.
//
//PARAMETER1:	Pointer to string buffer to store result
//PARAMETER2:  Seconds since January 1, 1980.
//
//
//RETURN VALUE: Pointer to the null terminator
//
//
//////////////////////////////////////////////////////////////////////////////
char* xTimeString(char* pBuff, long lTime)
{
		struct tm T;
		char*		 pT;

      mktm(&T,lTime);  //Converts seconds since jan 1, 1980 to
      					  //a 6 byte structure T

	   //Add 65 to each byte in the structure and place the results
      //in the buffer pBuff
      for(pT=(char*)(&T);pT<((char*)(&T))+6;pT++)
      *pBuff++ = *pT+65;

      *pBuff=0;	//Place the null terminator

      return pBuff; //Points to the null terminator
}
//////////////////////////////////////////////////////////////////////////////
char* PlaceHeader(char* pBuff, unsigned int CommandNumber)
{

   strcpy(pBuff,gcCommandHeader);		//Copy the command header
   pBuff += sizeof(gcCommandHeader)-1; //Set pointer to just after header
   pBuff=itoa(CommandNumber,pBuff);    //Put iin the command number
   *pBuff++ = ','; 							//Delimiter
   *pBuff = 0;     							//Null terminator

   return pBuff;
}
//////////////////////////////////////////////////////////////////////////////


//Convert an event record to a string to be transmitted to ERI
char* EventToString(char*pBuff,unsigned long pE)
{
	EventRecord	E;

	xmem2root(&E,pE,sizeof(EventRecord));

	//Convert the seconds from Jan 1, 1980 to a format that
   //can be sent over a serial port
	pBuff=xTimeString(pBuff,E.lTimeStamp);

   //Convert the event code to ASCII coded hex
	pBuff=btoh(pBuff,E.cEvent);

   return pBuff;
}


//Convert a WindRPM record to a string to be transmitted to ERI
char* WindRPMToString(char*pBuff,unsigned long pW)
{
	WindRecord	W;

	xmem2root(&W,pW,sizeof(WindRecord));

	//Convert the seconds from Jan 1, 1980 to a format that
   //can be sent over a serial port
	pBuff=xTimeString(pBuff,W.lTimeStamp);

   //Convert the recorded rpm to ASCII coded hex
	pBuff=uitoh(pBuff,(unsigned int*)(&W.iRPM));

	//Convert the recorded wind speed to ASCII coded hex
	pBuff=uitoh(pBuff,(unsigned int*)(&W.iWindSpeed));

   return pBuff;

}

void RecordEvent(char EventNumber)
{
	EventRecord	E;

   E.cEvent = EventNumber;

   if(EventNumber == EV_PowerDown)
   {//Recording the EV_PowerDown event must happen before gulTimeClock
    //is updated for the first time.
     	E.lTimeStamp=gulTimeClock;
   }
   else
   	E.lTimeStamp=read_rtc();

  	AddRecord(&E,&gEvents);

	gucLastRecEvent=EventNumber;

}



void RecordDiagnosticEvent(char EventNumber)
{
	EventRecord	E;

	if(!gbTriggers[sizeof(gbTriggers)-1]) //If trigger has not occured
   {
   	E.cEvent = EventNumber;

	   if(EventNumber == EV_PowerDown)
   	{//Recording the EV_PowerDown event must happen before gulTimeClock
	    //is updated for the first time.
   	  	E.lTimeStamp=gulTimeClock;
	   }
   	else
   		E.lTimeStamp=read_rtc();

		AddRecord(&E,&gEventsDiag);

  		gucLastRecEvent=EventNumber;

   }//End if( !gbTriggers[15] )
}

void RecordDoubleEvent(char EventNumber)
{// Record event into both diagnostic record buffer and regular buffer

	RecordDiagnosticEvent(EventNumber);
	RecordEvent(EventNumber);
}

//To do:

void RecordTestMode(UCHAR ucTestMode)
{
	static char ucLastTestMode;

   if(ucTestMode != ucLastTestMode)
   {
   	RecordDoubleEvent(EV_TestModes+ucTestMode);
      ucLastTestMode = ucTestMode;
   }
}

// Returns the recording interval in seconds
char GetRecordInterval(void)
{
	// Intervals must divide evenly into 60 for minutes
   // and must divide evenly into 24 for hours.
	const static char cIntervals[] = {1,1,1,1,1,1,1,
                                    10,10,10,10,10,
                                    60,60,60,60};

   // gcWindRecInterval should always be less than sizeof(cIntervals)
   if (gcWindRecInterval < sizeof(cIntervals))
	{
   	return cIntervals[gcWindRecInterval];
   }
   else
   {
      // As a fail safe, return last entry
      return cIntervals[sizeof(cIntervals) - 1];
   }
}

// Updates the ongoing wind speed logging
// Inputs:
//    currentWindSpeed - The current wind speed
//    samplePeriodSecs - The sample period, in seconds, for wind speed
void UpdateWindSpeedRecord(float currentWindSpeed, UINT samplePeriodSecs)
{
   // Static data for calculating a running average
   static UINT uiSampleCount;
   static float fWindSpeedSum;

   UINT uiSamplesPerRecord;
   BOOL bRecordThisTime;

   #GLOBAL_INIT
   {
      // Initialize the static data
      fWindSpeedSum = 0.0;
      uiSampleCount = 0;
   }

   // Calculate the number of samples per data record
   uiSamplesPerRecord = (GetRecordInterval() * 60 / samplePeriodSecs);

   // Add the current wind speed to the running total, and increment our count by one.
   // With these structures we can calculate the average at any time by dividing the
   // sum by the count (note that it is expected the samplePeriodSecs is constant)
   fWindSpeedSum += currentWindSpeed;
   uiSampleCount++;

   // Check to see if a log is required based on whether or not the last record
   // pending has been completed already/
   if (gulLastRecordPending > gulLastRecordComplete)
   {
      // Set the flag to record this iteration
      bRecordThisTime = TRUE;

      // Increment the number of records complete as we will record one
      gulLastRecordComplete++;
   }
   else
   {
      // Clear the flag so that we don't record this iteration
      bRecordThisTime = FALSE;
   }

   // Proceed with the record if we've determined this is appropriate
   if (bRecordThisTime == TRUE)
   {
      // Check to see if we have enough data (at least half of the log period),
      // and that we do not have too much data (at most double the log period)
      // to justify a log entry. We can end up with either not enough or too
      // much if the logging period has just changed during this logging
      // interval. We can also end up with not enough if we just started logging
      // and didn't get a full interval in.
      // ALso ensure we have at least one sample.
      if ((uiSampleCount >= 0.5 * uiSamplesPerRecord) &&
            (uiSampleCount <= 2 * uiSamplesPerRecord) &&
            (uiSampleCount > 0))
      {

         // Calculate the wind speed and log it
         RecordWind(fWindSpeedSum / uiSampleCount);
      }

      // Clear the running total and count to start the next period
      fWindSpeedSum = 0.0;
      uiSampleCount = 0;
   }
}

// Checks the current time against the recording interval
// Inputs:
//    theTime - The current time structure
void CheckRecordInterval(struct tm *theTime)
{
	char        intervalMins;
	char        interval;
   char        currentTime;
	static char lastTime;

   intervalMins = GetRecordInterval();

   if (intervalMins > 0)
	{
      // If the interval is less than 60 minutes, check the minutes value
      if (intervalMins < 60)
      {
         currentTime = theTime->tm_min;
         interval = intervalMins;
      }
      // If the interval is at least 60 minutes, check the hours
      // (And round the interval to hours)
      else
      {
         currentTime = theTime->tm_hour;
         interval = intervalMins / 60;

         // Cap the interval at 12 hours, as this algorithm isn't
         // smart enough to properly handle anything higher
         if (interval > 12)
         {
            interval = 12;
         }
      }

      // If we have not already recorded for this interval and if
      // the current time matches our recording interval, indicate that
      // a new record is pending
   	if ((lastTime != currentTime) && (currentTime % interval == 0))
	   {
         gulLastRecordPending++;
         lastTime = currentTime;
	   }
   }
}

// Records the current state if it has changed since this function was last invoked
//
// Inputs:
//    None
// Returns:
//    void
void RecordStateIfChanged(void)
{
   // last state - static
	static UCHAR ucLastRecState;	 	
	// last fault code - static
   static UCHAR ucLastFaultCode;
   
   // Flag indicating we're in a fault or warning (which requires special logging logic)
   BOOL isFaultOrWarning;
   // Temp variable for the event code to record
   char eventCode;

   // Initialization logic for static variables
   #GLOBAL_INIT
   {
      // force a record on first pass by setting to an invalid state
      ucLastRecState = 255; 
      
      // Default to no error - the first fault/warning will definitely be 
      // different because the fault code will be updated with the error
      ucLastFaultCode = ERR_NoError; 
   }

   // Set the isFaultOrWarning flag based on the current state
	switch(gucStateWindSpeed)
   {
      // If Fault or Warning set the flag
   	case	STATE_FAULT:
      case	STATE_WARN:
         isFaultOrWarning = TRUE;
      	break;

      // Otherwise clear the flag
      default:
         isFaultOrWarning = FALSE;
         break;
   }
   
   // Look for a change in states or fault codes (when in a fault or warning)
   if ((gucStateWindSpeed != ucLastRecState) || 
         ((isFaultOrWarning == TRUE) && (gucFaultCode != ucLastFaultCode)))
   {     	
      // Detect all events other than FAULT and handle accordingly
      if (isFaultOrWarning == FALSE)
      {
   		eventCode = EV_HaltState + gucStateWindSpeed;
      }
      // For fault or warning states fault codes are considered in the event code
      else
      {	
      	eventCode = EV_HaltState + STATE_FAULT + gucFaultCode - 1;
      }
      
      RecordEvent(eventCode);      
	}

   // Remember the last state & fault code for next time
   ucLastRecState = gucStateWindSpeed;
   ucLastFaultCode = gucFaultCode;
}

BOOL RecordPath(unsigned char ucPath)
{

	//Test current state and path against the last diagnostic record.
   //If different then record it.

	static UCHAR ucLastEventCode;	 	// last recorded state
   		 UCHAR ucEventCode;

  	#GLOBAL_INIT
   {
   	ucLastEventCode = 255; // force a record on first pass
  	}

   //Work out the event code based on the gucStateWindSpeed and the ucPath
   if(gucStateWindSpeed<STATE_FAULT)
   	ucEventCode=EV_StateWithPath+10*gucStateWindSpeed+ucPath;
   else if (gucStateWindSpeed==STATE_FAULT)
     	//For fault states gucFaultCode is 1, 2 or 3 and ucStatePath = 0,1 or 2
     	ucEventCode=EV_StateWithPath+10*STATE_FAULT+3*ucPath+gucFaultCode-1;
   else if (gucStateWindSpeed==STATE_WARN)
    	//For warning state gucFaultCode is 4, 5 or 6 and ucStatePath = 0,1 or 2
     	ucEventCode=EV_StateWithPath+10*STATE_WARN+3*ucPath+gucFaultCode-4;

	if(ucEventCode != ucLastEventCode)
   {
   	RecordDiagnosticEvent(ucEventCode);
      ucLastEventCode = ucEventCode;
      return TRUE;
   }
	else
   {
   	return FALSE;
   }
}

void SetState(UCHAR ucNewState)
{
	if(gucStateWindSpeed !=  ucNewState)
   {
		gucStateHistory[1] = gucStateHistory[0];
	   gucStateHistory[0] = gucStateWindSpeed;
   	gucStateWindSpeed	 = ucNewState;

      // Save state information to flash struct: Concatenate the current and 
      // past state values into a single integer, where each digit contains
      // one number
   	gFlashStruct.ulReserved[1] = (ULONG) ( (gucFaultCode * FLASH_FAULT_CODE_DIGIT) +
                                             (gucStateWindSpeed * FLASH_CURRENT_STATE_DIGIT) +
                                             (gucStateHistory[0] * FLASH_PAST_STATE_1_DIGIT) + 
                                             (gucStateHistory[1] * FLASH_PAST_STATE_2_DIGIT) );

      // Perform state-specific operations
      switch (ucNewState)
      {
         case STATE_FAULT:
            // Flag flash structure to be written to flash
            gbSemaphoreFlashUpdate[eFlashStruct] = TRUE;
            break;
            
         default:
            break;
      }
	}
}

// Sets the current model-specific parameters in use according to the
// current turbine model
void ModelParamsSet(void)
{
   ModelParamStruct newModelParamStruct;

   // Pick the proper ModelParamStruct for the model
   switch (gModelInfo.model)
   {
      // S-250
      case eS250:
         newModelParamStruct = kS250Params;
         break;

      // S-343
      case eS343:
         newModelParamStruct = kS343Params;
         break;

      // As a precaution, default to S-250
      default:
         newModelParamStruct = kS250Params;
         break;
   }

   // Set the parameters
   gModelParams = newModelParamStruct;
}

// Toggles the current turbine model between S-250 and S-343 and
// updates the current model specific parameters
void ToggleModel(void)
{
   ModelEnum newModel;

   // Determine what the new model should be based on the current model
   switch (gModelInfo.model)
   {
      // Currently S-250, set to S-343
      case eS250:
         newModel = eS343;
         break;

      // Currently S-343, set to S-250
      case eS343:
         newModel = eS250;
         break;

      // As a precaution, default to S-250
      default:
         newModel = eS250;
         break;
   }

   // Set the new model
   gModelInfo.model = newModel;

   // Save the new model to flash
   gbSemaphoreFlashUpdate[eModelInfo] = TRUE;

   // Update current model-specific parameters
   ModelParamsSet();
}

// Gets the LSS Synchronous RPM
float RpmLssSynchronousGet(void)
{
   return (RPM_HSS_SYNCHRONOUS / gModelParams.fGearRatio);
}

// Gets the RPM below which a sufficient slip-sum can bring turbine offline
float RpmOfflineGet(void)
{
   return (RpmLssSynchronousGet() * RPM_RATIO_OFFLINE);
}

// Gets the RPM below which a sufficient slip-sum can trigger downswitch
float RpmDownSwitchGet(void)
{
   return (RpmLssSynchronousGet() * RPM_RATIO_DOWNSWITCH);
}

// Gets the RPM above which an upswitch is triggerred
float RpmUpSwitchGet(void)
{
   return (RpmLssSynchronousGet() * RPM_RATIO_UPSWITCH);
}

// Gets the RPM threshold for slip-sum accumulation in GenHi
float RpmGenHiSlipSumThreshGet(void)
{
   return (RpmLssSynchronousGet() * RPM_RATIO_GENHI_SLIP_SUM_THRESH);
}

// Gets the maximum RPM at which motoring can start
float RpmMotorStartMaxGet(void)
{
   return (RpmLssSynchronousGet() * RPM_RATIO_MOTOR_START_MAX);
}

// Gets the target RPM to motor to, above which motoring ceases
float RpmMotorStopGet(void)
{
   return (RpmLssSynchronousGet() * RPM_RATIO_MOTOR_STOP);
}

// Gets the RPM above which an overspeed is triggerred. If in an overspeed
// test, returns the appropriate overspeed test value
float RpmOverSpeedGet(void)
{
   float fOverSpeed;

   switch (giParameterID)
   {
      case eOverSpeedTest:
         fOverSpeed = RpmLssSynchronousGet() * RPM_RATIO_OVERSPEED_TEST;
         break;

      default:
         fOverSpeed = RpmLssSynchronousGet() * RPM_RATIO_OVERSPEED;
         break;
   }

   return fOverSpeed;
}

// Gets the version number to display on the remote interface
// Returns:
//    The long integer representing the version major, minor and build numbers.
//       This is a three-digit decimal number in which the three digits
//       represent the three one-digit numbers mentioned above.
ULONG VersionDisplayNumberGet(void)
{
   // The version number to display
   ULONG ulVersionNumber;
   // An adjustment factor by which the concatenated version number
   // should be adjusted for the specific configuration
   UINT uiVersionAdjustment;

   // Concatenate the three digits into one three-digit number
   ulVersionNumber = (100 * VERSION_MAJOR) + (10 * VERSION_MINOR) +
                     (1 * VERSION_BUILD);

   // Adjust the number according to the model type.
   switch (gModelInfo.model)
   {
      // S-250: do not adjust
      case eS250:
         uiVersionAdjustment = 0;
         break;

      // S-343: add 1
      case eS343:
         uiVersionAdjustment = 1;
         break;

      // As a precaution, default to S-250
      default:
         uiVersionAdjustment = 0;
         break;
   }

   // Add the adjustement value to the concatenated number
   ulVersionNumber += uiVersionAdjustment;

   // Return the result
   return ulVersionNumber;
}

void CheckTriggers(void)
{

	unsigned char i; //Array index

	if(gucStateWindSpeed<STATE_FAULT)
   	i=gucStateWindSpeed;
	else if(gucStateWindSpeed<=STATE_WARN)
   {
   	if(gucFaultCode<7)
   		i=STATE_FAULT+gucFaultCode-1;
      else
      	i=14; // Unknown error
   }
   else
		i=14; // Unknown state implies unknown error

	//See if current state and fault code has been selected as a trigger
	if(gbTriggers[i])
   {
   	if(!gbTriggers[sizeof(gbTriggers)-1]);
      {//Trigger has just occured
      	RecordDiagnosticEvent(EV_Trigger);
   		gbTriggers[sizeof(gbTriggers)-1]=TRUE;
      }

   }
}

void EncryptPassword()
{
	//A string consisting of the characters with ASCII codes from
   //35 to 126 inclusive in a random order (except for @ \ %  and "#"):
	const static char RandomString[]=
   "cSX<>k$iob'HtlD|s)zBPf(VK:[]79pnU~v3^{5N,}ZQ-.g=&FAwyG;12_LJdC40Y*Rr?jMEua`I+WhxmOq8T6e/";
   int iLength;
   int iKeyLength;
   int i;
   int j;
	int iOffset;

   iLength=sizeof(gcPasswordKey)-1;
   for(i=0;i<iLength;i++)
		gcPasswordKey[i]= 'A'+ (char)(26*rand());

   gcPasswordKey[i]=0; //Null terminate the string
   iLength=strlen(structPassword.cPassword);
   iKeyLength=strlen(gcPasswordKey);

   for(i=0;i<iLength;i++)
   {
   	j = i % iKeyLength;  //j points to char in key
      iOffset=(*(gcPasswordKey+j)+*(structPassword.cPassword+i))%(sizeof(RandomString)-1);
      gcEncryptedPassword[i]=RandomString[iOffset];
   }

   gcEncryptedPassword[i]=0;	//Add the null terminator


   //Password has just been encrypted so no tower commands will be executed
   //until an encrypted password has been received and validated
   gbPasswordAccepted=FALSE;
}

void  TC_RequestPassKey(void)
{
	char  sTemp[50];  //String to be transmited is constructed here
   char	*p; 			//points to the location in the outgoing string that
         	 			//is under construction

	p=PlaceHeader(sTemp,TR_PasswordKey);

   strcpy(p,gcPasswordKey);  				//Add the password key

   p=p+strlen(gcPasswordKey);          //Adjust string pointer

   strcpy(p,gcCommandTerminator);      //Add the terminator

   SerialSendAeroComm( sTemp );        //Send it

}

void	ExecuteTowerCommand(char *pToParse)
{
	BOOL					bResponseSent;

   bResponseSent=FALSE;

   //Call the function for the command number
   switch( guiTowerCommand )
   {
   	case CMD_NULL:
      	TC_Null();
      	break;

   	case CMD_RUN:
      	TC_Run();
      	break;

   	case CMD_HALT:
      	TC_Halt();
      	break;

   	case CMD_CLEARSVC:
      	TC_ClearSVC();
      	break;

   	case CMD_CLEARMAX:
      	TC_ClearMax();
      	break;

   	case CMD_CLEAREVNT:
      	TC_ClearEvent();
      	break;

   	case CMD_TESTON:
       	TC_TestOn();
      	break;

   	case CMD_TESTOFF:
      	TC_TestOff();
      	break;

   	case CMD_SetDate:
      	TC_SetDate(pToParse);
   		bResponseSent=TRUE;
      	break;

   	case CMD_SetTime:
      	TC_SetTime(pToParse);
   		bResponseSent=TRUE;
      	break;

   	case CMD_SetIPAdd:
      	TC_SetIPAdd(pToParse);
   		bResponseSent=TRUE;
      	break;

   	case CMD_SetNetmask:
      	TC_SetNetmask(pToParse);
   		bResponseSent=TRUE;
      	break;

   	case CMD_SetNameServer:
      	TC_SetNameServer(pToParse);
   		bResponseSent=TRUE;
      	break;

   	case CMD_SetGateway:
      	TC_SetGateway(pToParse);
   		bResponseSent=TRUE;
      	break;

   	case CMD_SetIPPort:
      	TC_SetIPPort(pToParse);
   		bResponseSent=TRUE;
      	break;

      case CMD_ReqIPinfo:
      	TC_ReqIPinfo();
   		bResponseSent=TRUE;
      	break;

      case CMD_ReqDigIO:
      	gbSendDigIO=TRUE;
      	break;

      case CMD_CancelDigIO:
      	gbSendDigIO=FALSE;
      	break;

      case CMD_ApplyIPSettings:
      	TC_ApplyIPSettings();
   		bResponseSent=TRUE;
      	break;

      case CMD_ParamSet1:
     		giParameterID = eNormal;
         RecordTestMode(giParameterID);
      	break;

      case CMD_ParamSet2:
     		giParameterID = eOverSpeedTest*CommissionTest();
         RecordTestMode(giParameterID);
      	break;

      case CMD_ParamSet3:
     		giParameterID = eRpmErrorTest*CommissionTest();
         RecordTestMode(giParameterID);
      	break;

      case CMD_ParamSet4:
     		giParameterID = eCutOutTest*CommissionTest();
         RecordTestMode(giParameterID);
      	break;

      case CMD_ParamSet5:
     		giParameterID = eAnemometerTest*CommissionTest();
         RecordTestMode(giParameterID);
      	break;

		case CMD_Motor:
      	TC_Motor();
      	break;

      case CMD_ApplyBrake:
      	TC_Brake();
      	break;

      case CMD_StackReport:
      	TC_StackReport();
   		bResponseSent=TRUE;

		case CMD_RequestSiteInfo:
      	TC_RequestSiteInfo();
   		bResponseSent=TRUE;
			break;

		case CMD_SetSiteInfo:
      	TC_SetSiteInfo(pToParse);
   		bResponseSent=TRUE;
         break;

		case CMD_RequestFlashInfo:
      	TC_RequestFlashInfo();
   		bResponseSent=TRUE;
         break;

      case CMD_QueryTestMode:
      	TC_QueryTestMode();
   		bResponseSent=TRUE;
         break;

      case CMD_RequestRecInfo:
      	TC_RequestRecInfo(pToParse);
   		bResponseSent=TRUE;
         break;

      case CMD_RequestMainRec:
      	TC_RequestMainRec(pToParse);
         bResponseSent=TRUE;
         break;

      case CMD_CancelRecords:
      	TC_CancelRecords();
         bResponseSent=TRUE;
      	break;

      case CMD_SetRecInterval:
			TC_SetRecInterval(pToParse);
         bResponseSent=TRUE;
      	break;

	case CMD_RequestDate:
   		TC_RequestDate();
         bResponseSent=TRUE;
      	break;

	case CMD_RequestTime:
   		TC_RequestTime();
         bResponseSent=TRUE;
      	break;

	case CMD_RequestTriggers:
   		TC_RequestTriggers();
         bResponseSent=TRUE;
      	break;

   case CMD_SetTriggers:
         bResponseSent=TRUE;
   		TC_SetTriggers(pToParse);
      	break;

	case CMD_ReqRecInterval:
   		TC_RequestRecInterval();
         bResponseSent=TRUE;
      	break;

	case CMD_RequestPassKey:
		  TC_RequestPassKey();
   	  bResponseSent=TRUE;
        break;

	case CMD_Password:
		  TC_Password(pToParse);
   	  bResponseSent=TRUE;
        break;

	case CMD_NewPassword:
		  TC_NewPassword(pToParse);
   	  bResponseSent=TRUE;
        break;

	case CMD_SetNewPassword:
		  TC_SetNewPassword(pToParse);
   	  bResponseSent=TRUE;
        break;

	case CMD_FwUpgrade:
   	  TC_FwUpgrade(pToParse);
   	  bResponseSent=TRUE;
        break;

   case CMD_Hello:			//This should be the first command sent by
        TC_Hello(pToParse);  //ERI version 10.2 or higher. - Lets us know
      break;                  //Which version of ERI we are connected to.

	}


   //If one of the above functions has sent a reply then
   //we won't send the default reply.
   if (bResponseSent==FALSE) TC_SendDefaultString();

   guiTowerCommand=CMD_NULL;

  // If we get here, all of the fields were parsed correctly ...


}

void TC_Password(char* pToParse)
{
	char	sTemp[20];    	//Construct the response string here
   char* p;             //Pointer into sTemp
	int 	iParseLen;	  	//Length of string being parsed
   int 	iPasswordLen; 	//Length of correctly encrypted password
   int 	iPassStart;   	//Index into pToParse pointing to first char
   					  	  	//in encrypted password
	//															 "0123456789 123456789 12"
	//At this point gucBufferParse should contain "@!C86 xxxxxxxxxxxxxxxx#"
   //where xxxxxxxxxxxxxxxx is the encrypted password.
   //The calling routine has verified that the header is OK and that
   //the last char is '#"
   //The password is padded on both ends with random chars bring the
   //encrypted length to 19 or 20 chars
   //For example if the encrypted password is "abcd" then the ERI would
   //add 8 random chars to the begining and end of the string to make something
   //like "^&oPUU*'abcd^^fhJYtK".  Since we know the password length we know
   //how many chars to through away from each end of the string.

   p=PlaceHeader(sTemp,TR_PasswordResponse);


	iParseLen=strlen(pToParse);
   iPasswordLen=strlen(gcEncryptedPassword);
   iPassStart=(int)((20-iPasswordLen)/2) +6;

	if(iParseLen == iPasswordLen +2*(int)((20-iPasswordLen)/2) +7)
   {
   	//Place a null terminator after the encrypted password
		*(pToParse+iPassStart+iPasswordLen)=0;

    	if( strcmp(gcEncryptedPassword,pToParse+iPassStart) == 0)
      	gbPasswordAccepted=TRUE;
      else
      	gbPasswordAccepted=FALSE;
	}

   //We need a means to get connected when everyone has forgotten the password:
   if( CommissionTest() )  gbPasswordAccepted=TRUE;

   //Convert TRUE or FALSE to ASCII code for 1 or zero.
	*(p++)=(char)gbPasswordAccepted+'0';

   strcpy(p,gcCommandTerminator);      //Add the terminator

   SerialSendAeroComm( sTemp );        //Send the response

}

void 	TC_NewPassword(char* pToParse)
{
	//ERI is attempting to change the password.
   //The new password will be sent back to ERI to verify
   //that nothing was lost in the transmission.
   //If ERI sees the resent password as correct it
   //will send a command to apply the new password.
   //Otherwise it will retransmit the new password and
   //we will end up here again.

	char	sTemp[40];    	//Construct the response string here
   char* p;             //Pointer into sTemp

	//															 "0123456789 123456789 12"
	//At this point gucBufferParse should contain "@!C87 xxxxxxxxxxxxxxxx#"
   //where xxxxxxxxxxxxxxxx is the new password.
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   p=PlaceHeader(sTemp,TR_NewPasswordEcho);	//Construct the header

	//Replace the"#" with the null terminator so the following calls to
   //strcpy() will stop in the right place
   *(pToParse+strlen(pToParse)-1)=0;

   //Copy the new password to the ERI response string
	strcpy(p,pToParse+6);

   //Also copy it to gcPendingPassword. It will be applied later if it
   //is verified by ERI
	strcpy(gcPendingPassword,p);

   //Get the pointer to the end of the ERI response string where the
   //terminator will be added.
   p += strlen(gcPendingPassword);

   strcpy(p,gcCommandTerminator);      //Add the terminator

   SerialSendAeroComm( sTemp );        //Send the response

}

void 	TC_SetNewPassword(char* pToParse)
{
	char	sTemp[20];    	//Construct the response string here
   char* p;             //Pointer into sTemp

	//															 "0123456789 123456789 12"
	//At this point gucBufferParse should contain "@!C88 Set new password#"
   //where xxxxxxxxxxxxxxxx is the new password.
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   //Copy the pending password to the actual password
   strcpy(structPassword.cPassword,gcPendingPassword);

   p=PlaceHeader(sTemp,TR_NewPasswordSet);	//Construct the header

   strcpy(p,gcCommandTerminator);   		   //Add the terminator

   SerialSendAeroComm( sTemp );       			 //Send the response

   //Schedule a flash update for the new password
   gbSemaphoreFlashUpdate[ePassword]=TRUE;

}


// Prepares the controller for a firmware upgrade by halting
// the machine, saving data to flash, and responding to ERI
void  TC_FwUpgrade(char* pToParse)
{
	char	sTemp[20];    	//Construct the response string here
   char* p;             //Pointer into sTemp

	//															 "0123456789 123456789 12"
	//At this point gucBufferParse should contain "@!C89 Disable watchdog#"
   //The calling routine has verified that the header is OK and that
   //the last char is '#"

   //We need to save service hours etc to flash before the new firmware is loaded
	gbSemaphoreFlashUpdate[eFlashStruct] = TRUE ;

	if(gucStateWindSpeed != STATE_HALT)
   	TC_Halt();				  						// force halt state

   p=PlaceHeader(sTemp,TR_WatchDogDisabled);	//Construct the header

   strcpy(p,gcCommandTerminator);   		   //Add the terminator

   SerialSendAeroComm( sTemp );       			 //Send the response
}

void ExtWDCheck() //Called once per second
{
   //This function sets the external watch dog time out and enables it
   //this is only done once shortly after powerup.
   #define EXT_WD_OVERSPEED_RATIO (1.2)


   float hssOverSpeed;   // HSS Overspeed (Hz)
   float lssOverSpeed;   // LSS Overspeed (Hz)
   float sensorRatio; // [LSS (Hz)]/[HSS (Hz)] Ratio
   char strTemp[80];

   if(!gbExtWatchDogSet) //TRUE if the external watch dog is already enabled
   {
      if(gulExtWDConfigTimeout <= 0) //Number of secs left before it can be enabled
      {
         // Calculate variable parameters: model-specific overspeed and ratio values

         // HSS Overspeed (Hz)
         hssOverSpeed = ((RPM_HSS_SYNCHRONOUS * EXT_WD_OVERSPEED_RATIO *
                           HSS_TICKS_PER_REV) / (60));

         // LSS Overspeed (Hz)
         lssOverSpeed = ((RPM_HSS_SYNCHRONOUS * EXT_WD_OVERSPEED_RATIO *
                           LSS_TICKS_PER_REV) / (gModelParams.fGearRatio * 60));

         // [LSS (Hz)]/[HSS (Hz)] Ratio
         sensorRatio  = (LSS_TICKS_PER_REV) /
                           (HSS_TICKS_PER_REV * gModelParams.fGearRatio);


         // Send variable parameters to watchdog
         sprintf(strTemp, "@#CMD12=%.0f#\r\n", lssOverSpeed);
         SerialSendWatchDog((char*)strTemp);

         sprintf(strTemp, "@#CMD22=%.0f#\r\n", hssOverSpeed);
         SerialSendWatchDog((char*)strTemp);

         sprintf(strTemp, "@#CMD31=%.5f#\r\n", sensorRatio);
         SerialSendWatchDog((char*)strTemp);

         //Flag so we wont do it again
         gbExtWatchDogSet = TRUE;
      }
      else
      {
         //One less second to wait
         gulExtWDConfigTimeout--;
      }
   }
}

void FindNewMax(void)
{
   // snapshots for comparisons
   ULONG ulRPMLSS;
   float fMPS;
   float fWatts;
   float fRPMHSS;

   // 20041210 RSF - keep track of parameter maxima ...

   // Power Output (Watts) ...
   fWatts = gfPowerAvgDisplay;  // 20050506 ACH replace with function
   if (fWatts > gFlashStruct.ulPowerMaxX100 / 100.0) // have new maximum ...
   {
     //DiagnosticPrint( "FSMWindSpeed: New Power Max ...\r\n" );
     gFlashStruct.ulPowerMaxX100 = (ULONG) (fWatts * 100.0);

   }

   // Rotor RPM ...
   //Low speed shaft
   ulRPMLSS = (ULONG) RotorRPMGet();
   if (ulRPMLSS > gFlashStruct.ulRPMLSSMax) // have new maximum ...
   {
     //DiagnosticPrint( "FSMWindSpeed: New RPM Max ...\r\n" );
     gFlashStruct.ulRPMLSSMax = ulRPMLSS;
   }

   //High speed shaft
   fRPMHSS = RPMHSSGet();
   if (fRPMHSS > gfMaxRPMHSS)
   {
      gfMaxRPMHSS = fRPMHSS;
   }


   // Wind Speed (MPS) ...
   fMPS = WindSpeedMPSGet();
   if (fMPS > gFlashStruct.ulMPSMaxX100 / 100.0) // have new maximum ...
   {
     //DiagnosticPrint( "FSMWindSpeed: New WS Max ...\r\n" );
     gFlashStruct.ulMPSMaxX100 = (ULONG) (fMPS * 100.0);
   }
}

