/**
 * @file function_tracker_stub.h.
 * @date 12.04.2022
 * @author Yazilimperver
 * @brief 
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef FUNCTIONTRACKERSTUB
#define FUNCTIONTRACKERSTUB

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

#endif // !FUNCTIONTRACKERSTUB

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
