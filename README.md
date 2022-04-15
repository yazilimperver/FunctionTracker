# FunctionTracker
Modern C++ uygulamalari için basit bir "Mock" kütüphanesi.


Bu tek bir başlık dosyasından oluşan kütüphane ile, test edilecek olan sınıfınızın dış servislere ilişkin API'leri çağırıp/çağırmadığı ve çağırıyor ise doğru parametreler ile çağrıldığını kontrol edebilirsiniz.

İlk etapta eğitsel amaçlar ile geliştirilen bu kütüphane, basit birim test "mock" ihtiyaçlarınız için kullanılabilir.

Bu kütüphane ile ilgili daha detaylı bilgi için yazmış olduğum aşağıdaki yazıya göz atabilirsiniz:
* [Function Tracker](https://www.yazilimperver.com/?p=2512&preview=true) - Haftalık C++ - 48 - "Function Tracker": Basit bir "Mock" kütüphanesi

*[Read this page in English](https://github.com/yazilimperver/FunctionTracker/blob/main/README-En.md)*

## Başlarken

### Kabiliyetler
* Fonksiyonun çağrılıp/çağrılmadığı kontrolü
* Fonksiyon çağrılma adet kontrolü
* Geçirilen temel tipteki parametrelere erişim ya da direk geçirilmiş mi kontrolü
* Çoklu fonksiyon çağrısı ve çoklu parametre geçiş kontrolleri
* Çağrılma geçmiş sıfırlama

### Gereksinimler

C++ 17 uyumlu bir derleyici. Kütüphane aşağıdaki derleyiciler ile denenmiştir:

### Kurulum

Sadece **function_tracker.h** dosyasını projenize dahil etmeniz, kopyalamanız yeterlidir. 
Ayrıca CMake betikleri de bulunmaktadır.

### Örnek Kullanım

Temelde yapmanız gereken ilk şey, "mock" olarak kullanacağınız sınıfı, arayüz sınıfından ve "FunctionTracker" sınıfından türetmek olacak. Sonra da, arayüz sınıfını gerçekleyen her bir API içerisinden "AddCall" API'sini çağırmak olacak. Bunun dışında, mock nesnesi için yapacak bir şey kalmıyor. Hemen bir örneğe bakalım.

```
class DummyServerStub : public DummyService, public FunctionTracker { public: virtual void ServiceAPI1(bool basicInput1, const Obj& structInput, int32_t basicInput2, TestEnum enumInput) { // Bu cagri ile ilgili fonksiyon kayit altina alinir AddCall("ServiceAPI1", basicInput1, structInput, basicInput2, enumInput); } virtual void ServiceAPI2(const std::string& strValue) { AddCall("ServiceAPI2", strValue); } };
```


