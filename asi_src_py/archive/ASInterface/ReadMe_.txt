=====================================================================

                 Bihl + Wiedemann GmbH Mannheim

=====================================================================

IMPORTANT NOTE:
Install AS-Interface Control Tools before use of ASiDrv!

NOTE:
See also the Windows ASiDrv Sample Application in the sample directory!

    ===============================================
      => The use of the individual DLL-functions
            is explained in aasidrv.h. !!!
    ===============================================


Version 2.4.0

Readme.txt for AS-Interface driver ASIPCI.dll, CANOPEN.dll, DN32.dll, DN2.dll, 
DPV1.dll, MB32.dll, PC232.dll, RS32.dll, TCPMB.dll
=====================================================================

Contents of the disk:
---------------------

RS (Standard)-driver:
    rs32.dll		dynamic link library
    rs32.hlp		help file

DeviceNet driver (AS-Interface Spec. 2.04):
    dn32.dll		dynamic link library
    dn32.hlp		help file

DeviceNet driver (AS-Interface Spec. 2.1):
    dn2.dll		dynamic link library
    dn2.hlp		help file

CANopen driver (AS-Interface Spec. 2.1):
    canopen.dll		dynamic link library
    canopen.hlp		help file

Modbus driver:
    mb32.dll		dynamic link library
    mb32.hlp		help file

PC2 driver:
    pc232.dll		dynamic link library
    pc232.hlp		help file

PCI driver:
    asipci.dll		dynamic link library
    asipci.hlp		help file

PROFIBUS DP driver:
    dpv1.dll		dynamic link library
    dpv1.hlp		help file

Ethernet Modbus/TCP driver:
    tcpmb.dll		dynamic link library
    tcpmb.hlp		help file

common files for all drivers:
    asidrv32.dll	dynamic link library that invokes the other dlls
    asidrv32.lib	import library for asidrv32.dll
    aasidrv.h		header file for advanced AS-Interface applications (AS-Interface Spec. 2.1)
    asidrv32.ini	profile (ini file)    
    ReadMe.txt		this file
 
Use of the drivers:
===================
    It is only possible to link one library to your project. Link asidrv32.lib
	to your project. The other dlls will be loaded by the asidrv32.dll.
    
    To get into communication state with a master you must follow the following
    steps (step 2, 3 and 4 are optional):
    1. Call AASiRegisterMaster() to get a master identification number.
    2. Call AASiRegisterIniFileName() if you want to set a new INI filename
    	(Default is "asidrv32.ini" [path is the dll directory])
    3. Call AASiRegisterWindowHandle() if you want the DLL dialogs to be a child of
    	your main applications main window. (Default is NULL).
    4. Call AASiRegisterMsgCallback() if you want to set a callback function for DLL
    	waiting operations. (Default is NULL). This function is not needed for PC2.
    5. Call AASiInitDialog() or AASiInit() to initialize the driver with to without dialog.
    
    6. If all these steps have been performed without error, it is possible to use all
    other communication functions. (see aasidrv.h)
    
    To finish operation
    7. Call AASiExit() to break the master link and
    8. Call AASiUnRegisterMaster() to invalidate the master ID.

_______________________________________________________________________________

The following text explains the driver dependend format of "InitialSettings"
and "DisableSettings" in the functions AASiInit() and AASiInitDialog().
Also, the format of the INI file is explained.

Further information can be found in the header aasidrv.h.

For the function AASiDriver(), which is driver dependent, see
chapter "Driver Specific Functions" in this file.
_______________________________________________________________________________


Driver Dependent Parameters
---------------------------

parameter InitialSettings

If a NULL pointer or an empty string ("") is used instead of the following strings,
the settings of the ini-file are used. The ini-file name must be registered with
AASiRegisterIniFileName().


RS (Standard)-driver:
    "<dllname>: COM <port>, Baud <rate>, Addr <addr>, Circ <circ>"

	dllname: rs32.dll (optionally also with path)
    port (COM port number): 1..MAXPORT
    rate (baud rate):       1200, 2400, 4800, 9600, 19200, 28800, 38400, 57600
    addr (Master address):  -2 = auto search, -1 = no address, 1..32 master
                                address
    circ (AS-Interface circuit number, for double-masters):
                            1 = AS-Interface circuit 1, 2 = AS-Interface circuit 2 
    default: "COM 2, Baud 19200, Addr -2, Circ 1"

Modbus driver:
    "<dllname>: COM <port>, Baud <rate>, Frame <frame>, Addr <addr>"

	dllname: mb32.dll (optionally also with path)
    port (COM port number): 1..MAXPORT
    rate (baud rate):       1200, 2400, 4800, 9600, 19200, 28800, 38400, 57600
    frame (Framing):        data bits, parity, stop bits
    addr (Master address):  -1 = auto search, 1..64 master address
    default: "COM 2, Baud 19200, Frame 8n1, Addr -1"

PC2-driver:
    "<dllname>: IO <IOindex>"

	dllname: pc232.dll (optionally also with path)
    IOindex == 0:       automatic search for AS-Interface PC2
    IOindex <= 8:       index for IObases vector
    IOindex > 0x100:    I/O address

    default: "IO 0"

PCI-driver:
    "<dllname>: ID <deviceid>, Circ <circ>"

	dllname: asipci.dll (optionally also with path)
    deviceid (device position id
		format 0xhhhh (hexadecimal number),
        bit 15..8 = PIC bus
		bit 7..3 = PCI device
		bit 2..0 = PCI function)
		0xFFFF: autosearch, other: device position
    circ (AS-Interface circuit number, for double-masters):
                            1 = AS-Interface circuit 1, 2 = AS-Interface circuit 2          
    default: "ID 0xFFFF, Circ 1"

Ethernet Modbus/TCP driver:
	"<dllname>: Host <ipaddr>, Circ <circ>"

	dllname: tcpmb.dll (optionally also with path)
	ipaddr (IP address): Hostname or IP address
    circ (AS-Interface circuit number): 1 = AS-Interface circuit 1, 2 = AS-Interface circuit 2


PROFIbus driver:
    "<dllname>: COM <port>, Addr <sa1>, Circ <circ>, SA <sa2> BusSet <set>"


	<dllname>: dpv1.dll (optionally also with path)

	<sa1>:     PROFIbus station address of the gateway

	<circ>:    AS-Interface circuit number ("1" or "2")
	           (may be omitted for single masters)

	<sa2>:     PROFIbus station address of the PROFIbus master simulator

	<set>:     Index to the PROFIbus bus parameter set list given in the ini file
	           (the latter two may be omitted if no 'PROFIbus master simulator' 1258)


	- or, in case a Siemens CP is to be used -

	"<dllname>: CPxxxx, Addr <sa1>, Circ <circ>"



parameter DisableSettings

If a NULL pointer or an empty string ("") is used instead of the following strings,
all controls in the protocol settings dialog box will be enabled.

RS (Standard)-driver:
    DisableSettings is a null-terminated string with the format
    "rs32: <com,> <baud,> <addr,> <circ>;"
    If one or more of these options are specified the appropiate selection 
    box(es) are disabled.

Modbus driver:
    DisableSettings is a null-terminated string with the format
    "mb32: <com,> <baud,> <frame,> <addr,> <circ>;"
    If one or more of these options are specified the appropiate selection 
    box(es) are disabled.

PC2-driver:
    "pc232: <IO>;". If IO is part of the string, the I/O port list box will
    be disabled.

PCI-driver:
    "asipci: <io,> <circ>;". If IO is part of the string, the I/O port list box will
    be disabled.

PROFIbus driver:
    "<dpv1: <com,> <addr,> <circ>;"

DeviceNet driver (AS-Interface Spec. 2.04):
	"<dn32: <lpt,> <addr,> <baud>;"

DeviceNet driver (AS-Interface Spec. 2.1):
	"<dn2: <port,> <addr,> <baud,> <circ>;"

CANopen driver
	"<canopen: <port,> <addr,> <baud,> <circ>;"


Ethernet Modbus/TCP driver:
	"tcpmb: <host,> <circ>;"

Warning:
    The drivers names should not have path or extension!



In the function AASiGetSettings() the Settings string has the following format:

parameter Settings

RS (Standard)-driver:
    Short: "COM <port>, Addr <addr>, Circ <circ>"
    Long: "COM <port>, Baud <rate>, Addr <addr>, Circ <circ>"
        Address and circuit are only returned if available.

Modbus driver:
    Short: "COM <port>, Addr <addr>"
    Long: "COM <port>, Baud <rate>, Frame <frame>, Addr <addr>"

PC2 driver:
    Short: "IO <port>"
    Long: "IO <port>"
                                         
PCI driver:
    Short: "ID <port>, Circ <circ>"
    Long: "IO <port>, Circ <circ>"
                                         
Ethernet Modbus/TCP driver:
    Short: "Host <ipaddr>, Circ <circ>"
    Long: "Host <ipaddr>, Circ <circ>"

PCI-driver:
    Short: "ID <deviceid>, Circ <circ>"
    Long: "ID <deviceid>, Circ <circ>"


If asidrv32.lib is used and long format was requested, the selected driver name is added
before the settings string, e.g. "c:\projects\asidrv\rs\rs32.dll: COM 2, Addr 3, Circ 1"


Driver Specific Functions
-------------------------

With the function AASiDriver() you have access to driver specific commands. These
commands only supplement the DLL-functions listed in asidrv.h resp. aasidrv.h Please
use those functions for normal operation of the drivers.

RS (Standard)-driver
and
Modbus driver:
    The function AASiDriver() allows to send any possible telegram.
    Parameters:
        Command is the "command byte" or message ID character as it is described in 
            the ASi-Master manual.
        In is a pointer to the message string you want to send
        Out is a pointer to the answer string to receive

PC2 driver:
    There are four special commands for the PC2 protocol:
    Parameters:
        Command can be one of the four numbers:
            ASIPC2_RESET = 0x100; performs a hardware reset
            ASIPC2_REWRITE = 0x101; rewrites the DPRAM
            ASIPC2_RAW_WRITE = 0x102; direct write access to the DPRAM
            ASIPC2_RAW_READ = 0x103; direct read access to the DPRAM
        In
            ASIPC2_RESET and ASIPC2_REWRITE: idle
            ASIPC2_RAW_WRITE: In is a string with the following contents:
                offset (0-ff), page(0-3), amount, databytes
            ASIPC2_RAW_READ: In is a string with the following contents:
                offset (0-ff), page(0-3), amount
        Out
            ASIPC2_RESET, ASIPC2_REWRITE and ASIPC2_RAW_WRITE: idle
            ASIPC2_RAW_READ: Out is a string of databytes

PCI driver:
        Command can be the following numbers:
            ASIPCI_RESET = 0x100; performs a hardware reset
            ASIPCI_REWRITE = 0x101; rewrites the DPRAM
        In
            ASIPCI_RESET and ASIPCI_REWRITE: idle
        Out
            ASIPCI_RESET and ASIPCI_REWRITE: idle

Ethernet Modbus/TCP driver:
	The function AASiDriver makes it possible to read or write every accessable
	Modbus register.
    Parameters:
      Write registers:
        Command:
            ASITCPMB_WRITE_REGISTER = 0x200: writes a register
		In[0]: first register address, low byte
		In[1]: first register address, high byte
		In[2]: number of registers (words) to write (maximum: 128)
		In[3]: data word 1, low byte
		In[4]: data word 1, high byte
		In[5]: data word 2, low byte
		In[6]: data word 2, high byte
		...
      Read registers:
        Command (defined in tcpmb.h):
            ASITCPMB_READ_REGISTER = 0x201: reads a register
		In[0]: first register address, low byte
		In[1]: first register address, high byte
		In[2]: number of registers (words) to read (maximum: 128)
		Out[0]: data word 1, low byte
		Out[1]: data word 1, high byte
		Out[2]: data word 2, low byte
		Out[3]: data word 2, high byte
		...
_______________________________________________________________________________


Ini file:
---------

The default name for the ini file is "asidrv32.ini".
The INI file can contain a section for the current driver. If no section
is specified default settings are used.
This section name is created from the dll name, e.g. [PC232] or [RS32]. It can
contain an entry called "Settings=" followed by the Settings string as it is
decribed for the function AASiInit() or AASiInitDialog(). (see also above)

If you use asidrv.dll, the ini file must also contain a section [PROTOCOLS] for
the default driver list (if the parameter Drivers is not used). The entry names
must be unique for every driver. The contents string must consist of two parts:
the DLL name (with or without path and extension) and the visible text for the
dialog box.
The section [ASIDRV32] contains the default DLL name (with or without path and
extension) that is used if no driver is specified.

    Ini file template:

	[PROTOCOLS]
	RS32=rs32.dll: Standard
	RRS32=rs32.dll: Rockwell
	RRRS32=rs32.dll: Stainless Steel AS-i Master
	PC232=pc232.dll: AS-Interface PC2
	ASIPCI=asipci.dll: AS-Interface PCI
	CANOPEN=canopen.dll: CANopen 2.1
	DN2=dn2.dll: DeviceNet 2.1
	DN32=dn32.dll: DeviceNet 2.04
	TCPMB=tcpmb.dll: Ethernet Modbus/TCP
	MB32=mb32.dll: Modbus
	DPV1=dpv1.dll: PROFIBUS/DPV1

	[ASIDRV32]
	Default=RS32

	[RS32]
	Settings=COM 2, Baud 57600, Addr -2

	[PC232]
	Settings=IO 0

	[ASIPCI]
	Settings=ID 0x70, Circ 1

	[CANOPEN]
	Settings=Port LPT1, Addr 3, Baud 125, Circ 1

	[DN32]
	Settings=LPT 1, Baud 125k, Addr -1

	[TCPMB]
	ConnectionTimeout=10
	Settings=Host 192.168.42.152, Circ 2

	[MB32]
	Settings=COM 2, Baud 57600, Frame 8n1, Addr -1

	[DPV1]
	Settings=COM 2, Addr -1, Circ 1
	VendorID=0x1742, 0x1745, 0x1746, 0x0091
	Set0=9.6 kBaud,01,00,60,09,C0,12,33,00,7D,7E,01,2C,01,04,0B,1C,1E,D4,30,61,51,2B,68,1F,3A,D0,05
	Set1=19.2 kBaud,01,00,60,09,C0,12,33,00,7D,7E,01,22,00,04,31,0E,0F,6A,18,B1,28,15,34,10,1D,E8,02
	Set2=93.75 kBaud,01,00,60,09,C0,12,33,00,7D,7E,01,1F,00,04,0B,15,03,00,05,55,08,AB,0A,F4,05,98,00
	Set3=187.5 kBaud,01,00,60,09,C0,12,33,00,7D,7E,01,13,00,04,09,8B,01,80,02,2B,04,55,05,FA,02,4C,00
	Set4=500 kBaud,01,00,60,09,C0,12,33,00,7D,7E,01,08,00,04,08,94,00,90,01,20,03,00,04,2C,01,1E,00
	Set5=1.5 MBaud,01,00,60,09,C0,12,33,00,7D,7E,01,01,00,04,15,31,00,C8,00,90,01,00,02,6B,00,0B,00
	BaudInd=-1
