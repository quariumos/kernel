#ifndef STREAM_H
#define STREAM_H

#include <types.h>

typedef void (*stream_subscriber_t)(u8);
void NOSUB(u8 data)
{
    return;
}

// This structure reprsents an IN stream
typedef struct
{
    // Functions to be called upon a stream change, maximum 3
    stream_subscriber_t **s;
    // For writing to the stream
    void (*write)(u8);
} stream_t;

#define STREAM(name, subscribers)                        \
    static stream_t name;                                \
    static void f_##name(u8 data)                        \
    {                                                    \
    u32 i;                                               \
        while ((*name.s)[i++] != NOSUB)                     \
            (*name.s)[i](data);                             \
    }                                                    \
    void init_##name()                                   \
    {                                                    \
        stream_subscriber_t arr[3] = subscribers; \
        *name.s = arr;                                   \
        name.write = f_##name;                           \
    }
#define ARRAY(...)  \
    {               \
        __VA_ARGS__ \
    }
#endif