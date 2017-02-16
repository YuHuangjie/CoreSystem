#include "../inc/AuFile.h"
#include <math.h>
#include <string.h>

namespace Au_Core
{

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

AuFile::AuFile(void)
{
	fp=NULL;
	data_trunk_size=AU_DATA_TRUNK_4M;
}

AuFile::~AuFile(void)
{
	if(fp)
		fclose(fp);
}

bool AuFile::Open(const char *name, const char *mode)
{
	if((fp=fopen(name,mode))==NULL)
		return false;
	return true;
}

bool AuFile::Close()
{
	if(fp)
	{
		if(fclose(fp)==0)
		{
			fp=NULL;
			return true;
		}
		else
			return false;
		fp=NULL;
	}

	return true;
}

bool AuFile::Flush()
{
	if(fflush(fp)==0)
		return true;
	else
		return false;
}

bool AuFile::Seek(long offset, int origin)
{
	if(fp==NULL) return false;
	if(fseek(fp,offset,origin)==0)
		return true;
	return false;
}

bool AuFile::IsEndOfFile()
{
	if(feof(fp)==0)
		return false;
	else
		return true;
}

FILE * AuFile::GetHandle()
{
	return fp;
}

bool AuFile::IsValid()
{
	return fp!=NULL;
}

void AuFile::SetDataTrunkSize(size_t data_trunk_size)
{
	this->data_trunk_size=data_trunk_size;
}

bool AuFile::Write(void *buffer, size_t itemize_bytes, size_t count)
{
	if(fp==NULL) return false;

	size_t count_per_time=(size_t)ceil(double(min(itemize_bytes*count,data_trunk_size))/double(itemize_bytes));
	size_t bytes_written=0;

	char *p=(char *)buffer;

	while(bytes_written<itemize_bytes*count)
	{
		size_t count_written=min(count_per_time,(itemize_bytes*count-bytes_written)/itemize_bytes);
		size_t count_actual_written=fwrite(p,itemize_bytes,count_written,fp);
		if(count_actual_written!=count_written)
			return false;

		p+=itemize_bytes*count_written;
		bytes_written+=itemize_bytes*count_written;
	}

	if(bytes_written!=itemize_bytes*count)
		return false;

	return true;
}

bool AuFile::Write(char *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Write(buffer,sizeof(char),count)!=true)
		return false;
	return true;
}

bool AuFile::Write(unsigned char *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Write(buffer,sizeof(unsigned char),count)!=true)
		return false;
	return true;
}

bool AuFile::Write(const char *buffer)
{
	if(fp==NULL) return false;
	if(Write((void *)buffer,sizeof(char),strlen(buffer))!=true)
		return false;
	return true;
}

bool AuFile::Write(bool *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Write(buffer,sizeof(bool),count)!=true)
		return false;
	return true;
}

bool AuFile::Write(int *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Write(buffer,sizeof(int),count)!=true)
		return false;
	return true;
}

bool AuFile::Write(size_t *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Write(buffer,sizeof(size_t),count)!=true)
		return false;
	return true;
}

bool AuFile::Write(long *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Write(buffer,sizeof(long),count)!=true)
		return false;
	return true;
}

bool AuFile::Write(float *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Write(buffer,sizeof(float),count)!=true)
		return false;
	return true;
}

bool AuFile::Write(double *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Write(buffer,sizeof(double),count)!=true)
		return false;
	return true;
}

bool AuFile::Read(void *buffer, size_t itemize_bytes, size_t count)
{
	if(fp==NULL) return false;

	size_t count_per_time=(size_t)ceil(double(min(itemize_bytes*count,data_trunk_size))/double(itemize_bytes));
	size_t bytes_read=0;

	char *p=(char*)buffer;

	while(bytes_read<itemize_bytes*count)
	{
		size_t count_read=min(count_per_time,(itemize_bytes*count-bytes_read)/itemize_bytes);

		size_t count_actual_read=fread(p,itemize_bytes,count_read,fp);
		if(count_actual_read!=count_read)
			return false;

		p+=itemize_bytes*count_read;
		bytes_read+=itemize_bytes*count_read;
	}

	if(bytes_read!=itemize_bytes*count)
		return false;

	return true;
}

bool AuFile::Read(char *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Read(buffer,sizeof(char),count)!=true)
		return false;
	return true;
}

bool AuFile::Read(unsigned char *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Read(buffer,sizeof(unsigned char),count)!=true)
		return false;
	return true;
}

bool AuFile::Read(bool *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Read(buffer,sizeof(bool),count)!=true)
		return false;
	return true;
}

bool AuFile::Read(int *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Read(buffer,sizeof(int),count)!=true)
		return false;
	return true;
}

bool AuFile::Read(size_t *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Read(buffer,sizeof(size_t),count)!=true)
		return false;
	return true;
}

bool AuFile::Read(long *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Read(buffer,sizeof(long),count)!=true)
		return false;
	return true;
}

bool AuFile::Read(float *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Read(buffer,sizeof(float),count)!=true)
		return false;
	return true;
}

bool AuFile::Read(double *buffer, size_t count)
{
	if(fp==NULL) return false;
	if(Read(buffer,sizeof(double),count)!=true)
		return false;
	return true;
}

AuLog::AuLog(void)
{
	fp=NULL;
	data_trunk_size=AU_DATA_TRUNK_4M;
}

AuLog::~AuLog(void)
{
	if(fp)
		fclose(fp);
}

/* 
    功能：     获取当前系统时间 
    out:       保存返回的系统时间
*/  
bool AuLog::getTime(char *out)             // 获取当前系统时间  
{  
    time_t t;  
    struct tm *tp;  
  
    if(out == NULL)  
        return false;  
  
    t = time(NULL);  
    tp = localtime(&t);  
    sprintf(out, "%02d/%02d/%02d_%02d:%02d:%02d", tp->tm_year+1900, tp->tm_mon+1, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);  
    
    return true;  
}  

void AuLog::writeLog(char *fmt, ...) {
	va_list args;  
    static char logStr[MAX_BUFSIZE] = {0};  // store log string  
  
    va_start(args, fmt);   
    vsprintf(logStr, fmt, args);            // format log infor to logStr[]  
    va_end(args);
      
    writeFile(logStr, true);        // write log string to log file  
}

/* 
    功能：     将str写入到文件 
    str:        待写入的字符串 
    bLog:       1-是日志文件，0-不是日志文件 
    说明：     如果是日志文件，将会在str前加上当前时间(格式如：2011-04-12 12:10:20) 
*/ 
bool AuLog::writeFile(const char *str, bool bLog) {
	char curTime[MAX_BUFSIZE] = {0};  
    int ret = -1; 
    if(bLog) // 获取当前系统时间  
    {  
        getTime(curTime);  
        ret = fprintf(fp, "[%s] %s\n", curTime, str);  
    }  
    else  
        ret = fprintf(fp, "%s\n", str);  
  
    if(ret >= 0)  
    {  
        fflush(fp);  
        return true;               // 写文件成功  
    }  
    else  
        return false;  
}

}