#pragma once 
/**
 * @file function_tracker.h.
 * @date 25.03.2022
 * @author Yazilimperver
 * @brief  Birim testler için basitçe ilgili fonksiyonlarýn caðrýlýp/çaðrýlmadýðýný kontrol etmek, çaðrýlar için geçirilen parameterlerin tutulmasý için kullanýlabilecek sýnýftýr.
 * 		   Mevcut sýnýf fonksiyon caðrý adeti ve her bir çaðrýya geçirilen parametreler tutulmaktadýr. Kullaným aþaðýdaki gibi verilmiþtir:
 * 		   Örnek Kullaným:
 * 				Mock sýnýflarýnýn bu sýnýftan türetilmesi ve içerisinde bulunan ilgili fonksiyonlarda aþaðýdaki gibi ekleme yapýlmasý yeterlidir
 * 				
 *				AddCall("IsDataProvidedFunc", 12, 4.3F, customObject, "TraditionalString"); // Bu cagri ile ilgili fonksiyon kayit altina alinir
 *				Reset();  // Tutulan veriler sifirlanir
 *				IsFunctionCalled("IsDataProvidedFunc");   // Ilgili fonksiyon cagrildi mi?
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <string>
#include <any>
#include <cstdint>
#include <optional>
#include <type_traits>
#include <unordered_map>

using namespace std;

/**
 * @class FunctionTracker
 * @brief A function tracker.
 */
class FunctionTracker {
public:
	// Ilgili fonksiyon cagrisini kayit altina almak için giris fonksiyonu
	template <typename ...Param>
	void AddCall(const std::string& funcName, Param ...params);

	// Ilgili fonksiton cagrildi mi? Cagrilmadi mi? kontrolu. Tekli cagri kontrolleri icin kullanilabilir
	bool IsFunctionCalled(const std::string& funcName);

	// Fonksiyon cagri adetini donelim. Birden fazla cagri kontrolu icin kullanilabilir
	// Coklu adet kontrolu icin SetParameterTrackingForConseqCalls'in cagri oncesinde dogru olarak atanmalidir
	uint32_t GetFunctionCallCount(const std::string& funcName);

	// Cagrilmis ise ilgili parametreyi optional olarak donuyoruz. Cunku cagrilmamis olabilir
	// Eger ilgili parametre doner ise, ilgili degere .value() ile ulasabiliriz
	template <typename T>
	std::optional<T> GetParameter(const std::string& funcName, uint32_t parameterIndex);

	// Aritmetik parametreleri kontrol etmek icin kullanilabilecek fonksiyon
	template <typename T>
	bool IsSameSimpleParameter(const std::string& funcName, uint32_t parameterIndex, T valueToCheck);

	// POD nesneleri kontrol etmek icin kullanilabilecek fonksiyondur
	template <typename T>
	bool IsSameComplexParameter(const std::string& funcName, uint32_t parameterIndex, T valueToCheck);

	// Karakter dizilerini karsilastirmak icin asagidaki gibi bir yaklasim izlendi
	bool IsSameCharArrayParameter(const std::string& funcName, uint32_t parameterIndex, const char* valueToCheck);

	// En son tutulan degerler sifirlanir
	void ResetFunctionData();

	// Her fonksiyon cagrisinda, bir onceki tutualn parametreler silinsin mi, silinmesin mi?
	void SetParameterTrackingForConseqCalls(bool status);
protected:
	// Cagri parametreleri kaydedelim
	template <typename Head, typename ...Tail>
	void RecordParameters(const std::string& funcName, Head head, Tail ...tail);

	// Cagri parametreleri kaydedelim
	template <typename ...Tail>
	void RecordParameters(const std::string& funcName, const char* head, Tail ...tail);

	// Durdurma fonksiyonu (variadic template icin)
	void RecordParameters(const std::string& funcName) {}

	// Bir onceki cagri icin tutulan parametreler silinsin mi, silinmesin mi?
	bool mIsConseqCallParametersTrackingEnabled{ false };

	// Ilgili fonksiyon cagrildi mi, cagrilmadi mi?
	unordered_map<std::string, bool> mFunctionCallStatus;

	// Ilgili fonksiyon kac kere cagrildi
	unordered_map<std::string, uint32_t> mFunctionCallCount;
	
	// Cagrilan fonksiyonlarin argumanlari
	unordered_map<std::string, std::vector<std::any>> mFunctionParameters;
};

template<typename ...Param>
void FunctionTracker::AddCall(const std::string& funcName, Param ...params) {
	mFunctionCallStatus[funcName] = true;

	if (mFunctionCallCount.find(funcName) == mFunctionCallCount.end()) {
		mFunctionCallCount[funcName] = 1;
	}
	else {
		mFunctionCallCount[funcName]++;
	}

	if (false == mIsConseqCallParametersTrackingEnabled) {
		mFunctionParameters[funcName].clear();
		mFunctionCallCount[funcName] = 1;
	}

	RecordParameters(funcName, params ...);
}

template<typename T>
std::optional<T> FunctionTracker::GetParameter(const std::string& funcName, uint32_t parameterIndex) {
	if (auto itr = mFunctionParameters.find(funcName); itr != mFunctionParameters.end() && itr->second.size() > parameterIndex) {
		try {
			return std::any_cast<T>(itr->second[parameterIndex]);
		}
		catch (...) {
			return std::nullopt;
		}
	}
	else {
		return std::nullopt;
	}
}

template<typename T>
bool FunctionTracker::IsSameSimpleParameter(const std::string& funcName, uint32_t parameterIndex, T valueToCheck) {	

	if (auto itr = mFunctionParameters.find(funcName);  itr != mFunctionParameters.cend() && itr->second.size() > parameterIndex) {
		try {
			return valueToCheck == std::any_cast<T>(itr->second[parameterIndex]);
		}
		catch (...) {
			return false;
		}
	}
	else {
		return false;
	}
}

template<typename T>
bool FunctionTracker::IsSameComplexParameter(const std::string& funcName, uint32_t parameterIndex, T valueToCheck) {
	if (auto itr = mFunctionParameters.find(funcName); itr != mFunctionParameters.cend() && itr->second.size() > parameterIndex) {
		try {
			T value = std::any_cast<T>(itr->second[parameterIndex]);
			return (0 == memcmp(&valueToCheck, &value, sizeof(T)));
		}
		catch (...) {
			return false;
		}
	}
	else {
		return false;
	}
}

template<typename Head, typename ...Tail>
void FunctionTracker::RecordParameters(const std::string& funcName, Head head, Tail ...tail) {
	mFunctionParameters[funcName].push_back(head);
	RecordParameters(funcName, tail ...);
}

template<typename ...Tail>
void FunctionTracker::RecordParameters(const std::string& funcName, const char* head, Tail ...tail) {
	mFunctionParameters[funcName].push_back(std::string(head));
	RecordParameters(funcName, tail ...);
}

bool FunctionTracker::IsFunctionCalled(const std::string& funcName) {
	return (mFunctionCallStatus.find(funcName) != mFunctionCallStatus.cend());
}

uint32_t FunctionTracker::GetFunctionCallCount(const std::string& funcName) {
	if (auto itr = mFunctionCallCount.find(funcName); itr != mFunctionCallCount.end()) {
		return itr->second;
	}
	else {
		return 0;
	}
}

bool FunctionTracker::IsSameCharArrayParameter(const std::string& funcName, uint32_t parameterIndex, const char* valueToCheck)
{
	if (auto itr = mFunctionParameters.find(funcName); itr != mFunctionParameters.cend() && itr->second.size() > parameterIndex) {
		try {
			std::string value = std::any_cast<std::string>(itr->second[parameterIndex]);
			return (0 == strcmp(valueToCheck, value.c_str()));
		}
		catch (...) {
			return false;
		}
	}
	else {
		return false;
	}
}

void FunctionTracker::ResetFunctionData() {
	mFunctionCallCount.clear();
	mFunctionCallStatus.clear();
	mFunctionParameters.clear();
}

void FunctionTracker::SetParameterTrackingForConseqCalls(bool status) {
	mIsConseqCallParametersTrackingEnabled = status;
}

/**
Copyright (c) [2022][Yazilimperver - yazilimpervergs@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
