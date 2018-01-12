#define BIT(n) (1 << (n))
#define BIT_SET(v,mask) (v |= (mask))
#define BIT_CLEAR(v,mask) (v &= ~(mask))
#define BIT_FLIP(v,mask) (v ^= (mask))
#define IS_SET_ANY(v,mask) (v & (mask))

#define BF_GET(y,start,len) ((y) >> (start) & BIT_MASK(len))
#define BF_SET(y,x,start,len) (y & (~BIT_MASK(len) << (start)) | x << (start) )
