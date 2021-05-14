# SDLGame Project
* Họ và tên: Trương Minh Trí
* MSSV: 20020034
* Game: Đẩy hình

## Introduction Game 

* Game đẩy hình với logic game đơn giản là dùng 4 phím mũi tên điều hướng để đẩy các bức hình từ một bức tranh lộn xộn về bức tranh hoàn chỉnh ban đầu.
* Game có menu khởi đầu cho phép bắt đầu vào menu chọn option Play hoặc Exit game.
* Option menu cho phép chọn 4 kích cỡ 3x3, 4x4, 5x5, 6x6 tương ứng với hình ảnh bị chia ra làm bao nhiêu ô vuông
* Gameplay cho phép người chơi xem ảnh hoàn chỉnh rồi mới chơi. Trong phần gameplay của em còn có chức năng (resset button) reset lại để chơi lại từ đầu, (new button) tạo hình ảnh và thứ tự các ô hình mới, (menu button) trở về menu, (look back button) cho người chơi xem lại ảnh hoàn chỉnh.
* Game sẽ lưu điểm là số lần di chuyển, highcore là số lần di chuyển ít nhất trong các lần chơi. Trong quá trình chơi, số lần di chuyển tự cập nhật và hiển thị cùng với game play.
* Khi thắng sẽ có menu hiện ra thông báo điểm, highscore, số bước đi ít nhất để đưa bức tranh về hoàn chỉnh và 3 button resset, new, menu cho người chơi lựa chọn.
* Game có nhạc nền, hiệu ứng khi click chuột, di chuyển ô tranh và nhạc khi thắng.
* Game sẽ lưu lại các thông số game và đọc lại khi người chơi chạy lại game (image, highscore, optimal, data of pictures).
## Algorithm
 
 * Thuật toán chủ yếu của game em là BFS nhằm sinh ra các trạng thái của bức tranh dựa trên việc di chuyển ô trống.
 * Lí do dùng BFS:
```bash
	Dùng BFS cũng sẽ tính luôn được số bước di chuyển ít nhất để có thể đưa bức tranh về trạng thái ban đầu.
	Nếu sinh random thứ tự các ô tranh không đảm bảo về giải được game, đưa các ô tranh về đúng thứ tự.
```
* Hạn chế: Vì phải lưu trạng thái của n x n rồi tính các trạng thái nên BFS còn khá chậm khi muốn sinh dữ liệu lớn, vì vậy
	thuật toán sinh dữ liệu chưa tối ưu cho game này.

## Sources
* SDL Code:  Tự đọc hiểu code của cô Châu và ví dụ trên Lazyfoo và code lại theo cách của mình
* Graphics:  Thiết kế bởi bạn Bá Lương và em. (Bạn Bá thiết kế chính, em đóng góp ý kiến, ý tưởng sửa đổi cho phù hợp với game)
* Sound:     Nhặt nhạnh các file nhạc, effect trên Youtube và các trang cộng đồng nhạc.


