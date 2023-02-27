#pragma once
#include <string>
#include "CompressType.h"

using std::string;

class CompressedText
{
private:
	CompressType compressType;
	string text;
public:
	CompressedText();

	CompressedText(string text, CompressType compressType);

	CompressType getType();

	string getText();

	double calculateCompressionCoefficient(string rawText);
};
