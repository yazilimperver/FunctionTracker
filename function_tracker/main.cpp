#include "function_tracker.h"
#include <iostream>

using namespace std;

struct Point {
	int x{ 0 };
	int y{ 1 };
};

int main() {
	FunctionTracker callExamples;

	std::string a("StringInput");
	int b{35};
	callExamples.AddCall("Deneme", a, b, Point{10, 20});

	std::cout << "Fonksiyon cagrilmis mi: " << callExamples.IsFunctionCalled("Deneme") << "\n";

	auto param1 = callExamples.GetParameter<std::string>("Deneme", 0);

	std::cout << "is_arithmetic<Point> == " << std::boolalpha
		<< std::is_arithmetic<Point>::value << std::endl;

	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameSimpleParameter<int>("Deneme", 1, 35) << "\n";
	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameSimpleParameter<int>("Deneme", 1, 0) << "\n";
	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameComplexParameter<Point>("Deneme", 2, Point{ 0, 1 }) << "\n";
	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameComplexParameter<Point>("Deneme", 2, Point{ 10, 20 }) << "\n";
	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameSimpleParameter<std::string>("Deneme", 0, "StringInput") << "\n";
	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameSimpleParameter<std::string>("Deneme", 0, "StringInput2") << "\n";
	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameSimpleParameter<std::string>("Deneme", 5, "StringInput2") << "\n";

	if (param1.has_value()) {
		std::cout << "Parametre 1: " << param1.value()  << "\n";
	}
	else {
		std::cout << "Parameter yok\n";
	}

	callExamples.ResetFunctionData();
	callExamples.SetParameterTrackingForConseqCalls(true);

	callExamples.AddCall("Deneme", a, b, Point{ 10, 20 });
	callExamples.AddCall("Deneme", a, b*2, Point{ 30, 60 });

	std::cout << "Fonksiyon cagrilma adeti iki mi? " << callExamples.GetFunctionCallCount("Deneme") << "\n";
	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameSimpleParameter<std::string>("Deneme", 0, "StringInput") << "\n";
	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameSimpleParameter<int>("Deneme", 1, 35) << "\n";
	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameComplexParameter<Point>("Deneme", 2, Point{ 10, 20 }) << "\n";
	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameSimpleParameter<std::string>("Deneme", 3, "StringInput") << "\n";
	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameSimpleParameter<int>("Deneme", 4, 70) << "\n";
	std::cout << "Parameter var ve dogru mu:" << callExamples.IsSameComplexParameter<Point>("Deneme", 5, Point{ 30, 60 }) << "\n";

	return 0;
}
