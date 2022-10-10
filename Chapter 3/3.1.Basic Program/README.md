## Cấu trúc một chương trình ASM cơ bản
- Công cụ sử dụng: [CPU-lator](https://cpulator.01xz.net/)
- Chương trình cơ bản được viết như sau:
    ```C
    @Phan vung khoi tao
    .global _start
    
    @Phan vung hang so
    .equ data, 400
    
    @Phan vung chuong trinh
    _start:
    
    
    @Lenh ket thuc chuong trinh
    MOV R7, #1
    SWI 0
    
    @Phan vung du lieu
    .data
    list: .word 1,2,3,4,5,6,7,8
    ```
- Người lập trình có thể tham khảo cấu trúc chương trình cơ bản trong việc xây dựng các chương trình khác.
