# LẬP TRÌNH GPIO SỬ DỤNG THANH GHI

## Giới thiệu cơ bản về lập trình sử dụng thanh ghi

Với việc lập trình sử dụng trực tiếp thanh ghi người lập trình không cần thông qua thư viện SPL do vậy ở mục StdPeriph Drivers không cần lựa chọn.
![Cấu hình các gói thư viện](./docs/1.package.png)

## Thử nghiệm
**Kết nối**:
- LED - ***Pin C13*** (Hoặc LED on Board với Board Bluepill

    Vị trí LED C13 trên Board Bluepill
    ![Bluepill Board pinout](./docs/2.LedPin.png)

**Thử nghiệm**:
- Nạp code và quan sát hiện tượng trên LED
- Lưu ý: Một số Board có thể nạp nhưng không tự Reset cần nhấn nút Reset trên Board để MCU bắt đầu khởi chạy.
- Thử thay đổi thông số delay, build lại code, nạp và thử nghiệm lại.
-
**Mở rộng**:
- Thay đổi LED kết nối ngoài và cấu hình code cho phù hợp.