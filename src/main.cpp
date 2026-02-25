#include <print>
import weretype;
import modelgen;

int main() {
	std::println("test");

	const u8 norm = std::to_underlying(modelgen::dirEnum::y) | std::to_underlying(modelgen::dirEnum::n);
	std::println("Test: {}", modelgen::directionVN(norm));
	
	if (auto r = modelgen::WriteObj("./.out/obj/genSlab.obj", modelgen::SlabModel(36, 84, 1.75)); !r) {
		std::println("Failed: {}", r.error());
	} else {
		std::println("Success: ./out/obj/genSlab.obj");
	}
}