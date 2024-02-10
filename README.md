
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
