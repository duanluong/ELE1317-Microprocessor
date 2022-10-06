# THƯ VIỆN DELAY SỬ DỤNG SYSTICK
## Giải thích:
Ở các ví dụ trên chúng ta đã xây dựng hàm delay để tạo ra đỗ trễ về hoạt động nhằm có thể quan sát được các hiện tượng như nhấp nháy LED tuy nhiên các hàm delay này thường có độ chính xác không cao. Sau khi đã sử dụng Systick chúng ta thấy rằng đây là một bộ đếm có độ chính xác cao, do đó ở đây chúng ta tạo ra một thư viện Delay bao gồm 3 hàm Init, ms và us để tạo ra các hàm delay với độ chính xác cao.

Thư viện như sau:

Delay.h
```C
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
```

Trong đó:
>**DELAY_Init**: Hàm khởi tạo thư viện Delay sử dụng Systick. Tham số đầu vào là tần số xung nhịp hệ thống chia cho 1.000.000

>**DELAY_us**: Hàm delay với hệ số là us.

>**DELAY_ms**: Hàm delay với hệ số là ms.

Thư viện có thể được sử dụng với các trường hợp cần các giao tiếp hoặc xử lý yêu cầu khắt khe về thời gian (Yêu cầu tính chính xác cao).

**Lưu ý**: _Khi sử dụng thư viện Delay sử dụng Systick chúng ta sẽ không thể sử dụng Systick ở chế độ ngắt như ví dụ trước._