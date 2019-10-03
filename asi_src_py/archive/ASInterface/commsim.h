/****** Comm support ******************************************************/

#ifndef _COMMSIM_H
#define _COMMSIM_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NOPARITY	    0
#define ODDPARITY	    1
#define EVENPARITY	    2
#define MARKPARITY	    3
#define SPACEPARITY	    4

#define ONESTOPBIT	    0
#define ONE5STOPBITS	    1
#define TWOSTOPBITS	    2

#define IGNORE              0
//#define INFINITE            0xFFFF

/* Error Flags */
#define CE_RXOVER           0x0001
#define CE_OVERRUN          0x0002
#define CE_RXPARITY         0x0004
#define CE_FRAME            0x0008
#define CE_BREAK            0x0010
#define CE_CTSTO            0x0020
#define CE_DSRTO            0x0040
#define CE_RLSDTO           0x0080
#define CE_TXFULL           0x0100
#define CE_PTO              0x0200
#define CE_IOE              0x0400
#define CE_DNS              0x0800
#define CE_OOP              0x1000
#define CE_MODE             0x8000

#define IE_BADID            (-1)
#define IE_OPEN             (-2)
#define IE_NOPEN            (-3)
#define IE_MEMORY           (-4)
#define IE_DEFAULT          (-5)
#define IE_HARDWARE         (-10)
#define IE_BYTESIZE         (-11)
#define IE_BAUDRATE         (-12)

/* Events */
#if 0
#define EV_RXCHAR           0x0001
#define EV_RXFLAG           0x0002
#define EV_TXEMPTY          0x0004
#define EV_CTS              0x0008
#define EV_DSR              0x0010
#define EV_RLSD             0x0020
#define EV_BREAK            0x0040
#define EV_ERR              0x0080
#define EV_RING             0x0100
#define EV_PERR             0x0200
#define EV_CTSS             0x0400
#define EV_DSRS             0x0800
#define EV_RLSDS            0x1000
#define EV_RingTe           0x2000
#define EV_RINGTE	    EV_RingTe
#endif

/* Escape Functions */
#define SETXOFF             1
#define SETXON              2
#define SETRTS              3
#define CLRRTS              4
#define SETDTR              5
#define CLRDTR              6
#define RESETDEV            7

#define LPTx                0x80

#if (WINVER >= 0x030a)

/* new escape functions */
#define GETMAXLPT           8
#define GETMAXCOM           9
#define GETBASEIRQ          10

/* Comm Baud Rate indices */

#define __CBR_110	   0xFF10
#define __CBR_300      0xFF11
#define __CBR_600      0xFF12
#define __CBR_1200     0xFF13
#define __CBR_2400     0xFF14
#define __CBR_4800     0xFF15
#define __CBR_9600     0xFF16
#define __CBR_14400    0xFF17
#define __CBR_19200    0xFF18
#define __CBR_38400    0xFF1B
#define __CBR_56000    0xFF1F
#define __CBR_128000   0xFF23
#define __CBR_256000   0xFF27

/* notifications passed in low word of lParam on WM_COMMNOTIFY messages */
#define CN_RECEIVE  0x0001
#define CN_TRANSMIT 0x0002
#ifndef CN_EVENT
#define CN_EVENT    0x0004
#endif

#endif  /* WINVER >= 0x030a */

typedef struct tagDCB
{
    BYTE Id;
    UINT BaudRate;
    BYTE ByteSize;
    BYTE Parity;
    BYTE StopBits;
    UINT RlsTimeout;
    UINT CtsTimeout;
    UINT DsrTimeout;

    UINT fBinary        :1;
    UINT fRtsDisable    :1;
    UINT fParity        :1;
    UINT fOutxCtsFlow   :1;
    UINT fOutxDsrFlow   :1;
    UINT fDummy         :2;
    UINT fDtrDisable    :1;

    UINT fOutX          :1;
    UINT fInX           :1;
    UINT fPeChar        :1;
    UINT fNull          :1;
    UINT fChEvt         :1;
    UINT fDtrflow       :1;
    UINT fRtsflow       :1;
    UINT fDummy2        :1;

    char XonChar;
    char XoffChar;
    UINT XonLim;
    UINT XoffLim;
    char PeChar;
    char EofChar;
    char EvtChar;
    UINT TxDelay;
} __DCB;
typedef __DCB FAR* __LPDCB;

#if (defined(STRICT) | (WINVER >= 0x030a))

typedef struct tagCOMSTAT
{
    BYTE status;
    UINT cbInQue;
    UINT cbOutQue;
} __COMSTAT;

#define CSTF_CTSHOLD    0x01
#define CSTF_DSRHOLD    0x02
#define CSTF_RLSDHOLD   0x04
#define CSTF_XOFFHOLD   0x08
#define CSTF_XOFFSENT   0x10
#define CSTF_EOF        0x20
#define CSTF_TXIM       0x40

#else   /* (STRICT | WINVER >= 0x030a) */

/* NOTE: This structure declaration is not ANSI compatible! */
typedef struct tagCOMSTAT
{
    BYTE fCtsHold  :1;
    BYTE fDsrHold  :1;
    BYTE fRlsdHold :1;
    BYTE fXoffHold :1;
    BYTE fXoffSent :1;
    BYTE fEof      :1;
    BYTE fTxim     :1;
    UINT cbInQue;
    UINT cbOutQue;
} __COMSTAT;

#endif  /* !(STRICT | WINVER >= 0x030a */

BOOL __InitComm(void);
BOOL __ExitComm(void);

int		 __BuildCommDCB(LPCSTR, __DCB FAR*);

int      __OpenComm(LPCSTR, UINT, UINT);
int      __CloseComm(int);

int      __ReadComm(int, void FAR*, int);
int      __WriteComm(int, const void FAR*, int);
int      __UngetCommChar(int, char);
int      __FlushComm(int, int);
int      __TransmitCommChar(int, char);

int      __SetCommState(const __DCB FAR*);
int      __GetCommState(int, __DCB FAR*);
int      __GetCommError(int, __COMSTAT FAR* );

int      __SetCommBreak(int);
int      __ClearCommBreak(int);

UINT FAR*  __SetCommEventMask(int, UINT);
UINT     __GetCommEventMask(int, int);

LONG     __EscapeCommFunction(int, int);

#if (WINVER >= 0x030a)
BOOL     __EnableCommNotification(int, HWND, int, int);

#define WM_COMMNOTIFY		0x0044
#endif  /* WINVER >= 0x030a */

#ifdef __cplusplus
}		// extern "C"
#endif
#endif // _COMMSIM_H