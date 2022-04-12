/**
 * @file dummy_service.h.
 * @date 8.04.2022
 * @author Yazilimperver
 * @brief  FunctionTracker mock fonksiyon cagri kabiliyetini gostermek icin kullanilacak basit bir arayuz ve ilgili bilesenler
 * @remark Copyright (c) 2022, Check Bottom For Copyright Notice <yazilimpervergs@gmail.com>
 */
#ifndef DUMMYSERVICE_H
#define DUMMYSERVICE_H

#include <string>
#include <cstdint>

/**
 * @enum TestEnum
 * @brief Test etmek icin kullanabilecegimiz enum tipi
 */
enum class TestEnum : int32_t{
	ENUM_LITERAL_1,
	ENUM_LITERAL_2,
	ENUM_LITERAL_3
};

/**
 * @struct Obj
 * @brief Basit bir POD tip
 */
struct Obj {
	int X;
	int Y;
};

/**
 * @class DummyService
 * @brief Test edilecek olan sinif tarafindan kullanilacak olan servic arayuzu
 */
class DummyService {
public:
	virtual void ServiceAPI1(bool basicInput1, const Obj& structInput, int32_t basicInput2, TestEnum enumInput) = 0;
	virtual void ServiceAPI2(const std::string& strValue) = 0;
};

#endif // DUMMYSERVICE_H