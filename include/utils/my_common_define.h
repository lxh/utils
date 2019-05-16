#ifndef _MY_COMMON_DEFINE_H_
#define _MY_COMMON_DEFINE_H_
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>

//20190516新版本定义 
//注: 
//  后设配置(Lu,Iu,Mapu,...)
//  64位系统
//  ptr为主，可以直接放在最后
//->分析方法:
//1. ptr在最后,说明是shared_ptr,先去除
//2. 前面找出结构主体(map,set,...)
//3. 分析数字中间部分, 数字大于0, 跳转到1
//Mapu -> unordered_map
//Map  -> map
//Vec  -> vector
//Pair -> pair
//Setu -> unordered_set
//Set  -> set
//S    -> string
//F    -> float
//Lu   -> unsigned long
//Iu   -> unsigned int
//L    -> long
//I    -> int
//Ptr  -> shared_ptr ->后缀
//D    -> double
#if 1
typedef std::unordered_map<std::string, float> MapuSF;
typedef std::unordered_set<std::string> SetuS;
typedef std::pair<std::string, float> PairSF;
typedef std::vector<PairSF> Vec0PairSF0;
typedef std::unordered_map<std::string, Vec0PairSF0> MapuS1Vec0PairSF01;
typedef std::unordered_map<uint64_t, float> MapuLuF;
typedef std::shared_ptr<MapuLuF> MapuLuFPtr;
typedef std::shared_ptr<MapuSF> MapuSFPtr;
typedef std::unordered_map<std::string, MapuSFPtr> MapuS0MapuSFPtr0;
typedef std::shared_ptr<MapuS0MapuSFPtr0>  MapuS0MapuSFPtr0Ptr;
typedef std::unordered_map<std::string, MapuSF>  MapuS0MapuSF0;
typedef std::shared_ptr<MapuS0MapuSF0> MapuS0MapuSF0Ptr;
typedef std::unordered_map<std::string, double> MapuSD;
typedef std::unordered_map<std::string, MapuSD> MapuS0MapuSD0;
typedef std::unordered_map<std::string, std::string> MapuSS;
typedef std::unordered_map<std::string, MapuSS> MapuS0MapuSS0;
typedef std::vector<double> VecD;
typedef std::unordered_map<std::string, VecD> MapuS0VecD0;
typedef std::unordered_map<std::string, MapuS0VecD0> MapuS1MapuS0VecD01;
typedef std::vector<std::shared_ptr<std::unordered_map<std::string, float>>> Vec0MapuSFPtr0;
#else
typedef std::unordered_map<std::string, float> MapSF;
typedef std::unordered_set<std::string> HashSetS;
typedef std::unordered_map<std::string, std::vector<std::pair<std::string, float> > > MapLitSSF;
typedef std::unordered_map<uint64_t, float> HashMapLF;
typedef std::shared_ptr<HashMapLF> HashMapLFPtr;
typedef std::shared_ptr<MapSF> MapSFPtr;
typedef std::unordered_map<std::string, MapSFPtr> MapSPmsf; //MapuS0MapuSFPtr0
typedef std::shared_ptr<MapSPmsf>  MapSPmsfPtr;
typedef std::unordered_map<std::string, MapSF>  MapSMsf;
typedef std::shared_ptr<MapSMsf> MapSMsfPtr;
typedef std::unordered_map<uint64_t, float> MapLF;
typedef std::shared_ptr<MapLF> MapLFPtr;
typedef std::unordered_map<std::string, double> MapSD;
typedef std::unordered_map<std::string, MapSD> MapSMsd;
typedef std::unordered_map<std::string, std::string> MapSS;
typedef std::unordered_map<std::string, MapSS> MapSMss;
typedef std::unordered_map<std::string, std::vector<double> > MapSVd;
typedef std::unordered_map<std::string, MapSVd> MapSMsvd;
#endif

#endif
