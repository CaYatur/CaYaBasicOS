# CYX Uygulama Geliştirme Rehberi

Bu rehber, CaYaBasicOS içinde çalışan `.CYX` uygulamaları yazmak için
hazırlanmıştır. Amaç sadece komutları listelemek değil; dosya gezgininden
açılabilen, penceresi düzgün görünen, fare/klavye ile kullanılabilen ve
hatası kolay ayıklanabilen uygulamalar geliştirmeyi anlatmaktır.

CYX küçük ve bilinçli olarak sınırlı bir script dilidir. Uygulamalar UEFI modda
dosya gezgininden açılır, CaYaBasicOS içindeki CYX yorumlayıcısı tarafından
çalıştırılır ve kendi pencereleri içinde çizim, buton, etiket, input, klavye
olayı ve basit dosya işlemleri yapabilir.

## Hızlı başlangıç

Bir CYX uygulaması yazmak için:

1. `assets/cyx` klasörüne yeni bir `.CYX` dosyası ekleyin.
2. Dosyada en az bir `ON START ... END` bloğu oluşturun.
3. `WINDOW` ile pencere boyutunu belirleyin.
4. Gerekli buton, etiket, input ve çizimleri ekleyin.
5. `.\build.ps1` çalıştırarak ISO'yu yeniden üretin.
6. CaYaBasicOS'u UEFI modda açın, dosya gezgininden `.CYX` dosyasını bulun.
7. Dosyayı açınca **ÇALIŞTIR** veya **DÜZENLE** seçeneğini kullanın.

En küçük çalışan örnek:

```text
ON START
  WINDOW 240 120 "Merhaba"
  FILL NAVY
  LABEL baslik 16 18 YELLOW "Merhaba CYX"
  BUTTON kapat 16 58 96 28 "KAPAT"
END

ON CLICK kapat
  EXIT
END
```

## Dosyanın ISO'ya eklenmesi

Build scripti `assets/cyx` içindeki `.cyx` ve `.txt` dosyalarını UEFI FAT
imajına kopyalar. Dosya adı FAT 8.3 formatına çevrilir; bu yüzden kısa ve
büyük harfli ad kullanmak en sorunsuz yoldur:

```text
HESAP.CYX
KALEM.CYX
DOSYA.CYX
PINPONG.CYX
```

Yeni uygulama örneği:

```text
assets/cyx/NOTLAR.CYX
```

Build:

```powershell
.\build.ps1
```

Çıktı ISO:

```text
dist\CaYaBasicOS.iso
```

## Çalıştırma ve düzenleme akışı

Dosya gezgininde bir `.CYX` dosyası açıldığında CaYaBasicOS bir seçim penceresi
gösterir:

| Seçenek | Kısayol | Açıklama |
| --- | --- | --- |
| ÇALIŞTIR | `C` veya `Enter` | Script yorumlanır ve uygulama penceresi açılır. |
| DÜZENLE | `D` | Script not defteri düzenleme modunda açılır. |
| Kapat | `ESC` | Seçim penceresi kapatılır. |

Uygulama çalışırken `ESC` uygulamayı kapatır. Script hataya düşerse pencerenin
altında kırmızı hata seridi görünür. Hata seridinde `HATA SAT N : MESAJ`
biçiminde satır numarası ve hata nedeni yazar. Hata varken `E` tuşu kaynağı not
defteri düzenleme modunda açar.

## Dilin temel kuralları

- Her satır tek komuttur.
- Boş satırlar geçerlidir.
- Yorum satırı `#` ile başlamalıdır.
- Satır sonu yorum yoktur; `BUTTON b 0 0 80 24 "OK" # yorum` yazmayın.
- Komut adları büyük/küçük harfe duyarlı değildir, ama büyük harf kullanmak
  okunabilirliği artırır.
- Değişken, etiket, buton, label ve input ID'leri pratikte birebir karşılaştırılır;
  aynı yazımı tutarlı kullanın.
- String değerler çift tırnak içine yazılır.
- Bir satırda en fazla 8 token okunur. Uzun komutları sade tutun.
- Kod `ON ... END` blokları içinde olmalıdır.
- İç içe `ON` bloğu yoktur.

Örnek:

```text
# Bu geçerli bir yorumdur.
ON START
  WINDOW 320 180 "Ornek"
  SET $puan 0
  LABEL skor 12 12 WHITE "PUAN: 0"
END
```

## Olay modeli

CYX uygulamaları olay bloklarıyla çalışır. Yorumlayıcı, ilgili olay gerçekleştiği
zaman uygun `ON` bloğunu çalıştırır.

| Olay | Ne zaman çalışır? |
| --- | --- |
| `ON START` | Uygulama açıldığında bir kez çalışır. Genellikle `WINDOW`, ilk çizim ve değişken hazırlığı burada yapılır. |
| `ON CLICK id` | `id` değerine sahip butona tıklanınca çalışır. |
| `ON KEY KEYNAME` | Belirli tuşa basılınca çalışır. Örnek: `ON KEY R`, `ON KEY ENTER`. |
| `ON KEY` | Her tuş olayında çalışır. Basılan tuş `@key` ile okunabilir. |
| `ON DRAG` | Mouse sol tuşu basılıyken canvas üzerinde her kare çalışır. |
| `ON MOVE` | Mouse canvas üzerindeyken ve sol tuş basılı değilken çalışır. |
| `ON TICK` | Yaklaşık düzenli aralıklarla çalışır. Animasyon ve oyun döngüsü için kullanılır. |

Her `ON` bloğu `END` ile kapatılır:

```text
ON KEY R
  PRINT "Sifirlandi"
END
```

## Pencere ve koordinatlar

`WINDOW W H "Başlık"` uygulamanın canvas boyutunu belirler. Runtime boyutu şu
aralıklara sıkıştırır:

| Değer | En küçük | En büyük |
| --- | ---: | ---: |
| Genişlik | 120 | 760 |
| Yükseklik | 80 | 520 |

Koordinat sistemi canvas içindedir:

- `x = 0`, sol kenardır.
- `y = 0`, üst kenardır.
- Sağ alt sınır yaklaşık `@width - 1`, `@height - 1` değerleridir.
- Buton, label, input ve çizim komutları bu canvas koordinatlarını kullanır.

Pencere kabuğu, başlık çubuğu ve hata/durum alanı runtime tarafından çizilir.
Siz sadece canvas içeriğini tasarlarsınız.

## Özel değişkenler

Özel değişkenler runtime tarafından sağlanır ve salt okunur kabul edilmelidir.

| Değişken | Tür | Açıklama |
| --- | --- | --- |
| `@x` | sayı | Mouse'un canvas içindeki x konumu. |
| `@y` | sayı | Mouse'un canvas içindeki y konumu. |
| `@prevx` | sayı | Önceki drag noktasının x konumu. Çizim uygulamalarında çizgi sürekliliği için kullanılır. |
| `@prevy` | sayı | Önceki drag noktasının y konumu. |
| `@key` | metin | Son basılan tuşun adı. |
| `@click_btn` | metin | Son tıklanan buton ID'si. |
| `@tick` | sayı | `ON TICK` sayacı. Basit zamanlama ve rastgelelik için kullanılabilir. |
| `@width` | sayı | Canvas genişliği. |
| `@height` | sayı | Canvas yüksekliği. |

Desteklenen yaygın tuş adları:

```text
UP DOWN LEFT RIGHT ESC SPACE ENTER A..Z 0..9 + - * / =
```

Harf tuşları büyük harfe çevrilir. Bu yüzden `ON KEY R` yazın, `ON KEY r`
yazmayın.

## Değişkenler ve veri türleri

Kullanıcı değişkenleri `$` ile başlar:

```text
SET $puan 0
SETSTR $ad "CaYa"
```

CYX iki pratik değer türüyle çalışır:

| Tür | Komut | Açıklama |
| --- | --- | --- |
| Tam sayı | `SET`, `ADD`, `SUB`, `MUL`, `DIV`, `MOD`, `TOINT` | Oyun durumu, koordinat, skor ve sayaçlar için kullanılır. |
| Metin | `SETSTR`, `APPEND`, `TOSTR`, `GET_INPUT` | Etiket, input ve durum mesajları için kullanılır. |

Değişken örnekleri:

```text
SET $skor 0
ADD $skor 1

TOSTR $skor_text $skor
SETSTR $msg "SKOR: "
APPEND $msg $skor_text
SET_LABEL skor $msg
```

Bir sayı değişkeni metin beklenen yerde kullanılırsa metne çevrilir. Bir metin
değişkeni sayı beklenen yerde kullanılırsa sayıya parse edilmeye çalışılır.

## Renkler

Renk parametresi üç şekilde verilebilir:

```text
FILL 0
FILL NAVY
FILL 0x102040
```

Hazır renk adları:

```text
BLACK NAVY BLUE GREEN DGREEN CYAN RED MAGENTA
BROWN LGRAY DGRAY LBLUE LGREEN LCYAN YELLOW WHITE
```

`0..15` arası sayısal palette renk de kullanılabilir. `0xRRGGBB` biçimindeki
renkler en yakın palet rengine çevrilir.

## Pencere ve durum komutları

| Komut | Açıklama |
| --- | --- |
| `WINDOW W H "Başlık"` | Canvas boyutunu ve pencere başlığını belirler. Genellikle `ON START` içinde kullanılır. |
| `TITLE "Yeni Başlık"` | Pencere başlığını değiştirir. |
| `PRINT "mesaj"` | Pencerenin alt durum alanına mesaj yazar. |
| `PRINT $var` | Değişken değerini durum alanına yazar. |
| `EXIT` | Uygulamayı kapatır. |

Örnek:

```text
ON CLICK kaydet
  PRINT "Kaydedildi"
END
```

## Çizim komutları

Çizim komutları canvas üzerinde kalıcı bir çizim listesine eklenir. Her render
anında bu liste yeniden oynatılır.

| Komut | Açıklama |
| --- | --- |
| `FILL renk` | Tüm canvas'ı doldurur ve önceki çizim listesini temizler. |
| `CLEAR` | `FILL BLACK` ile aynı pratik etkiye sahiptir. |
| `PIXEL X Y renk` | Tek piksel çizer. |
| `LINE X1 Y1 X2 Y2 renk` | Çizgi çizer. |
| `RECT X Y W H renk` | Çerçeve dikdörtgen çizer. |
| `FILLRECT X Y W H renk` | Dolu dikdörtgen çizer. |
| `TEXT X Y renk "metin"` | Canvas'a kısa metin çizer. Metin 15 karakter civarında tutulmalıdır. |

Çizim uygulaması için drag örneği:

```text
ON DRAG
  LINE @prevx @prevy @x @y WHITE
END
```

Performans notu: Çok sayıda `PIXEL` biriktirmek yerine `LINE` veya küçük
`FILLRECT` kullanın. Ekranı tamamen yenilemeniz gerekiyorsa önce `FILL` veya
`CLEAR` çağırın; bu çizim listesini sıfırlar.

## Arayüz öğeleri

CYX üç temel UI öğesi sunar: `BUTTON`, `LABEL`, `INPUT`.

| Komut | Açıklama |
| --- | --- |
| `BUTTON ID X Y W H "metin"` | Tıklanabilir buton oluşturur veya aynı ID'li butonu günceller. |
| `LABEL ID X Y renk "metin"` | Güncellenebilir yazı alanı oluşturur veya aynı ID'li label'ı günceller. |
| `INPUT ID X Y W H` | Klavye ile yazı girilebilen alan oluşturur veya aynı ID'li input'u günceller. |
| `SET_LABEL ID metin` | Label metnini değiştirir. |
| `SET_INPUT ID metin` | Input içeriğini değiştirir. |
| `GET_INPUT ID $var` | Input içeriğini metin değişkenine aktarır. |

Buton örneği:

```text
ON START
  WINDOW 260 140 "Sayac"
  LABEL sayac 16 16 YELLOW "0"
  BUTTON artir 16 52 90 28 "ARTIR"
END

ON CLICK artir
  ADD $n 1
  SET_LABEL sayac $n
END
```

Input örneği:

```text
ON START
  WINDOW 360 150 "Selam"
  INPUT ad 16 38 180 24
  BUTTON yaz 210 38 90 24 "YAZ"
  LABEL sonuc 16 80 LCYAN "Ad bekleniyor"
END

ON CLICK yaz
  GET_INPUT ad $isim
  SETSTR $msg "Merhaba "
  APPEND $msg $isim
  SET_LABEL sonuc $msg
END
```

## Matematik komutları

| Komut | Açıklama |
| --- | --- |
| `SET $var değer` | Tam sayı atar. |
| `ADD $var değer` | Değişkene değer ekler. |
| `SUB $var değer` | Değişkenden değer çıkarır. |
| `MUL $var değer` | Değişkeni değer ile çarpar. |
| `DIV $var değer` | Değişkeni değere böler. Sıfıra bölme hata üretir. |
| `MOD $var değer` | Kalan alır. Sıfır ile mod hata üretir. |
| `TOSTR $dst değer` | Sayıyı metne çevirir. |
| `TOINT $dst metin` | Metni sayıya çevirir. |

Koordinat sınırlama örneği:

```text
SET $x @x
IF $x < 0 GOTO xmin
IF $x > 300 GOTO xmax
GOTO done
:xmin
SET $x 0
GOTO done
:xmax
SET $x 300
:done
```

## Kontrol akışı

CYX'te fonksiyon yoktur. Akış, etiket ve `GOTO` ile yönetilir.

| Komut | Açıklama |
| --- | --- |
| `:etiket` | Atlama hedefi tanımlar. |
| `GOTO etiket` | Etikete atlar. |
| `IF a OP b GOTO etiket` | Şart doğruysa etikete atlar. |

Desteklenen karşılaştırma operatörleri:

```text
== != < > <= >=
```

Örnek:

```text
ADD $can 1
IF $can >= 100 GOTO dolu
GOTO devam
:dolu
SET $can 100
:devam
```

Etiketleri aynı olay bloğu içinde benzersiz tutun. Yorumlayıcı önce aktif blok
içinde arar; benzer adları farklı bloklarda kullanmak mümkün olsa da uzun
uygulamalarda daha açık adlar seçmek hata riskini azaltır.

## Dosya sistemi komutları

Dosya sistemi komutları UEFI tarafında görünen mantıksal birimler üzerinde
çalışır. Birim indeksleri `0..N-1` aralığındadır.

| Komut | Açıklama |
| --- | --- |
| `LIST_DISKS $count` | Görünen mantıksal birim sayısını `$count` içine yazar. |
| `COPY srcDisk "src" dstDisk "dst"` | Dosya kopyalar. |
| `MOVE srcDisk "src" dstDisk "dst"` | Dosya taşır. |
| `DELETE disk "path"` | Dosyayı siler. |

Yollar `\` veya `/` kullanabilir; runtime bunları normalize eder.

Örnek:

```text
ON CLICK liste
  LIST_DISKS $cnt
  SETSTR $msg "Birim sayisi: "
  APPEND $msg $cnt
  SET_LABEL durum $msg
END

ON CLICK kopyala
  COPY 0 "\CAYADEV.SVG" 1 "\CAYADEV.SVG"
  PRINT "Kopyalama tamamlandi"
END
```

Dosya yazma/silme işlemlerinde hedef birimin yazılabilir olduğundan emin olun.
Hata olursa uygulama hata seridine düşer.

## Güzel uygulama tasarlama

CYX sınırlı bir runtime olduğu için iyi uygulama yazmak çoğunlukla düzenli
state yönetimi ve sade ekran çizimiyle ilgilidir.

Pratik öneriler:

- `ON START` içinde tüm başlangıç state'ini açıkça kurun.
- Skor, mod, seçim, koordinat gibi değerleri `$` değişkenlerinde tutun.
- Ekran sürekli değişiyorsa `ON TICK` içinde önce `FILL` veya `CLEAR` çağırıp
  sahneyi yeniden çizin.
- Sadece küçük bir alan değişiyorsa ilgili `LABEL` veya `BUTTON` öğesini
  güncelleyin; tüm canvas'ı temizlemek gerekmeyebilir.
- Buton ID'lerini kısa ama anlamlı seçin: `btnsave`, `btnclear`, `tgt`, `ok`.
- Metinleri kısa tutun. Buton ve label metinleri küçük pencerelerde taşabilir.
- Oyunlarda hızları ve koordinatları değişkenlerde tutun: `$vx`, `$vy`, `$x`,
  `$y`, `$score`.
- `ON MOVE` fare kontrollü uygulamalar için, `ON TICK` zaman kontrollü oyunlar
  için daha uygundur.
- Çok uzun `GOTO` zincirleri yerine her olay bloğunu küçük tutun.
- Dosya işlemlerinde önce `LIST_DISKS` ile birim sayısını gösteren bir buton
  eklemek kullanıcıya yardımcı olur.

## Animasyon ve oyun döngüsü

Basit animasyonlar için önerilen yapı:

```text
ON START
  WINDOW 320 200 "Top"
  SET $x 20
  SET $y 80
  SET $vx 4
END

ON TICK
  ADD $x $vx
  IF $x < 0 GOTO sol
  IF $x > 300 GOTO sag
  GOTO draw
  :sol
  SET $x 0
  SET $vx 4
  GOTO draw
  :sag
  SET $x 300
  SET $vx 0
  SUB $vx 4
  :draw
  FILL BLACK
  FILLRECT $x $y 16 16 YELLOW
END
```

Pinpon/Pong tarzı uygulamalar için `PINPONG.CYX` iyi bir referanstır:

- Oyuncu raketi `ON MOVE`, `ON KEY W`, `ON KEY S`, `ON KEY UP`, `ON KEY DOWN`
  ile kontrol edilir.
- Top ve bilgisayar raketi `ON TICK` içinde güncellenir.
- Skor değişince `SET_LABEL` ile skor etiketleri güncellenir.
- `SPACE` oyunu duraklatır, `R` oyunu sıfırlar.

## Hata ayıklama

Hata alırsanız önce hata seridindeki satır numarasına bakın. Satır numarası
1 tabanlıdır.

Yaygın hatalar:

| Hata | Muhtemel neden |
| --- | --- |
| `CODE OUTSIDE HANDLER` | Komut `ON ... END` bloğu dışında kalmıştır. |
| `MISSING END` | Bir `ON` bloğu `END` ile kapatılmamıştır. |
| `UNKNOWN COMMAND` | Komut adı yanlış yazılmıştır. |
| `UNKNOWN LABEL` | `GOTO` veya `IF ... GOTO` hedefi bulunamamıştır. |
| `UNKNOWN LABEL` / `UNKNOWN INPUT` | Güncellenmek istenen ID daha önce oluşturulmamıştır. |
| `DIV BY ZERO` / `MOD BY ZERO` | Bölme veya mod işlemi sıfırla yapılmıştır. |
| `TOO MANY VARS` | 48 değişken sınırı aşılmıştır. |
| `TOO MANY BUTTONS` | 24 buton sınırı aşılmıştır. |
| `TOO MANY LABELS` | 24 label sınırı aşılmıştır. |
| `TOO MANY INPUTS` | 6 input sınırı aşılmıştır. |
| `INFINITE LOOP` | Aynı olay bloğu tek dispatch içinde çok uzun çalışmıştır. |

Debug için `PRINT` kullanın:

```text
PRINT "Buraya geldi"
PRINT $x
```

Bir değeri label'a da yazabilirsiniz:

```text
SET_LABEL debug $x
```

## Runtime sınırları

| Sınır | Değer |
| --- | ---: |
| Kaynak boyutu | 16 KB |
| Satır sayısı | 512 |
| Satır başına token | 8 |
| Token uzunluğu | 80 byte |
| Değişken sayısı | 48 |
| Değişken adı uzunluğu | 15 karakter civarı |
| Metin değişkeni uzunluğu | 63 karakter civarı |
| Olay bloğu sayısı | 48 |
| Etiket sayısı | 96 |
| Buton sayısı | 24 |
| Label sayısı | 24 |
| Input sayısı | 6 |
| Çizim işlemi sayısı | 1024 |
| Tek dispatch çalışma bütçesi | 50000 satır |

`FILL` ve `CLEAR` çizim işlemi listesini sıfırladığı için animasyonlarda
1024 çizim işlemi sınırına takılmayı önler.

## Komut referansı

### Olaylar

```text
ON START
ON CLICK buttonId
ON KEY KEYNAME
ON KEY
ON DRAG
ON MOVE
ON TICK
END
```

### Pencere ve durum

```text
WINDOW W H "Baslik"
TITLE "Yeni Baslik"
PRINT "mesaj"
PRINT $degisken
EXIT
```

### Çizim

```text
FILL renk
CLEAR
PIXEL X Y renk
LINE X1 Y1 X2 Y2 renk
RECT X Y W H renk
FILLRECT X Y W H renk
TEXT X Y renk "metin"
```

### UI

```text
BUTTON ID X Y W H "metin"
LABEL ID X Y renk "metin"
INPUT ID X Y W H
SET_LABEL ID metin
SET_INPUT ID metin
GET_INPUT ID $degisken
```

### Değişken ve matematik

```text
SET $var değer
SETSTR $var "metin"
APPEND $var "ek"
ADD $var değer
SUB $var değer
MUL $var değer
DIV $var değer
MOD $var değer
TOSTR $dst değer
TOINT $dst metin
```

### Kontrol akışı

```text
:etiket
GOTO etiket
IF a == b GOTO etiket
IF a != b GOTO etiket
IF a < b GOTO etiket
IF a > b GOTO etiket
IF a <= b GOTO etiket
IF a >= b GOTO etiket
```

### Dosya sistemi

```text
LIST_DISKS $count
COPY srcDisk "src" dstDisk "dst"
MOVE srcDisk "src" dstDisk "dst"
DELETE disk "path"
```

## Tam örnek: sayaç uygulaması

Bu örnek buton, label, değişken, metin üretme ve klavye olaylarını birlikte
kullanır.

```text
# SAYAC.CYX

ON START
  WINDOW 300 170 "Sayac"
  FILL NAVY
  SET $n 0
  LABEL baslik 16 16 YELLOW "BASIT SAYAC"
  LABEL deger  16 46 LCYAN  "0"
  BUTTON artir 16 82 80 28 "ARTIR"
  BUTTON azalt 106 82 80 28 "AZALT"
  BUTTON sifir 196 82 80 28 "SIFIR"
  LABEL yardim 16 128 LGRAY "Klavye: A artir, Z azalt, R sifir"
END

ON CLICK artir
  ADD $n 1
  SET_LABEL deger $n
  PRINT "Arttirildi"
END

ON CLICK azalt
  SUB $n 1
  SET_LABEL deger $n
  PRINT "Azaltildi"
END

ON CLICK sifir
  SET $n 0
  SET_LABEL deger $n
  PRINT "Sifirlandi"
END

ON KEY A
  ADD $n 1
  SET_LABEL deger $n
END

ON KEY Z
  SUB $n 1
  SET_LABEL deger $n
END

ON KEY R
  SET $n 0
  SET_LABEL deger $n
END
```

## Mevcut örneklerden öğrenme

Depodaki örnekler farklı uygulama tiplerini gösterir:

| Dosya | Öğrenilecek konu |
| --- | --- |
| `assets/cyx/HESAP.CYX` | Çok sayıda buton, hesap durumu, klavye ve fareyi aynı iş akışına bağlama. |
| `assets/cyx/KALEM.CYX` | `ON DRAG`, `@prevx/@prevy`, çizim rengi ve fırça kalınlığı. |
| `assets/cyx/DOSYA.CYX` | `INPUT`, `GET_INPUT`, `COPY`, `MOVE`, `DELETE`, `LIST_DISKS`. |
| `assets/cyx/OYUN.CYX` | Hedef butonunu dinamik konumlandırma, skor ve `@tick` ile basit rastgelelik. |
| `assets/cyx/PINPONG.CYX` | `ON TICK` oyun döngüsü, çarpışma, skor, duraklatma ve reset akışı. |

Yeni bir uygulama yazarken önce bu örneklerden en yakın olanını kopyalayıp
küçük değişikliklerle ilerlemek en hızlı yoldur.
