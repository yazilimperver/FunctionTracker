/**
 * @file class_under_test.h.
 * @date 12.04.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef CLASSUNDERTEST_H
#define CLASSUNDERTEST_H

#include <memory>

#include "dummy_service.h"

/**
 * @class ClassUnderTest
 * @brief Bu sinif tarafindan kullanilan DummyService arayuzunun cagrilip/cagrilmadigini
 *        FunctionTracker ile nasil kontrol edebilecegimiz gorecegiz.		  
 *        Simdilik basitce verilen butun parametreler ilgili servise gecirilecek
 */
class ClassUnderTest {
public:
	virtual void PublicAPI1(bool basicInput1, const Obj& structInput, int32_t basicInput2, TestEnum enumInput) {
		if (nullptr != mDummyService) {
			mDummyService->ServiceAPI1(basicInput1, structInput, basicInput2, enumInput);
		}
	}
	virtual void PublicAPI2(const std::string& strValue) {
		if (nullptr != mDummyService) {
			mDummyService->ServiceAPI2(strValue);
		}
	}

	void AssignService(std::shared_ptr<DummyService> arg) {
		mDummyService = arg;
	}
private:
	std::shared_ptr<DummyService> mDummyService{ nullptr };
};

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

#endif // !CLASSUNDERTEST_H