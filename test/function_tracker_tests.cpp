#include "function_tracker_tests.h"

#include <cstdint>

#include "gtest/gtest.h"
#include "class_under_test.h"

// Arayuz siniflar ile kullanimi test edelim
TEST_F(ClassUnderTest_F, PublicAPI1ShouldCallServiceAPI1) {
	mInstanceCUT->PublicAPI1(true, Obj{ 10, 20 }, 45, TestEnum::ENUM_LITERAL_2);

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
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<TestEnum>(funcName, 3, TestEnum::ENUM_LITERAL_2));
}

TEST_F(ClassUnderTest_F, PublicAPI2ShouldCallServiceAPI2) {
	mInstanceCUT->PublicAPI2(std::string{ "StrInput" });

	std::string funcName{ "ServiceAPI2" };

	// Fonksiyon cagrildi mi kontrolu asagidaki gibi yapabiliriz
	ASSERT_TRUE(mDummyServerStub->IsFunctionCalled(funcName));

	// Gecirilen parametreleri degerlerini karislastirarak kontrol edebiliriz
	ASSERT_EQ(*mDummyServerStub->GetParameter<std::string>(funcName, 0), std::string{ "StrInput" });

	// Ya da direk IsSame... API'lerini kullanabiliriz
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<std::string>(funcName, 0, std::string{ "StrInput" }));
}

TEST_F(ClassUnderTest_F, PublicAPI1ShouldCallServiceAPI1_MultipleCallCase) {

	mDummyServerStub->SetParameterTrackingForConseqCalls(true);

	mInstanceCUT->PublicAPI1(true, Obj{ 10, 20 }, 45, TestEnum::ENUM_LITERAL_2);
	mInstanceCUT->PublicAPI1(false, Obj{ 100, 200 }, -45, TestEnum::ENUM_LITERAL_3);
	mInstanceCUT->PublicAPI1(true, Obj{ 10, 20 }, 45, TestEnum::ENUM_LITERAL_2);

	std::string funcName{ "ServiceAPI1" };

	// Fonksiyon cagrildi mi kontrolu asagidaki gibi yapabiliriz
	ASSERT_EQ(mDummyServerStub->GetFunctionCallCount(funcName), 3);

	// Ya da direk IsSame... API'lerini kullanabiliriz
	// Ilk cagri icin gecirilen parametreler
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<bool>(funcName, 0, true));
	ASSERT_TRUE(mDummyServerStub->IsSameComplexParameter<Obj>(funcName, 1, Obj{ 10, 20 }));
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<int>(funcName, 2, 45));
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<TestEnum>(funcName, 3, TestEnum::ENUM_LITERAL_2));

	// Ikinci cagri icin gecirilen parametreler. Sadece parametre indekslerini arttiriyoruz
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<bool>(funcName, 4, false));
	ASSERT_TRUE(mDummyServerStub->IsSameComplexParameter<Obj>(funcName, 5, Obj{ 100, 200 }));
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<int>(funcName, 6, -45));
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<TestEnum>(funcName, 7, TestEnum::ENUM_LITERAL_3));
	
	// Ucuncu cagri icin gecirilen parametreler
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<bool>(funcName, 8, true));
	ASSERT_TRUE(mDummyServerStub->IsSameComplexParameter<Obj>(funcName, 9, Obj{ 10, 20 }));
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<int>(funcName, 10, 45));
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<TestEnum>(funcName, 11, TestEnum::ENUM_LITERAL_2));
}

TEST_F(ClassUnderTest_F, ResetShouldClearCallHistory) {
	mInstanceCUT->PublicAPI1(true, Obj{ 10, 20 }, 45, TestEnum::ENUM_LITERAL_2);

	std::string funcName{ "ServiceAPI1" };

	// Fonksiyon cagrildi mi kontrolu asagidaki gibi yapabiliriz
	ASSERT_TRUE(mDummyServerStub->IsFunctionCalled(funcName));

	// Ya da direk IsSame... API'lerini kullanabiliriz
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<bool>(funcName, 0, true));
	ASSERT_TRUE(mDummyServerStub->IsSameComplexParameter<Obj>(funcName, 1, Obj{ 10, 20 }));
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<int>(funcName, 2, 45));
	ASSERT_TRUE(mDummyServerStub->IsSameSimpleParameter<TestEnum>(funcName, 3, TestEnum::ENUM_LITERAL_2));

	mDummyServerStub->ResetFunctionData();

	// Artik ilgili cagri bilgileri sifirlanmali
	ASSERT_FALSE(mDummyServerStub->IsFunctionCalled(funcName));
	ASSERT_FALSE(mDummyServerStub->IsSameSimpleParameter<bool>(funcName, 0, true));
	ASSERT_FALSE(mDummyServerStub->IsSameComplexParameter<Obj>(funcName, 1, Obj{ 10, 20 }));
	ASSERT_FALSE(mDummyServerStub->IsSameSimpleParameter<int>(funcName, 2, 45));
	ASSERT_FALSE(mDummyServerStub->IsSameSimpleParameter<TestEnum>(funcName, 3, TestEnum::ENUM_LITERAL_2));
}

// FunctionTracker'in Acik API'lerine iliskin servisleri bir test edelim
TEST(FunctionTracker, SimpleOneParameterCallShouldBeTracked) {
	FunctionTracker classUnderTestInstance;
	std::string funcName {"ExampleFunction"};

	int32_t input{ 35 };
	classUnderTestInstance.AddCall(funcName, input);

	ASSERT_TRUE(classUnderTestInstance.IsFunctionCalled(funcName));
	ASSERT_EQ(*classUnderTestInstance.GetParameter<int32_t>(funcName, 0), input);
}

TEST(FunctionTracker, SimpleEnumParameterCallShouldBeTracked) {
	FunctionTracker classUnderTestInstance;
	std::string funcName{ "ExampleFunction" };

	enum class Color : int32_t {
		Red,
		Green,
		Blue
	};

	Color input{ Color::Green };
	classUnderTestInstance.AddCall(funcName, input);

	ASSERT_TRUE(classUnderTestInstance.IsFunctionCalled(funcName));
	ASSERT_EQ(*classUnderTestInstance.GetParameter<Color>(funcName, 0), input);
	ASSERT_NE(*classUnderTestInstance.GetParameter<Color>(funcName, 0), Color::Blue);
}

TEST(FunctionTracker, ConstCharParameterCallShouldBeTracked) {
	FunctionTracker classUnderTestInstance;
	std::string funcName{ "ExampleFunction" };

	const char input[]("StringInput");
	classUnderTestInstance.AddCall(funcName, input);

	ASSERT_TRUE(classUnderTestInstance.IsFunctionCalled(funcName));
	ASSERT_STREQ(classUnderTestInstance.GetParameter<std::string>(funcName, 0).value().c_str(), "StringInput");
}


TEST(FunctionTracker, StringParameterCallShouldBeTracked) {
	FunctionTracker classUnderTestInstance;
	std::string funcName{ "ExampleFunction" };

	std::string input("StringInput");
	classUnderTestInstance.AddCall(funcName, input);

	ASSERT_TRUE(classUnderTestInstance.IsFunctionCalled(funcName));
	ASSERT_EQ(*classUnderTestInstance.GetParameter<std::string>(funcName, 0), input);
}

TEST(FunctionTracker, ComplexParameterCallShouldBeTracked) {
	struct Point {
		int x;
		int y;
	};

	FunctionTracker classUnderTestInstance;
	std::string funcName{ "ExampleFunction" };

	Point input{ 10, 20 };
	classUnderTestInstance.AddCall(funcName, input);

	ASSERT_TRUE(classUnderTestInstance.IsFunctionCalled(funcName));
	ASSERT_EQ(classUnderTestInstance.GetParameter<Point>(funcName, 0).value().x, input.x);
	ASSERT_EQ(classUnderTestInstance.GetParameter<Point>(funcName, 0).value().y, input.y);
}

TEST(FunctionTracker, MultipleParameterCallShouldBeTracked) {
	struct Point {
		int x;
		int y;
	};

	int32_t input1{ 35 };
	Point input2{ 10, 20 };
	std::string input3("StringInput");

	FunctionTracker classUnderTestInstance;
	std::string funcName{ "ExampleFunction" };

	classUnderTestInstance.AddCall(funcName, input1, input2, input3);

	ASSERT_TRUE(classUnderTestInstance.IsFunctionCalled(funcName));
	ASSERT_EQ(*classUnderTestInstance.GetParameter<int32_t>(funcName, 0), input1);
	ASSERT_EQ(classUnderTestInstance.GetParameter<Point>(funcName, 1).value().x, input2.x);
	ASSERT_EQ(classUnderTestInstance.GetParameter<Point>(funcName, 1).value().y, input2.y);
	ASSERT_EQ(*classUnderTestInstance.GetParameter<std::string>(funcName, 2), input3);
}

TEST(FunctionTracker, IsSameSimpleParameterShouldCheckProvidedParameter) {
	FunctionTracker classUnderTestInstance;
	std::string funcName {"ExampleFunction"};

	int32_t input{ 35 };
	classUnderTestInstance.AddCall(funcName, input);

	ASSERT_TRUE(classUnderTestInstance.IsSameSimpleParameter<int32_t>(funcName, 0, input));
	ASSERT_FALSE(classUnderTestInstance.IsSameSimpleParameter<int32_t>(funcName, 0, 40));
}

TEST(FunctionTracker, IsConstCharParameterShouldCheckProvidedParameter) {
	FunctionTracker classUnderTestInstance;
	std::string funcName{ "ExampleFunction" };

	const char input[]("StringInput");
	classUnderTestInstance.AddCall(funcName, input);

	ASSERT_TRUE(classUnderTestInstance.IsSameCharArrayParameter(funcName, 0, input));
}

TEST(FunctionTracker, IsSameComplexParameterShouldCheckProvidedParameter) {
	struct Point {
		int x;
		int y;
	};

	FunctionTracker classUnderTestInstance;
	std::string funcName{ "ExampleFunction" };
	
	Point input{ 10, 20 };
	classUnderTestInstance.AddCall(funcName, input);

	ASSERT_TRUE(classUnderTestInstance.IsSameComplexParameter<Point>(funcName, 0, input));
	
	Point falseInput{ 1, 2 };
	ASSERT_FALSE(classUnderTestInstance.IsSameComplexParameter<Point>(funcName, 0, falseInput));
}

TEST(FunctionTracker, IsSameParameterShouldCheckProvidedMultipleParameters) {
	struct Point {
		int x;
		int y;
	};

	int32_t input1{ 35 };
	Point input2{ 10, 20 };
	std::string input3("StringInput");

	FunctionTracker classUnderTestInstance;
	std::string funcName{ "ExampleFunction" };

	classUnderTestInstance.AddCall(funcName, input1, input2, input3);

	ASSERT_TRUE(classUnderTestInstance.IsFunctionCalled(funcName));
	ASSERT_TRUE(classUnderTestInstance.IsSameSimpleParameter<int32_t>(funcName, 0, input1));
	ASSERT_TRUE(classUnderTestInstance.IsSameComplexParameter<Point>(funcName, 1, input2));
	ASSERT_TRUE(classUnderTestInstance.IsSameSimpleParameter<std::string>(funcName, 2, input3));
}

TEST(FunctionTracker, ResetAPIShouldClearCallInformation) {
	struct Point {
		int x;
		int y;
	};

	int32_t input1{ 35 };
	Point input2{ 10, 20 };
	std::string input3("StringInput");

	FunctionTracker classUnderTestInstance;
	std::string funcName{ "ExampleFunction" };

	classUnderTestInstance.AddCall(funcName, input1, input2, input3);

	ASSERT_TRUE(classUnderTestInstance.IsFunctionCalled(funcName));
	ASSERT_EQ(classUnderTestInstance.GetFunctionCallCount(funcName), 1);
	ASSERT_TRUE(classUnderTestInstance.IsSameSimpleParameter<int32_t>(funcName, 0, input1));
	ASSERT_TRUE(classUnderTestInstance.IsSameComplexParameter<Point>(funcName, 1, input2));
	ASSERT_TRUE(classUnderTestInstance.IsSameSimpleParameter<std::string>(funcName, 2, input3));

	classUnderTestInstance.ResetFunctionData();

	ASSERT_EQ(classUnderTestInstance.GetFunctionCallCount(funcName), 0);
	ASSERT_FALSE(classUnderTestInstance.IsFunctionCalled(funcName));
	ASSERT_FALSE(classUnderTestInstance.IsSameSimpleParameter<int32_t>(funcName, 0, input1));
	ASSERT_FALSE(classUnderTestInstance.IsSameComplexParameter<Point>(funcName, 1, input2));
	ASSERT_FALSE(classUnderTestInstance.IsSameSimpleParameter<std::string>(funcName, 2, input3));
}

TEST(FunctionTracker, ConsequtiveCallsShouldBeTrackedIfAssociatedFlagSet) {
	struct Point {
		int x;
		int y;
	};

	int32_t input1a{ 35 };
	int32_t input1b{ 45 };
	Point input2a{ 10, 20 };
	Point input2b{ 30, 40 };
	std::string input3a("StringInput1");
	std::string input3b("StringInput2");

	FunctionTracker classUnderTestInstance;
	std::string funcName{ "ExampleFunction" };

	classUnderTestInstance.SetParameterTrackingForConseqCalls(true);
	classUnderTestInstance.AddCall(funcName, input1a, input2a, input3a);
	classUnderTestInstance.AddCall(funcName, input1b, input2b, input3b);
	classUnderTestInstance.AddCall(funcName, input1a, input2a, input3a);

	ASSERT_EQ(classUnderTestInstance.GetFunctionCallCount(funcName), 3);
	ASSERT_TRUE(classUnderTestInstance.IsSameSimpleParameter<int32_t>(funcName, 0, input1a));
	ASSERT_TRUE(classUnderTestInstance.IsSameComplexParameter<Point>(funcName, 1, input2a));
	ASSERT_TRUE(classUnderTestInstance.IsSameSimpleParameter<std::string>(funcName, 2, input3a));
	ASSERT_TRUE(classUnderTestInstance.IsSameSimpleParameter<int32_t>(funcName, 3, input1b));
	ASSERT_TRUE(classUnderTestInstance.IsSameComplexParameter<Point>(funcName, 4, input2b));
	ASSERT_TRUE(classUnderTestInstance.IsSameSimpleParameter<std::string>(funcName, 5, input3b));
	ASSERT_TRUE(classUnderTestInstance.IsSameSimpleParameter<int32_t>(funcName, 6, input1a));
	ASSERT_TRUE(classUnderTestInstance.IsSameComplexParameter<Point>(funcName, 7, input2a));
	ASSERT_TRUE(classUnderTestInstance.IsSameSimpleParameter<std::string>(funcName, 8, input3a));
}