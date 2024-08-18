# SIMPLE CONTRA
###### Thử nghiệm game:
###### Phá đảo game:

## Giới thiệu game:
Simple contra là một game thuộc thể loại game run and shot, nội dung game là nhập vai vào một nhân vật soldier vượt qua những chướng ngại vật và kết thúc game bằng việc đối đầu với một quái vật boss.

## Cách tải game:

### Không bao gồm code

### Bao gồm code và có thể biên dịch

## 1. Bắt đầu game:

### Giao diện khi bắt đầu chạy game:

![image](https://github.com/user-attachments/assets/b6203743-1ca4-4bc1-9560-34ccc9e4cb9f)

Ở đây người chơi có 2 sự lựa chọn :
  Đầu tiên là chơi game sẽ lập tức bắt đầu trò chơi
  Thứ hai là Exit sẽ lập tức tắt trò chơi

## 2. Các thành phần trong game:
  ![image](https://github.com/user-attachments/assets/7cc77104-b478-4df1-b86b-235447849ca6)

  Đầu tiên ở góc bên trái trên cùng ta có thể thấy ba biểu tượng trái tim, nó đại diện cho chỉ số lượt chơi
  ![image](https://github.com/user-attachments/assets/17a38286-0105-45d8-9257-9710b33a59b1)

  Tiếp theo là Coin, Kill và Time lần lượt là các biểu tượng dạng text hiển thị số coin đã ăn được, số quái đã tiêu diệt được cũng như thời gian đếm ngược là 180s để chơi game
  ![image](https://github.com/user-attachments/assets/eb2baf29-8c33-44b6-b88f-bac4a2049e12)


## 3. Cách chơi

  Trò chơi di chuyển bằng các hướng mũi tên, cùng với đó hướng đạn bắn cũng theo hướng khi bạn di chuyển mũi tên và đạn được bắn khi người chơi nhấn nút chuột trái. Trong trò chơi này người chơi sẽ phải đối diện với ba loại mối đe dọa:

### a. Các loại mói đe dọa:
####  Đầu tiên là quái vật sói: vừa di chuyển vừa có thể bắn ra đạn
  ![image](https://github.com/user-attachments/assets/311699fe-84a6-4b74-bd79-5180ea6a4786)

  ##### Khi bị trúng đạn hay xảy ra va chạm với đối tượng này bạn sẽ mất đi một lượt chơi, và đối với đối tượng này bạn chỉ cần bắn trúng một lần thì đối tượng sẽ bị tiêu diệt
  
#### Tiếp theo là đối tượng tĩnh

![image](https://github.com/user-attachments/assets/25d24d6f-320f-4f07-b9a5-695dc8c53568)

##### Đối với đối tượng này, kể cả khi bắn đạn nó sẽ vẫn tồn tại, bạn chỉ có thể vượt qua nó bằng cách nhảy qua và tương tự như đối tượng trên nếu va chạm người chơi cũng sẽ mất một lượt chơi

#### Và cuối cùng là đối tượng boss

![image](https://github.com/user-attachments/assets/afa7ffe4-b06f-4021-a9e7-70b93f9fb42a)

##### Đối tượng này cũng tương tự như đối tượng động nhưng đạn của chúng có ảnh hưởng xa hơn và vì đây là boss nên đạn nhanh hơn và chúng ta cũng mất 6 lần bắn trúng mới tiêu diệt được.



  


## 4. Chiến thắng và thất bại

### Đối với thất bại: Mỗi người chơi chỉ có 3 sinh mệnh và mỗi lần bị va chạm với mối đe dọa hay đạn của chúng và khi rơi xuống hồ đều sẽ bị trừ 1 điểm sinh mệnh và cứ như vậy khi dùng hết 3 lượt sinh mệnh sẽ bị thất bại

### Đối chiến thắng: khi bạn có thể vượt qua được hết chướng ngại vật đồng thời giết được đối tượng boss thì khi này sẽ phá đảo hay giành chiến thắng game.
