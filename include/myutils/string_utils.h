#ifndef _STR_UTILS_H_
#define _STR_UTILS_H_
#include <math.h>
#include <string>
#include <vector>
#include <string.h>

class StringUtils {
public:
	static inline std::string Trim(const std::string& str) {
		if (str.empty()) return std::string();
		size_t start = 0;
		size_t end = str.size() - 1;
		while (isspace(str[start]) != 0 && start <= end) {
			++start;
		}
		while (isspace(str[end]) != 0 && start <= end) {
			--end;
		}
		if (start <= end) {
			return str.substr(start, end - start + 1); 
		}
		return std::string();
	}

	static inline void Tokenize(const std::string & src, std::vector<std::string> &v, std::string tok = " ", bool trim = false, std::string null_subst = "")
	{
		if( src.empty()) {
			return;
		}
		if(tok.empty() ) {
			v.push_back(src);
			return;
		}

		size_t pre_index = 0, index = 0, len = 0;
		while((index = src.find_first_of(tok, pre_index)) != std::string::npos) {
			if( (len = index-pre_index)!=0 ) {
				v.push_back(src.substr(pre_index, len));
			} else if(trim==false) {
				v.push_back(null_subst);
			}
			pre_index = index+1;
		}
		std::string endstr = src.substr(pre_index);
		if(trim == false) {
			v.push_back(endstr.empty() ? null_subst : endstr);
		} else if(!endstr.empty()) {
			v.push_back(endstr);
		}
	}
	static inline void TokenizeStr(const std::string & s, std::vector<std::string> & v, const std::string & c)
	{
		size_t pos1, pos2;
		pos2 = s.find(c);
		pos1 = 0;
		while(std::string::npos != pos2) {
			v.push_back(s.substr(pos1, pos2-pos1));

			pos1 = pos2 + c.size();
			pos2 = s.find(c, pos1);
		}
		if(pos1 != s.size()) {
			v.push_back(s.substr(pos1));
		}
	}
	static void JoinMultiSpace(std::string & s)
	{
		int iSize = s.size();
		int iLoop;
		std::string strRet = ""; 
		bool bSpace = false;
		for(iLoop = 0; iLoop < iSize; iLoop++) {
			if(s[iLoop] == ' ') {
				if(bSpace) {
					continue;
				}   
				strRet += s[iLoop];
				bSpace = true;
			} else {
				bSpace = false;
				strRet += s[iLoop];
			}   
		}   
		s = strRet;
	}
    static int SplitStr2KVec(const std::string & s, std::string & key, std::vector<std::string> & data)
    {
        std::vector<std::string> sv;
        StringUtils::Tokenize(s, sv, "\t");
        if(sv.size() == 2) {
            key = sv[0];
            StringUtils::Tokenize(sv[1], data);
            return data.size();
        }
        return 0;
    }

    static int SplitStr2KVec(const std::string & s, std::string & key, std::vector<float> & data)
    {
        std::vector<std::string> str_data;
        int dim = StringUtils::SplitStr2KVec(s, key, str_data);
        if(dim > 0) {
            for(int i = 0; i < dim; i++) {
                data.push_back(atof(str_data[i].c_str()));
            }
        }
        return dim;
    }
    static bool VectorNormalization(std::vector<float> & v)
    {
        std::vector<float>::iterator it = v.begin();
        float inner_product = 0.0f;
        for(; it != v.end(); ++it) {
            inner_product += (*it) * (*it);
        }
        float divisor = sqrt(inner_product);
        if(divisor <= 0.0f) {
            return false;
        }
        for(size_t i = 0; i < v.size(); ++i) {
            v[i] = v[i] / divisor;
        }
        return true;
    }
    static bool VectorNormalization(float * v, const int dim)
    {
        float inner_product = 0.0f;
        for(int i = 0; i < dim; ++i) {
            inner_product += v[i] * v[i];
        }
        float divisor = sqrt(inner_product);
        if(divisor <= 0.0f) {
            return false;
        }
        for(int i = 0; i < dim; ++i) {
            v[i] = v[i] / divisor;
        }
        return true;
    }
};

#endif
