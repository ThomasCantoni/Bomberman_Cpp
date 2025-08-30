#include "ByteConverter.h"

#pragma region OLD
//int ByteConverter::BytesAppend(std::shared_ptr<std::shared_punsigned char> Dest, size_t destLength, int startIndex, unsigned char toInsert)
//{
//
//	if (startIndex + 1 >= destLength)
//	{
//		return -1;
//	}
//
//	Dest.get()[startIndex + 1] = toInsert;
//
//	return 0;
//}
//int ByteConverter::BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, unsigned char* str2, int bytesToInsert)
//{
//
//	if (startIndex == 0 && startIndex + bytesToInsert < destLength)
//	{
//		memcpy(Dest, str2, bytesToInsert);
//		return 0;
//	}
//	for (int i = 0; (i < bytesToInsert); ++i)
//	{
//		if (startIndex + i >= destLength)
//		{
//			return -1;
//		}
//		char toInsert = str2[i];
//		if (toInsert < 0x30)
//		{
//			//toInsert = 0x30;
//		}
//		Dest[startIndex + i] = toInsert;
//	}
//
//	return 0;
//}
//int ByteConverter::BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, float ToAppend)
//{
//	auto BUFFER_TEST = ByteConverter::FloatToBytes(ToAppend);
//	int errors = ByteConverter::BytesAppend(Dest, destLength, startIndex, BUFFER_TEST, 4);
//	free(BUFFER_TEST);
//	return errors;
//}
//int ByteConverter::BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, int ToAppend)
//{
//	auto BUFFER_TEST = ByteConverter::IntToBytes(ToAppend);
//	int errors = ByteConverter::BytesAppend(Dest, destLength, startIndex, BUFFER_TEST, 4);
//	free(BUFFER_TEST);
//	return errors;
//}
//unsigned char* ByteConverter::BytesCopy(unsigned char* Source, size_t destSize, int startIndex, int bytesToCopy)
//{
//	unsigned char* toReturn = static_cast<unsigned char*>(malloc(bytesToCopy));
//	if (toReturn == nullptr)
//	{
//		return NULL;
//	}
//	for (size_t i = 0; i < bytesToCopy; ++i)
//	{
//		toReturn[i] = Source[startIndex + i];
//	}
//
//	return toReturn;
//}

//int ByteConverter::BytesAppend(unsigned char* Dest, size_t destLength, int startIndex, unsigned char toInsert)
//{
//
//	if (startIndex + 1 >= destLength)
//	{
//		return -1;
//	}
//
//	Dest[startIndex + 1] = toInsert;
//
//	return 0;
//}
#pragma endregion

int ByteConverter::BytesCopy(std::shared_ptr<std::vector<unsigned char>> destination, std::shared_ptr<std::vector<unsigned char>> src, int startIndex, int bytesToCopy)
{
	if (startIndex > src->size())
	{
		return -1;
	}
	int diff = (startIndex + bytesToCopy) - destination->size();

	if ( diff > 0)
	{
		destination->resize(destination->size() + diff);
	}
	for (int i = 0; i < bytesToCopy; i++)
	{
		destination->data()[startIndex + i] = src->data()[i];
	}
	return 0;
}
int ByteConverter::BytesAppend(std::shared_ptr<std::vector<unsigned char>> Dest, int startIndex, std::vector<unsigned char>* toInsert, int bytesToInsert)
{

	if (startIndex + bytesToInsert > Dest->size())
	{
		Dest->resize(Dest->size() + bytesToInsert);
	}
	for (int i = 0; i < bytesToInsert; ++i)
	{
		Dest->data()[startIndex+i] = toInsert->at(i);

	}
	

	return 0;
}

int ByteConverter::BytesAppend(std::shared_ptr<std::vector<unsigned char>> Dest,int startIndex, std::shared_ptr<std::vector<unsigned char >>toInsert,int bytesToInsert)
{


	ByteConverter::BytesAppend(Dest, startIndex, toInsert.get(), bytesToInsert);

	return 0;
}
int ByteConverter::BytesAppend(std::shared_ptr<std::vector<unsigned char>> Dest, int startIndex, std::shared_ptr<std::vector<unsigned char >>toInsert)
{


	ByteConverter::BytesAppend(Dest, startIndex, toInsert.get(), toInsert->size());

	return 0;
}
int ByteConverter::BytesAppend(std::vector<unsigned char>* Dest, int startIndex, std::vector<unsigned char>* toInsert,int bytesToInser)
{

	if (startIndex + toInsert->size() > Dest->size())
	{
		unsigned int diff = Dest->size() - toInsert->size();
		Dest->resize(Dest->size() + diff);
	}
	for (int i = 0; i < toInsert->size(); ++i)
	{
		(*Dest)[startIndex+i] = (*toInsert)[i];
		
	}


	return 0;
}
int ByteConverter::BytesAppend(std::vector<unsigned char>* Dest, int startIndex, std::shared_ptr< std::vector<unsigned char>> toInsert, int bytesToInsert)
{
	ByteConverter::BytesAppend(Dest, startIndex, toInsert.get(), bytesToInsert);
	return 0;
}

int ByteConverter::BytesAppend(std::string& Dest, size_t destLength, int startIndex, std::string& str2, int bytesToInsert)
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
int ByteConverter::BytesAppend(std::shared_ptr<std::vector<unsigned char>> Dest, int startIndex, int toInsert) 
{

	if (startIndex + 4 > Dest->size())
	{
		Dest->resize(Dest->size() + 4);
	}
	
	auto toInsertC =  ByteConverter::IntToBytes(toInsert) ;
	for (int i = 0; i < 4; ++i)
	{
		Dest->data()[startIndex+i] = toInsertC.get()->at(i);

	}
	

	return 0;
}
int ByteConverter::BytesAppend(std::shared_ptr<std::vector<unsigned char>> Dest, int startIndex, float toInsert)
{

	if (startIndex + 4 > Dest->size())
	{
		Dest->resize(Dest->size() + 4);
	}
	
	auto  toInsertC = ByteConverter::FloatToBytes(toInsert);
	for (int i = 0; i < 4; ++i)
	{
		Dest->data()[startIndex + i] = toInsertC->at(i);

	}


	return 0;
}
int ByteConverter::BytesToInt(const unsigned char* buffer, int startIndex, bool BigEndian)
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
int ByteConverter::BytesToInt(const std::vector<unsigned char>* buffer, int startIndex, bool BigEndian)
{

	return ByteConverter::BytesToInt(buffer->data(), startIndex, BigEndian);
	
}
int ByteConverter::BytesToInt(const std::shared_ptr<std::vector<unsigned char>> buffer, int startIndex, bool BigEndian)
{
	return ByteConverter::BytesToInt(buffer->data(), startIndex, BigEndian);
	
}
std::shared_ptr<std::vector<unsigned char>> ByteConverter::IntToBytes(int num)
{
	auto bytes = std::make_shared<std::vector<unsigned char>>(4);
	for (int i = 0; i < sizeof(int); i++)
	{
		bytes->data()[i] = (num >> (i * 8)) & 0xff;
	}
	return bytes;

}
std::shared_ptr<std::string> ByteConverter::IntToBytes_String(int num)
{
	char b2[4];
	for (int i = 0; i < sizeof(int); i++)
	{
		b2[i] = (num >> (i * 8)) & 0xff;
	}
	auto shr = std::make_shared<std::string>(static_cast<char*>(b2));

	return shr;
}

void ByteConverter::FloatToBytes(float toConvert,std::shared_ptr<std::vector<unsigned char>> bufferToFill)
{
	std::memcpy(bufferToFill.get()->data(), &toConvert, sizeof(float));
	

}

std::shared_ptr<std::vector<unsigned char>> ByteConverter::FloatToBytes(float toConvert)
{
	std::shared_ptr<std::vector<unsigned char>> t = std::make_shared<std::vector<unsigned char>>(4);
	ByteConverter::FloatToBytes(toConvert, t);
	return t;
}

//unsigned char* ByteConverter::FloatToBytes(float toConvert)
//{
//
//	unsigned char* buffer = (unsigned char*)calloc(1, sizeof(float));
//	if (buffer != NULL)
//	{
//		memcpy(buffer, &toConvert, sizeof(float));
//
//	}
//	return buffer;
//
//
//}

std::shared_ptr<std::string> ByteConverter::FloatToBytes_Str(float toConvert)
{

	unsigned char* buffer = (unsigned char*)calloc(1, sizeof(float));
	if (buffer != NULL)
	{
		memcpy(buffer, &toConvert, sizeof(float));

	}
	auto b2 = std::make_shared<std::string>((char*)buffer);
	return b2;


}
//unsigned char** byteconverter::FloatToBytes2(float toConvert)
//{
//	//unsigned char const * buffer = (unsigned char*)calloc(1, sizeof(float));
//	float f = toConvert;
//	unsigned char* buffer = reinterpret_cast<unsigned char*>(&f);
//	return &buffer;
//
//}
float ByteConverter::BytesToFloat(const unsigned char* bytes, int startIndex, bool big_endian)
{

	if (big_endian)
		u.ul = (bytes[startIndex + 0] << 24) | (bytes[startIndex + 1] << 16) | (bytes[startIndex + 2] << 8) | bytes[startIndex + 3];
	else
		u.ul = (bytes[startIndex + 3] << 24) | (bytes[startIndex + 2] << 16) | (bytes[startIndex + 1] << 8) | bytes[startIndex + 0];

	return u.f;
}
float ByteConverter::BytesToFloat(const std::vector<unsigned char>* bytes, int startIndex, bool big_endian)
{

	if (big_endian)
		u.ul = (bytes->data()[startIndex + 0] << 24) | (bytes->data()[startIndex + 1] << 16) | (bytes->data()[startIndex + 2] << 8) | bytes->data()[startIndex + 3];
	else
		u.ul = (bytes->data()[startIndex + 3] << 24) | (bytes->data()[startIndex + 2] << 16) | (bytes->data()[startIndex + 1] << 8) | bytes->data()[startIndex + 0];

	return u.f;
}
std::vector<std::string> ByteConverter::split(const std::string& s, char delimiter)
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

std::vector<std::shared_ptr<unsigned char[]>> ByteConverter::split(const unsigned char* toSplit, int toSplitLength, char delimiter)
{
	std::vector<std::shared_ptr<unsigned char[]>> tokens = std::vector< std::shared_ptr<unsigned char[]>>();
	
	int startingPoint = 0;
	for (int i = 0; i < toSplitLength; ++i)
	{

		if (toSplit[i] == delimiter)
		{
			
			std::shared_ptr<unsigned char[]> newToken(new unsigned char[i-startingPoint]);
			
			for (int j = startingPoint; j < i; ++j)
			{
				newToken.get()[j-startingPoint] = toSplit[j];
				if((j-startingPoint)%4==0)
					std::cout  << "\n";
				std::cout <<std::hex<<(int) newToken.get()[j-startingPoint] <<std::dec<< "|";
			}
			startingPoint = i+1;
			std::cout << "\n\n";

			tokens.push_back(newToken);
		}
	}
	
	return tokens;
}


std::vector<std::vector<unsigned char>*>* ByteConverter::split(const std::vector<unsigned char>* toSplit, char delimiter)
{
	std::vector<std::vector<unsigned char>*>* tokens = new std::vector<std::vector<unsigned char>*>();

	int startingPoint = 0;
	for (int i = 0; i < toSplit->size(); ++i)
	{

		if (toSplit->at(i) == delimiter)
		{

			std::vector<unsigned char>* newToken = new std::vector<unsigned char>();
			newToken->reserve(i - startingPoint);
			for (int j = startingPoint; j < i; ++j)
			{
				
				newToken->push_back( toSplit->at(j));			//if ((j - startingPoint) % 4 == 0)
				//	std::cout << "\n";
				//std::cout << std::hex << (int)newToken.get()[j - startingPoint] << std::dec << "|";
			}
			//std::cout << "\n\n";

			startingPoint = i + 1;
			tokens->push_back(newToken);
		}
	}

	return tokens;
}
/// <summary>
/// INCOMPLETE!!!!!
/// Searches for a substring in 'Input', then removes the matching characters if found. 
/// This is designed to be used cascadingly on a single string in order to extract specific contextes. 
/// Recommended for console commands.
/// </summary>
/// <param name="Input"> = Modifiable input string. The substring matching with 'ToScan' will be removed</param>
/// <param name="ToScan"> = The substring to search in input</param>
/// <returns> true if 'Input' contains 'ToScan', otherwise returns false </returns>
bool ByteConverter::Scan(std::string Input, std::string ToScan)
{
	size_t len_a, len_b;
	len_a = Input.length();
	len_b = ToScan.length();

	// std::string
	return false;
}


/// <summary>
/// EXPERIMENTAL!!!!!
/// Given an input string and a range of that string to erase this function will return a new string without that specified range.
/// </summary>
/// <param name="Input">The string to modify</param>
/// <param name="InputLength">How long the Input string is</param>
/// <param name="StartIndex">The start position of the range to erase</param>
/// <param name="BytesToCutAmount">How many characters to erase</param>
/// <returns>Returns a string without the range specified</returns>
unsigned char* ByteConverter::Cut(unsigned char** Input,int InputLength, int StartIndex, int BytesToCutAmount)
{
	/*int length1 = StartIndex;
	int length2 = InputLength - (StartIndex + BytesToCutAmount);
	unsigned char* cutString1 = static_cast<unsigned char*>(malloc(length1));
	unsigned char* cutString2 = static_cast<unsigned char*>(malloc(length2));
	unsigned char* cutFinal	  = static_cast<unsigned char*>(malloc(length1 + length2));
	if(cutString1 != nullptr && cutString2 != nullptr && cutFinal != nullptr)
	{
	
		memcpy(cutString1, Input,length1);
		memcpy(cutString2, Input, length2);

		BytesAppend(cutFinal,length1+length2,  0,cutString1, length1);
		BytesAppend(cutFinal,length1+length2,  0,cutString2, length2);
		free(cutString1);
		free(cutString2);

		return cutFinal;
	}*/
	return nullptr;
}

std::shared_ptr<std::vector<unsigned char>> ByteConverter::EraseRegion(std::shared_ptr<std::vector<unsigned char>> Input, int InputLength, int StartIndex, int BytesToCutAmount)
{
	/*int length1 = StartIndex;
	int length2 = InputLength - (StartIndex + BytesToCutAmount);
	unsigned char* cutString1 = static_cast<unsigned char*>(malloc(length1));
	unsigned char* cutString2 = static_cast<unsigned char*>(malloc(length2));
	std::shared_ptr<unsigned char> cutFinal = std::make_shared<unsigned char>(length1 + length2);
	if (cutString1 != nullptr && cutString2 != nullptr && cutFinal != nullptr)
	{

		memcpy(cutString1, Input.get(), length1);
		memcpy(cutString2, Input.get(), length2);

		BytesAppend(cutFinal.get(), length1 + length2, 0, cutString1, length1);
		BytesAppend(cutFinal.get(), length1 + length2, 0, cutString2, length2);
		free(cutString1);
		free(cutString2);

		return cutFinal;
	}*/
	return nullptr;
}
