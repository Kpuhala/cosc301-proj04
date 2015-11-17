typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;
typedef struct _lock_t{
       uint locked;
}lock_t;
typedef struct _semaphore_t {
    uint val;
    uint locked;
} semaphore_t;
