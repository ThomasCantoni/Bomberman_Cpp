#include "byteconverter.h"


//#define FAST_FLOAT_TO_BYTE(BYTES,FLOAT) BYTES = reinterpret_cast<unsigned char*>(&FLOAT);


unsigned char* byteconverter::BytesCopy(unsigned char* Source, size_t destLength, int startIndex, int bytesToCopy)
{
	unsigned char* toReturn = static_cast<unsigned char*>(malloc(bytesToCopy));
	if (toReturn == nullptr)
	{
		return NULL;
	}
	for (size_t i = 0; i < bytesToCopy; ++i)
	{
		toReturn[i] = Source[startIndex + i];
	}

	return toReturn;
}
int byteconverter::BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, unsigned char* str2, int bytesToInsert)
{
	
	if (startIndex == 0 && startIndex + bytesToInsert < destLength)
	{
		memcpy(Dest, str2, bytesToInsert);
		return 0;
	}
	for (int i = 0; (i < bytesToInsert); ++i)
	{
		if (startIndex + i >= destLength)
		{
			return -1;
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
int byteconverter::BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, float ToAppend)
{
	auto BUFFER_TEST = byteconverter::FloatToBytes3(ToAppend);
	int errors = byteconverter::BytesAppend(Dest, destLength, startIndex, BUFFER_TEST, 4);
	free(BUFFER_TEST);
	return errors;
}
int byteconverter::BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, int ToAppend)
{
	auto BUFFER_TEST = byteconverter::IntToBytes(ToAppend);
	int errors = byteconverter::BytesAppend(Dest, destLength, startIndex, BUFFER_TEST, 4);
	free(BUFFER_TEST);
	return errors;
}
int byteconverter::BytesAppend(std::string& Dest, size_t destLength, int startIndex, std::string& str2, int bytesToInsert)
{
	for (int i = 0; (i < bytesToInsert); ++i)
	{
		if (startIndex + i >= destLength)
		{
			return -1;
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
int byteconverter::BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, unsigned char toInsert)
{

	if (startIndex + 1 >= destLength)
	{
		return -1;
	}

	Dest[startIndex + 1] = toInsert;

	return 0;
}

int byteconverter::BytesToInt(const unsigned char* buffer, int startIndex, bool BigEndian)
{

	char buffer2[4];
	for (int i = 0; i < 4; i++)
	{
		buffer2[i] = buffer[startIndex + i];
	}

	if (BigEndian)
		return (int)(buffer2[0] << 24) + (buffer2[1] << 16) + (buffer2[2] << 8) + buffer2[3];
	else
		return (int)(buffer2[3] << 24) + (buffer2[2] << 16) + (buffer2[1] << 8) + buffer2[0];

}
int byteconverter::BytesToIntString(std::string buffer, int startIndex)
{
	unsigned char* str = (unsigned char*)buffer.c_str();

	char* buffer2 = (char*)calloc(1, sizeof(int));
	if (buffer2 == NULL)
		return -1;
	for (int i = 0; i < 4; i++)
	{
		buffer2[i] = str[startIndex + i];
	}
	return (int)(buffer2[0] << 24) + (buffer2[1] << 16) + (buffer2[2] << 8) + buffer2[3];

}
unsigned char* byteconverter::IntToBytes(int num)
{
	unsigned char* bytes = static_cast<unsigned char*>(calloc(1, sizeof(int)));
	if (bytes == NULL)
		return NULL;
	for (int i = 0; i < sizeof(int); i++)
	{
		bytes[i] = (num >> (i * 8)) & 0xff;
	}
	return bytes;

}
std::shared_ptr<std::string> byteconverter::IntToBytes_String(int num)
{
	char b2[4];
	for (int i = 0; i < sizeof(int); i++)
	{
		b2[i] = (num >> (i * 8)) & 0xff;
	}
	auto shr = std::make_shared<std::string>(static_cast<char*>(b2));

	return shr;
}
/// <summary>
/// DEPRECATED, PLEASE USE FloatToBytes3 INSTEAD
/// </summary>
/// <param name="toConvert"></param>
/// <returns></returns>
unsigned char* byteconverter::FloatToBytes(float toConvert)
{
	unsigned char buffer[sizeof(float)];
	std::memcpy(buffer, &toConvert, sizeof(float));
	return buffer;

}


unsigned char* byteconverter::FloatToBytes3(float toConvert)
{

	unsigned char* buffer = (unsigned char*)calloc(1, sizeof(float));
	if (buffer != NULL)
	{
		memcpy(buffer, &toConvert, sizeof(float));

	}
	return buffer;


}
void byteconverter::FloatToBytes3(float toConvert, unsigned char* toFill)
{

	//unsigned char* buffer = (unsigned char*)calloc(1, sizeof(float));
	if (toFill != NULL)
	{
		memcpy(toFill, &toConvert, sizeof(float));

	}
}
std::shared_ptr<std::string> byteconverter::FloatToBytes3_Str(float toConvert)
{

	unsigned char* buffer = (unsigned char*)calloc(1, sizeof(float));
	if (buffer != NULL)
	{
		memcpy(buffer, &toConvert, sizeof(float));

	}
	auto b2 = std::make_shared<std::string>((char*)buffer);
	return b2;


}
unsigned char** byteconverter::FloatToBytes2(float toConvert)
{
	//unsigned char const * buffer = (unsigned char*)calloc(1, sizeof(float));
	float f = toConvert;
	unsigned char* buffer = reinterpret_cast<unsigned char*>(&f);
	return &buffer;

}
float byteconverter::BytesToFloat(const unsigned char* bytes, int startIndex, bool big_endian)
{

	if (big_endian)
		u.ul = (bytes[startIndex + 0] << 24) | (bytes[startIndex + 1] << 16) | (bytes[startIndex + 2] << 8) | bytes[startIndex + 3];
	else
		u.ul = (bytes[startIndex + 3] << 24) | (bytes[startIndex + 2] << 16) | (bytes[startIndex + 1] << 8) | bytes[startIndex + 0];

	return u.f;
}
std::vector<std::string> byteconverter::split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

/// <summary>
/// INCOMPLETE!!!!!
/// Searches for a substring in 'Input', then removes the matching characters if found. 
/// This is designed to be used cascadingly on a single string in order to extract specific contextes. 
/// Recommended for console commands.
/// </summary>
/// <param name="Input"> = Modifiable input string. The substring overlapping with 'ToScan' will be removed</param>
/// <param name="ToScan"> = The substring to search in input</param>
/// <returns> true if 'Input' contains 'ToScan', otherwise returns false </returns>
bool byteconverter::Scan(std::string Input, std::string ToScan)
{
	size_t len_a, len_b;
	len_a = Input.length();
	len_b = ToScan.length();

	// std::string
	return false;
}

