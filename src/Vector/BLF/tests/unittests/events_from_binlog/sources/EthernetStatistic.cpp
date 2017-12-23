#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <stdio.h>
#define STRICT
#include <windows.h>

#include "binlog.h"

int main(int argc, char ** argv)
{
    /* create file */
    LPCTSTR pFileName = _T("test_EthernetStatistic.blf");
    HANDLE hFile = BLCreateFile(pFileName, GENERIC_WRITE);
    if (hFile == INVALID_HANDLE_VALUE) {
        return -1;
    }

    /* set write options */
    if (!BLSetWriteOptions(hFile, BL_COMPRESSION_NONE, 0)) {
        return -1;
    }

    /* define object */
    VBLEthernetStatistic obj;
    memset(&obj, 0, sizeof(VBLEthernetStatistic));

    /* VBLEthernetStatistic */
    obj.mChannel = 0x1111;
    obj.mRcvOk_HW = 0x2222222222222222;
    obj.mXmitOk_HW = 0x3333333333333333;
    obj.mRcvError_HW = 0x4444444444444444;
    obj.mXmitError_HW = 0x5555555555555555;
    obj.mRcvBytes_HW = 0x6666666666666666;
    obj.mXmitBytes_HW = 0x7777777777777777;
    obj.mRcvNoBuffer_HW = 0x8888888888888888;
    obj.mSQI = 0x7999;
    obj.mHardwareChannel = 0xAAAA;

    /* VBLObjectHeader */
    obj.mHeader.mObjectFlags = BL_OBJ_FLAG_TIME_ONE_NANS;
    obj.mHeader.mClientIndex = 0x1111;
    obj.mHeader.mObjectVersion = 0;
    obj.mHeader.mObjectTimeStamp = 0x2222222222222222;

    /* VBLObjectHeaderBase */
    obj.mHeader.mBase.mSignature = BL_OBJ_SIGNATURE;
    obj.mHeader.mBase.mHeaderSize = sizeof(obj.mHeader);
    obj.mHeader.mBase.mHeaderVersion = 1;
    obj.mHeader.mBase.mObjectSize = sizeof(VBLEthernetStatistic);
    obj.mHeader.mBase.mObjectType = BL_OBJ_TYPE_ETHERNET_STATISTIC;

    /* write object */
    if (!BLWriteObject(hFile, &obj.mHeader.mBase)) {
        return -1;
    }

    /* write object again */
    if (!BLWriteObject(hFile, &obj.mHeader.mBase)) {
        return -1;
    }

    /* close handle */
    if (!BLCloseHandle(hFile)) {
        return -1;
    }

    return 0;
}