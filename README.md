<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/logo2.svg"><br>
</div>

---

<h1><strong>futurevision: Robotik eğitiminde yeni bir çağ</strong></h1>

## Nedir

**Python** dili ile Arduino kartınızdaki led'leri, RGB led'i, butonları ve 8x8 led matrisi kontrol etmenizi sağlar.

Ana bilgisayarınızı kullanarak bilgisayarlı görü ile Arduino'yu kontrol edebilir ve Raspberry Pi, bilgisayarlı görüyü kolaylaştırır.

Kütüphane için oluşturulan bir **Darwin Future Vision** isimli mobil uygulaması, iPhone telefonunuzun gözlemsel donanımları olan flaşını, ekran parlaklığını ve hoparlör ses oranını kontrol etmenizi sağlar.

Telefonun ekran parlaklığı, hoparlör ses şiddeti oranı ve telefonun hangi ses düğmesine basıldığının verilerini iPhone donanım bilgilerini çekerek python kodunuzda bu verileri almanızı ve kullanabilmenize olanak tanır

iPhone uygulamasındaki LEDs bölümünde 5 led grafiğini kontrol edebilirsiniz.

iPhone uygulaması ile python kodunuza veri gönderebilir veya python kodunuzdan göndereceğiniz verileri uygulamada görebilirsiniz.

## Neyi amaçlar

Klasikleşmiş robotik eğitiminin dışına çıkarak robotik eğitiminde çocukların merakını yeniden uyandırmayı ve robotik eğitiminde yeni bir çığır açmayı hedeflemektedir

## Modüler ve ozellikleri

**Future Vision** kütüphanesinin **Arduino** modülüyle Python dilini kullanarak Arduino'daki LED'leri, RGB LED'leri ve 8x8 LED matrisini kontrol edebilir, ayrıca Arduino'nun analog pinlerine bağlı olan butonlardan değer okuyabilirsiniz.

**Future Vision** kütüphanesinin **Raspberry Pi** modülüyle Raspberry Pi'daki LED'leri, RGB LED'leri, Sense HAT üzerindeki 8x8 LED matrisini ve Sense HAT sensörlerini okuyabilir ve kontrol edebilirsiniz, ayrıca Sense HAT joystick değerlerini de okuyabilirsiniz.

**Future Vision** kütüphanesinin **Vision** modülüyle kendi işaret dilinizi oluşturabilir, elleri tespit edebilir, yüzünüzdeki mutluluk ve mutsuzluk oranını tespit edebilir, bir odadaki anlık yüz sayısını tespit edebilir, renkleri algılayabilir, gözlerin kapalı veya açık olduğunu tespit edebilir, klavyedeki tuşları yönetebilir, ses şiddetini ölçebilir, bilgisayarınızı konuşturabilir, sağ ve sol kol hareketlerini analiz edebilir, objeleri tanıyabilir ve kişisel yüz tanıma yapabilirsiniz.

**Future Vision** kütüphanesinin **iPhone** modülü ve mobil uygulama ile iPhone telefonunuzun gözlemsel donanımları olan flaş, ekran parlaklığı ve hoparlörün ses şiddetini kontrol edebilirsiniz. Ayrıca, ekran parlaklığı, hoparlör ses şiddeti oranı ve sesi yükseltme veya alçaltma tuşlarına basılma verilerini bilgisayarınızda görebilir ve bu verilere göre Arduino veya Raspberry Pi kartınızı kontrol edebilirsiniz veya Arduino ve Raspberry Pi ile örneğin butona basarak telefonunuzun flaşını kontrol edebilirsiniz.

## Modullerin Kullanımı

<h3><strong>Arduino</strong></h3>

future vision kütüphanesinin arduino uno kartınızla doğru çalışabilmesi için bu [FutureVision-Arduino.ino](https://github.com/AliEdis/futurevision/blob/main/FutureVision-Arduino/FutureVision-Arduino.ino) kodunu arduino uno kartınıza yüklemeniz gerekmektedir.

13, 12 ve 11 pinleri led matrixe ayrılmıştır 10, 9, 8 pinleri rgb lede ayrılmıştır. Sadece 7, 6, 5, 4, 3, 2 pinlerini dijital çıkış olarak kullabilirsiniz

#### Led açma ve kapatma

```python
from futurevision import arduino
uno=arduino.Arduino(usb_port="/dev/cu.usbmodem101",baud=9600)
uno.on(pin=7)
uno.wait(1)
uno.off(pin=7)
```

Led bağlantıları aşağadaki gibidir

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/led1.png"><br>
</div>

#### RGB Led Kontrollü

RGB Ledde Gösterebileceğiniz renkler

1. Red 🔴
2. Yellow 🟡
3. Green 🟢
4. Blue 🔵
5. Purple 🟣
6. White ⚪️
7. Light Blue 🩵
8. Off veya clear

RGB ledin Pin Düzeni R:10 G:9 B:8

```python
from futurevision import arduino
uno=arduino.Arduino(usb_port="/dev/cu.usbmodem101",baud=9600)
uno.rgb_led("red")
uno.wait(1)
uno.rgb_led("yellow")
uno.wait(1)
uno.rgb_led("green")
uno.wait(1)
uno.rgb_led("blue")
uno.wait(1)
uno.rgb_led("purple")
uno.wait(1)
uno.rgb_led("white")
uno.wait(1)
uno.rgb_led("clear")
uno.wait(1)
```

RGB Led şekli aşağadaki gibidir

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/rgb_led_pin.png"><br>
</div>

#### Buton Değeri Okuma

Butonların Değerleri Sadece Analog Pinlerden Okunacak şekilde ayarlanmıştır.
Döndürülen Buton Değeri {PIN} olarak verilecektir.
Örneğin A0 ve A3 pinlerine bağlı iki butonumuzun olduğunu düşünelim 3 defa A3 pinine bağlı butona bastığımızda ve iki defa A0 pinindeki butona bastığımızda terminal çıktısı aşağıdaki gibi olacaktır.

```python
from futurevision import arduino
uno=arduino.Arduino(usb_port="/dev/cu.usbmodem101",baud=9600)
while True:
    read=uno.read()
    print(read)
```

Terminal Çıktısı

```sh
(base) ali@aliedis-MacBook-Air Desktop % python3 test.py
3
3
3
0
0
```

Buton bağlantıları aşağadaki gibidir

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/button_pin1.png"><br>
</div>

#### Led Matrix Kontrollü

Led Matrixin Pin Düzeni DIN:13 CS:12 CLK:11
Led Matrixte istediğiniz karakterleri gösterebilirsiniz karakter ve şekil listesi şu şekildedir

A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
1, 2, 3, 4, 5, 6, 7, 8, 9, 0
+, -, *, /, %, =, up, down, right, left, happy, unhappy, heart
Bu komutlardan birini girerek led matrixinizi kapatabilirsiniz clear & off

Led Matrix default olarak dikey çalışacak şekilde ayarlanmıştır bunu değiştirmek için direction parametresini 0 olarak değiştirebilirsiniz

Örnek: uno.show_led_matrix("A",0)

```python
from futurevision import arduino
uno=arduino.Arduino(usb_port="/dev/cu.usbmodem101",baud=9600)

upper_letter_list=['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
lower_letter_list=['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

number_list=[1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
sign_list=['+', '-', '*', '/', '%', '=', 'up', 'down', 'right', 'left', 'happy', 'unhappy', 'heart']

for i in upper_letter_list:
  uno.show_led_matrix(i)
  uno.wait(1)
  uno.show_led_matrix("clear")

for i in lower_letter_list:
  uno.show_led_matrix(i)
  uno.wait(1)
  uno.show_led_matrix("clear")

for i in number_list:
  uno.show_led_matrix(i)
  uno.wait(1)
  uno.show_led_matrix("clear")

for i in sign_list:
  uno.show_led_matrix(i)
  uno.wait(1)
  uno.show_led_matrix("clear")
```

Led Matrix bağlantıları aşağadaki gibidir

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/led_matrix1.png"><br>
</div>

<h3><strong>Raspberry Pi</strong></h3>

#### Led açma ve kapatma

```python
from futurevision import raspberrypi
rpi=raspberrypi.RaspberryPi()
rpi.on(14)
rpi.wait(1)
rpi.off(14)
```

#### RGB Led Kontrollü

RGB Ledde Gösterebileceğiniz renkler

1. Red 🔴
2. Yellow 🟡
3. Green 🟢
4. Blue 🔵
5. Purple 🟣
6. White ⚪️
7. Light Blue 🩵
8. Off veya clear

```python
from futurevision import raspberrypi
rpi=raspberrypi.RaspberryPi()
rpi.rgb_led("red",14,15,18)
rpi.wait(1)
rpi.rgb_led("yellow",14,15,18)
rpi.wait(1)
rpi.rgb_led("green",14,15,18)
rpi.wait(1)
rpi.rgb_led("blue",14,15,18)
rpi.wait(1)
rpi.rgb_led("purple",14,15,18)
rpi.wait(1)
rpi.rgb_led("white",14,15,18)
rpi.wait(1)
rpi.rgb_led("lightblue",14,15,18)
rpi.wait(1)
rpi.rgb_led("clear",14,15,18)
rpi.wait(1)
```

#### Buton Değeri Okuma

Buton PULL UP olarak ayarlanmıştr

```python
from futurevision import raspberrypi
rpi=raspberrypi.RaspberryPi()
while True:
    button=rpi.read_button(14)
    if(button):
     print("Button Pressed")
    rpi.wait(0.1)
```

Terminal çıktısı

```sh
>>> %Run test.py
Button Pressed
```

#### Sense Hat Led Matrix Harf veya Sayı Gösterme

```python
from futurevision import raspberrypi
rpi=raspberrypi.RaspberryPi(sense_hat=True)
rpi.show_letter("A")
rpi.wait(1)
rpi.show_letter("1")
rpi.wait(1)
rpi.clear()
```

##### Yazı Rengi ve Arka Plan Rengi Değiştirme

Sense hat led matrixinde seçebileceğiniz renklerin listesi:

None
White
Red
Green
Blue
Yellow
Purple
Orange
Pink
Cyan
Brown
Lime
Teal
Maroon

```python
from futurevision import raspberrypi
rpi=raspberrypi.RaspberryPi(sense_hat=True)
rpi.show_letter("A",text_colour="red",back_colour="white")
rpi.wait(1)
rpi.clear()
```

#### Sense Hat Led Matrix Mesaj Gösterme

```python
from futurevision import raspberrypi
rpi=raspberrypi.RaspberryPi(sense_hat=True)
rpi.show_message("Future Vision")
```

##### Sense Hat Mesaj Gösterilme Hızı Değiştirme

```python
from futurevision import raspberrypi
rpi=raspberrypi.RaspberryPi(sense_hat=True)
rpi.show_message("Future Vision",scroll_speed=0.2)
```

#### Sense Hat Led Matrix Boyama

```python
from futurevision import raspberrypi
rpi=raspberrypi.RaspberryPi(sense_hat=True)
rpi.fill("red")
rpi.wait(1)
rpi.clear()
```

#### Sense Hat Led Matrix İşaret Gösterme

Gösterebileceğiniz işaretler up, down, right, left, happy, unhappy, heart

```python
from futurevision import raspberrypi
rpi=raspberrypi.RaspberryPi(sense_hat=True)
sign_list=['up', 'down', 'right', 'left', 'happy', 'unhappy', 'heart']
for i in sign_list:
  rpi.show_sign(i)
  rpi.wait(1)
  rpi.clear()
```

#### Sense Hat Sensörlerini Kullanma

```python
from futurevision import raspberrypi
rpi=raspberrypi.RaspberryPi(sense_hat=True)
temperature=rpi.get_temperature()
humidity=rpi.get_humidity()
pressure=rpi.get_pressure()
gyroscope=rpi.get_gyroscope()
accelerometer=rpi.get_accelerometer()
compass=rpi.get_compass()

print(temperature)
print(humidity)
print(pressure)
print(gyroscope)
print(accelerometer)
print(compass)
```

Terminal Çıktısı

```sh
>>> %Run test.py
34.51753616333008
38.123626708984375
0
[-0.535936176776886, 0.06923675537109375, -0.25748658180236816]
[0.11419202387332916, 0.3673451840877533, 0.8629305362701416]
174.1544422493143
```

#### Sense Hat Joystick Butonuna Tıklanmayı Algılama

```python
from futurevision import raspberrypi
rpi=raspberrypi.RaspberryPi(sense_hat=True)
while True:
  btn=rpi.joystick_button()
  print(btn)
  rpi.wait(0.1)
```

Terminal Çıktısı

```sh
>>> %Run test.py
False
False 
True
False
```

#### Sense Hat Joystick Haraketleri

```python
from futurevision import raspberrypi
rpi=raspberrypi.RaspberryPi(sense_hat=True)
while True:
  btn=rpi.joystick()
  print(btn)
  rpi.wait(0.1)
```

Terminal Çıktısı

```sh
>>> %Run test.py
up
down 
right
left
middle
```

<h3><strong>Vision</strong></h3>

#### El Tespiti

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img, fingers, status=vision.detect_hand(img)
    print("Finger List: ",fingers,"Hand Status: ",status)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

Terminal Çıktısı

Kapalı olan parmaklar için 0 değeri döner açık olan parmaklar için 1 değeri döndürür
Eğer bütün parmaklar açıksa status True döndürür
Eğer bütün parmaklar kapalıysa status False döndürür

```sh
>>> %Run test.py
Finger List:  [1, 1, 1, 1, 1] Hand Status:  True
Finger List:  [0, 0, 0, 0, 0] Hand Status:  False
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/default_hand_detection.gif"><br>
</div>

<br>

##### El çiziminin Rengini değiştirme

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img, fingers, status=vision.detect_hand(img,line_color="red",circle_color="green")
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/custom_hand_detection.gif"><br>
</div>

<br>

##### El çizimini Devredışı Bırakma

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img, fingers, status=vision.detect_hand(img,draw=False)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

##### İşaret dili oluşturma

Listedeki indexlerin temsil ettiği parmaklar aşağıdaki resimdeki gibidir

<div align="center">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/fingers_numbers.png"><br>
</div>

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
        _,img=cap.read()
        img,list,status=vision.detect_hand(img)
        if len(list) > 0:
               if(list==[0,0,0,0,0]):
                      print("off")
               if(list==[0,0,0,0,1]):
                      print("right")
               if(list==[1,1,0,0,0]):
                      print("left")
        cv2.imshow("Future Vision",img)
        cv2.waitKey(1)
```

#### Duygu Tespiti

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img, emotion,th=vision.detect_emotion(img)
    print(emotion)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

Terminal Çıktısı

```sh
unhappy 0.025
happy 0.045
unhappy 0.025
happy 0.045
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/emotion_default1.gif"><br>
</div>

<br>

##### Yüz ve Yazının Rengini değiştirme

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img, emotion,th=vision.detect_emotion(img,line_color="green",text_color="green")
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/custom_emotion2.gif"><br>
</div>

<br>

##### Yüz Çizimini Devre dışı bırakma

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img, emotion=vision.detect_emotion(img,draw=False,text=False)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

#### Anlık Yüz Sayaçı

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img, count=vision.count_faces(img)
    print(count)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

Terminal Çıktısı

```sh
2
2
2
2
1
1
2
2
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/count_faces.gif"><br>
</div>

<br>

##### Anlık Yüz Sayaçı Çizimini Devre dışı bırakma

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img, count=vision.count_faces(img,draw=False)
    print(count)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

#### Renk Tanıma

Tanıyabildiği renkler: Kırmızı, Yeşil, Mavi

Threshold değeri default olarak 1000 ayarlanmıştır ihtiyacınıza göre bu değeri düşürebilir yada yükseltebilirsiniz

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img,name,list=vision.detect_colors(img)
    print(name,list)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

```sh
blue [844.5, 415.5, 173812.0]
red [600.5, 311.0, 530.5]
green [0, 772.0, 0]
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/color.gif"><br>
</div>

<br>

##### Çizim rengini değiştirme

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img,name,list=vision.detect_colors(img,rectangle_color="yellow")
    print(name,list)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/custom_color.gif"><br>
</div>

<br>

##### Çizimi devre dışı bırakma

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img,name,list=vision.detect_colors(img,draw=False)
    print(name,list)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

#### Göz kırpma algılama

Yüz tanımanın çalışabilmesi için yüz tanıma modelini indirmelisiniz [shape_predictor_68_face_landmarks.dat](https://github.com/davisking/dlib-models/blob/master/shape_predictor_68_face_landmarks.dat.bz2)

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
vision.blink_setup(path="shape_predictor_68_face_landmarks.dat")
while True:
    _,img=cap.read()
    img,EAR,status,time=vision.detect_blink(img)
    print(EAR,status,time)
  
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

```sh
0.2 False None
0.21 False None
0.22 False None
0.1 True None
0.1 True None
0.17 False 1.50
0.23 False None
0.23 False None
0.21 False None
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/eye_blink.gif"><br>
</div>

<br>

##### Göz çizimini devre dışı bırakma

```python
from futurevision import vision
import cv2
vision=vision.Vision()
vision.blink_setup(path="shape_predictor_68_face_landmarks.dat")
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img,EAR,status,time=vision.detect_blink(img)
    print(EAR,status,time)
  
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

#### Vucut Tespiti ve Analizi

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img,left,right=vision.detect_body(img)
    print(left,right)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

```sh
175.43727322952194 186.38214534742016
159.12635745126173 181.2641703620141
0.8016276382526805 67.3130811726478
7.112369711132518 3.427382752073662
3.0965441578399973 3.4120390844959267
0.008587732984777094 1.7826284349542627
1.46573896432903 1.4118781257852226
5.318943889580121 1.1099510521746376
4.449516553979241 2.073257712440663
7.570394013983709 3.0725981509538887
16.59312469528359 22.83114476402925
20.703749065899352 95.33857084841868
168.733170676982 177.10299133508224
175.13547154106007 178.61997780496543

```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/body.gif"><br>
</div>

<br>

##### Vucut Çizimini Devre dışı bırakma

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img,left,right=vision.detect_body(img,draw=False)
    print(left,right)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

#### Obje Tanıma

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
while True:
    _,img=cap.read()
    img,left,right=vision.detect_body(img)
    print(left,right)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

```sh
person
person
person
person
person
person
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/object.gif"><br>
</div>

<br>

#### Yüz Tanıma

Yüz tanımanın çalışabilmesi için yüz tanıma modelini indirmelisiniz [shape_predictor_68_face_landmarks.dat](https://github.com/davisking/dlib-models/blob/master/shape_predictor_68_face_landmarks.dat.bz2)

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
vision.face_recognizer_setup(["Ali_Edis.png","Carl_Sagan.png"],path="shape_predictor_68_face_landmarks.dat")
while True:
    _,img=cap.read()
    img,name=vision.face_recognizer(img)
    print(name)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

```sh
['Ali Edis']
['Ali Edis']
['Carl Sagan', 'Ali Edis']
['Carl Sagan', 'Ali Edis']
['Carl Sagan', 'Ali Edis']
['Carl Sagan', 'Ali Edis']
['unknown', 'Ali Edis']
['unknown', 'Ali Edis']
['unknown', 'Ali Edis']
['Ali Edis']
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/face_rec.gif"><br>
</div>

Çizimi devre dışı bırakma

```python
from futurevision import vision
import cv2
vision=vision.Vision()
cap=cv2.VideoCapture(0)
vision.face_recognizer_setup(["Ali_Edis.png","Carl_Sagan.png"],path="shape_predictor_68_face_landmarks.dat")
while True:
    _,img=cap.read()
    img,name=vision.face_recognizer(img,draw=False)
    print(name)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

#### Klavye Kontrollü

```python
from futurevision import vision
vision=vision.Vision()
vision.press("a")
```

#### Klavye ile Metin Yazma

```python
from futurevision import vision
vision=vision.Vision()
vision.write("future vision")
```

#### Bilgisayarınızı Konuşturma

```python
from futurevision import vision
vision=vision.Vision()
vision.speak("Future Vision")
```

Dil Değiştirme

```python
from futurevision import vision
vision=vision.Vision()
vision.speak("Merhaba",lang="tr")
```

Dosya ismi değiştirme

```python
from futurevision import vision
vision=vision.Vision()
vision.speak("Future Vision",filename="test.mp3")
```

#### Bilgisayarınızın Mikrofonunu kullanarak Ses şiddeti Ölçme

```python
from futurevision import vision
vision=vision.Vision ()
try:
    vision.start_stream()
    while True:
        sound= vision.detect_sound()
        print(sound)
except KeyboardInterrupt:
    vision.stop_stream ()
```

<h3><strong>iPhone</strong></h3>

<p style="text-align: center;"><b>App Store Açın</b></p>

<div align="center">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/1.PNG">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/2.PNG">
</div>

<br>

<p style="text-align: center;"><b>Arama çubuğunda Darwin Future Vision Aratın</b></p> 
<div align="center">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/3.PNG">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/4.PNG">
</div>

<br>

<p style="text-align: center;"><b>Uygulama Sayfasına Girin</b></p>

<div align="center">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/5.PNG">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/6.PNG">
</div>
<br>

<p style="text-align: center;"><b>Uygulamayı İndirin</b></p> 
<div align="center">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/7.PNG">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/8.PNG">
</div>

#### Uygulama Bölümleri ve Örnek Kodlar

<div align="center">
<img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/9.PNG"><br>
</div>

#### Settings

Settings Bölümünde Uygulamanın yazacağınız python kodunuzla haberleşebilmesi için python kodunuzun size vereceği ip adresi ve port bilgilerini kaydetmelisiniz.

<div align="center">
<img style="width:700px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/ip_result_terminal.PNG"><br>
</div>
<div align="center">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/10.PNG">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/11.PNG">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/12.PNG"><br>
</div>

#### HWC

Bu bölümde **future vision** kütüphanesinin **iphone** modülü ile yazacağınız kodlara göre iPhone telefonunuzun gözlemsel donanımlarını kontrol etme imkanını sunar. **flash_on()** **flash_off()** fonksiyonları ile Flaşı,  **screen_brightness(value)** fonksiyonu ile Ekran Parlaklığını, **volume_intensity(value)** fonksiyonu ile Hoparlorun Ses Şiddetini Kontrol Etmenizi Sağlar.

<div align="center">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/hwc.PNG">
</div>

#### CwH

Bu bölümde **future vision** kütüphanesinin **iphone** modülü ile yazacağınız kodlara göre iPhone telefonunuzun gözlemsel donanım bilgilerini python kodunuza bir liste olarak gönderir. Bu liste verisini **read_data()** fonksiyonu ile okuyabilirsiniz veriler arasında Ekran parlaklığı değeri Ses Şiddeti Değeri ve Telefonunuzun hangi ses tuşuna basıldığının verisini gönderir örnek bir veri:

```sh
['25', '70', 'Down']
['25', '75', 'Up']
```

<div align="center">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/cwh.PNG">
</div>

#### LEDs

Bu bölümde **future vision** kütüphanesinin **iphone** modülü ile yazacağınız kodlara göre uygulama içerisinde bulunan 5 adet led grafiğini kontrol etme imkanı sunar ve 5 adet ledin renklerini yeşil, mavi ve kirmizi olarak değiştirebilirsiniz. Uygulamadaki ledleri açmak için **led_on(pin)** kapatmak için **led_off(pin)** fonksiyonlarını kullanabilirsiniz

<div align="center">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/leds.PNG">
</div>

#### SEND&SHOW

Bu bölümde **future vision** kütüphanesinin **iphone** modülü ile yazacağınız kodlara göre uygulama içerisindeki input'a gireceğiniz verileri bilgisayarınıza gönderebilir veya bilgisayarınızdan mobil uygulamaya veri gönderebilirsiniz. mobil uygulamaya veri göndermek için **send_data(data)** mobil uygulamanın göndereceği verileri okumak için **read_data()** fonksiyonlarını kullanabilirsiniz.

<div align="center">
  <img style="width:300px;" src="/Users/ali/Desktop/futurevision/README-IMAGE/sendshow.PNG">
</div>

#### Örnek Kodlar

#### HWC

##### Flaş Kontrollü

```python
from futurevision import iphone
iphone=iphone.iPhone()
while True:
    iphone.flash_on()
    iphone.wait(3)
    iphone.flash_off()
    iphone.wait(3)
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/flash_hwc.gif"><br>
</div>

##### Ekran Parlaklığı Kontrollü

```python
from futurevision import iphone
iphone=iphone.iPhone()
while True:
    iphone.screen_brightness(100)
    iphone.wait(3)
    iphone.screen_brightness(0)
    iphone.wait(3)
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/sb_hwc.gif"><br>
</div>

##### Ses Şiddeti Kontrollü

```python
from futurevision import iphone
iphone=iphone.iPhone()
while True:
    iphone.volume_intensity(100)
    iphone.wait(3)
    iphone.volume_intensity(0)
    iphone.wait(3)
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/si_hwc.gif"><br>
</div>

#### CwH

##### iPhone Gözlemsel Donanımının Verilerini Okuma

```python
from futurevision import iphone
iphone=iphone.iPhone()
while True:
    data=iphone.read_data()
    print(data)
```

**Listenin index sıralamasındaki ilk index ekran parlaklığı, ikinci index ses şiddeti, üçüncü index telefonun hangi ses yükseltme tuşuna basıldığının bilgilerini saklamaktadır**

```sh
['25', '70', 'Down']
['25', '75', 'Up']
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/cwh_data.gif"><br>
</div>

#### LEDs

```python
from futurevision import iphone
iphone=iphone.iPhone()
while True:
    iphone.led_on(1)
    iphone.led_on(2)
    iphone.led_on(3)
    iphone.led_on(4)
    iphone.led_on(5)
    iphone.wait(3)
    iphone.led_off(1)
    iphone.led_off(2)
    iphone.led_off(3)
    iphone.led_off(4)
    iphone.led_off(5)
    iphone.wait(3)
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/leds_data.gif"><br>
</div>

**Change Color**

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/colored_leds_data.gif"><br>
</div>

#### Read Data

```python
from futurevision import iphone
iphone=iphone.iPhone()
while True:
    data=iphone.read_data()
    print(data)
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/read_data.gif"><br>
</div>

#### Send Data

```python
from futurevision import iphone
iphone=iphone.iPhone()
while True:
    iphone.send_data("Future Vision")
```

<div align="center">
  <img src="/Users/ali/Desktop/futurevision/README-IMAGE/send_data.gif"><br>
</div>

## License

[MIT](https://github.com/AliEdis/futurevision/blob/main/LICENSE)
