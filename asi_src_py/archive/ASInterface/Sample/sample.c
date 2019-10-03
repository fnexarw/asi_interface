/***************************************************************************

    PROGRAM: Sample.c

    PURPOSE: shows the use of the driver DLLs for the Bihl+Wiedemann AS-Interface masters,
			 especially the initialization process.

			 This program shows two ways of initialization:

			 1. Menu Driver:
				initializing an AS-i master with the function AASiInitDialog()
			    (with dialog box for selecting the desired AS-i master and circuit
				as realized in the AS-i Control Tools). Also, a profile (ini-file)
				is used to store the previously used 'Settings'-string.

			 2. Menu Driver (2 Circuits):
				initializing an AS-i master with two AS-i circuits
				(for example the AS-Interface/Ethernet Gateway or the AS-i PCI card)
				with the function AASiInit(). Here, the ini-file is not used, but
				the 'Settings'-string is hardcoded.

			 The menu functions has only one entry: Data Exchange. This command
			 opens a dialog box that can exchange data with one slave. Depending on
			 the method how you initialize the AS-i master (1. or 2.) the 'circuit 2'-
			 checkbox will appear (for method 2.), so you can also switch between the
			 two circuits of the AS-i master.

    FUNCTIONS:

    WinMain() - calls initialization function, processes message loop
    InitApplication() - initializes window data and registers window
    InitInstance() - saves instance handle and creates main window
    MainWndProc() - processes messages
    About() - processes messages for "About" dialog box

    COMMENTS:
		This program uses the "AASi...()"-function set for the Advanced AS-interface
		(specification 2.1). If you are using an "old" AS-i Master (according to
		spec. 2.0) the driver asidrv32.dll manages all the casting of the data from
		Advanced AS-i (AASi) to "old" AS-i (ASi) and vice versa.

	Author: Daniel Rudolf
	Date: 26.10.2000

	ATTENTION:
	Before calling the function AASiDataExchange() the AS-i Master is
	switched to configuration mode with the function AASiSetConfigMode()
	in order to enable data exchange even if the AS-i slave is not
	projected.

	IMPORTANT:
	The project must contain the following files:
	sample.c
	asidrv.lib
	sample.rc

****************************************************************************/

#include <windows.h>            /* required for all Windows applications */
#include "adapt.h"				/* adapts 16bit Windows programs to 32bit Windows programs */
#include "sample.h"             /* specific to this program */
#include "aasidrv.h"			/* contains prototypes for AS-i functions (including the advanced AS-i features) */
#include <stdio.h>
#include <stdlib.h>

HANDLE hInst;               /* current instance */

static FARPROC TranslateCallback = NULL;

int MasterID = -1;   	/* master identifier */
int MasterID2 = -1;   	/* master identifier for second AS-i circuit */
BOOL bInit = FALSE;		/* driver init (not) successful */
BOOL b2Circs = FALSE;   /* one or two AS-i circuits initialized */
LPCSTR lpcStrError;		/* error string */
LPCSTR lpcStrInitDone = "Init done.";
LPCSTR lpcStrASiDrvSample = "AASiDrv Sample Application";

int EXPORT CALLBACK TranslateMsg(MSG FAR * msg)
{
	TranslateMessage(msg);
	DispatchMessage(msg);
	return TRUE;
}

/****************************************************************************

    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)

    PURPOSE: calls initialization function, processes message loop

    COMMENTS:

        Windows recognizes this function by name as the initial entry point
        for the program.  This function calls the application initialization
        routine, if no other instance of the program is running, and always
        calls the instance initialization routine.  It then executes a message
        retrieval and dispatch loop that is the top-level control structure
        for the remainder of execution.  The loop is terminated when a WM_QUIT
        message is received, at which time this function exits the application
        instance by returning the value passed by PostQuitMessage().

        If this function must abort before entering the message loop, it
        returns the conventional value NULL.

****************************************************************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
/*HANDLE hInstance;                 current instance         */
/*HANDLE hPrevInstance;             previous instance        */
/*LPSTR lpCmdLine;                  command line             */
/*int nCmdShow;                     show-window type (open/icon) */
{
    MSG msg;                     /* message              */

	lpCmdLine = NULL;

    if (!hPrevInstance)          /* Other instances of app running? */
    if (!InitApplication(hInstance)) /* Initialize shared things */
        return (FALSE);      /* Exits if unable to initialize     */

    /* Perform initializations that apply to a specific instance */

    if (!InitInstance(hInstance, nCmdShow))
	{
	    ExitInstance();
        return (FALSE);
	}

    /* Acquire and dispatch messages until a WM_QUIT message is received. */

    while (GetMessage(&msg,    /* message structure              */
        NULL,          /* handle of window receiving the message */
        0,				/* lowest message to examine          */
        0) == TRUE)         /* highest message to examine         */
    {
    	TranslateMessage(&msg);    /* Translates virtual key codes       */
    	DispatchMessage(&msg);     /* Dispatches message to window       */
    }
    
    if (!ExitInstance())
        return (msg.wParam);

    return (msg.wParam);       /* Returns the value from PostQuitMessage */
}


/****************************************************************************

    FUNCTION: InitApplication(HANDLE)

    PURPOSE: Initializes window data and registers window class

    COMMENTS:

        This function is called at initialization time only if no other
        instances of the application are running.  This function performs
        initialization tasks that can be done once for any number of running
        instances.

        In this case, we initialize a window class by filling out a data
        structure of type WNDCLASS and calling the Windows RegisterClass()
        function.  Since all instances of this application use the same window
        class, we only need to do this when the first instance is initialized.


****************************************************************************/

BOOL InitApplication(HANDLE hInstance)
/*HANDLE hInstance;                   current instance       */
{
    WNDCLASS  wc;

    /* Fill in window class structure with parameters that describe the       */
    /* main window.                                                           */

    wc.style = 0;						/* Class style(s).                    */
    wc.lpfnWndProc = MainWndProc;       /* Function to retrieve messages for  */
                                        /* windows of this class.             */
    wc.cbClsExtra = 0;                  /* No per-class extra data.           */
    wc.cbWndExtra = 0;                  /* No per-window extra data.          */
    wc.hInstance = hInstance;           /* Application that owns the class.   */
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName =  "ASiDrvSampleMenu";   /* Name of menu resource in .RC file. */
    wc.lpszClassName = "ASiDrvSampleWClass"; /* Name used in call to CreateWindow. */

    /* Register the window class and return success/failure code. */

	TranslateCallback = MakeProcInstance(TranslateMsg, hInst);
    return (RegisterClass(&wc));
}


/****************************************************************************

    FUNCTION:  InitInstance(HANDLE, int)

    PURPOSE:  Saves instance handle and creates main window

    COMMENTS:

        This function is called at initialization time for every instance of
        this application.  This function performs initialization tasks that
        cannot be shared by multiple instances.

        In this case, we save the instance handle in a static variable and
        create and display the main program window.

****************************************************************************/

BOOL InitInstance(HANDLE hInstance, int nCmdShow)
/*    HANDLE          hInstance;           Current instance identifier.       */
/*    int             nCmdShow;            Param for first ShowWindow() call. */
{
    HWND            hWnd;               /* Main window handle.                */
    
    /* Save the instance handle in static variable, which will be used in  */
    /* many subsequence calls from this application to Windows.            */

	MasterID = -1;

    hInst = hInstance;

    /* Create a main window for this application instance.  */

    hWnd = CreateWindow(
        "ASiDrvSampleWClass",           /* See RegisterClass() call.          */
        "AASiDrv Sample Application",	/* Text for window title bar.         */
        WS_OVERLAPPEDWINDOW,            /* Window style.                      */
        CW_USEDEFAULT,                  /* Default horizontal position.       */
        CW_USEDEFAULT,                  /* Default vertical position.         */
        CW_USEDEFAULT,                  /* Default width.                     */
        CW_USEDEFAULT,                  /* Default height.                    */
        NULL,                           /* Overlapped windows have no parent. */
        NULL,                           /* Use the window class menu.         */
        hInstance,                      /* This instance owns this window.    */
        NULL                            /* Pointer not needed.                */
    );

    /* If window could not be created, return "failure" */
    if (!hWnd)
        return (FALSE);

    /* Make the window visible; update its client area; and return "success" */
    ShowWindow(hWnd, nCmdShow);  /* Show the window                        */
    UpdateWindow(hWnd);          /* Sends WM_PAINT message                 */

    return (TRUE);               /* Returns the value from PostQuitMessage */

}

/****************************************************************************

    FUNCTION:  ExitInstance()

****************************************************************************/

BOOL ExitInstance()
{
	if (TranslateCallback)
	{
		FreeProcInstance(TranslateCallback);
	}
	return TRUE;
}


/****************************************************************************

    FUNCTION: MainWndProc(HWND, UINT, WPARAM, LPARAM)

    PURPOSE:  Processes messages

    MESSAGES:

    WM_COMMAND    - application menu (About dialog box)
    WM_DESTROY    - destroy window

    COMMENTS:

    To process the IDM_ABOUT message, call MakeProcInstance() to get the
    current instance address of the About() function.  Then call Dialog
    box which will create the box according to the information in your
    generic.rc file and turn control over to the About() function.  When
    it returns, free the intance address.

****************************************************************************/

long EXPORT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
/*HWND hWnd;                       window handle                 */
/*UINT message;                    type of message               */
/*WPARAM wParam;                   additional information        */
/*LPARAM lParam;                   additional information        */
{
	int sError;		/* error result */

    switch (message)
    {
        case WM_CLOSE:

       		if (MasterID != -1)
       		{
       			AASiExit(MasterID);
       		}
       		if (MasterID2 != -1)
       		{
       			AASiExit(MasterID2);
       		}
        	DestroyWindow(hWnd);
        	break;
        
        case WM_COMMAND:       /* message: command from application menu */
        
	    	switch (WM_COMMAND_ID(wParam, lParam))
    		{
	            case IDM_ABOUT:
                	DialogBox(hInst,        /* current instance          */
	                    "AboutBox",         /* resource to use           */
                    	hWnd,               /* parent handle             */
                    	About);             /* About() instance address  */	
                	break;

	            case IDM_FUNCTIONS_DATAEXCHANGE:
	            	if (!bInit)                     
	            	{
						lpcStrError = "Open Driver first!";
						MessageBox(hWnd, lpcStrError, lpcStrASiDrvSample, MB_OK);
						break;
					}
                	DialogBox(hInst,        /* current instance          */
	                    "DataExBox",         /* resource to use           */
                    	hWnd,               /* parent handle             */
                    	DataExDialog);             /* About() instance address  */	
                	break;

				/* initialize one AS-i Master (one AS-i circuit) with dialog box, using the ini-file */
				case IDM_OPEN_DRIVER:
	            	if (bInit)
	            	{
						lpcStrError = "Close Driver first!";
						MessageBox(hWnd, lpcStrError, lpcStrASiDrvSample, MB_OK);
						break;
					}
					sError = AASiRegisterMaster(&MasterID);
					if (sError)
					{
						MessageBox(NULL, "Master couldn't be registrated", "Error", MB_OK | MB_ICONSTOP);
						return FALSE;
					}  
								/* assign ini file name */
					sError = AASiRegisterIniFileName(MasterID, "asidrvsa.ini");
					if (sError)
					{
						AASiGetErrorMessage(MasterID, sError, &lpcStrError);
					}
								/* Register window handle (for dialog boxes of the dll) */
					AASiRegisterWindowHandle(MasterID, hWnd);

					if (AASiRegisterMsgCallback(MasterID, (int (CALLBACK* )(MSG FAR *)) TranslateCallback))
					{
						lpcStrError = "AASiRegisterMsgCallback() failed.";
						MessageBox(hWnd, lpcStrError, lpcStrASiDrvSample, MB_OK); 
					}
			    	sError = AASiInitDialog(MasterID, NULL, NULL, NULL);
					if (sError)
					{
						AASiGetErrorMessage(MasterID, sError, &lpcStrError);
						MessageBox(hWnd, lpcStrError, lpcStrASiDrvSample, MB_OK); 
						bInit = FALSE;
					}
					else
					{                                              
						MessageBox(hWnd, lpcStrInitDone, lpcStrASiDrvSample, MB_OK);
						bInit = TRUE;
						b2Circs = FALSE;
					}
					/* switch to configuration mode to ensure that all data bits 
						can be set, even if the slave is only detected but not projected */
					AASiSetConfigMode(MasterID, 1);
					break;

	            case IDM_CLOSE_DRIVER:
            		if (MasterID != -1)
            		{
						/* switch back to protected mode */
						AASiSetConfigMode(MasterID, 0);
            			AASiExit(MasterID);
						bInit = FALSE;
						AASiUnRegisterMaster(MasterID);
	           		}
                	break;

				/* initialize two AS-i Masters (both AS-i circuits of a device with two AS-i Masters)
					without dialog box and without using the ini-file */
				case IDM_OPEN_2_CIRCUITS:
					/* first circuit */
					if (bInit)
	            	{
						lpcStrError = "Close Driver first!";
						MessageBox(hWnd, lpcStrError, lpcStrASiDrvSample, MB_OK);
						break;
					}

					sError = AASiRegisterMaster(&MasterID);
					if (sError)
					{
						MessageBox(NULL, "Master couldn't be registrated", "Error", MB_OK | MB_ICONSTOP);
						return FALSE;
					}  

					/* example for AS-Interface/Ethernet Gateway */
					/* sError = AASiInit(MasterID, "tcpmb.dll: Host 192.168.42.162, Circ 1"); */
					/* example for AS-i PCI card, auto search = first card found */
					sError = AASiInit(MasterID, "asipci.dll: ID 0xffff, Circ 1");
					/* example for AS-i PCI board, certain card */
					/* sError = AASiInit(MasterID, "asipci.dll: ID 0xa0, Circ 1"); */
					if (sError)
					{
						AASiGetErrorMessage(MasterID, sError, &lpcStrError);
						MessageBox(hWnd, lpcStrError, lpcStrASiDrvSample, MB_OK); 
						bInit = FALSE;
						return FALSE;
					}

					/* second circuit */
					sError = AASiRegisterMaster(&MasterID2);
					if (sError)
					{
						MessageBox(NULL, "Master 2 couldn't be registrated", "Error", MB_OK | MB_ICONSTOP);
						return FALSE;
					}  

					/* example for AS-Interface/Ethernet Gateway */
					/* sError = AASiInit(MasterID2, "tcpmb.dll: Host 192.168.42.162, Circ 2"); */
					/* example for AS-i PCI card, auto search = first card found */
					sError = AASiInit(MasterID2, "asipci.dll: ID 0xffff, Circ 2");
					/* example for AS-i PCI board, certain card */
					/* sError = AASiInit(MasterID2, "asipci.dll: ID 0xa0, Circ 2"); */
					if (sError)
					{
						AASiGetErrorMessage(MasterID2, sError, &lpcStrError);
						MessageBox(hWnd, lpcStrError, lpcStrASiDrvSample, MB_OK); 
						bInit = FALSE;
						return FALSE;
					}
					else
					{                                              
						MessageBox(hWnd, lpcStrInitDone, lpcStrASiDrvSample, MB_OK);
						bInit = TRUE;
						b2Circs = TRUE;
					}

					/* switch to configuration mode to ensure that all data bits 
						can be set, even if the slave is only detected but not projected */
					AASiSetConfigMode(MasterID, 1);
					AASiSetConfigMode(MasterID2, 1);
					break;

				case IDM_CLOSE_2_CIRCUITS:
            		if (MasterID != -1)
            		{
						/* switch back to protected mode */
						AASiSetConfigMode(MasterID, 0);
            			AASiExit(MasterID);
						AASiUnRegisterMaster(MasterID);
	           		}
            		if (MasterID2 != -1)
            		{
						/* switch back to protected mode */
						AASiSetConfigMode(MasterID2, 0);
            			AASiExit(MasterID2);
						AASiUnRegisterMaster(MasterID2);
	           		}
					bInit = FALSE;
                	break;

	            case ID_FILE_EXIT:
					PostMessage(hWnd, WM_CLOSE, 0, 0);
                	break;

				default:                    /* Lets Windows process it   */
	                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            break;
            
		/* message: window being destroyed */
        case WM_DESTROY:
       		if (MasterID != -1)
       		{
				/* switch back to protected mode */
				AASiSetConfigMode(MasterID, 0);
       			AASiExit(MasterID);
				AASiUnRegisterMaster(MasterID);
       		}
       		if (MasterID2 != -1)
       		{
				AASiSetConfigMode(MasterID2, 0);
       			AASiExit(MasterID2);
				AASiUnRegisterMaster(MasterID2);
       		}
			PostQuitMessage(0);
            break;


        default:                  /* Passes it on if unproccessed */
            return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return (FALSE);
}



/****************************************************************************

    FUNCTION: About(HWND, UINT, WPARAM, LPARAM)

    PURPOSE:  Processes messages for "About" dialog box

    MESSAGES:

    WM_INITDIALOG - initialize dialog box
    WM_COMMAND    - Input received

    COMMENTS:

    No initialization is needed for this particular dialog box, but TRUE
    must be returned to Windows.

    Wait for user to click on "Ok" button, then close the dialog box.

****************************************************************************/

BOOL EXPORT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
/* HWND hDlg;		window handle of the dialog box */
/* UINT message;	type of message                 */
/* WPARAM wParam;	message-specific information    */
/* LPARAM lParam; */
{
	lParam = 0;
    switch (message)
    {
        case WM_INITDIALOG:            /* message: initialize dialog box */
            return (TRUE);

        case WM_COMMAND:               /* message: received a command */
            if (wParam == IDOK         /* "OK" box selected?          */
                || wParam == IDCANCEL) /* System menu close command?  */
            {
                EndDialog(hDlg, TRUE); /* Exits the dialog box        */
                return (TRUE);
            }
            break;
    }
    return (FALSE);               /* Didn't process a message    */
} 

/****************************************************************************

    FUNCTION: DataExDialog(HWND, UINT, WPARAM, LPARAM)

    PURPOSE:  Processes messages for "DataExDialog" dialog box

    MESSAGES:

    WM_INITDIALOG - initialize dialog box
    WM_COMMAND    - Input received


****************************************************************************/

BOOL EXPORT CALLBACK DataExDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
/* HWND hDlg;		window handle of the dialog box */
/* UINT message;	type of message                 */
/* WPARAM wParam;	message-specific information    */
/* LPARAM lParam; */
{
	static AASiProcessData ODI;		/* output data image (AS-i output data) */
	static AASiProcessData IDI;		/* input data image (AS-i input data) */
	static AASiEcFlags EcFlags;		/* execution control flags */
	static int Addr = 1;			/* AS-i slave address */

	/* the same as above for AS-i circuit 2 */
	static AASiProcessData ODI2;
	static AASiProcessData IDI2;
	static AASiEcFlags EcFlags2;
	static int Addr2 = 1;

	int shift;
	char szBuf[128];
	WORD cbText;
	static bCircuit2 = FALSE;		/* state of circuit 2 checkbox */

	lParam = 0;

    switch (message)
    {
        case WM_INITDIALOG:            /* message: initialize dialog box */
			sprintf(szBuf, "%d", Addr);
			SendDlgItemMessage(hDlg, IDC_EDIT_SLAVE_ADDR, WM_SETTEXT, 0,   /* line number */
			    (DWORD) (LPSTR) szBuf);      /* buffer address             */
        	SetTimer (hDlg, 1, 200, NULL);
			/* show circuit 2 checkbox */
		  	if (b2Circs)
				ShowWindow(GetDlgItem(hDlg, IDC_CHECK_CIRC2), SW_SHOW);
			else
				ShowWindow(GetDlgItem(hDlg, IDC_CHECK_CIRC2), SW_HIDE);

            return (TRUE);

		case WM_TIMER:
			*(WORD *) szBuf = sizeof(szBuf) - 1; /* sets the buffer size   */
			cbText = (WORD) SendDlgItemMessage(hDlg, IDC_EDIT_SLAVE_ADDR, EM_GETLINE, 0,   /* line number */
			    (DWORD) (LPSTR) szBuf);      /* buffer address             */
			szBuf[cbText] = '\0';            /* terminating null character */
			/* get state of circuit 2 checkbox */
			if (SendDlgItemMessage(hDlg, IDC_CHECK_CIRC2, BM_GETCHECK, 0, 0)) bCircuit2 = TRUE;
		   	else bCircuit2 = FALSE;

			if (bCircuit2 == FALSE)
			{
				/* circuit 1 respectively only one circuit */
				Addr = atoi(szBuf);
				if (Addr < 0 || Addr > 31 )
				{
					Addr = 1;
					sprintf(szBuf, "%d", Addr);
					SendDlgItemMessage(hDlg, IDC_EDIT_SLAVE_ADDR, WM_SETTEXT, 0,   /* line number */
						(DWORD) (LPSTR) szBuf);      /* buffer address */
				}
				shift = 4*(Addr%2);

				/* get state of output checkboxes */
				if (SendDlgItemMessage(hDlg, IDC_CHECK_OUT0, BM_GETCHECK, 0, 0))
					ODI[(Addr/2)] |= 0x01 << shift;
		   		else
					ODI[(Addr/2)] &= ~(0x01 << shift);
		   		if (SendDlgItemMessage(hDlg, IDC_CHECK_OUT1, BM_GETCHECK, 0, 0))
					ODI[(Addr/2)] |= 0x02 << shift;
		   		else
					ODI[(Addr/2)] &= ~(0x02 << shift);
		   		if (SendDlgItemMessage(hDlg, IDC_CHECK_OUT2, BM_GETCHECK, 0, 0))
					ODI[(Addr/2)] |= 0x04 << shift;
		   		else
					ODI[(Addr/2)] &= ~(0x04 << shift);
		   		if (SendDlgItemMessage(hDlg, IDC_CHECK_OUT3, BM_GETCHECK, 0, 0))
					ODI[(Addr/2)] |= 0x08 << shift;
		   		else
					ODI[(Addr/2)] &= ~(0x08 << shift);
				/* writes output data and reads input data */
				AASiDataExchange(MasterID, ODI, IDI, &EcFlags);
		   		SendDlgItemMessage(hDlg, IDC_CHECK_IN0, BM_SETCHECK, IDI[(Addr/2)] & (0x01 << shift), 0);
		   		SendDlgItemMessage(hDlg, IDC_CHECK_IN1, BM_SETCHECK, IDI[(Addr/2)] & (0x02 << shift), 0);
		   		SendDlgItemMessage(hDlg, IDC_CHECK_IN2, BM_SETCHECK, IDI[(Addr/2)] & (0x04 << shift), 0);
		   		SendDlgItemMessage(hDlg, IDC_CHECK_IN3, BM_SETCHECK, IDI[(Addr/2)] & (0x08 << shift), 0);
			}
			else
			{
				/* circuit 2 */
				Addr2 = atoi(szBuf);
				if (Addr2 < 0 || Addr2 > 31 )
				{
					Addr2 = 1;
					sprintf(szBuf, "%d", Addr2);
					SendDlgItemMessage(hDlg, IDC_EDIT_SLAVE_ADDR, WM_SETTEXT, 0,   /* line number */
						(DWORD) (LPSTR) szBuf);      /* buffer address             */
				}
				shift = 4*(Addr2%2);

				/* get state of output checkboxes */
				if (SendDlgItemMessage(hDlg, IDC_CHECK_OUT0, BM_GETCHECK, 0, 0))
					ODI2[(Addr2/2)] |= 0x01 << shift;
		   		else
					ODI2[(Addr2/2)] &= ~(0x01 << shift);
		   		if (SendDlgItemMessage(hDlg, IDC_CHECK_OUT1, BM_GETCHECK, 0, 0))
					ODI2[(Addr2/2)] |= 0x02 << shift;
		   		else
					ODI2[(Addr2/2)] &= ~(0x02 << shift);
		   		if (SendDlgItemMessage(hDlg, IDC_CHECK_OUT2, BM_GETCHECK, 0, 0))
					ODI2[(Addr2/2)] |= 0x04 << shift;
		   		else
					ODI2[(Addr2/2)] &= ~(0x04 << shift);
		   		if (SendDlgItemMessage(hDlg, IDC_CHECK_OUT3, BM_GETCHECK, 0, 0))
					ODI2[(Addr2/2)] |= 0x08 << shift;
		   		else
					ODI2[(Addr2/2)] &= ~(0x08 << shift);
				/* writes output data and reads input data */
				AASiDataExchange(MasterID2, ODI2, IDI2, &EcFlags2);
		   		SendDlgItemMessage(hDlg, IDC_CHECK_IN0, BM_SETCHECK, IDI2[(Addr2/2)] & (0x01 << shift), 0);
		   		SendDlgItemMessage(hDlg, IDC_CHECK_IN1, BM_SETCHECK, IDI2[(Addr2/2)] & (0x02 << shift), 0);
		   		SendDlgItemMessage(hDlg, IDC_CHECK_IN2, BM_SETCHECK, IDI2[(Addr2/2)] & (0x04 << shift), 0);
		   		SendDlgItemMessage(hDlg, IDC_CHECK_IN3, BM_SETCHECK, IDI2[(Addr2/2)] & (0x08 << shift), 0);
			}

		   	break;

        case WM_COMMAND:               /* message: received a command */
            if (wParam == IDOK         /* "OK" box selected?          */
                || wParam == IDCANCEL) /* System menu close command?  */
            {
                EndDialog(hDlg, TRUE); /* Exits the dialog box        */
                return (TRUE);
            }
            break;
    }
    return (FALSE);               /* Didn't process a message    */
} 
