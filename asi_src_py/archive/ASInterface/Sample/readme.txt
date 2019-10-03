PROGRAM: Sample.c

PURPOSE: shows the use of the driver DLLs for the Bihl+Wiedemann AS-Interface masters,
		 especially the initialization process.

		 This program shows two ways of initialization:

		 1. Menu Driver:
			initializing an AS-Interface master with the function AASiInitDialog()
			(with dialog box for selecting the desired AS-Interface master and circuit
			as realized in the AS-Interface Control Tools). Also, a profile (ini-file)
			is used to store the previously used 'Settings'-string.

		 2. Menu Driver (2 Circuits):
			initializing an AS-Interface master with two AS-Interface circuits
			(for example the AS-Interface/Ethernet Gateway or the AS-Interface PCI card)
			with the function AASiInit(). Here, the ini-file is not used, but
			the 'Settings'-string is hardcoded.

		 The menu functions has only one entry: Data Exchange. This command
		 opens a dialog box that can exchange data with one slave. Depending on
		 the method how you initialize the AS-Interface master (1. or 2.) the 'circuit 2'-
		 checkbox will appear (for method 2.), so you can also switch between the
		 two circuits of the AS-Interface master.

COMMENTS:
	This program uses the "AASi...()"-function set for the Advanced AS-Interface
	(specification 2.1). If you are using an "old" AS-Interface Master (according to
	spec. 2.0) the driver asidrv32.dll manages all the casting of the data from
	Advanced AS-Interface (AASi) to "old" AS-Interface (ASi) and vice versa.

Author: Daniel Rudolf
Date: 24.08.2001

ATTENTION:
Before calling the function AASiDataExchange() the AS-Interface Master is
switched to configuration mode with the function AASiSetConfigMode()
in order to enable data exchange even if the AS-Interface slave is not
projected.

IMPORTANT:
The project must contain the following files:
sample.c
asidrv.lib
sample.rc
