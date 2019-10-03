/*********************************************************************
 *
 *                       Bihl+Wiedemann GmbH
 *
 *
 *       project: AS-Interface Driver
 *   module name: aasidrv.h
 *        author: Daniel Rudolf
 *          date: 11/12/96
 *
 *      RCS info:
 *         $Date: 2007/02/22 13:41:28 $
 *       $Locker:  $
 *     $Revision: 1.26 $
 *        $State: Exp $
 *
 *       history:
 *
 *   description:
 *  Header file for applications that use the AS-Interface driver DLLs with the
 *  AASi...-functions according to AS-Interface spec. 2.1
 *
 *********************************************************************/

#ifndef AASIDRV_H
#define AASIDRV_H

#ifdef _WINDOWS
#	include <windows.h>
#	ifdef _WIN32
#		if (defined(_CVI_)) || (defined(_NI_i386_)) || (defined(_NI_mswin_))
#			define EXP __stdcall __export
/*			windowsx.h is not delivered with CVI	*/
#		else
#			define EXP __stdcall
#			include <windowsx.h>
#		endif
#	else
#		define EXP FAR __pascal __export
#	endif
#else
#   define EXP FAR
	typedef char FAR*        LPSTR;
	typedef const char FAR*  LPCSTR;
    typedef enum {FALSE = 0, TRUE = 1} BOOL;
#endif

/*********************************************************************
 *  global definitions                                               *
 *********************************************************************/

#define	ASI_MASK_DUPLICATE_ADR     0x080           /* mask to duplicate adr */
#define	ASI_MASK_EFLT			   0x010           /* mask to earth fault */
#define	ASI_MASK_OVERVOLTAGE	   0x020           /* mask to overvoltage */
#define	ASI_MASK_NOIS			   0x040           /* mask to noise */
#define	ASI_MASK_24V_ERROR		   0x008           /* mask to 24V error (retundant) */

/*  Return codes
 */
#define	ASI_ERR_MASK_TYPE     0xF000           /* mask to get the error type */
#define	ASI_ERR_MASK_DETAIL   0x0FFF           /* mask to get the error detail */

#define ASI_ERR_OK            0x0000           /* no error occured */
#define ASI_ERR_MASTER        0x1000           /* generic master error */
#define ASI_ERR_INTERFACE     0x2000           /* generic interface error */
#define ASI_ERR_DRIVER        0x3000           /* generic driver error */
#define ASI_ERR_DRIVER_CHANGE 0x4000           /* other interface selected */ 
#define ASI_ERR_USER          0x8000           /* reserved for user extensions */ 

#define ASI_ERR_SND (ASI_ERR_MASTER | 0x02)    /*  Slave (adr1) Not Detected   */
#define ASI_ERR_SD0 (ASI_ERR_MASTER | 0x03)    /*  Slave 0 Detected            */
#define ASI_ERR_SD2 (ASI_ERR_MASTER | 0x04)    /*  Slave (adr2) Detected       */
#define ASI_ERR_DE  (ASI_ERR_MASTER | 0x05)    /*  Delete Error                */
#define ASI_ERR_SE  (ASI_ERR_MASTER | 0x06)    /*  Set Error                   */
#define ASI_ERR_AT  (ASI_ERR_MASTER | 0x07)    /*  Adress stored temporarily   */
#define ASI_ERR_APF (ASI_ERR_MASTER | 0x08)    /*  AS-Interface power failure  */

#define ASI_ERR_NOCTRL       (ASI_ERR_MASTER | 0x10)    /* no AS-Interface Control connected */
#define ASI_ERR_UNSUPPORTED  (ASI_ERR_MASTER | 0x11)    /* command not supported     */

/* error codes for the "write extended ID code 1" function
 */
#define AASI_ERR_SND (ASI_ERR_MASTER | 0x12)    /*  Slave 0 Not Detected   */
#define AASI_ERR_SE  (ASI_ERR_MASTER | 0x13)    /*  Set Error              */
#define AASI_ERR_ET  (ASI_ERR_MASTER | 0x14)    /*  Extended ID1 stored temporarily */
#define AASI_ERR_RE  (ASI_ERR_MASTER | 0x15)    /*  Error reading extended ID1 */

#define ASI_ERR_ERRORTEL   	(ASI_ERR_MASTER | 0x20)		/* error telegram */
#define ASI_ERR_WATCHDOG   	(ASI_ERR_MASTER | 0x21)		/* watchdog has barked */
#define ASI_ERR_CIRC    	(ASI_ERR_MASTER | 0x22)		/* AS-Interface circuit 2 not available */
#define ASI_ERR_DENYED   	(ASI_ERR_MASTER | 0x23)		/* denyed telegram */


/* error codes for "AS-Interface UART" function
*/
#define ASI_ERR_UART   (ASI_ERR_MASTER | 0x30)    /*  generic UART error          */
#define ASI_ERR_ONLINE (ASI_ERR_MASTER | 0x31)    /*  master not offline          */

/* error codes for string transfer functions (7.4 slaves)
*/
#define ASI_ERR_READ_STRING   (ASI_ERR_MASTER | 0x41)    /*  could not read string         */
#define ASI_ERR_WRITE_STRING  (ASI_ERR_MASTER | 0x42)    /*  could not write string         */

#define ASI_ERR_TIMEOUT    	(ASI_ERR_INTERFACE | 0x10)	/* timeout */
#define ASI_ERR_OVERRUN    	(ASI_ERR_INTERFACE | 0x11)	/* uart overrun */
#define ASI_ERR_PARITY    	(ASI_ERR_INTERFACE | 0x12)	/* parity error */
#define ASI_ERR_FRAMING    	(ASI_ERR_INTERFACE | 0x13)	/* framing error */
#define ASI_ERR_BREAK    	(ASI_ERR_INTERFACE | 0x14)	/* wire break */
#define ASI_ERR_PROTOCOL_BUS_NONE			(ASI_ERR_INTERFACE | 0x15)
#define ASI_ERR_PROTOCOL_BUS_ADDRESS		(ASI_ERR_INTERFACE | 0x16)
#define ASI_ERR_CONVERTER					(ASI_ERR_INTERFACE | 0x18)
#define ASI_ERR_DONGLE						(ASI_ERR_INTERFACE | 0x19)
#define ASI_ERR_LICENCE						(ASI_ERR_INTERFACE | 0x1A)

#define ASI_ERR_HOSTNAMENOTFOUND   (ASI_ERR_INTERFACE | 0x20)
#define ASI_ERR_INVALIDHOSTADDRESS (ASI_ERR_INTERFACE | 0x21)
#define ASI_ERR_INPROGRESS         (ASI_ERR_INTERFACE | 0x22)  /* a blocking Windows Sockets 1.1 call is in progress */
#define ASI_ERR_NETDOWN            (ASI_ERR_INTERFACE | 0x23)
#define ASI_ERR_NETRESET           (ASI_ERR_INTERFACE | 0x24)
#define ASI_ERR_CONNABORTED        (ASI_ERR_INTERFACE | 0x25)
#define ASI_ERR_NOTCONN            (ASI_ERR_INTERFACE | 0x26)
#define ASI_ERR_HOSTUNREACH        (ASI_ERR_INTERFACE | 0x27)
#define ASI_ERR_PROCLIM            (ASI_ERR_INTERFACE | 0x28)
#define ASI_ERR_SYSNOTREADY        (ASI_ERR_INTERFACE | 0x29)
#define ASI_ERR_VERNOTSUPPORTED    (ASI_ERR_INTERFACE | 0x2A)
#define ASI_ERR_CONNRESET          (ASI_ERR_INTERFACE | 0x2B)

#define ASI_ERR_INIT     	(ASI_ERR_DRIVER | 0x01)    /* driver not initialized */
#define ASI_ERR_VALUE    	(ASI_ERR_DRIVER | 0x02)    /* bad driver parameters */
#define ASI_ERR_NOTFOUND 	(ASI_ERR_DRIVER | 0x03)    /* no master found */
#define ASI_ERR_CANCEL   	(ASI_ERR_DRIVER | 0x04)    /* user cancel */
#define ASI_ERR_DRVNOTFOUND (ASI_ERR_DRIVER | 0x05)    /* driver not found */
#define ASI_ERR_NODRIVER 	(ASI_ERR_DRIVER | 0x06)    /* no driver selected */
#define ASI_ERR_NOFUNC	 	(ASI_ERR_DRIVER | 0x07)    /* unable to call function */
#define ASI_ERR_NOMASTERID 	(ASI_ERR_DRIVER | 0x08)	   /* Master ID invalid */
#define ASI_ERR_DRVINIT		(ASI_ERR_DRIVER | 0x10)    /* COM driver not initialized	*/
#define ASI_ERR_BAUD    	(ASI_ERR_DRIVER | 0x11)    /* invalid baud rate	*/
#define ASI_ERR_PORT    	(ASI_ERR_DRIVER | 0x12)    /* invalid port number */
#define ASI_ERR_PAR    		(ASI_ERR_DRIVER | 0x13)    /* bad parameter    			*/
#define ASI_ERR_FRAMEPAR 	(ASI_ERR_DRIVER | 0x14)    /* bad parameter    			*/
#define ASI_ERR_NOUART    	(ASI_ERR_DRIVER | 0x15)    /* UART not found */
#define ASI_ERR_NOMEM       (ASI_ERR_DRIVER | 0x16)    /* memory allocation failed */
#define ASI_ERR_BUFFER	    (ASI_ERR_DRIVER | 0x17)    /* internal buffer overflow	*/
#define ASI_ERR_TELTYPE		(ASI_ERR_DRIVER | 0x20)    /* telegram type			*/
#define ASI_ERR_TELLENGTH	(ASI_ERR_DRIVER | 0x21)    /* telegram length			*/
#define ASI_ERR_CHECKSUM	(ASI_ERR_DRIVER | 0x22)    /* checksum error			*/
#define ASI_ERR_FUNCTION	(ASI_ERR_DRIVER | 0x23)    /* illegal function		*/
#define ASI_ERR_DATA_ADDR	(ASI_ERR_DRIVER | 0x24)    /* invalid data address 	*/
#define ASI_ERR_DATA_VAL	(ASI_ERR_DRIVER | 0x25)    /* invalid data value		*/
#define ASI_ERR_BAD_DRIVER  (ASI_ERR_DRIVER | 0x26)    /* bad device driver installed */
#define ASI_ERR_INI	        (ASI_ERR_DRIVER | 0x81)    /* ini-file error */
#define ASI_ERR_NOTAVAIL    (ASI_ERR_DRIVER | 0x90)    /* function not available */

/*  Execution Control flags
 */
#define ASI_CONFIG_OK               0x01			/* there is no configuration error */
#define ASI_LDS0                    0x02			/* a slave with address zero is existing */
#define ASI_AUTO_ADDRESS_ASSIGN     0x04			/* automatic programming is activated */
#define ASI_AUTO_ADDRESS_AVAILABLE  0x08			/* automatic programming is avalible */
#define ASI_CONFIGURATION_ACTIVE    0x10			/* the configuration mode is active */
#define ASI_NORMAL_OPERATION_ACTIVE 0x20			/* the normal operation mode is active */
#define ASI_APF                     0x40			/* ASI has power fail */
#define ASI_OFFLINE_READY           0x80			/* the offline phase is active */
#define AASI_PERIPHERY_OK           0x100			/* there is no peripheral fault */


/*  Host Interface flags
 */
#define ASI_DATA_EXCHANGE_ACTIVE    0x01			/* bit reset: data exchange with the slaves is locked */
#define ASI_OFFLINE                 0x02			/* bit set: master is set to offline state */
#define ASI_AUTO_ADDRESS_ENABLE     0x04			/* bit set: automatic programming is allowed */

/*  Bitcodes for ASiCtrlFlags
 */
#define ASI_CTRL_RUN                0x01			/* bit set: start control program */
#define ASI_CTRL_RESET              0x02			/* bit set: reset control program */
#define ASI_CTRL_IGNORE_CONFIG_OK   0x04			/* bit set: configuration errors are ignored */
#define ASI_CTRL_AUTO_START         0x08			/* bit set: automatic program start */
#define ASI_CTRL_COUNTER_MAP        0x10			/* bit set: the counters are mapped into user data field */
#define ASI_CTRL_INPUT_FILTER       0x20            /* bit set: inputs are filtered */
#define ASI_CTRL_SYNCHRONIZE        0x40            /* bit set: controller program is synchronized with the AS-Interface cycle */
#define ASI_CTRL_ACTIVE             0x80			/* bit set: a program is running */

/*	String constants
 */
#ifdef _WIN32
#define DEFAULT_INI_FILENAME "asidrv32.ini"			/* name of ini file */
#else
#define DEFAULT_INI_FILENAME "asidrv.ini"			/* name of ini file */
#endif

/*********************************************************************
 *  type definitions                                                 *
 *********************************************************************/

typedef unsigned char    AASiProcessData [32];

#if (defined(NOINT64))
typedef struct
{
	/* Both AS-Interface circuits */
	unsigned long a;
	unsigned long b;
}
AASiSlaveList;
#else
typedef unsigned __int64 AASiSlaveList;
#endif

typedef unsigned char    AASiHiFlags;
typedef unsigned short   AASiEcFlags;
typedef unsigned char    AASiSlaveData;
typedef unsigned char    AASiSlaveAddr;
typedef unsigned short   AASiConfigData;

typedef unsigned char  AASiErrorCounters [64];
//typedef unsigned short AASi16BitData [4];
typedef signed short AASi16BitData [4];

typedef struct {
    AASiConfigData PCD [64];
    AASiSlaveData PP [64];
} AASiConfig;

typedef unsigned char  AASiCtrlData [16];
typedef unsigned short AASiCtrlAddr;
typedef unsigned char  AASiCtrlFlags;

typedef enum {
	A_DT_NULL     = 0x0000,
	A_DT_NIBBLE   = 0x0001,
	A_DT_BYTE     = 0x0002,
	A_DT_WORD     = 0x0003,
	A_DT_DWORD    = 0x0004,
	A_DT_QUARTERK = 0x0005,
	A_DT_USIGN8   = 0x0011,
	A_DT_USIGN16  = 0x0012,
	A_DT_USIGN32  = 0x0013,
	A_DT_FUNCTION = 0x1000,
} AASiCtrlResDT;

typedef enum {
	A_AR_NULL      = 0x0000,
	A_AR_NONE      = 0x0001,
	A_AR_READ      = 0x0002,
	A_AR_READWRITE = 0x0003,
	A_AR_WRITE     = 0x0004,
	A_AR_EXECUTE   = 0x1000,
	A_AR_COUNTER   = 0x7F00,
	A_AR_TIMER     = 0x7F01,
} AASiCtrlResAR;

typedef struct {
	unsigned int  ID;
	unsigned int  Address;
	unsigned char Extra;
	AASiCtrlResDT  Type;
	AASiCtrlResAR  Access;
	unsigned int  Size;
	char          Symbol [10];
	char          Text   [50];
} AASiCtrlResource;

typedef struct
{
	unsigned char DataLen;
	unsigned char Opcode;
	unsigned char Circuit;
	unsigned char Data [36];
} AASiMbRequestType;

typedef struct
{
	unsigned char DataLen;
	unsigned char Opcode;
	unsigned char Result;
	unsigned char Data [36];
} AASiMbResponseType;

/*********************************************************************
 *  public functions                                                  *
 *********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


/*************************************************************
 *
 *  error = AASiRegisterMaster (lpsMasterID);
 *
 *  description:
 *		Gets a new handle (Master Identifer) for AS-Interface Master
 *		operation. All Master functions need this handle as
 *		master identification. 
 *		To finish all operations with a master ID call AASiUnRegisterMaster().
 *		If the master ID is invalid, it holds the value -1.
 *
 *  parameters:
 *
 *  returns:
 *		lpsMasterID: pointer to master identifier. The return value of the
 *			master identifier is >= 0. 
 */ 
int EXP AASiRegisterMaster (int FAR *lpsMasterID);

/*************************************************************
 *
 *  error = AASiUnRegisterMaster (MasterID);
 *
 *  description:
 *		Invalidates the master identifier and closes all master
 *		operation done with this handle.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *  returns:
 */ 
int EXP AASiUnRegisterMaster (int MasterID);

/*********************************************************************
 *
 *  error = AASiInit (MasterID, Settings);
 *
 *  description:
 *		Initializes the driver
 *
 *  parameters:
 *		MasterID: master identifier
 *		Settings is a null-terminated string with a driver dependent format.
 *		(See readme.txt).
 *		If Settings is NULL, the string is read from driver section of the ini file.
 *		If the string can't be loaded from the ini file, the default settings
 *		are used.
 *		On usage asidrv.lib is is neccesary to add the DLL name of the driver
 *		(with or without path and extension) before the settings parameter.
 *		Both parts must be seperated with " " or ": ". It is also possible to
 *		specify only the DLL name - then the default settings are used and only
 *		the driver is selected.
 *
 *  returns:
 */
int EXP AASiInit (int MasterID, LPCSTR Settings);

/*********************************************************************
 *
 *  error = AASiInitDialog (MasterID, Drivers, InitialSettings,
 *		DisableSettings);
 *
 *  description:
 *		Initializes the driver with user dialog
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *		Drivers is a pointer to the driver list.
 *		The driver list is a string list terminated with a NULL pointer.
 *		Each string describes one entry for the driver selection box in the
 *		following format:
 *		<DLL name (with or without path and extension)>: <String to display
 *			in the dialog selection box>
 *		If a NULL pointer is specified the selection box is disabled. On use
 *		of asidrv.lib the driver list is read from the INI file (with NULL
 *		pointer specified).
 *
 *		InitialSettings is a null-terminated string with a driver dependent
 *		format (See readme.txt).
 *		If asidrv.lib is used, it is neccesary to add the DLL name
 *		of the driver before the settings string. Both parts must be seperated
 *		with " " or ": ". It is also possible to specify only the DLL name -
 *		then the default settings are used and only the driver is selected.
 *		If InitialSettings is NULL, the string is read from the ini file.
 *		If the string can't be loaded from the ini file, the default settings
 *		are used.
 *
 *		DisableSettings is a null-terminated string with a driver dependent
 *		format (See readme.txt).
 *	
 */
int EXP AASiInitDialog (int MasterID, LPCSTR FAR Drivers [], LPCSTR InitialSettings, LPCSTR DisableSettings);

/*********************************************************************
 *
 *  AASiExit(MasterID)
 *
 *  description:
 *		Close AS-Interface Driver.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *	returns:
 */
int EXP AASiExit (int MasterID);

// wraps function below for the use with Visual Basic
int EXP VBAASiGetSettings(int MasterID, LPSTR Settings, unsigned int Length, BOOL Short);

/*********************************************************************
 *
 *  AASiGetSettings(MasterID, Settings, Short)
 *
 *  description:
 *		Get the actual driver configuration (See readme.txt).
 *
 *  parameters:
 *		MasterID: master identifier
 *		Short: Short (TRUE) or Long (FALSE) string format
 *
 *	returns:
 *		Settings: With Short == FALSE, the driver configuration is returned
 *		as a string in the same format as the AASiInit() Settings string.
 *		If asidrv.lib is used, the drivers name is added before the settings
 *		entry.
 *
 */
int EXP AASiGetSettings (int MasterID, LPCSTR FAR *Settings, BOOL Short);

/*********************************************************************
 *
 *  AASiDriver(MasterID, Command, In, Out)
 *
 *  description:
 *		Protocol specific calling function. (See readme.txt)
 *
 *  parameters:
 *		MasterID: master identifier
 *		Command: ASi Master command
 *		In: Message data to the master
 *		Out: Response data from the master
 *
 *	returns:
 */
int EXP AASiDriver (int MasterID, int Command, void FAR *In, void FAR *Out);

// wraps function below for the use with Visual Basic
int EXP VBAASiGetDriverName(int MasterID, LPSTR Name, unsigned int Length, BOOL Short);

/*********************************************************************
 *
 *  AASiGetDriverName(MasterID, Name, Short)
 *
 *  description:
 *		Get the name of this driver.
 *
 *  parameters:
 *		MasterID: master identifier
 *		Short: Short (TRUE) or Long (FALSE) string format
 *
 *	returns:
 *		Name: Driver name
 */
int EXP AASiGetDriverName (int MasterID, LPCSTR FAR *Name, BOOL Short);

// wraps function below for the use with Visual Basic
int EXP VBAASiGetErrorMessage(int MasterID, int ErrorCode, LPSTR Name, unsigned int Length);

/*********************************************************************
 *
 *  AASiGetErrorMessage(MasterID, ErrorCode, Name)
 *
 *  description:
 *		Transformation of the error code to an error description string.
 *
 *  parameters:
 *		MasterID: master identifier
 *		ErrorCode: Error code to analyze.
 *
 *	returns:
 *		Name: Description string for the error code. The contents of name
 *			is only valid until the next invocation of AASiGetErrorMessage
 *			(which can eventually be called by a second application using
 *			this dll) since the text is stored in a static local character
 *			string.
 */
int EXP AASiGetErrorMessage (int MasterID, int ErrorCode, LPCSTR FAR *Name);

/*  Execution Control
 */
/*********************************************************************
 *
 *  error = AASiDataExchange (MasterID, ODI, IDI, &EcFlags);
 *
 *  description:
 *		exchange of ASi Slave data and reading of the execution control flags.
 *
 *  parameters:
 *		MasterID: master identifier
 *		ODI: 32 bytes output data to the slaves (output data image).
 *			Every slave uses one nibble of a byte. The format is as follows:
 *			Byte  0, low  nibble: data of slave  0/0A
 *			Byte  0, high nibble: data of slave  1/1A
 *			...
 *			Byte 15, low  nibble: data of slave 30/30A
 *			Byte 15, high nibble: data of slave 31/31A
 *			Byte 16, low  nibble: data of slave  0B
 *			Byte 16, high nibble: data of slave  1B
 *			...
 *			Byte 31, low  nibble: data of slave 30B
 *			Byte 31, high nibble: data of slave 31B
 *
 *	returns:
 *		IDI: 32 bytes input data from the slave (input data image).
 *			The format is the same is in ODI.
 *
 *		EcFlags: Execution control flags (2 bytes) of the AS-Interface Master.
 *			The flags are defined in aasidrv.h
 */
int EXP AASiDataExchange (int MasterID, AASiProcessData FAR ODI, AASiProcessData FAR IDI, AASiEcFlags FAR *EcFlags);

/*********************************************************************
 *
 *  error = AASiReadIDI (MasterID, IDI, First, Amount, &EcFlags);
 *
 *  description:
 *		read the input data of specific slave and the execution control flags.
 *
 *  parameters:
 *		MasterID: master identifier
 *		First: Index of the first slave to get data from (0..63)
 *		Amount: Number of slaves to get data from. (1..64)
 *
 *	returns:
 *		IDI: 32 bytes input data of the slaves (input data image).
 *			Every slave uses one nibble of a byte. Unused bytes are set to zero.
 *			The format is as follows:
 *			Byte 0, low  nibble: Slave 'First' data
 *			Byte 0, high nibble: Slave 'First'+1 data
 *			...
 *
 *		EcFlags: Execution control flags (2 bytes) of the ASi Master.
 *			The flags are defined in aasidrv.h
 */
int EXP AASiReadIDI (int MasterID, AASiProcessData FAR IDI, AASiSlaveAddr First, unsigned char Amount, AASiEcFlags FAR *EcFlags);

/*****************************************************************
 *
 *  error = AASiWriteODI (MasterID, ODI, First, Amount);
 *
 *  description:
 *		Writes output data to specific slaves.
 *
 *  parameters:
 *		MasterID: master identifier
 *		ODI: 32 bytes of output data (output data image).
 *			Every slave uses one nibble of a byte.
 *			The format is as follows:
 *			Byte  0, low  nibble: Slave  'First' data
 *			Byte  0, high nibble: Slave  'First'+1 data
 *			...
 *
 *		First: Index of the first slave to send data to (0..63)
 *
 *		Amount: Number of slaves to send data to. (1..64)
 *
 *	returns:
 */
int EXP AASiWriteODI (int MasterID, AASiProcessData FAR ODI, AASiSlaveAddr First, unsigned char Amount);

/************************************************************
 *
 *  error = AASiReadODI (MasterID, ODI);
 *
 *  description:
 *		Read back the actual output data from the AS-Interface master.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *  returns:
 *		ODI: 32 bytes output data to the slaves (output data image).
 *			Every slave uses one nibble of a byte. The format is as follows:
 *			Byte  0, low  nibble: data of slave  0/0A
 *			Byte  0, high nibble: data of slave  1/1A
 *			...
 *			Byte 15, low  nibble: data of slave 30/30A
 *			Byte 15, high nibble: data of slave 31/31A
 *			Byte 16, low  nibble: data of slave  0B
 *			Byte 16, high nibble: data of slave  1B
 *			...
 *			Byte 31, low  nibble: data of slave 30B
 *			Byte 31, high nibble: data of slave 31B
 *          
 */
int EXP AASiReadODI (int MasterID, AASiProcessData FAR ODI);

/**************************************************************
 *
 *  error = AASiWritePP (MasterID, Address, PP);
 *
 *  description:
 *		Set the permanent parameters of one slave
 *
 *  parameters:
 *		MasterID: master identifier
 *		Address: Address of slave to set the parameters for (1..31, 33..63).
 *		PP:	Permanent parameters to set (low nibble).
 *
 *  returns:
 */
int EXP AASiWritePP (int MasterID, AASiSlaveAddr Address, AASiSlaveData PP);

/***************************************************************
 *
 *  error = AASiReadPP (MasterID, Address, &PP);
 *
 *  description:
 *		Read the permanent parameters of one slave
 *
 *  parameters:
 *		MasterID: master identifier
 *		Address: Address of slave to get the parameters from (1..31, 33..63).
 *
 *  returns:
 *		PP: Permanent parameters of the slave (low nibble)
 */
int EXP AASiReadPP (int MasterID, AASiSlaveAddr Address, AASiSlaveData FAR *PP);
                                                 
/*********************************************************************
 *
 *  error = AASiSendParameter (MasterID, Address, PI, &Ret);
 *
 *  description:
 *		Send parameters to one slave.
 *
 *  parameters:
 *		MasterID: master identifier
 *		Address: Address of slave to send parameters to (1..31, 33..63).
 *		PI: Parameters to send (low nibble)
 *
 *	returns:
 *		Ret: On error PI is returned inverted.
 */
int EXP AASiSendParameter (int MasterID, AASiSlaveAddr Address, AASiSlaveData PI, AASiSlaveData FAR *Return);

/*********************************************************************
 *
 *  error = AASiReadPI (MasterID, Address, &PI);
 *
 *  description:
 *		Read the actual parameters of one slave
 *
 *  parameters:
 *		MasterID: master identifier
 *		Address: Address of slave to read the parameters from (1..31, 33..63).
 *
 *	returns:
 *		PI: Parameters of the slave. (low nibble).
 */
int EXP AASiReadPI (int MasterID, AASiSlaveAddr Address, AASiSlaveData FAR *PI);

/*********************************************************************
 *
 *  error = AASiStorePI (MasterID);
 *
 *  description:
 *		Store the actual slave parameters as permanent parameters.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *	returns:
 */
int EXP AASiStorePI (int MasterID);

/*************************************************************
 *
 *  error = AASiReadDuplicateAdrList (MasterID, Address, SingleTransfer, Request, Response);
 *
 *  description:
 *		Read List of duplicate address
 *
 *  parameters:
 *		MasterID: master identifier
 *		DpAdrList: List of duplicate address
 *
 *  returns:
 *	
 */
int EXP AASiReadDuplicateAdrList (int MasterID, AASiSlaveList  *DpAdrList);

/*************************************************************
 *
 *  error = AASiReadFaultDetector (MasterID, unsigned char  *pucFaultDetectorActiv, unsigned char  *pucFaultDetectorHistoric);
 *
 *  description:
 *		Read Overvoltage, Nois, EFLT, Duplicate adr.
 *
 *  parameters:
 *		MasterID:				  master identifier
 *		pucFaultDetectorActiv:    active fault detector
 *		pucFaultDetectorHistoric: historic fault detector
 *
 *  returns:
 *	
 */
int EXP AASiReadFaultDetector (int MasterID, unsigned char  *pucFaultDetectorActiv, unsigned char  *pucFaultDetectorHistoric);

/*********************************************************************
 *
 *  error = AASiWritePCD (MasterID, Address, PCD);
 *
 *  description:
 *		Write the projected configuration of one slave.
 *
 *  parameters:
 *		MasterID: master identifier
 *		Address: Address of the slave to write the configuration to (1..31, 33..63).
 *		PCD:	 Configuration to write.
 *	             Byte 0, low nibble: I/O configuration
 *	             Byte 0, high nibble: slave ID
 *	             Byte 1, low nibble: extended ID1
 *	             Byte 1, high nibble: extended ID2
 *
 *  returns:
 */
int EXP AASiWritePCD (int MasterID, AASiSlaveAddr Address, AASiConfigData PCD);

/************************************************************************
 *
 *  error = AASiReadPCD (MasterID, Address, &PCD);
 *
 *  description:
 *		read the projected configuration of one slave.
 *
 *  parameters:
 *		MasterID: master identifier
 *		Address: Address of slave to read the configuration from (1..31, 33..63).
 *
 *  returns:
 *		PCD: Configuration of the slave
 *	             Byte 0, low nibble: I/O configuration
 *	             Byte 0, high nibble: slave ID
 *	             Byte 1, low nibble: extended ID1
 *	             Byte 1, high nibble: extended ID2
 */
int EXP AASiReadPCD (int MasterID, AASiSlaveAddr Address, AASiConfigData FAR *PCD);

/*************************************************************************
 *
 *  error = AASiStoreCDI (MasterID);
 *
 *  description:
 *		Store the actual configuration as permanent configuration.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *  returns:
 */
int EXP AASiStoreCDI (int MasterID);

/***********************************************************************
 *
 *  error = AASiReadCDI (MasterID, Address, &CDI);
 *
 *  description:
 *		Read the actual configuration of one slave.
 *
 *  parameters:
 *		MasterID: master identifier
 *		Address: Address of slave to get the configuration from (0..31, 33..63).
 *
 *  returns:
 *		CDI: Configuration of the slave
 *	             Byte 0, low nibble: I/O configuration
 *	             Byte 0, high nibble: slave ID
 *	             Byte 1, low nibble: extended ID1
 *	             Byte 1, high nibble: extended ID2
 */
int EXP AASiReadCDI (int MasterID, AASiSlaveAddr Address, AASiConfigData FAR *CDI);

/*********************************************************************
 *
 *  error = AASiWriteExtID1 (MasterID, ID1);
 *
 *  description:
 *		Write the extended ID code 1 of slave 0
 *
 *  parameters:
 *		MasterID: master identification address
 *		ID1: extended ID code 1
 *
 *  returns:
 *		This function returns special error codes reporting
 *		the reason of operation failure. The codes are defined in
 *		aasidrv.h.
 */
int EXP AASiWriteExtID1 (int MasterID, AASiSlaveData ID1);

/*****************************************************************
 *
 *  error = AASiWriteLPS (MasterID, LPS);
 *
 *  description:
 *		Write list of projected slave.
 *
 *  parameters:
 *		MasterID: master identifier
 *		LPS: 8 bytes projected slave list.
 *			Every bit in the LPS corresponds to one slave after the following scheme:
 *			Bit 0:	Slave 0/0A - can not be set!
 *			Bit 1:	Slave 1/1A
 *			...
 *			Bit31:	Slave 31/31A
 *			Bit32 :	Slave 0B - can not be set!
 *			Bit33:	Slave 1B
 *			...
 *			Bit63:	Slave 31B
 *			The slave is projected if the bit is set.
 * 
 * 	returns:
 */
int EXP AASiWriteLPS (int MasterID, AASiSlaveList LPS);
                            
/*********************************************************************
 *
 *  error = AASiReadLPS (MasterID, &LPS);
 *
 *  description:
 *		Read list of projected slaves.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *	returns:
 *		LPS: 8 bytes projected slave list.
 *			Bit 0:	Slave 0/0A - can not be set!
 *			Bit 1:	Slave 1/1A
 *			...
 *			Bit31:	Slave 31/31A
 *			Bit32 :	Slave 0B - can not be set!
 *			Bit33:	Slave 1B
 *			...
 *			Bit63:	Slave 31B
 *			The slave is projected if the bit is set.
 */
int EXP AASiReadLPS (int MasterID, AASiSlaveList FAR *LPS);
                            
/*****************************************************************
 *
 *  error = AASiReadLAS (MasterID, &LAS);
 *
 *  description:
 *		Read list of activated slaves.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *  returns:
 *		LAS: 8 bytes activated slave list.
 *			Bit 0:	Slave 0/0A
 *			Bit 1:	Slave 1/1A
 *			...
 *			Bit31:	Slave 31/31A
 *			Bit32 :	Slave 0B
 *			Bit33:	Slave 1B
 *			...
 *			Bit63:	Slave 31B
 *			The slave is activated if the bit is set.
 */
int EXP AASiReadLAS (int MasterID, AASiSlaveList FAR *LAS);
                            
/****************************************************************
 *
 *  error = AASiReadLDS (MasterID, &LDS);
 *
 *  description:
 *		Read list of detected slaves.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *  returns:
 *		LDS: 8 bytes detected slave list.
 *			Every bit in the LDS corresponds to one slave after the following scheme:
 *			Bit 0:	Slave 0/0A
 *			Bit 1:	Slave 1/1A
 *			...
 *			Bit31:	Slave 31/31A
 *			Bit32 :	Slave 0B
 *			Bit33:	Slave 1B
 *			...
 *			Bit63:	Slave 31B
 *			The slave is detected if the bit is set.
 */
int EXP AASiReadLDS (int MasterID, AASiSlaveList FAR *LDS);
                            
/****************************************************************
 *
 *  error = AASiReadLCS (MasterID, &LCS);
 *
 *  description:
 *		Read list of corrupted slaves. Every read resets the list.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *  returns:
 *		LCS: 8 bytes corrupted slave list.
 *			Every bit in the LCS corresponds to one slave after the following scheme:
 *			Bit 0:	Slave 0/0A can not be corrupted, AS-Interface power fail indication instead
 *			Bit 1:	Slave 1/1A
 *			...
 *			Bit31:	Slave 31/31A
 *			Bit32 :	Slave 0B can not be corrupted.
 *			Bit33:	Slave 1B
 *			...
 *			Bit63:	Slave 31B
 *			The slave is corrupted if the bit is set.
 */
int EXP AASiReadLCS (int MasterID, AASiSlaveList FAR *LCS);
                            
/*****************************************************************
 *
 *  error = AASiWriteLOS (MasterID, LOS);
 *
 *  description:
 *		Write list of slave addresses which trigger offline on config error.
 *
 *  parameters:
 *		MasterID: master identifier
 *		LOS: 8 bytes slave addresses list.
 *			Every bit in the LOS corresponds to one slave after the following scheme:
 *			Bit 0:	Slave 0/0A
 *			Bit 1:	Slave 1/1A
 *			...
 *			Bit31:	Slave 31/31A
 *			Bit32 :	Slave 0B
 *			Bit33:	Slave 1B
 *			...
 *			Bit63:	Slave 31B
 *			The slave is projected if the bit is set.
 * 
 * 	returns:
 */
int EXP AASiWriteLOS (int MasterID, AASiSlaveList LOS);
                            
/****************************************************************
 *
 *  error = AASiReadLOS (MasterID, &LOS);
 *
 *  description:
 *		Write list of slave addresses which trigger offline on config error.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *  returns:
 *		LOS: 8 bytes slave addresses list.
 *			Every bit in the LOS corresponds to one slave after the following scheme:
 *			Bit 0:	Slave 0/0A
 *			Bit 1:	Slave 1/1A
 *			...
 *			Bit31:	Slave 31/31A
 *			Bit32 :	Slave 0B
 *			Bit33:	Slave 1B
 *			...
 *			Bit63:	Slave 31B
 *			The slave is detected if the bit is set.
 */
int EXP AASiReadLOS (int MasterID, AASiSlaveList FAR *LOS);
                            
/****************************************************************
 *
 *  error = AASiReadLPF (MasterID, &LPF);
 *
 *  description:
 *		Read list of slave addresses with peripheral fault.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *  returns:
 *		LPF: 8 bytes slave addresses list.
 *			Every bit in the LOS corresponds to one slave after the following scheme:
 *			Bit 0:	Slave 0/0A
 *			Bit 1:	Slave 1/1A
 *			...
 *			Bit31:	Slave 31/31A
 *			Bit32:	Slave 0B
 *			...
 *			Bit63:	Slave 31B
 *			The slave has a peripheral fault if the bit is set.
 */
int EXP AASiReadLPF (int MasterID, AASiSlaveList FAR *LOS);
                            
/**********************************************************************
 *
 *  error = AASiReadEcFlags (MasterID, &EcFlags);
 *
 *  description:
 *		Read execution control flags.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *  returns:
 *		EcFlags: Two bytes execution control flags.
 *			The flags are defined in aasidrv.h
 */
int EXP AASiReadEcFlags (int MasterID, AASiEcFlags FAR *EcFlags);
                            
/********************************************************************
 *
 *  error = AASiSetConfigMode (MasterID, Mode);
 *
 *  description:
 *		Set ASi Master to configuration or protected operation mode.
 *
 *  parameters:
 *		MasterID: master identifier
 *		Mode: 1 = Configuration mode, 0 = Protected operation mode.
 *
 *  returns:
 */
int EXP AASiSetConfigMode (int MasterID, BOOL Mode);

/*******************************************************************
 *
 *  error = AASiWriteHiFlags (MasterID, HiFlags);			
 *
 *  description:
 *		Write host interface flags to the ASi Master.
 *
 *  parameters:
 *		MasterID: master identifier
 *		HiFlags: Host interface flags to write.
 *	The flags are defined in aasidrv.h
 *
 *  returns:
 */
int EXP AASiWriteHiFlags (int MasterID, AASiHiFlags HiFlags);

/*******************************************************************
 *
 *  error = AASiReadHiFlags (MasterID, &HiFlags);
 *
 *  description:
 *		Read acatual host interface flags from the master.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *  returns:
 *		HiFlags: host interface flags (one byte).
 *			The flags are defined in aasidrv.h
 */
int EXP AASiReadHiFlags (int MasterID, AASiHiFlags FAR *HiFlags);
                            
/****************************************************************
 *
 *  error = AASiAddressSlave (MasterID, Addr1, Addr2);
 *
 *  description:
 *		Change the address of one slave.
 *
 *  parameters:
 *		MasterID: master identifier
 *		Addr1: Old slave address.
 *		Addr2: New slave address.
 *
 *  returns:
 *		This function returns special error codes reporting
 *		the reason of operation failure. The codes are defined in
 *		aasidrv.h.
 */
int EXP AASiAddressSlave (int MasterID, AASiSlaveAddr OldAddress, AASiSlaveAddr NewAddress);
                            
/*************************************************************
 *
 *  error = AASiExecuteCommand (MasterID, Address, Request, &Response);
 *
 *  description:
 *		Send directly an AS-Interface command.
 *
 *  parameters:
 *		MasterID: master identifier
 *		Address: Slave address to send command to.
 *		Request: AS-Interface request command.
 *
 *  returns:
 *		Response: AS-Interface response.
 */
int EXP AASiExecuteCommand (int MasterID, AASiSlaveAddr Address, AASiSlaveData Request, AASiSlaveData FAR *Response);

/*********************************************************************
 *
 *  error = AASiWrite16BitODI (MasterID, Address, Out);
 *
 *  description:
 *      writes four channels of 16bit ODI to an AS-Interface slave
 *      with e.g. analog slave profil 7.3 or 7.4
 *
 *  parameters:
 *		MasterID: master identifier
 *		Address: Slave address (1..31)
 *      Out: 4 channels of 16-Bit values
 *           Word 0: channel 1
 *           ...
 *           Word 3: channel 4
 *
 *	returns:
 */
int EXP AASiWrite16BitODI (int MasterID, AASiSlaveAddr Address, AASi16BitData FAR Out);

/*********************************************************************
 *
 *  error = AASiRead16BitODI (MasterID, Address, In);
 *
 *  description:
 *      reads four channels of 16bit data from an AS-Interface slave
 *      with e.g. analog slave profil 7.3 or 7.4
 *
 *  parameters:
 *		MasterID: master identifier
 *		Address: Slave address (1..31)
 *
 *	returns:
 *      In:  4 channels of 16-Bit values
 *           Word 0: channel 1
 *           ...
 *           Word 3: channel 4
 */
int EXP AASiRead16BitODI (int MasterID, AASiSlaveAddr Address, AASi16BitData FAR In);

/*********************************************************************
 *
 *  error = AASiRead16BitIDI (MasterID, Address, In);
 *
 *  description:
 *      reads four channels of 16bit data from an AS-Interface slave
 *      with e.g. analog slave profil 7.3 or 7.4
 *
 *  parameters:
 *		MasterID: master identifier
 *		Address: Slave address (1..31)
 *
 *	returns:
 *      In:  4 channels of 16-Bit values
 *           Word 0: channel 1
 *           ...
 *           Word 3: channel 4
 */
int EXP AASiRead16BitIDI (int MasterID, AASiSlaveAddr Address, AASi16BitData FAR In);

// wraps function below for the use with Visual Basic
int EXP VBAASiReadIDString(int MasterID, AASiSlaveAddr Address, unsigned char* IDString, unsigned int* Length);

/*********************************************************************
 *
 *  error = AASiReadIDString (MasterID, Address, IDString, Length);
 *
 *  description:
 *		Read ID string of 7.4-slave.
 *
 *  parameters:
 *		MasterID: master identifier, 
 *		Address: Address of slave to read the string from (1..31, 33..63).
 *
 *	returns:
 *		IDString: Pointer to an unsigned character array holding the ID string.
 *		Length: Pointer to an unsigned character holding the length of the string.
 */
int EXP AASiReadIDString(int MasterID, AASiSlaveAddr Address, unsigned char **IDString, unsigned char *Length);

// wraps function below for the use with Visual Basic
int EXP VBAASiReadDiagnosisString(int MasterID, AASiSlaveAddr Address, unsigned char* DiagnosticString, unsigned int* Length);

/*********************************************************************
 *
 *  error = AASiReadDiagnosticString (MasterID, Address, DiagnosticString);
 *
 *  description:
 *		Read diagnostic string of 7.4-slave.
 *
 *  parameters:
 *		MasterID: master identifier, 
 *		Address: Address of slave to read the string from (1..31, 33..63).
 *
 *	returns:
 *		DiagnosticString: Pointer to an unsigned character array holding the diagnostic string.
 *		Length: Pointer to an unsigned character holding the length of the string.
 */
int EXP AASiReadDiagnosticString(int MasterID, AASiSlaveAddr Address, unsigned char **DiagnosticString, unsigned char *Length);

// wraps function below for the use with Visual Basic
int EXP VBAASiReadParameterString(int MasterID, AASiSlaveAddr Address, unsigned char* ParameterString, unsigned int* Length);

/*********************************************************************
 *
 *  error = AASiReadParameterString (MasterID, Address, ParameterString, Length);
 *
 *  description:
 *		Read parameter string of 7.4-slave.
 *
 *  parameters:
 *		MasterID: master identifier, 
 *		Address: Address of slave to read the string from (1..31, 33..63).
 *
 *	returns:
 *		ParameterString: Pointer to an unsigned character array holding the parameter string.
 *		Length: Pointer to an unsigned character holding the length of the string.
 */
int EXP AASiReadParameterString(int MasterID, AASiSlaveAddr Address, unsigned char **ParameterString, unsigned char *Length);

/*********************************************************************
 *
 *  error = AASiWriteParameterString (MasterID, Address, ParameterString, Length);
 *
 *  description:
 *		Write parameter string of 7.4-slave.
 *
 *  parameters:
 *		MasterID: master identifier, ParameterString: parameter string
 *		Address: Address of slave to write the string to (1..31, 33..63).
 *		ParameterString: parameter string to write to 7.4 slave
 *		Length: length of parameter string
 *
 *	returns:
 *
 */
int EXP AASiWriteParameterString(int MasterID, AASiSlaveAddr Address, unsigned char *ParameterString, unsigned char Length);

/*********************************************************************
 *
 *  error = AASiGetDllName (MasterID, LPCSTR* dllname );
 *
 *  description:
 *		Read the name of the communication dll 
 *
 *
 *  parameters:
 *		dllname:        name of the communication dll
 *		MasterID:       master identifier
 *
 *	returns:
 */
int EXP AASiGetDllName (int MasterID, LPCSTR* dllname );

/*********************************************************************
 *
 *  error = AASiGetUserName (MasterID, LPCSTR* dllname );
 *
 *  description:
 *		Read the name of the communication dll 
 *
 *
 *  parameters:
 *		username:       user name of the AS-Interface Master
 *		MasterID:       master identifier
 *
 *	returns:
 */
int EXP AASiGetUserName (int MasterID, LPCSTR* username );

/*********************************************************************
 *
 *  error = AASiReadAllConfig (MasterID, ASiCircuits, Configurations);
 *
 *  description:
 *		Read all the configuration data (i.e. LPS, PP[] and PCD[]) for 
 *		all AS-Interface slaves of all AS-Interface circuits of the connected master.
 *
 *  parameters:
 *		MasterID:       master identifier
 *		MaxASiCircIdx:  maximum AS-Interface circuit index
 *                      number = 0: only AS-Interface circuit 1
 *                      number = 1: both AS-Interface circuits
 *		Configurations:	vector to hold the configuration data.
 *
 *	returns:
 *		the configuration data in Configurations[].
 */
int EXP AASiReadAllConfig (int MasterID, int MaxASiCircIdx, AASiConfig FAR Configurations []);

/*********************************************************************
 *
 *  error = AASiWriteAllConfig (MasterID, ASiCircuits, Configurations);
 *
 *  description:
 *		Write all the configuration data (i.e. LPS, PP[] and PCD[]) for
 *		all AS-Interface slaves of all AS-Interface circuits of the connected master.
 *
 *  parameters:
 *		MasterID:       master identifier
 *		MaxASiCircIdx:  maximum AS-Interface circuit index
 *                      number = 0: only AS-Interface circuit 1
 *                      number = 1: both AS-Interface circuits
 *		Configurations:	vector holding the configuration data to be written.
 *
 *	returns:
 */
int EXP AASiWriteAllConfig (int MasterID, int MaxASiCircIdx, AASiConfig FAR Configurations []);

// wraps function below for the use with Visual Basic
int EXP VBAASiReadName(int MasterID, LPSTR Name, unsigned int Length);

/*********************************************************************
 *
 *  error = AASiReadName(MasterID, &Name)
 *
 *  description:
 *		Read the name of the AS-Interface Master.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *	returns:
 *		Pointer to a static null terminated string holding the master name.
 */
int EXP AASiReadName (int MasterID, LPCSTR FAR *Name);

// wraps function below for the use with Visual Basic
int EXP VBAASiReadVersionID(int MasterID, LPSTR VersionID, unsigned int Length);

/*********************************************************************
 *
 *  error = AASiReadVersionID(MasterID, &VersionID)
 *
 *  description:
 *		Read the master version.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *	returns:
 *		Pointer to a static null terminated string holding the master version ID.
 */
int EXP AASiReadVersionID (int MasterID, LPCSTR FAR *VersionID);

// wraps function below for the use with Visual Basic
int EXP VBAASiReadFeatures(int MasterID, LPSTR Features, unsigned int Length);

/*********************************************************************
 *
 *  error = AASiReadFeatures(MasterID)
 *
 *  description:
 *		Read the ASi master features.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *	returns:
 *		Pointer to a static null terminated string holding the master features.
 */
int EXP AASiReadFeatures (int MasterID, LPCSTR FAR *Features);

/*********************************************************************
 *
 *  error = AASiReadErrorCounters(MasterID, Counters)
 *
 *  description:
 *		Read the slave error counters. Every read resets the counters.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *	returns:
 *		Counters: 64 bytes holding one error counter per slave.
 */
int EXP AASiReadErrorCounters (int MasterID, AASiErrorCounters FAR Counters);

/*********************************************************************
 *
 *  error = AASiSetWatchdog(MasterID, Milliseconds)
 *
 *  description:
 *		Set the timeout of the master communication watchdog.
 *
 *  parameters:
 *		MasterID: master identifier
 *		Milliseconds: Timeout of master watchdog in [ms] (in steps of 10ms).
 *			If the value is zero the watchdog is disabled.
 *
 *	returns:
 */
int EXP AASiSetWatchdog (int MasterID, unsigned short Milliseconds);

/*********************************************************************
 *
 *  error = AASiGetWatchdog(MasterID, &TimedOut)
 *
 *  description:
 *		Read the timeout value of the master communication watchdog.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *	returns:
 *		TimedOut: TRUE if the watchdog has detected a timeout.
 */
int EXP AASiGetWatchdog (int MasterID, BOOL FAR *TimedOut);

/*  AS-Interface Control
 */
/************************************************************
 *
 *  error = AASiCtrlDownload (MasterID, Addr, Data);
 *
 *  description:
 *		Download part of ASi Control program.
 *
 *  parameters:
 *		MasterID: master identifier
 *		Addr: Start address of program data to write
 *		Data: 16 bytes of program to write
 *
 *  returns:
 */
int EXP AASiCtrlDownload (int MasterID, AASiCtrlAddr Address, AASiCtrlData FAR Data);

/***************************************************************
 *
 *  error = AASiCtrlUpload (MasterID, Addr, &Data);
 *
 *  description:
 *		Upload control program from ASi Control.
 *
 *  parameters:
 *		MasterID: master identifier
 *		Addr: Start address of program data to write
 *
 *  returns:
 *		Data: 16 bytes uploaded program
 */
int EXP AASiCtrlUpload (int MasterID, AASiCtrlAddr Address, AASiCtrlData FAR Data);

/************************************************************
 *
 *  error = AASiCtrlReadStatus (MasterID, &Status, &ActCycle, &MaxCycle);
 *
 *  description:
 *		Read the actual control status
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *  returns:
 *		Status: 1 byte actual control status. The values are defined in aasidrv.h
 *		ActCycle: Actual cycle time of control program [10 ms]
 *		MaxCycle: Maximum cyccle time of control program [10ms]
 */
int EXP AASiCtrlReadStatus (int MasterID, AASiCtrlFlags FAR *Status, unsigned short FAR *ActCycle, unsigned short FAR *MaxCycle);

/*******************************************************************
 *
 *  error = AASiCtrlReadResource (MasterID, Index, Resource);
 *
 *  description:
 *		Read next resource.
 *
 *  parameters:
 *		MasterID: master identifier
 *
 *  returns:
 *		Index: Resource index.
 *		Resource: ASiCtrlResource.
 */
int EXP AASiCtrlReadResource (int MasterID, int FAR *Index, AASiCtrlResource FAR *Resource);

/*******************************************************************
 *
 *  error = AASiCtrlWriteFlags (MasterID, CFlags);
 *
 *  description:
 *		Write new ASi Control flags to the master.
 *
 *  parameters:
 *		MasterID: master identifier
 *		CFlags: Control flags to write. The values are defined in aasidrv.h
 *
 *  returns:
 */
int EXP AASiCtrlWriteFlags (int MasterID, AASiCtrlFlags Status);

/****************************************************************
 *
 *  error = AASiCtrlReadMemory (MasterID, Addr, Amount, Data);
 *
 *  description:
 *		Read the ASi control user memory
 *
 *  parameters:
 *		MasterID: master identifier
 *		Addr: Start address to read from
 *		Amount: Number of bytes to read (1..16)
 *
 *  returns:
 *		Data: Up to 16 bytes of user memory
 */
int EXP AASiCtrlReadMemory (int MasterID, AASiCtrlAddr Address, unsigned char Amount, AASiCtrlData FAR Data);

/*************************************************************
 *
 *  error = AASiCtrlWriteMemory (MasterID, Addr, Amount, Data);
 *
 *  description:
 *		Write ASi control user memory.
 *
 *  parameters:
 *		MasterID: master identifier
 *		Addr: Write start address
 *		Amount: Number of bytes to write (1..16)
 *		Data: Up to 16 bytes user data to write
 *
 *  returns:
 */ 
int EXP AASiCtrlWriteMemory (int MasterID, AASiCtrlAddr Address, unsigned char Amount, AASiCtrlData FAR Data);

/*************************************************************
 *
 *  error = AASiWriteEmcSetup (MasterID, Flags, Request, Response, LAS);
 *
 *  description:
 *		Read the Emc Counters
 *
 *  parameters:
 *		MasterID: master identifier
 *		Flags:
 *				 2^0 = 1: TT=MT
 *				 2^1 = 1: Count invalid response frames and missing reponses as error
 *				 2^2 = 1: Compare data of valid respones with 'Response' and count differences as errors
 *		Request: Request for AS-Interface Slave
 *		Response: Expected response from AS-Interface Slave
 *		LAS: List of Slaves to communicate with
 *
 *  returns:
 *		ASiTelegrams: Number of counted AS-Interface telegrams
 *		ASiErrors: Number of incorrect AS-Interface telegrams
 */ 
int EXP AASiWriteEmcSetup (int MasterID, unsigned char Flags, unsigned char Request, unsigned char Response, unsigned long LAS);

/*************************************************************
 *
 *  error = AASiReadEmcCounter (MasterID, ASiTelegrams, ASiErrors);
 *
 *  description:
 *		Read the Emc Counters
 *
 *  parameters:
 *		MasterID: master identifier
 *		Addr: Write start address
 *		Amount: Number of bytes to write (1..16)
 *		Data: Up to 16 bytes user data to write
 *
 *  returns:
 *		ASiTelegrams: Number of counted AS-Interface telegrams
 *		ASiErrors: Number of incorrect AS-Interface telegrams
 */ 
int EXP AASiReadEmcCounter (int MasterID, unsigned int *ASiTelegrams, unsigned int *ASiErrors);

/*************************************************************
 *
 *  error = AASiUART (MasterID, Address, SingleTransfer, Request, Response);
 *
 *  description:
 *		Data exchange with AS-Interface UART
 *
 *  parameters:
 *		MasterID: master identifier
 *		SlaveAddress: Slave address (1..31)
 *		SingleTransfer: Single transfer transmission type (true/false)
 *		Request: Data send to master
 *
 *  returns:
 *		Response: Data returned from Slave
 */ 
int EXP AASiUART (int MasterID, AASiSlaveAddr Address, BOOL SingleTransfer, AASiSlaveData Request, AASiSlaveData *Response);

/*************************************************************
 *
 *  error = AASiMailbox (MasterID, Request, Response);
 *
 *  description:
 *		Generic mailbox function
 *
 *  parameters:
 *		MasterID: master identifier
 *		Request: structure for mailbox request
 *      ExpResLen: expected response length (-1 == don't know)
 *
 *  returns:
 *		Response: structure for mailbox response
 */ 
int EXP AASiMailbox (int MasterID, AASiMbRequestType Request, int ExpResLen, AASiMbResponseType *Response);

#ifdef _WINDOWS	/*	{	*/

/*********************************************************************
 *
 *  error = AASiRegisterIniFileName(MasterID, FileName)
 *
 *  description:
 *		Tells the driver dll the filename of the ini file.
 *		The default ini file name is "asidrv.ini".
 *
 *  parameters:
 *		MasterID: master identifier
 *		FileName is a string that can either contain the whole path of the
 *		ini filename or only the filename (with the suffix).
 *		If only the filename is quoted, ASiRegisterIniFileName() creates the whole path
 *		from the path of the module (dll) by appending the filename.
 *
 *	returns:
 */
int EXP AASiRegisterIniFileName (int MasterID, LPCSTR FileName);

/*************************************************************
 *
 *  error = AASiRegisterWindowHandle (MasterID, hWnd);
 *
 *  description:
 *		MasterID: master identifier
 *		Register window handle of calling application program.
 *
 *  parameters:
 *		hWnd: Window handle or NULL.
 *
 *  returns:
 */ 
int EXP AASiRegisterWindowHandle (int MasterID, HWND hWnd);

/*************************************************************
 *
 *  error = AASiRegisterMsgCallback (MasterID, DispatchFunction);
 *
 *  description:
 *		Register a dispatch function for window messages during idle time.
 *
 *  parameters:
 *		MasterID: master identifier
 *		DispatchFunction: Callback function for message dispatch or NULL
 *			if not supported.
 *			If no function is specified windows will slow down during communication
 *			operation. This isn't crucial for ASi PC2, however.
 *
 *  returns:
 */ 
int EXP AASiRegisterMsgCallback (int MasterID, int (CALLBACK* DispatchFunction)(MSG FAR *));

/*************************************************************
 *
 *  error = AASiRegisterMsgCallbackKeep (MasterID, DispatchFunction, bKeepMessage);
 *
 *  description:
 *		Register a dispatch function for window messages during idle time.
 *
 *  parameters:
 *		MasterID: master identifier
 *		DispatchFunction: Callback function for message dispatch or NULL
 *			if not supported.
 *			If no function is specified windows will slow down during communication
 *			operation. This isn't crucial for ASi PC2, however.
 *		bKeepMessage: TRUE=don't remove message from queue
 *
 *  returns:
 */ 
int EXP AASiRegisterMsgCallbackKeep (int MasterID, int (CALLBACK* DispatchFunction)(MSG FAR *), BOOL bKeepMessage);

#endif	/*	ifdef _WINDOWS	}	*/

#ifdef __cplusplus
}
#endif

/*********************************************************************
 *  eof                                                              *
 *********************************************************************/

#endif  /*  ifndef AASIDRV_H */

