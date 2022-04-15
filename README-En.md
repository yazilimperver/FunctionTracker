# Function Tracker
A simple mock library for modern C++ applications.

This header only library help you to test if "class under test" calls external interface APIs correctly with provided parameters.
It is developed for educational purposes but also served well for simple unit test mock requirements.

For more details you can check out my blog post about this library:
* [Function Tracker](https://www.yazilimperver.com/?p=2512&preview=true) - Haftalık C++ - 48 - "Function Tracker": Basit bir "Mock" kütüphanesi

*[Bu sayfayı Türkçe okuyun](https://github.com/yazilimperver/FunctionTracker/blob/main/README.md)*

## Getting Started

### Capabilities

- Function call checks
- Function execution count checks
- Control the parameters passed and functions to check correctness
- Multiple consecutive function call and parameter tracking
- Function/parameter track history reset

### Prerequisites

You just need to have a C++ 17 compatible compiler.

### Installing

You just need to copy **function_tracker.h** to your project and start to use it right away. 
Provided unit tests can be checked for possible usage. CMake scripts are also provided.

## Example Usage

Basically, the first thing you need to do is derive the class that you will use as "mock" from the interface class and the "**FunctionTracker**" class. Next "**AddCall**" API should be called from within each API that implements the interface class. Other than that, there's nothing left to do for the mock object. Let's take a quick look at an example.

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

Here you can see a mock class for the **DummService** interface and what to do for each public API. You can also reset the history of being called and passed parameters with the **Reset**() API.

To use the "Mock" class in later tests, you can do something like this:

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

## Employed Modern C++ Capabilities

Let's list which capabilities we use in this library related to Modern C++, of course, with the articles that I have shared about them before 🙂

- std::unordered_map (**[Haftalık C++ 2 – Konteynerler ve Sıralı Tutma](https://www.yazilimperver.com/index.php/2018/10/25/haftalik-c-2-konteynerler-ve-sirali-tutma/)**)
- if ilklendirme ifadeleri ([**Haftalık C++ 3 – if/switch ilklendirme ifadeleri**](https://www.yazilimperver.com/index.php/2018/10/31/english-weekly-c-3-if-switch-init-statements/))
- std::optional ([**Haftalık C++ 14 – std::optional**)](https://www.yazilimperver.com/index.php/2019/04/15/haftalik-c-14-stdoptional/)
- std::any (**[Haftalık C++ 18 – std::any](https://www.yazilimperver.com/index.php/2019/08/14/haftalik-c-18-stdany/)**)
- Variadic templates ([**Haftalık C++ 37 – Değişken Şablonlar (“Variadic Templates”**)](
