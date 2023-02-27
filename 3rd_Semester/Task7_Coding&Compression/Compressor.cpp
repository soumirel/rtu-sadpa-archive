#include "Compressor.h"

using std::to_string;

Compressor::Compressor()
{
	this->compressType = CompressType::NONE;
}

Compressor::Compressor(CompressType compressType)
{
	this->compressType = compressType;
}

CompressType Compressor::getCompressType()
{
	return compressType;
}

void Compressor::setCompressType(CompressType compressType)
{
	this->compressType = compressType;
}

CompressedText* Compressor::Compress(string text)
{
	string AcompressedString;

	switch (compressType)
	{
	case CompressType::RLE:
		AcompressedString = RLE_Compress(text);
		break;

	/*case CompressType::LZ77:
		compressedString = LZ77_Compress(text);
		break;
		
	case CompressType::LZ78:
		compressedString = LZ78_Compress(text);
		break;

	case CompressType::ShannonFano:
		compressedString = ShannonFano_Compress(text);
		break;

	case CompressType::Huffman:
		compressedString = Huffman_Compress(text);
		break;*/
	
	default:
		AcompressedString = text;
	}
	CompressedText* compressedText =  new CompressedText(AcompressedString, this->compressType);
	return compressedText;
}

string Compressor::Decompress(CompressedText compressedText)
{
	string decompressedString;

	switch (compressedText.getType())
	{
	case CompressType::RLE:
		decompressedString = RLE_Decompress(compressedText.getText());
		break;

	/*case CompressType::LZ77:
		decompressedString = LZ77_Decompress(compressedText.getText());
		break;

	case CompressType::LZ78:
		decompressedString = LZ78_Decompress(compressedText.getText());
		break;

	case CompressType::ShannonFano:
		decompressedString = ShannonFano_Decompress(compressedText.getText());
		break;

	case CompressType::Huffman:
		decompressedString = Huffman_Decompress(compressedText.getText());
		break;*/

	default:
		break;
	}
	return decompressedString;
}

string Compressor::RLE_Compress(string text)
{
	string compressedString = "";
	char count = 0;
	string prevSeq = "";
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == text[i + 1])
		{
			if (count < 0)
			{
				compressedString += count + prevSeq;
				count = 0;
				prevSeq = "";
			}
			prevSeq += text[i];
			count++;
		}
		else
		{
			if (count > 0)
			{
				compressedString += count + prevSeq;
				count = 0;
				prevSeq = "";
			}
			prevSeq += text[i];
			count--;
		}
	}

	return compressedString;
}

string Compressor::RLE_Decompress(string text)
{
	string decompressedString;
	for (char i = 0; i < text.length(); i+= abs(text[i]))
	{
		int currentSeqLength = abs(text[i]);
		for (int j = i + 1; j < currentSeqLength + 1; j++)
		{
			decompressedString += text[j];
		}
	}
	return decompressedString;
}



