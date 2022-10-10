#ifndef __DELAY__
#define __DELAY__

#ifdef __cplusplus
extern "C" {
#endif

void Delay_Init (unsigned char _CLK);
void Delay_ms (unsigned int _vrui_Time);
void Delay_us (unsigned long _vrui_Time);

#ifdef __cplusplus
}
#endif


#endif // __DELAY__

