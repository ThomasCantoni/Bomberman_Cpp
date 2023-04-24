#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <sstream>

union {
    float f;
    unsigned long ul;
} u;

#define FAST_FLOAT_TO_BYTE(BYTES,FLOAT) BYTES = reinterpret_cast<unsigned char*>(&FLOAT);

class byteconverter
{
public:

	static unsigned char* BytesCopy(unsigned char* Source, size_t destLength, int startIndex, int bytesToCopy);
	
		
	static int BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, unsigned char* str2, int bytesToInsert);
	
	static int BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, float ToAppend);
	
	static int BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, int ToAppend);
	
	static int BytesAppend(std::string& Dest, size_t destLength, int startIndex, std::string& str2, int bytesToInsert);
	
	static int BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, unsigned char toInsert);
	

	static int BytesToInt(const unsigned char* buffer, int startIndex = 0, bool BigEndian = true);
	
	static int BytesToIntString(std::string buffer, int startIndex = 0);
	
	static unsigned char* IntToBytes(int num);
	
	static std::shared_ptr<std::string> IntToBytes_String(int num);
	
	/// <summary>
	/// DEPRECATED, PLEASE USE FloatToBytes3 INSTEAD
	/// </summary>
	/// <param name="toConvert"></param>
	/// <returns></returns>
	static unsigned char* FloatToBytes(float toConvert);
	


	static unsigned char* FloatToBytes3(float toConvert);
	
	static void FloatToBytes3(float toConvert, unsigned char* toFill);
	
	static std::shared_ptr<std::string> FloatToBytes3_Str(float toConvert);
	
	static unsigned char** FloatToBytes2(float toConvert);
	
	static float BytesToFloat(const unsigned char* bytes, int startIndex, bool big_endian);
	
	static std::vector<std::string> split(const std::string& s, char delimiter);
	
	/// <summary>
	/// INCOMPLETE!!!!!
	/// Searches for a substring in 'Input', then removes the matching characters if found. 
	/// This is designed to be used cascadingly on a single string in order to extract specific contextes. 
	/// Recommended for console commands.
	/// </summary>
	/// <param name="Input"> = Modifiable input string. The substring overlapping with 'ToScan' will be removed</param>
	/// <param name="ToScan"> = The substring to search in input</param>
	/// <returns> true if 'Input' contains 'ToScan', otherwise returns false </returns>
	static bool Scan(std::string Input, std::string ToScan);
	
};

//static int BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, unsigned char* str2, int bytesToInsert);
