#define BIT(n) (1 << (n))
#define BIT_SET(v, mask) (v |= (mask))
#define BIT_CLEAR(v, mask) (v &= ~(mask))
#define BIT_FILP(v, mask) (v ^= (mask))
#define IS_SET_ANY(v, mask) (v & (mask))

#define BIT_MASK(len) (BIT(len) - 1)
#define BF_MASK(start, len) (BIT_MASK(len) << (start))
#define BF_PREP(x, start, len) (((x)&BIT_MASK(len)) << (start))

#define BF_GET(y, start, len) ( ((y) >> (start)) & BIT_MASK(len) )
#define BF_SET(y, x, start, len) (BF_PREP((x), (start), (len)) | ((y) & ~BF_MASK((start), (len))))
