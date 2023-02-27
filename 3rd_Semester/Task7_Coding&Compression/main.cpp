#include <iostream>
#include <locale.h>

#include "CompressType.h"
#include "CompressedText.h"
#include "Compressor.h"

using namespace std;


int main()
{
	setlocale(LC_ALL, "ru");


	Compressor* compressor = new Compressor();
	CompressedText* compressedText = new CompressedText();
	string toCompress = "";
	
	//RLE test
	compressor->setCompressType(RLE);

	//test 1 - A string with repeating and unique symbols
	toCompress = "abcccdeeeeeffggh";
	compressedText = compressor->Compress(toCompress);
	cout << toCompress << '\n';
	cout << compressedText->getText() << '\n';
	cout << compressor->Decompress(*compressedText) << '\n';


	return 0;
}