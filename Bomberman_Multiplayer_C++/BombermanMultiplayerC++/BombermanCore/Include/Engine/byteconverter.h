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

class ByteConverter
{
public:

	//static unsigned char* BytesCopy(unsigned char* Source, size_t destLength, int startIndex, int bytesToCopy);
	//static std::shared_ptr<std::vector<unsigned char>> BytesCopy(std::shared_ptr<std::vector<unsigned char>> destination, std::shared_ptr<std::vector<unsigned char>> src, int startIndex, int bytesToCopy);
	static int BytesCopy(std::shared_ptr<std::vector<unsigned char>> destination, std::shared_ptr<std::vector<unsigned char>> src, int startIndex, int bytesToCopy);

		
	//static int BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, unsigned char* str2, int bytesToInsert);
	//static int BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, float ToAppend);
	//static int BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, int ToAppend);
	//static int BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, unsigned char toInsert);


	static int BytesAppend(std::vector<unsigned char>* Dest, int startIndex, std::vector<unsigned char>* toInsert, int bytesToInsert);
	static int BytesAppend(std::vector<unsigned char>* Dest, int startIndex,std::shared_ptr< std::vector<unsigned char>> toInsert, int bytesToInsert);
	static int BytesAppend(std::shared_ptr<std::vector<unsigned char>> Dest, int startIndex, std::vector<unsigned char>* toInsert, int bytesToInsert);
	static int BytesAppend(std::shared_ptr<std::vector<unsigned char>> Dest, int startIndex, std::shared_ptr<std::vector<unsigned char>> toInsert);

	static int BytesAppend(std::shared_ptr<std::vector<unsigned char>> Dest, int startIndex, std::shared_ptr<std::vector<unsigned char>> toInsert,int bytesToInsert);
	static int BytesAppend(std::shared_ptr<std::vector<unsigned char>> Dest, int startIndex, int toInsert);
	static int BytesAppend(std::shared_ptr<std::vector<unsigned char>> Dest, int startIndex, float toInsert);
	static int BytesAppend(std::string& Dest, size_t destLength, int startIndex, std::string& str2, int bytesToInsert);



	

	static int BytesToInt(const unsigned char* buffer, int startIndex = 0, bool BigEndian = true);
	static int BytesToInt(const std::vector<unsigned char>* buffer, int startIndex = 0, bool BigEndian = true);
	static int BytesToInt(const std::shared_ptr<std::vector<unsigned char>> buffer, int startIndex = 0, bool BigEndian = true);
	//static int BytesToInt(std::string buffer, int startIndex = 0, bool BigEndian = true);

	

	static std::shared_ptr<std::vector<unsigned char>> IntToBytes(int num);
	static std::shared_ptr<std::string> IntToBytes_String(int num);
	
	/// <summary>
/// RETURNS ALLOCATED MEMORY. REMEMBER TO DESTROY IT;
/// </summary>
/// <param name="toConvert"></param>
/// <returns></returns>
	static std::shared_ptr<std::vector<unsigned char>> FloatToBytes(float toConvert);
	static void FloatToBytes(float toConvert, std::shared_ptr < std::vector< unsigned char>> toFill);
	static std::shared_ptr<std::string> FloatToBytes_Str(float toConvert);
	
	
	static float BytesToFloat(const unsigned char* bytes, int startIndex, bool big_endian);
	static float BytesToFloat(const std::vector<unsigned char>* bytes, int startIndex, bool big_endian);

	
	/// <summary>
	/// Scans a string for a character called "Delimiter" and returns a string vector with all substrings between the delimiters
	/// </summary>
	static std::vector<std::string> split(const std::string& s, char delimiter);
	static std::vector<std::shared_ptr<unsigned char[]>> split(const unsigned char* s, int length, char delimiter);
	//static std::vector<std::shared_ptr<unsigned char[]>> split(const std::vector<unsigned char>* s,  char delimiter);
	static std::vector<std::vector<unsigned char>*>* split(const std::vector<unsigned char>* s, char delimiter);
	//static std::shared_ptr<std::vector<std::vector<unsigned char>>> split(const std::shared_ptr<std::vector<unsigned char>> s, char delimiter);




	
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
	
	static unsigned char* Cut(unsigned char** Input,int InputLength, int StartIndex, int amount);
	std::shared_ptr<std::vector<unsigned char>> EraseRegion(std::shared_ptr<std::vector<unsigned char>> Input,int InputLength, int StartIndex, int amount);
};

//static int BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, unsigned char* str2, int bytesToInsert);
