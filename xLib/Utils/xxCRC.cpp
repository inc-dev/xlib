//---------------------------------------------------------------------------
#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxCRC.h"
/*------------------------------------------------------------------------------
  Name  : CRC-8
  Poly  : 0x31	x^8 + x^5 + x^4 + 1
  Init  : 0xFF
  Revert: false
  XorOut: 0x00
  Check : 0xF7 ("123456789")
  MaxLen: 15 байт(127 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/

unsigned char Crc8(unsigned char *pcBlock, unsigned char len)
{
    unsigned char crc = 0xFF;
    unsigned char i;

    while (len--)
    {
        crc ^= *pcBlock++;

        for (i = 0; i < 8; i++)
            crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
    }

    return crc;
}
/*------------------------------------------------------------------------------
  Name  : CRC-16 CCITT
  Poly  : 0x1021	x^16 + x^12 + x^5 + 1
  Init  : 0xFFFF
  Revert: false
  XorOut: 0x0000
  Check : 0x29B1 ("123456789")
  MaxLen: 4095 байт (32767 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/

unsigned short Crc16( unsigned char *pcBlock, unsigned short len )
{
    unsigned short crc = 0xFFFF;
    unsigned char i;

    while( len-- )
    {
        crc ^= *pcBlock++ << 8;

        for( i = 0; i < 8; i++ )
	    crc = crc & 0x8000 ? ( crc << 1 ) ^ 0x1021 : crc << 1;
    }

    return crc;
}
/*------------------------------------------------------------------------------
  Name  : CRC-32
  Poly  : 0x04C11DB7	x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11
                       + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
  Init  : 0xFFFFFFFF
  Revert: true
  XorOut: 0xFFFFFFFF
  Check : 0xCBF43926 ("123456789")
  MaxLen: 268 435 455 байт (2 147 483 647 бит) - обнаружение
   одинарных, двойных, пакетных и всех нечетных ошибок
*/
unsigned long Crc32(unsigned char *buf, unsigned long len)
{
    unsigned long crc_table[256];
    unsigned long crc;

    for (int i = 0; i < 256; i++)
    {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
 
        crc_table[i] = crc;
    };
 
    crc = 0xFFFFFFFFUL;
 
    while (len--) 
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
 
    return crc ^ 0xFFFFFFFFUL;
};

#ifndef __GNUC__
#pragma package(smart_init)
#endif
