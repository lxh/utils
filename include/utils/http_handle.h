#ifndef _HTTP_HANDLE_H_
#define _HTTP_HANDLE_H_
#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include "myutils/time_utils.h"

using namespace std;

class HttpHandle {
public:
	static size_t WriteFunction(void *input, size_t size, size_t count, void *avg) {
		size_t len = size * count;  
		string *str = (string *)(avg); 
		//printf("%d;%d;%s\n", size, count, (char*)input);
		str->append((char*)(input), len);
		return len;
	}
	//static bool GetUrl(const char * url, const int in_buffer_len, char *&  out_buffer, int & out_buffer_len) {
	static bool GetUrl(const char * url, string & buffer_res) {
		/*
		long t0 = TimeUtils::GetCurrentTimeUS();
		bool ret = GetUrl2(url, buffer_res);
		long t1 = TimeUtils::GetCurrentTimeUS();
		printf("time: %ld; url: %s\n", t1 - t0, url);
		return ret;
	}
	static bool GetUrl2(const char * url, string & buffer_res) {
	*/
		CURL *curl;
		CURLcode res;
		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "Accept: Agent-lxh");
		curl = curl_easy_init();    // 初始化
		if (curl) {
			//curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");// 代理
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);// 改协议头
			curl_easy_setopt(curl, CURLOPT_URL, url);
			//curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); //将返回的http头输出到fp指向的文件
			//curl_easy_setopt(curl, CURLOPT_HEADERDATA, fp); //将返回的html主体数据输出到fp指向的文件
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteFunction); // !数据回调函数
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer_res); //将返回的http头输出到fp指向的文件
			res = curl_easy_perform(curl);   // 执行
			if (res != CURLE_OK) { 
				printf("GetUrl:%s failed\n", url);
			}
			curl_slist_free_all(headers);
			curl_easy_cleanup(curl);
			return true;
		} else {
			return false;
		}
		return true;
	}

/*
	bool postUrl(char *filename)
	{
		CURL *curl;
		CURLcode res;
		FILE *fp;
		if ((fp = fopen(filename, "w")) == NULL)
			return false;
		curl = curl_easy_init();
		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt"); // 指定cookie文件
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "&logintype=uid&u=xieyan&psw=xxx86");    // 指定post内容
			//curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");
			curl_easy_setopt(curl, CURLOPT_URL, " http://mail.sina.com.cn/cgi-bin/login.cgi ");   // 指定url
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
		}
		fclose(fp);
		return true;
	}
	*/



};

#endif
