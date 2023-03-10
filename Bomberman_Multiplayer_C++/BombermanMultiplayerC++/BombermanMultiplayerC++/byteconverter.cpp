#include "byteconverter.h"
#pragma once
#include <string>
#include <iostream>
static class byteconverter
{
   
public:
	static int BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, unsigned char* str2, int bytesToInsert)
    {
        for (int i = 0; (i < bytesToInsert); ++i)
        {
            if (startIndex + i >= destLength)
            {
                return 1;
            }
            char toInsert = str2[i];
            if (toInsert < 0x30)
            {
                //toInsert = 0x30;
            }
            Dest[startIndex + i] = toInsert;
        }

        return 0;
    }
    static int BytesAppend(std::string& Dest, size_t destLength, int startIndex, std::string& str2, int bytesToInsert)
    {
        for (int i = 0; (i < bytesToInsert); ++i)
        {
            if (startIndex + i >= destLength)
            {
                return 1;
            }
            char toInsert = str2[i];
            if (toInsert < 0x30)
            {
                //toInsert = 0x30;
            }
            Dest[startIndex + i] = toInsert;
        }

        return 0;
    }
    static int BytesToInt(char* buffer)
    {

        return (buffer[3] << 24) + (buffer[2] << 16) + (buffer[1] << 8) + buffer[0];
    }
    static int BytesToInt(std::string buffer)
    {
        
        return (buffer[3] << 24) + (buffer[2] << 16) + (buffer[1] << 8) + buffer[0];
    }
    static int BytesToInt_V2(const unsigned char* buffer, int startIndex)
    {

        char buffer2[4];
        for (int i = 0; i < 4; i++)
        {
            buffer2[i] = buffer[startIndex + i];
        }


        return (int)(buffer2[0] << 24) + (buffer2[1] << 16) + (buffer2[2] << 8) + buffer2[3];
    }
   static void IntToBytes(int num, unsigned char* bytes)
    {
        for (int i = 0; i < sizeof(int); i++)
        {
            bytes[i] = (num >> (i * 8)) & 0xff;
        }
    }
   static void FloatToBytes(unsigned char* buffer, float toConvert)
   {
       
       std::memcpy(buffer, &toConvert, sizeof(float));
       return;
       for (int i = 0; i < sizeof(float); ++i)
       {
           std::cout << " " << i << " : " << static_cast<int>(buffer[i]) ;
       }
       std::cout << std::endl;
   }
   static float BytesToFloat(const unsigned char* bytes, int startIndex,bool big_endian)
   {

       if(big_endian)
         u.ul = (bytes[startIndex + 0] << 24) | (bytes[startIndex + 1] << 16) | (bytes[startIndex + 2] << 8) | bytes[startIndex + 3];
       else
         u.ul = (bytes[startIndex + 3] << 24) | (bytes[startIndex + 2] << 16) | (bytes[startIndex + 1] << 8) | bytes[startIndex + 0];

       return u.f;
   }
};
