# Function Tracker
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
* Geçirilen parametrelere erişim ya da geçirilmiş mi kontrolü
* Çoklu fonksiyon çağrısı ve çoklu parametre geçiş kontrolleri
* Çağrılma geçmiş sıfırlama

### Gereksinimler

C++ 17 uyumlu bir derleyici.

### Kurulum

Sadece **function_tracker.h** dosyasını projenize dahil etmeniz, kopyalamanız yeterlidir. 
Ayrıca CMake betikleri de bulunmaktadır.

## Örnek Kullanım

Temelde yapmanız gereken ilk şey, "mock" olarak kullanacağınız sınıfı, arayüz sınıfından ve "**FunctionTracker**" sınıfından türetmek olacak. Sonra da, arayüz sınıfını gerçekleyen her bir API içerisinden "**AddCall**" API'sini çağırmak olacak. Bunun dışında, mock nesnesi için yapacak bir şey kalmıyor. Hemen bir örneğe bakalım.

```c++
#include "dummy_service.h"
#include "function_tracker.h"

class DummyServerStub
	: public DummyService,
	public FunctionTracker {
public:
	virtual void ServiceAPI1(bool basicInput1, const Obj& structInput, int32_t basicInput2, TestEnum enumInput) {
		AddCall("ServiceAPI1", basicInput1, structInput, basicInput2, enumInput);
	}
	virtual void ServiceAPI2(const std::string& strValue) {
		AddCall("ServiceAPI2", strValue);
	}
};
```

Burada **DummService** arayüzüne ilişkin bir “mock” sınıfı görebilirsiniz ve her bir public API için ne yapmanız gerektiğini de. Ayrıca **Reset**() API’si ile de çağrılma ve geçirilen parametre geçmişini sıfırlayabilirsiniz.

“Mock” sınıfını daha sonra testlerde kullanmak için ise aşağıdaki gibi bir yol izleyebilirsiniz:

```c++
std::string funcName{ "ServiceAPI1" };
 
// Fonksiyon cagrildi mi kontrolu asagidaki gibi yapabiliriz
ASSERT_TRUE(mDummyServerStub->IsFunctionCalled(funcName));
 
// Gecirilen parametreleri degerlerini karislastirarak kontrol edebiliriz
ASSERT_EQ(*mDummyServerStub->GetParameter<bool>(funcName, 0), true);
ASSERT_EQ((*mDummyServerStub->GetParameter<Obj>(funcName, 1)).X, 10);
ASSERT_EQ((*mDummyServerStub->GetParameter<Obj>(funcName, 1)).Y, 20);
ASSERT_EQ(*mDummyServerStub->GetParameter<int>(funcName, 2), 45);
ASSERT_EQ(*mDummyServerStub->GetParameter<TestEnum>(funcName, 3), TestEnum::ENUM_LITERAL_2);
 
// Ya da direk IsSame... API'lerini kullanabiliriz
ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<bool>(funcName, 0, true));
ASSERT_TRUE(mDummyServerStub->IsSameComplexParameter<Obj>(funcName, 1, Obj{10, 20}));
ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<int>(funcName, 2, 45));
ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<TestEnum>(funcName, 3, TestEnum::ENUM_L
```

## Kullanılan C++ Kabiliyetleri

Bu kütüphanede C++’a ilişkin hangi kabiliyetleri kullandığımızı sıralayalım, elbette bunlara ilişkin daha önce paylaştığım yazılar ile birlikte 🙂

- std::unordered_map (**[Haftalık C++ 2 – Konteynerler ve Sıralı Tutma](https://www.yazilimperver.com/index.php/2018/10/25/haftalik-c-2-konteynerler-ve-sirali-tutma/)**)
- if ilklendirme ifadeleri ([**Haftalık C++ 3 – if/switch ilklendirme ifadeleri**](https://www.yazilimperver.com/index.php/2018/10/31/english-weekly-c-3-if-switch-init-statements/))
- std::optional ([**Haftalık C++ 14 – std::optional**)](https://www.yazilimperver.com/index.php/2019/04/15/haftalik-c-14-stdoptional/)
- std::any (**[Haftalık C++ 18 – std::any](https://www.yazilimperver.com/index.php/2019/08/14/haftalik-c-18-stdany/)**)
- Variadic templates ([**Haftalık C++ 37 – Değişken Şablonlar (“Variadic Templates”**)](https://www.yazilimperver.com/index.php/2021/04/27/haftalik-c-37-degisken-sablonlar-variadic-templates/)
