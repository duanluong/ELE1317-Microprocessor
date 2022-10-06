#ifndef __DELAY__
#define __DELAY__

#ifdef __cplusplus
extern "C" {
#endif

void DELAY_Init (unsigned char _CLK);
void DELAY_ms (unsigned int _vrui_Time);
void DELAY_us (unsigned long _vrui_Time)

#ifdef __cplusplus
}
#endif


#endif // __DELAY__