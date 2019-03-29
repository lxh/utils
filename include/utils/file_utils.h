#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_
//#include "utils/md5.h"
#include <dirent.h>
#include <time.h>  
#include <memory>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#define SMALL_READ_DATA_SIZE  512
#define READ_DATA_SIZE  4096000 //4M
#define MD5_SIZE        32
#define MD5_STR_LEN     (MD5_SIZE * 2)
//using namespace XMD5;
class FileUtils {
public:
	static long GetFileLastModifyTime(const char *file_path) {
		long t = -1;
#if 0
		FILE * fp;
		int fd;
		fp = fopen(file_path,"r");
		if(fp) {
			struct stat buf;
			fstat(fd, &buf);
			//int size = buf.st_size; //get file size (byte)
			t = buf.st_mtime; 
			fclose(fp);
		}
#else
		struct stat buf;
		int result;
		result = stat( file_path, &buf ); 
		if(result == 0) {
			t = buf.st_mtime;
		}
#endif
		return t;
	}
	/*static bool ComputeFileMd5_0(const char *file_path, string & md5_ret) {
		char md5_str[64] = {0};
		int i;
		int fd;
		int ret;
		unsigned char * data = new unsigned char[SMALL_READ_DATA_SIZE];
		std::shared_ptr<unsigned char> ap(data);
		unsigned char md5_value[MD5_SIZE];
		MD5_CTX md5;

		fd = open(file_path, O_RDONLY);
		if (-1 == fd) {
			perror("open");
			return false;
		}
		// init md5
		MD5Init(&md5);
		while (1) {
			ret = read(fd, data, SMALL_READ_DATA_SIZE);
			if (-1 == ret) {
				perror("read");
				return false;
			}
			MD5Update(&md5, data, ret);
			if (0 == ret || ret < SMALL_READ_DATA_SIZE) {
				break;
			}
		}
		close(fd);
		MD5Final(&md5, md5_value);
		for(i = 0; i < MD5_SIZE; i++) { // convert md5 value to md5 string
			snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
		}

		md5_str[MD5_SIZE] = 0;
		md5_ret = md5_str;
		return true;
	}
	static bool ComputeFileMd5(const char *file_path, string & md5_ret) {
		char md5_str[64] = {0};
		int i;
		int fd;
		int ret;
		unsigned char * data = new unsigned char[READ_DATA_SIZE];
		std::shared_ptr<unsigned char> ap(data);
		unsigned char md5_value[MD5_SIZE];
		MD5_CTX md5;

		fd = open(file_path, O_RDONLY);
		if (-1 == fd) {
			perror("open");
			return false;
		}
		// init md5
		MD5Init(&md5);
		while (1) {
			ret = read(fd, data, READ_DATA_SIZE);
			if (-1 == ret) {
				perror("read");
				return false;
			}
			MD5Update(&md5, data, ret);
			if (0 == ret || ret < READ_DATA_SIZE) {
				break;
			}
		}
		close(fd);
		MD5Final(&md5, md5_value);
		for(i = 0; i < MD5_SIZE; i++) { // convert md5 value to md5 string
			snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
		}

		md5_str[MD5_SIZE] = 0;
		md5_ret = md5_str;
		return true;
	}*/
    static bool GetDirFiles(const char * dir, vector<string> & file_names) {
        DIR * directory_pointer;
        struct dirent * entry;
        if((directory_pointer = opendir(dir)) == NULL) {
            return false;
        }
        while((entry = readdir(directory_pointer)) != NULL) {
            if(entry->d_name[0] == '.') continue;
            file_names.push_back(entry->d_name);
        }
        return true;
    }
    static bool ReadConfFileContext(const char * file, string & file_context, const char comment_char = '#') {
        ifstream in(file);
        if(!in) {
            return false;
        }
        std::string line;
        while(getline(in, line)) {
            if(line == "") continue;
            if(line[0] == comment_char) continue;
            file_context += line;
        }
        in.close();
        return true;
    }
    static bool ReadConfFile2Map(const char * file, vector<string> & res, const char comment_char = '#') {
        ifstream in(file);
        if(!in) {
            return false;
        }
        std::string line;
        while(getline(in, line)) {
            if(line == "") continue;
            if(line[0] == comment_char) continue;
            res.push_back(line);
        }
        in.close();
        return true;
    }

};
#endif
