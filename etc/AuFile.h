#pragma once

#ifndef AUFILE_H
#define AUFILE_H

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

namespace Au_Core
{

#define AU_FILE_SEEK_BEGIN SEEK_SET //SEEK_SET
#define AU_FILE_SEEK_CURRENT SEEK_CUR //SEEK_CUR
#define AU_FILE_SEEK_END SEEK_END //SEEK_END

/////the mode options//////
//b: Open in binary mode
//t or t+: Open in text mode
//r or rb: Open file for reading.
//w or wb: Truncate to zero length or create file for writing.
//a or ab: Append; open or create file for writing at end-of-file.
//r+ or rb+ or r+b:Open file for update (reading and writing).
//w+ or wb+ or w+b:Truncate to zero length or create file for update.
//a+ or ab+ or a+b:Append; open or create file for update, writing at end-of-file. 

#define AU_DATA_TRUNK_1K 1024
#define AU_DATA_TRUNK_2K 2*1024
#define AU_DATA_TRUNK_4K 4*1024
#define AU_DATA_TRUNK_8K 8*1024
#define AU_DATA_TRUNK_16K 16*1024
#define AU_DATA_TRUNK_32K 32*1024
#define AU_DATA_TRUNK_64K 64*1024
#define AU_DATA_TRUNK_128K 128*1024
#define AU_DATA_TRUNK_256K 256*1024
#define AU_DATA_TRUNK_512K 512*1024
#define AU_DATA_TRUNK_1M 1*1024*1024
#define AU_DATA_TRUNK_2M 2*1024*1024
#define AU_DATA_TRUNK_4M 4*1024*1024
#define AU_DATA_TRUNK_8M 8*1024*1024
#define AU_DATA_TRUNK_16M 16*1024*1024
#define AU_DATA_TRUNK_32M 32*1024*1024
#define AU_DATA_TRUNK_64M 64*1024*1024
#define AU_DATA_TRUNK_128M 128*1024*1024
#define AU_DATA_TRUNK_256M 256*1024*1024

class AuFile
{
public:
	bool Open(const char *name, const char * mode="wb");
	bool Close();

	bool Write(void *buffer, size_t item_size_bytes, size_t count);
	bool Write(char *buffer, size_t count);
	bool Write(unsigned char *buffer, size_t count);
	bool Write(const char *buffer);
	bool Write(bool *buffer, size_t count);
	bool Write(int *buffer, size_t count);
	bool Write(size_t *buffer, size_t count);
	bool Write(long *buffer, size_t count);
	bool Write(float *buffer, size_t count);
	bool Write(double *buffer, size_t count);

	bool Read(void *buffer, size_t item_size_bytes, size_t count);
	bool Read(char *buffer, size_t count);
	bool Read(unsigned char *buffer, size_t count);
	bool Read(bool *buffer, size_t count);
	bool Read(int *buffer, size_t count);
	bool Read(size_t *buffer, size_t count);
	bool Read(long *buffer, size_t count);
	bool Read(float *buffer, size_t count);
	bool Read(double *buffer, size_t count);

	bool Flush();

	bool Seek(long offset=0, int origin=AU_FILE_SEEK_BEGIN);

	bool IsEndOfFile();

	FILE * GetHandle();
	bool IsValid();

	void SetDataTrunkSize(size_t data_trunk_size=AU_DATA_TRUNK_4M);

	AuFile(void);
	~AuFile(void);
protected:
	FILE *fp;
	size_t data_trunk_size;
};

#define MAX_BUFSIZE 250 

class AuLog : public AuFile {

public:
	void writeLog(char *fmt, ...);
	bool getTime(char *out);
	bool writeFile(const char *str, bool bLog);

	AuLog(void);
	~AuLog(void);
};

}
using namespace Au_Core;

#endif //AUFILE_H
