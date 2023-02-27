#include "CompressedText.h"

CompressedText::CompressedText()
{
	this->compressType = CompressType::NONE;
	this->text = "";
}

CompressedText::CompressedText(string text, CompressType compressType)
{
	this->text = text;
	this->compressType = compressType;
}

CompressType CompressedText::getType()
{
	return compressType;
}

string CompressedText::getText()
{
	return text;
}