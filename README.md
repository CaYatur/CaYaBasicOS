# CaYaBasicOS

CaYaBasicOS, dışarıdan runtime kütüphane kullanmadan geliştirilen küçük bir
bare-metal işletim sistemi prototipidir. Proje, tek bir hibrit ISO üretir ve bu
ISO hem Legacy BIOS hem de UEFI x64 sistemlerde önyüklenebilir.

Bu proje genel amaçlı bir işletim sistemi olmaktan çok; donanım algılama, disk
inceleme, basit dosya gezgini, terminal, grafik arayüz ve gömülü mini uygulama
çalıştırma deneyleri için hazırlanmış düşük seviyeli bir kontrol ortamıdır.

## Öne çıkanlar

- Hibrit ISO: Legacy BIOS ve UEFI x64 önyükleme desteği.
- Özel BIOS boot sector: GRUB, Limine veya hazır bir OS bootloader kullanmaz.
- UEFI uygulaması: `/EFI/BOOT/BOOTX64.EFI` ve UEFI El Torito boot girdisi.
- BIOS tarafında 320x200 VGA Mode 13h grafik arayüz.
- UEFI tarafında GOP framebuffer üzerinde double-buffer grafik arayüz.
- CaYaDev koyu lacivert/kırmızı paletine uygun sade UEFI masaüstü görünümü.
- Klavye, PS/2 fare, UEFI Simple Pointer ve Absolute Pointer girişleri.
- Fare, touchpad ve dokunmatik ekran için hotplug sonrasında giriş yenileme.
- CaYaDev logolu grafik hata ekranı.
- CPU, bellek, depolama, ekran ve dosya sistemi bilgilerini gösteren sayfalar.
- UEFI dosya gezgini, çoklu pencere, sürüklenebilir pencere başlıkları ve seçim
  akışı.
- UEFI terminali: `dir`, `cd`, `copy`, `move`, `del`, `open`, `clear`, `help`,
  `reboot` ve `shutdown` komutları.
- Gömülü CYX uygulama runtime'ı: küçük `.cyx` script dosyalarını çalıştırma veya
  düzenleme.
- ISO9660/El Torito yazımı için PowerShell içinde yazılmış basit ISO üreticisi.

## Mimari

CaYaBasicOS iki ayrı önyükleme yolu içerir:

| Yol | Dosyalar | Açıklama |
| --- | --- | --- |
| Legacy BIOS | `src/boot/boot.asm`, `src/kernel/stage16.asm`, `src/kernel/kernel.c` | Boot sector, 16-bit hazırlık kodu ve 32-bit freestanding kernel. |
| UEFI x64 | `src/uefi/bootx64.c` | Freestanding UEFI uygulaması, GOP grafik arayüzü, dosya gezgini, terminal ve CYX runtime. |

Build süreci `build.ps1` tarafından yönetilir. Script; assembly ve C
kaynaklarını derler, BIOS boot imajını üretir, UEFI FAT imajını hazırlar ve
sonunda hibrit ISO dosyasını oluşturur.

## Depo yapısı

```text
.
|-- assets/
|   |-- CaYaDev.svg
|   |-- Consolas.ttf
|   `-- cyx/
|       |-- HESAP.CYX
|       |-- KALEM.CYX
|       |-- DOSYA.CYX
|       |-- OYUN.CYX
|       |-- PINPONG.CYX
|       `-- CYX_DOC.TXT
|-- drivers/
|   |-- README.md
|   `-- ntfs_x64.efi
|-- src/
|   |-- boot/
|   |-- kernel/
|   `-- uefi/
|-- build.ps1
|-- build.bat
`-- README.md
```

`build/` ve `dist/` klasörleri derleme çıktısıdır. Kaynak depoya eklenmeleri
gerekmez.

## Gereksinimler

Runtime tarafında harici C runtime veya işletim sistemi kütüphanesi
kullanılmaz. Kaynakları ISO'ya çevirmek için aşağıdaki araçlar gerekir:

- NASM
- Tercihen `i686-elf-gcc`, `i686-elf-ld`, `i686-elf-objcopy`
- Alternatif olarak `clang`, `ld.lld`, `llvm-objcopy`
- UEFI uygulaması için `clang` ve `lld-link`
- Test için opsiyonel: `qemu-system-i386`

Araçlar `PATH` içinde bulunmazsa `build.ps1` açık bir hata mesajıyla durur.

## Derleme

PowerShell ile:

```powershell
.\build.ps1
```

Windows üzerinde çift tıklayarak derlemek için:

```text
build.bat
```

Varsayılan çıktı:

```text
dist\CaYaBasicOS.iso
build\boot.img
build\uefi.img
build\BOOTX64.EFI
```

Farklı ISO yolu vermek için:

```powershell
.\build.ps1 -IsoPath "dist\test.iso"
```

QEMU kuruluysa derlemeden sonra çalıştırmak için:

```powershell
.\build.ps1 -Run
```

## Kullanım

CaYaBasicOS açıldığında sol tarafta sayfa menüsü, sağ tarafta seçili sayfanın
içeriği görünür. UEFI modda grafik arayüz daha geniş çözünürlükte çalışır;
BIOS modda ise 320x200 VGA arayüz kullanılır.

Temel kısayollar:

| Tuş | İşlev |
| --- | --- |
| `1..5` / `1..6` | Sayfa değiştirme. BIOS modda 5, UEFI modda 6 sayfa vardır. |
| `Up` / `Down` | Aktif listede veya sayfada seçim. |
| `Tab` | Dosyalar sayfasında aktif gezgin penceresini değiştirir. |
| `N` | Yeni gezgin penceresi açar. |
| `T` | Terminal penceresini açar. |
| `V` | Aktif dosya penceresini sıradaki UEFI dosya birimine alır. |
| `R` | Giriş cihazlarını, diskleri ve UEFI dosya birimlerini yeniler. |
| `Enter` | Seçili klasöre girer veya seçili dosyayı açar. |
| `Backspace` | Üst klasöre çıkar. |
| `C` | Seçili normal dosyayı diğer pencereye kopyalar. |
| `M` | Seçili normal dosyayı diğer pencereye taşır. |
| `Delete` | Seçili dosya veya boş klasörü silmeyi dener. |

Fare veya dokunmatik giriş çalışıyorsa menüler ve dosya satırları doğrudan
tıklanabilir. Gezgin ve terminal pencereleri başlık çubuğundan sürüklenebilir.
Dosya satırında ilk tıklama seçim, ikinci tıklama açma işlemidir.

## Terminal örnekleri

UEFI moddaki terminal, firmware veya native dosya sistemi katmanından görünen
birimler üzerinde çalışır:

```text
dir
cd VOL0:\EFI
copy VOL0:\CAYADEV.SVG VOL1:\CAYADEV.SVG
move VOL0:\A.TXT VOL1:\A.TXT
del VOL1:\A.TXT
open VOL0:\CAYADEV.SVG
clear
```

## CYX uygulamaları

CYX, CaYaBasicOS içine gömülü küçük uygulamalar yazmak için kullanılan basit
script dilidir. `.CYX` dosyası dosya gezgininden açıldığında iki seçenek çıkar:

- **ÇALIŞTIR:** Script yorumlanır ve uygulama penceresi açılır.
- **DÜZENLE:** Script not defteri düzenleme modunda açılır. `ESC` ile
  kaydedilip kapatılır.

Çalışma sırasında hata oluşursa pencere altında `HATA SAT N : MESAJ` biçiminde
bir hata seridi gösterilir. `E` tuşu hatalı kaynağı not defterinde açar.

ISO içine gömülen örnekler:

| Dosya | Açıklama |
| --- | --- |
| `HESAP.CYX` | Basit hesap makinesi. `SET`, `ADD`, `IF GOTO` ve `SET_LABEL` örnekleri içerir. |
| `KALEM.CYX` | Basit çizim uygulaması. `ON DRAG`, `FILLRECT` ve renk butonları kullanır. |
| `DOSYA.CYX` | Kaynak/hedef yolu girip kopyalama, taşıma ve silme işlemleri yapan panel. |
| `OYUN.CYX` | Hareketli hedefe tıklanan refleks oyunu. |
| `PINPONG.CYX` | Pong benzeri pinpon oyunu. `ON TICK`, `ON MOVE`, `ON KEY W/S/SPACE/R` ve basit fizik döngüsü kullanır. |
| `CYX_DOC.TXT` | CYX dilinin Türkçe komut referansı. |

CYX komutlarının tamamı için `CYX_DOC.TXT` dosyasını dosya gezgininden açın.
Depo içinde daha ayrıntılı uygulama geliştirme anlatımı için
[`CYX_REHBERI.md`](CYX_REHBERI.md) dosyasına bakın.

## Dosya sistemi ve depolama

BIOS tarafında temel ATA PIO algılama, MBR bölüm tablosu okuma denemesi ve
sınırlı FAT16/FAT32 kök dizin incelemesi bulunur. Bu yol daha çok donanım ve
önyükleme deneyi içindir.

UEFI tarafında:

- Block IO diskleri ve bölümleri listelenir.
- Firmware tarafından sunulan Simple File System birimleri açılır.
- RAW, exFAT ve NTFS boot-sector imzaları tespit edilir.
- exFAT için yeni dosya/klasör oluşturma, kopyalama ve mevcut dosyaya yazma
  desteği bulunur.
- NTFS native katmanı şu anda okuma odaklıdır.
- `drivers\ntfs_x64.efi`, ISO içinde `\EFI\BOOT\DRIVERS` altına paketlenir ve
  UEFI NTFS sürücüsü olarak yüklenmeye çalışılır.

## Sınırlar

CaYaBasicOS üretim amaçlı veya genel amaçlı bir işletim sistemi değildir.
Özellikle disk yazma işlemleri test ortamında denenmelidir.

Bilinen sınırlar:

- BIOS yolu sınırlı grafik, dosya sistemi ve giriş desteğine sahiptir.
- UEFI fare/touch desteği firmware'in Simple Pointer veya Absolute Pointer
  protokollerini sunmasına bağlıdır.
- Bazı cihazlarda preboot ortamı USB HID, touchpad veya özel denetleyici
  sürücülerini sağlamayabilir.
- NTFS için tam yazma desteği; MFT kaydı ayırma, `$Bitmap`, `$I30` indexleri,
  attribute-list durumları, journal/dirty bitleri, güvenli flush ve geri alma
  mantığı gerektirir.
- exFAT yazma desteği deneysel kabul edilmelidir.

## Katkı notları

- Kaynak değişikliklerinden sonra `.\build.ps1` ile ISO'nun üretildiğini
  doğrulayın.
- `build/` ve `dist/` çıktıları commit edilmemelidir.
- Yeni CYX örnekleri `assets/cyx` altına eklenmelidir.
- README, GitHub üzerinde UTF-8 olarak görüntülenmelidir.
