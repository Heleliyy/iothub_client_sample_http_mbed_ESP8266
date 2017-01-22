// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#ifdef _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include "azure_c_shared_utility/platform.h"
#include "ESP8266Interface.h"
#include "NTPClient.h"
#include "azure_c_shared_utility/xio.h"
#include "azure_c_shared_utility/tlsio_wolfssl.h"
#include "mbed.h"

ESP8266Interface wifi(D8,D2,D0,"Ruff_R0101965","Password01!",115200); // TX,RX,Reset,SSID,Password,Baud
RawSerial pc(USBTX, USBRX); // tx, rx

int setupRealTime(void)
{
    int result;
    
    NTPClient ntp;
    if (ntp.setTime("be.pool.ntp.org") != 0) //0.pool.ntp.org 59.106.180.168
    {
        result = __LINE__;
    }
    else
    {
        result = 0;
    }
    return result;
}

int platform_init(void)
{
    int result;
    pc.baud(115200); //It is required.
    
    if (wifi.init() != 0)
    {
        result = __LINE__;
    }
    
    if (wifi.connect())
    {
        //(void)printf("#DEBUG: func: %s, file: %s, line: %d, Wifi connection is setup successfully!\r\n", __FUNCTION__, __FILE__, __LINE__);
        (void)printf("Wifi connection is setup successfully!\r\n");
        result = 0;
    }
    else
    {
        result = __LINE__;
    }
    
    if (setupRealTime() != 0)
    {
        result = __LINE__;
    }
    
    return result;
}

const IO_INTERFACE_DESCRIPTION* platform_get_default_tlsio(void)
{
    return tlsio_wolfssl_get_interface_description();
}

void platform_deinit(void)
{
    wifi.disconnect();
}
