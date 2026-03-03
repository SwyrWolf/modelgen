#include <print>
#include <array>
#include <vector>
#include <algorithm>

import weretype;
import werevec;
import modelgen;
import hinge;
import direction;

int main() {
	const u8 norm = std::to_underlying(eDirection::y) | std::to_underlying(eDirection::n);
	
	std::vector<f32> val;
	for (auto elm : CubicDir_Array()) {
		std::array<f32,3> tmp = elm;
		val.append_range(tmp);
		std::println("CubicDir: {}", elm);
	}

	auto vec = HingeCTC(84, 3);
	std::println("{}", vec);

	std::println("Default Comparison test: {}", (modelgen::direction::Front == modelgen::direction::Back));
	
	if (auto r = modelgen::WriteObj("./.out/obj/genSlab.obj", modelgen::SlabModel(36, 84, 1.75)); !r) {
		std::println("Failed: {}", r.error());
	} else {
		std::println("Success: ./out/obj/genSlab.obj");
	}
}