/* Copyright © 2012 Demetris Stavrou
 * version 1.0
 * ---------------------------------
 * Minimal Library for the TMP100 temperature sensor from TI
 *
 * Just include this file in your project.
 */

#ifndef __TMP100_H
#define __TMP100_H

#include <i2c.h>

/*---------------------*/
#define TMP100_RES_9bits    0x00
#define TMP100_RES_10bits   0x01
#define TMP100_RES_11bits   0x02
#define TMP100_RES_12bits   0x03
/*----------------------*/

void tm_setres(unsigned char tmpres)
{
    StartI2C();
    WriteI2C(0x90); // Write to point register
    WriteI2C(0x01); // Write configuration reg to point register;
    WriteI2C(tmpres<<5);
    StopI2C();
}

void tm_setconf(unsigned char conf)
{
    StartI2C();
    WriteI2C(0x90); // Write to point register
    WriteI2C(0x01); // Write configuration reg to point register;
    WriteI2C(conf);
    StopI2C();
}

int tm_gettemp()
{
    unsigned char rec_char;
    unsigned int rec_temp;

    StartI2C();
    WriteI2C(0x90); // Write to point register
    WriteI2C(0x00); // Write Temp reg to point register;
    StartI2C();
    WriteI2C(0x91);
    rec_char = ReadI2C();
    rec_temp = (int)rec_char;
    AckI2C();
    rec_char = ReadI2C();
    rec_temp = rec_temp << 8;
    rec_temp = rec_temp | rec_char;
    StopI2C();
    return rec_temp;
}

void tm_tostr(unsigned int temp, char* tempstr)
{
    unsigned int dec;
    dec = ((temp >> 4) & 0x000F)*625;
    sprintf(tempstr,"%d.%04d",temp>>8,dec);
}

#endif
