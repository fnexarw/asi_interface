#-------------------------------------------------------------------------------
# Name:        Asibus Interface
# Purpose:
#
# Author:      Eric Cheong
#
# Created:     25.10.2012
# Copyright:   (c) ERW2HI 2012
# Licence:     <your licence>
#-------------------------------------------------------------------------------
#!/usr/bin/env python

## http://code.activestate.com/recipes/181063-windows-dll-with-pointers-parameters-calling-with-/
import sys
from ctypes import windll, byref, c_int, c_ubyte, c_short, c_ushort, c_char, c_char_p, c_bool, c_ulonglong


class ASiInterface():

    def __init__(self):

         try:
            self.ureg = ""
            self.exit = None
            self.InitialSettings = ""
            self.retMasterIDObj = byref(c_int())
            self.handler = windll.LoadLibrary("C://Program Files (x86)/AS-Interface Control Tools/BW/en/asidrv32.dll")
            ##self.handler = windll.LoadLibrary("C://ASInterface/asidrv32.dll")
            self.error = hex(self.handler.AASiRegisterMaster(self.retMasterIDObj))
            self.MID = self.retMasterIDObj._obj.value
            self.init = hex(self.handler.AASiInit(self.MID, self.InitialSettings))
            self.init_status = 0
         except Exception:
            self.init_status = -1
            print "Errors during initialization. Make sure asidrv32.dll is available.\n"
            self.ASI_INIT()


    def ASI_INIT(self):
        if self.init_status == 0:
            slave_detected = self.detectSlaveList()
            if slave_detected != -1:
                for i in range(0,31):
                    self.BYTE_CLEAR(int(i+1))
                return 0
            else:
                print "Warning: No slave is detected. Check your power supply!!!"
                return -2
        else:
            return -1

## *************************************************************************************************************************
## *************************************************************************************************************************

## int EXP AASiReadName (int MasterID, LPCSTR FAR *Name);
## error = AASiReadName(MasterID, &Name);
    def getReadName(self):
        self.name = byref(c_char_p())
        readname = hex(self.handler.AASiReadName(self.MID, self.name))
        return readname

## int EXP AASiGetDllName (int MasterID, LPCSTR* dllname );
## error = AASiGetDllName (MasterID, LPCSTR* dllname );
    def getDLLName(self):
        self.dllname = byref(c_char_p())
        dllname = hex(self.handler.AASiGetDllName(self.MID, self.dllname))
        return dllname

## int EXP AASiReadVersionID (int MasterID, LPCSTR FAR *VersionID);
## error = AASiReadVersionID(MasterID, &VersionID);
    def getVersionID(self):
        self.versionid = byref(c_char_p())
        versionid = hex(self.handler.AASiReadVersionID(self.MID, self.versionid))
        return versionid

## int EXP AASiGetDriverName (int MasterID, LPCSTR FAR *Name, BOOL Short);
## AASiGetDriverName(MasterID, Name, Short);
    def getDriverName(self):
        self.drvName = byref(c_char_p())
        drivername = hex(self.handler.AASiGetDriverName(self.MID,self.drvName,False))
        return drivername

## int EXP AASiGetWatchdog (int MasterID, BOOL FAR *TimedOut);
## error = AASiGetWatchdog(MasterID, &TimedOut);
    def getTM(self):
        self.tmVal = byref(c_bool())
        watchdog = self.handler.AASiGetWatchdog(self.MID, self.tmVal)
        return watchdog

## int EXP AASiGetSettings (int MasterID, LPCSTR FAR *Settings, BOOL Short);
## AASiGetSettings(MasterID, Settings, Short);
    def getSettings(self):
        self.settings = byref(c_char_p())
        settings = hex(self.handler.AASiGetSettings(self.MID, self.settings, c_bool(1)))
        return settings

## int EXP AASiGetUserName (int MasterID, LPCSTR* username );
## error = AASiGetUserName (MasterID, LPCSTR* dllname );
    def getUserName(self):
        self.username = byref(c_char_p())
        username = hex(self.handler.AASiGetUserName(self.MID, self.username))
        return username

## *************************************************************************************************************************
## *************************************************************************************************************************

## int EXP AASiReadDiagnosticString(int MasterID, AASiSlaveAddr Address, unsigned char **DiagnosticString, unsigned char *Length);
## error = AASiReadDiagnosticString (MasterID, Address, DiagnosticString);
    def readDiagString(self):
        self.diagString = byref(c_ubyte())
        resp = hex(self.handler.AASiReadDiagnosticString(self.MID, c_ubyte(2), self.diagString))
        return resp

## int EXP AASiExecuteCommand (int MasterID, AASiSlaveAddr Address, AASiSlaveData Request, AASiSlaveData FAR *Response);
## error = AASiExecuteCommand (MasterID, Address, Request, &Response);
    def execCommand(self):
        self.response = byref(c_char())
        execute_command = hex(self.handler.AASiExecuteCommand(self.MID, c_ubyte(int(0x02)), c_ubyte(int(0x02)), self.response))
        return execute_command

## int EXP AASiWrite16BitODI (int MasterID, AASiSlaveAddr Address, AASi16BitData FAR Out);
## error = AASiWrite16BitODI (MasterID, Address, Out);
    def write16BitODI(self):
        slave_addr = c_ubyte(2)
        self.data_out = (c_short*4)(2,2,2,2)
        execute_command = hex(self.handler.AASiWrite16BitODI(self.MID, slave_addr, self.data_out))
        return execute_command

## int EXP AASiRead16BitODI (int MasterID, AASiSlaveAddr Address, AASi16BitData FAR In);
## error = AASiRead16BitODI (MasterID, Address, In);
    def read16BitODI(self):
        slave_addr = c_ubyte(0x2)
        self.data_in = (c_short*4)()
        read_command = hex(self.handler.AASiRead16BitODI(self.MID, slave_addr, self.data_in))
        data = self.data_in._type_.value
        return read_command

    def retErrorCode(self,func):
        self.code = hex(func)
        return self.code

    def unloadDLL(self):
        exit = hex(self.handler.AASiExit(self.MID))
        return exit

    def unregister(self):
        if self.exit is 0x00:
            unregister_master = self.handler.AASiUnRegisterMaster(self.MID)
            return unregister_master
        if self.ureg is None:
            return "unregister masterid is successful"

## int EXP AASiWriteODI (int MasterID, AASiProcessData FAR ODI, AASiSlaveAddr First, unsigned char Amount);
## error = AASiWriteODI (MasterID, ODI, First, Amount);
    def writeODI(self, SlaveAddr, ODI_value):
        self.ODI = (c_ubyte*32)(ODI_value)
        self.First = c_ubyte(int(SlaveAddr))
        wrODI = self.handler.AASiWriteODI(self.MID, self.ODI, self.First, c_ubyte(1))
        return wrODI

## int EXP AASiReadODI (int MasterID, AASiProcessData FAR ODI);
## error = AASiReadODI (MasterID, ODI);
    def readODI(self):
        self.ODI = (c_ubyte*32)()
        ODI = self.handler.AASiReadODI(self.MID, self.ODI)
        return ODI

## int EXP AASiReadIDI (int MasterID, AASiProcessData FAR IDI, AASiSlaveAddr First, unsigned char Amount, AASiEcFlags FAR *EcFlags);
## error = AASiReadIDI (MasterID, IDI, First, Amount, &EcFlags);
    def readIDI(self, SlaveAddr):
        self.IDI = (c_ubyte*32)()
        self.First = c_ubyte(SlaveAddr)
        self.EcFlags = byref(c_ushort())
        rdIDI = self.handler.AASiReadIDI(self.MID, self.IDI, self.First, c_ubyte(1), self.EcFlags)
        return rdIDI

## int EXP AASiReadPCD (int MasterID, AASiSlaveAddr Address, AASiConfigData FAR *PCD);
## error = AASiReadPCD (MasterID, Address, &PCD);
    def readPCD(self, SlaveAddr):
        self.slaveAddr = c_ubyte(SlaveAddr)
        self.PCD = byref(c_ushort())
        readPCD = self.handler.AASiReadPCD(self.MID,self.slaveAddr,self.PCD)
        PCD = hex(self.PCD._obj.value)
        return readPCD

## int EXP AASiReadLDS (int MasterID, AASiSlaveList FAR *LDS);
## error = AASiReadLDS (MasterID, &LDS);
    def detectSlaveList(self):
        self.SlaveList = byref(c_ulonglong())
        slaveList = self.handler.AASiReadLDS(self.MID, self.SlaveList)
        sList = hex(self.SlaveList._obj.value)
        slave_detection_status = sList == '0x0L' and -1 or 0
        return slave_detection_status

## *****************************************************************************
##                             END-USER FUNCTIONS
## *****************************************************************************

##    def GET_OUTPUT_BIT(self, slaveAddr, bit_toCheck):
##        self.readODI()
##        val = self.ODI.__getslice__(0,32)
##        retval_at_slave_address = self.ODI.__getitem__(1)
##        result = retval_at_slave_address & (1<<bit_toCheck-1) and 1 or 0
##        return result

    def GET_INPUT_BIT(self, slaveAddr, bit_toCheck):
        self.readIDI(slaveAddr)
        retval_at_slave_address = self.IDI.__getitem__(0)
        result = retval_at_slave_address & (1<<bit_toCheck-1) and 1 or 0
        buf = self.IDI.__getslice__(0,32)
        return result

    def BIT_SET(self, slaveAddr, bit_toSet):
        self.readODI()
        retval_at_slave_address = self.ODI.__getitem__(slaveAddr-1)
        arr = self.ODI.__getslice__(0,31)
        ODI_value_toWrite = retval_at_slave_address | (1<<bit_toSet-1)
        result = self.writeODI(slaveAddr, ODI_value_toWrite) is 0 and True or False
        return result

    def BIT_CLEAR(self, slaveAddr, bit_toClear):
        self.readODI()
        retval_at_slave_address = self.ODI.__getitem__(slaveAddr-1)
        ODI_value_toWrite = retval_at_slave_address & ~(1<<bit_toClear-1)
        result = self.writeODI(slaveAddr, ODI_value_toWrite) is 0 and True or False
        return result

    def BYTE_CLEAR(self, slaveAddr):
        result = self.writeODI(slaveAddr, 0x0) is 0 and True or False
        return result

    def BYTE_SET(self, slaveAddr, low_byte_toSet):
        result = self.writeODI(slaveAddr, low_byte_toSet) is 0 and True or False
        return result

## *****************************************************************************
## *****************************************************************************

## int EXP AASiWritePP (int MasterID, AASiSlaveAddr Address, AASiSlaveData PP);
## error = AASiWritePP (MasterID, Address, PP);
    def writePP(self):
        self.Addr_wrPP = c_ubyte(int(0x2))
        self.Data_wrPP = c_ubyte(int(0xF))
        writePP = hex(self.handler.AASiWritePP(self.MID, self.Addr_wrPP, self.Data_wrPP))
        return writePP

## int EXP AASiReadPP (int MasterID, AASiSlaveAddr Address, AASiSlaveData FAR *PP);
## error = AASiReadPP (MasterID, Address, &PP);
    def readPP(self):
        self.Addr_rdPP = c_ubyte(int(0x2))
        self.Data_rdPP = byref(c_ubyte())
        PP = hex(self.handler.AASiReadPP(self.MID, self.Addr_rdPP, self.Data_rdPP))
        return PP

## int EXP AASiSendParameter (int MasterID, AASiSlaveAddr Address, AASiSlaveData PI, AASiSlaveData FAR *Return);
## error = AASiSendParameter (MasterID, Address, PI, &Ret);
    def SendPP(self):
        self.Addr_sPP = c_ubyte(int(0x2))
        self.Data_PI = c_ubyte(int(0xF))
        self.Data_sPP = byref(c_ubyte())
        sendParameter = hex(self.handler.AASiSendParameter(self.MID, self.Addr_sPP, self.Data_PI, self.Data_sPP))
        return sendParameter

## int EXP AASiDriver (int MasterID, int Command, void FAR *In, void FAR *Out);
## AASiDriver(MasterID, Command, In, Out);
    def asiDriver(self):
        self.in_cmd = c_void_p()
        self.out_cmd = c_void_p()
        asiDriver = hex(self.handler.AASiDriver(self.MID, c_int(0x100), self.in_cmd, self.out_cmd))
        return asiDriver
## *************************************************************************************************************************
## *************************************************************************************************************************

def main():

    asi = ASiInterface()
    asi.BIT_SET(9,2)

    if asi.init_status == -1:
        sys.exit(11)
    else:
        argument_length = len(sys.argv)
        if argument_length == 1:
            res = '''\nAvailable Options:
            [0] asibus.exe ASI_INIT
            [1] asibus.exe BIT_SET          <SlaveAddress> <SET bit>
            [2] asibus.exe BYTE_SET         <SlaveAddress> <SET byte>
            [3] asibus.exe BIT_CLEAR        <SlaveAddress> <CLEAR bit>
            [4] asibus.exe BYTE_CLEAR       <SlaveAddress>
            [5] asibus.exe GET_INPUT_BIT    <SlaveAddress> <GET bit>
            '''
            print res
            resp = 0

        elif argument_length == 2:
            if sys.argv[1] == "ASI_INIT":
                resp = asi.ASI_INIT()
                print resp
            else:
                resp = -2
        elif argument_length == 3:
            if sys.argv[1] == "BYTE_CLEAR":
                resp = asi.BYTE_CLEAR(int(sys.argv[2]))
            else:
                resp = -1
        elif argument_length == 4:
            if sys.argv[1] == "BIT_SET":
                resp = asi.BIT_SET(int(sys.argv[2]),int(sys.argv[3]))
            elif sys.argv[1] == "BIT_CLEAR":
                resp = asi.BIT_CLEAR(int(sys.argv[2]),int(sys.argv[3]))
            elif sys.argv[1] == "GET_INPUT_BIT":
                resp = asi.GET_INPUT_BIT(int(sys.argv[2]),int(sys.argv[3]))
                print resp
            elif sys.argv[1] == "BYTE_SET":
                resp = asi.BYTE_SET(int(sys.argv[2]),int(sys.argv[3]))
            else:
                resp = -1
        else:
            resp = -1

    ext = asi.unloadDLL()
    ureg = asi.unregister()
    if resp == 0 :
        sys.exit(0)
    elif resp == -1:
        print "Please check if correct command is used..."
        sys.exit(11)
    else:
        sys.exit(22)


if __name__ == '__main__':
    main()