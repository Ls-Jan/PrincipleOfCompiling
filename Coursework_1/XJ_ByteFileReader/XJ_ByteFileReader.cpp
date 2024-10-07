#include"XJ_ByteFileReader.h"
#include<memory.h>

XJ_ByteFileReader::XJ_ByteFileReader(unsigned int bufSize) {
	this->bufSize = bufSize;
	for (auto i = 0; i < 2; ++i) {
		this->buffer[i] = new char[bufSize];
	}
	this->currBuffer = this->buffer[0];
}

XJ_ByteFileReader::~XJ_ByteFileReader() {
	if (this->file)
		fclose(this->file);
	for (auto i = 0; i < 2; ++i) {
		delete this->buffer[i];
	}
}

bool XJ_ByteFileReader::Opt_LoadFile(const char* fileName) {
	if (this->file)
		fclose(this->file);
	this->bufCount = -1;
	this->currBuffer = this->buffer[1];
	this->bufLength = this->bufSize-1;
	this->bufPst = this->bufSize;
	auto err = fopen_s(&this->file, fileName, "rb");
	if (err != 0) {
		this->bufLength = 0;
		this->bufPst = 0;
	}
	return err == 0;
}

char XJ_ByteFileReader::Get_Byte() {
	return this->currBuffer[this->bufPst];
}

bool XJ_ByteFileReader::Opt_Next() {
	if (this->bufPst >= this->bufLength) {
		if (this->bufLength+1!= this->bufSize)
			return false;
		this->bufCount += 1;
		this->currBuffer = this->buffer[this->bufCount & 1];
		this->bufLength = fread_s(this->currBuffer, this->bufSize, 1, this->bufSize, this->file)-1;
		if (this->bufLength == -1) {
			this->bufCount -= 1;
			this->currBuffer = this->buffer[this->bufCount & 1];
			return false;
		}
		this->bufPst = 0;
	}
	else {
		++this->bufPst;
	}
	return true;
}

unsigned int XJ_ByteFileReader::Get_Pos() {
	return this->bufPst + this->bufCount*this->bufSize;
}


