#ifndef _HASH64_H_
#define _HASH64_H_
#include <stdint.h>
#include <stddef.h>

#define hash64 hash64Default
class CHash {
public:
    static uint64_t hash64Default(const char *data, const int length, const int seed) {
        uint64_t m = 0xc6a4a7935bd1e995L;
        int r = 47;

        uint64_t h = (seed&0xffffffffl)^(length*m);

        int length8 = length/8;

        for (int i=0; i<length8; i++) {
            int i8 = i*8;
            uint64_t k =  ((uint64_t)data[i8+0]&0xff)      +(((uint64_t)data[i8+1]&0xff)<<8)
                +(((uint64_t)data[i8+2]&0xff)<<16) +(((uint64_t)data[i8+3]&0xff)<<24)
                +(((uint64_t)data[i8+4]&0xff)<<32) +(((uint64_t)data[i8+5]&0xff)<<40)
                +(((uint64_t)data[i8+6]&0xff)<<48) +(((uint64_t)data[i8+7]&0xff)<<56);

            k *= m;
            k ^= k >> r;
            k *= m;

            h ^= k;
            h *= m;
        }

        switch (length%8) {
            case 7: h ^= (uint64_t)(data[(length&~7)+6]&0xff) << 48;
            case 6: h ^= (uint64_t)(data[(length&~7)+5]&0xff) << 40;
            case 5: h ^= (uint64_t)(data[(length&~7)+4]&0xff) << 32;
            case 4: h ^= (uint64_t)(data[(length&~7)+3]&0xff) << 24;
            case 3: h ^= (uint64_t)(data[(length&~7)+2]&0xff) << 16;
            case 2: h ^= (uint64_t)(data[(length&~7)+1]&0xff) << 8;
            case 1: h ^= (uint64_t)(data[length&~7]&0xff);
                    h *= m;
        }

        h ^= h >> r;
        h *= m;
        h ^= h >> r;

        return h;
    }
    static uint64_t hash64Default(const char *data, const int length) {
        return hash64Default(data, length, 0xe17a1465);
    }
};

#endif
