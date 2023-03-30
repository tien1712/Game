Cards Matching Memory
Nguyễn Hữu Tiến -22028180

Project này mình làm về game Cards Matching Memory. Ngôn ngữ được sử dụng trong game là C++ và thư viện đồ họa SDL2.

Mục lục:
1. Hướng dẫn cài đặt
2. Mô tả chung
3. Các chức năng
4. Các kĩ thuật sử dụng
5. Nguồn tham khảo
6. Kết luận

1. Hướng dẫn cài đặt:
Bước 1: Cài đặt SDL2 vào Visual Studio Code theo như Hướng dẫn.
Bước 2: Tải project game về và mở Visual Studio Code.
Bước 3: Mở terminal gõ lệnh make và sau đó ./main

2. Mô tả chung:
Cards Matching Memory Game là một trò chơi trí nhớ vui nhộn giúp phát triển các kỹ năng ghi nhớ tuyệt vời. Game có cách chơi đơn giản. Lật 2 thẻ bài bằng cách nhấp chuột vào chúng. Nếu chúng giống nhau, cặp bài sẽ tự động biến mất. Nếu không khớp, chúng sẽ lật lại để người chơi thử lại. Trò chơi sẽ kết thúc khi tất cả các thẻ bài biến mất

3. Các chức năng:
Video minh họa: Cards Matching Memory
Chọn độ khó: Độ khó khác nhau thì số lượng thẻ bài sẽ khác nhau.
Chức năng xem Hướng dẫn chơi

4. Các kĩ thuật sử dụng:
Thư viện đồ họa SDL2: Sử dụng hiển thị ảnh, chữ.
Mảng 2 chiều: dùng để lưu trữ trạng thái hiển thị của các thẻ.
Đọc, in dữ liệu ra file: dùng để lưu trữ dữ liệu thành tích, tránh bị mất mỗi lần chạy game và lưu trữ.
Random để chọn ngẫu nhiên các cặp thẻ bài trong kho thẻ ban đầu.
Cấu trúc, lớp: Xây dựng một số cấu trúc để lưu tọa độ (x và y), cấu trúc thẻ bài (bao gồm loại thẻ, chiều dài, chiều rộng , chế độ ẩn,...).
Chia code thành các folder: General (xử lý khởi tạo, đóng SDL, xử lí chuyển đổi màn hình), GUI (xử lý việc hiển thị các nút, thay đổi trạng thái nút)), Screens (xử lý việc hiển thị ảnh và text), Game (chứa việc xử lý các sự kiện cũng như logic game),Media (chứa các font, graphics, music ).
Photoshop: Cắt ghép ảnh, chỉnh sửa các ảnh trên mạng theo ý thích để đưa vào game.

5.Nguồn tham khảo:
Cách chia file
Tile.
Button.

6. Kết luận:
Sau khi hoàn thành dự án game cuối kì trong học phần này, em học và tìm hiểu được nhiều kiến thức và kinh nghiệm về SDL2. tư duy Code, thuật toán, kĩ năng chỉnh sửa ảnh.
Cách sử dụng thêm nhiều chức năng của Github

- Các hướng phát triển trong tương lai:

Nâng cao kỹ năng photoshop để có đồ họa đẹp hơn cho game.
Thêm chế độ nhiều người chơi.
Mọi thắc mắc gửi về email: 22028180@vnu.edu.vn
