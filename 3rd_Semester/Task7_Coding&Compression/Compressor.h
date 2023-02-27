#pragma once
#include <string>

#include "CompressType.h"
#include "CompressedText.h"

using std::string;

class Compressor
{
private:
	CompressType compressType;

	string RLE_Compress(string text);

	string RLE_Decompress(string text);



public:
	Compressor();

	Compressor(CompressType compressType);

	CompressType getCompressType();

	void setCompressType(CompressType compressType);

	CompressedText* Compress(string text);

	string Decompress(CompressedText compressedText);	
};