#include <print>
import weretype;
import modelgen;
import hinge;

int main() {
	const u8 norm = std::to_underlying(modelgen::dirEnum::y) | std::to_underlying(modelgen::dirEnum::n);
	std::println("Normal direction Test: {}", modelgen::directionVN(norm));

	auto vec = HingeCTC(84, 3);
	std::println("{}", vec);

	std::println("Default Comparison test: {}", (modelgen::direction::Front == modelgen::direction::Back));
	
	if (auto r = modelgen::WriteObj("./.out/obj/genSlab.obj", modelgen::SlabModel(36, 84, 1.75)); !r) {
		std::println("Failed: {}", r.error());
	} else {
		std::println("Success: ./out/obj/genSlab.obj");
	}
}