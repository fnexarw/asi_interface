/****************************************************************************

    PROGRAM: adapt.h

    PURPOSE: adapt for various compilers

****************************************************************************/

#ifndef _ADAPT_H
#define _ADAPT_H

#ifdef _WIN32
#include <windows.h>
#include <windowsx.h>
#include "commsim.h"

// macros for WM_COMMAND
#define	WM_COMMAND_ID(_wparam, _lparam) (LOWORD(_wparam))
#define	WM_COMMAND_CMD(_wparam, _lparam) (HIWORD(_wparam))
#define	WM_COMMAND_HWND(_wparam, _lparam) (_lparam)

#ifndef EXPORT
#define EXPORT
#endif

#define READ			OF_READ
#define WRITE			OF_WRITE

#define __segname
#define _fcalloc calloc

#else	// _win16

#include <windows.h>
// macros for WM_COMMAND
#define	WM_COMMAND_ID(_wparam, _lparam) (_wparam)
#define	WM_COMMAND_CMD(_wparam, _lparam) (HIWORD(_lparam))
#define	WM_COMMAND_HWND(_wparam, _lparam) (LOWORD(_lparam))

#ifndef HUGEP
#define HUGEP _huge
#endif

#ifndef EXPORT
#define EXPORT _export
#endif

#define __COMSTAT					COMSTAT
#define __DCB						DCB
#define	__BuildCommDCB				BuildCommDCB
#define	__OpenComm					OpenComm
#define	__CloseComm					CloseComm
#define	__ReadComm					ReadComm
#define	__WriteComm					WriteComm
#define	__UngetCommChar				UngetCommChar
#define	__FlushComm					FlushComm
#define __TransmitCommChar			TransmitCommChar
#define	__SetCommState				SetCommState
#define	__GetCommState				GetCommState
#define	__GetCommError				GetCommError
#define	__SetCommBreak				SetCommBreak
#define	__ClearCommBreak			ClearCommBreak
#define	__SetCommEventMask			SetCommEventMask
#define	__GetCommEventMask			GetCommEventMask
#define	__EscapeCommFunction		EscapeCommFunction
#define	__EnableCommNotification	EnableCommNotification

#endif


#endif	//_ADAPT_H