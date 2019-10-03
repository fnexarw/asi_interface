from ctypes import *

#LPSTR   = c_char_p
#LPCSTR  = c_char_p

AASiProcessData     = c_ubyte*32
AASiSlaveList       = c_ulonglong
AASiHiFlags         = c_ubyte
AASiECFlags         = c_ushort
AASiSlaveData       = c_ubyte
AASiSlaveAddr       = c_ubyte
AASiConfigData      = c_ushort
AASiErrorCounters   = c_ubyte*64
AASi16BitData       = c_short*4
AASiCtrlData        = c_ubyte*16
AASiCtrlAddr        = c_ushort
AASiCtrlFlags       = c_ubyte


##class AASiCtrlResDT:
##    A_DT_NULL       = int(0x0000)
##    A_DT_NIBBLE     = int(0x0001)
##    A_DT_BYTE       = int(0x0002)
##    A_DT_WORD       = int(0x0003)
##    A_DT_DWORD      = int(0x0004)
##    A_DT_QUARTERK   = int(0x0005)
##    A_DT_USIGN8     = int(0x0011)
##    A_DT_USIGN16    = int(0x0012)
##    A_DT_USIGN32    = int(0x0013)
##    A_DT_FUNCTION   = int(0x1000)
##
##class AASiCtrlResAR:
##    A_AR_NULL       = int(0x0000)
##    A_AR_NONE       = int(0x0001)
##    A_AR_READ       = int(0x0002)
##    A_AR_READWRITE  = int(0x0003)
##    A_AR_WRITE      = int(0x0004)
##    A_AR_EXECUTE    = int(0x1000)
##    A_AR_COUNTER    = int(0x7F00)
##    A_AR_TIMER      = int(0x7F01)
##
##class BOOL(Structure):
##    _fields_ = [('FALSE',c_bool),
##                ('TRUE',c_bool)]
##

class AASiConfig(Structure):
    _fields_ = [('PCD',AASiConfigData*64),
                ('PP',AASiSlaveData*64)]
##
##class AASiCtrlResource(Structure):
##    _fields_ = [('ID',c_uint),
##                ('Address',c_uint),
##                ('Extra',c_ubyte),
##                ('Type', AASiCtrlResDT),
##                ('Access',AASiCtrlResAR),
##                ('Size',c_uint),
##                ('Symbol',c_char*10),
##                ('Text',c_char*50)]





