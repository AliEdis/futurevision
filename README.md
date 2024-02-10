
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

count değişkeni kaç adet yüz olduğunu döndürür.

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
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/count_faces.gif?raw=true"><br>
</div>

<br>

##### Anlık Yüz Sayaçı Çizimini Devre Dışı Bırakma

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

name değişkeni tespit ettiğini rengin ismini döndürür.
list değişkeni tespit edilen rengin RGB oranlarını R G B sırası ile döndürür.

```sh
blue [844.5, 415.5, 173812.0]
red [600.5, 311.0, 530.5]
green [0, 772.0, 0]
```

Threshold değeri varsayılan olarak 1000 olarak ayarlanmıştır. İhtiyacınıza göre bu değeri düşürebilir veya yükseltebilirsiniz.

```python
img,name,list=vision.detect_colors(img,threshold=500)
```

<div align="center">
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/color.gif?raw=true"><br>
</div>

<br>

##### Çizim Rengini Değiştirme

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
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/custom_color.gif?raw=true"><br>
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

Yüz tanımanın çalışabilmesi için yüz tanıma modelini indirmelisiniz.[shape_predictor_68_face_landmarks.dat](https://github.com/davisking/dlib-models/blob/master/shape_predictor_68_face_landmarks.dat.bz2)

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

EAR değişkeni gözün kapalılık oranını döndürür.
status değişkeni gözün kapalı ve açık olma durumunu döndürür.
time değişkeni gözün kaç saniye kapalı olduğunu döndürür.

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

Threshold değeri varsayılan olarak 0.15 olarak ayarlanmıştır. İhtiyacınıza göre bu değeri düşürebilir veya yükseltebilirsiniz.

```python
img,EAR,status,time=vision.detect_blink(img,threshold=0.20)
```

<div align="center">
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/eye_blink.gif?raw=true"><br>
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

#### Vücut Tespiti ve Analizi

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

left değişkeni sol kolunuzun omzunuza yakınlık oranını döndürür.
right değişkeni sol kolunuzun omzunuza yakınlık oranını döndürür.

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
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/body.gif?raw=true"><br>
</div>

<br>

##### Vücut Çizimini Devre Dışı Bırakma

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
    img,name=vision.detect_objects(img)
    print(name)
    cv2.imshow("Future Vision",img)
    cv2.waitKey(1)
```

name değişkeni tespit edilen objenin ismini döndürür.

```sh
person
person
person
person
person
person
```

<div align="center">
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/object.gif?raw=true"><br>
</div>

<br>

#### Yüz Tanıma

Yüz tanımanın çalışabilmesi için yüz tanıma modelini indirmelisiniz.[shape_predictor_68_face_landmarks.dat](https://github.com/davisking/dlib-models/blob/master/shape_predictor_68_face_landmarks.dat.bz2)

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
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/face_rec.gif?raw=true"><br>
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
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/1.PNG">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/2.PNG">
</div>

<br>

<p style="text-align: center;"><b>Arama çubuğunda Darwin Future Vision Aratın</b></p> 
<div align="center">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/3.PNG">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/4.PNG">
</div>

<br>

<p style="text-align: center;"><b>Uygulama Sayfasına Girin</b></p>

<div align="center">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/5.PNG">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/6.PNG">
</div>
<br>

<p style="text-align: center;"><b>Uygulamayı İndirin</b></p> 
<div align="center">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/7.PNG">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/8.PNG">
</div>

#### Uygulama Bölümleri ve Örnek Kodlar

<div align="center">
<img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/9.PNG"><br>
</div>

#### Settings

Settings bölümünde, uygulamanın yazacağınız Python koduyla haberleşebilmesi için Python kodunuzun size vereceği IP adresi ve port bilgilerini kaydetmelisiniz.

<div align="center">
<img style="width:700px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/ip_result_terminal.PNG"><br>
</div>
<div align="center">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/10.PNG">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/11.PNG">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/12.PNG"><br>
</div>

#### HWC

Bu bölümde, **Future Vision** kütüphanesinin **iPhone** modülü ile yazacağınız kodlara göre iPhone telefonunuzun gözlemsel donanımlarını kontrol etme imkanını sunar. **flash_on()** ve **flash_off()** fonksiyonlarıyla Flaşı, **screen_brightness(value)** fonksiyonuyla Ekran Parlaklığını, **volume_intensity(value)** fonksiyonuyla Hoparlörün Ses Şiddetini kontrol etmenizi sağlar.

<div align="center">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/hwc.PNG">
</div>

#### CwH

Bu bölümde **Future Vision** kütüphanesinin **iPhone** modülü ile yazacağınız kodlara göre iPhone telefonunuzun gözlemsel donanım bilgilerini python kodunuza bir liste olarak gönderir. Bu liste verisini **read_data()** fonksiyonu ile okuyabilirsiniz veriler arasında Ekran parlaklığı değeri Ses Şiddeti Değeri ve Telefonunuzun hangi ses tuşuna basıldığının verisini yer almaktadır örnek veri listesi:

```sh
['25', '70', 'Down']
['25', '75', 'Up']
```

<div align="center">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/cwh.PNG">
</div>

#### LEDs

Bu bölümde **Future Vision** kütüphanesinin **iPhone** modülü ile yazacağınız kodlara göre uygulama içerisinde bulunan 5 adet led grafiğini kontrol etme imkanı sunar ve 5 adet ledin renklerini yeşil, mavi ve kirmizi olarak değiştirebilirsiniz. Uygulamadaki ledleri açmak için **led_on(pin)** kapatmak için **led_off(pin)** fonksiyonlarını kullanabilirsiniz.

<div align="center">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/leds.PNG">
</div>

#### SEND&SHOW

Bu bölümde **future vision** kütüphanesinin **iPhone** modülü ile yazacağınız kodlara göre uygulama içerisindeki input'a gireceğiniz verileri bilgisayarınıza gönderebilir veya bilgisayarınızdan mobil uygulamaya veri gönderebilirsiniz. mobil uygulamaya veri göndermek için **send_data(data)** mobil uygulamanın göndereceği verileri okumak için **read_data()** fonksiyonlarını kullanabilirsiniz.

<div align="center">
  <img style="width:300px;" src="https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/sendshow.PNG">
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
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/flash_hwc.gif?raw=true"><br>
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
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/sb_hwc.gif?raw=true"><br>
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
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/si_hwc.gif?raw=true"><br>
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

**Listenin index sıralamasındaki ilk index ekran parlaklığı, ikinci index ses şiddeti, üçüncü index telefonun hangi ses yükseltme tuşuna basıldığının bilgilerini temsil etmektedir**

```sh
['25', '70', 'Down']
['25', '75', 'Up']
```

<div align="center">
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/cwh_data.gif?raw=true"><br>
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
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/leds_data.gif?raw=true"><br>
</div>

**Change Color**

<div align="center">
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/colored_leds_data.gif?raw=true"><br>
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
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/read_data.gif?raw=true"><br>
</div>

#### Send Data

```python
from futurevision import iphone
iphone=iphone.iPhone()
while True:
    iphone.send_data("Future Vision")
```

<div align="center">
  <img src="https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/send_data.gif?raw=true"><br>
</div>

![Demo File](https://github.com/AliEdis/futurevision/blob/main/README-IMAGE/send_data.gif?raw=true)


## Modüllerin birlikte kullanımlarının anlatımı için:

<a href="https://www.youtube.com/channel/UCZwR4LvkgdLl-T0cAf19b7A" target="_blank">
  <img src="https://upload.wikimedia.org/wikipedia/commons/e/ef/Youtube_logo.png" alt="YouTube Logo" width="150" height="100">
</a>



## License

[MIT](https://raw.githubusercontent.com/AliEdis/futurevision/main/README-IMAGE/LICENSE)
