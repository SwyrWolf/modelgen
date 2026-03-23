#include <print>
#include <array>
#include <vector>
#include <algorithm>

import weretype;
import werevec;
import modelgen;
import hinge;
import door;
import direction;
import vrtx;

int main() {
	const u8 norm = std::to_underlying(eDirection::y) | std::to_underlying(eDirection::n);
	
	std::vector<f32> val;
	for (auto elm : CubicDir_Array()) {
		std::array<f32,3> tmp(elm);
		val.append_range(tmp);
		std::println("CubicDir: {}", elm);
	}
	for (auto elm : modelgen::CubicGen(36, 84, 1.75)) {
		std::println("CubicGen: {}", elm);
	}

	auto vec = HingeCTC(84, 3);
	std::println("HingeCTC: {}", vec);

	auto hg = door::Calc_HingeGap(84, 9, 3);
	std::println("HingeGap 7f0: {}", hg);

	auto hg2 = door::Calc_HingeGap(96, 9, 4);
	std::println("HingeGap 8f0: {}", hg2);
	
	for (auto elm : door::Create_SquareQuad(12,64)) {
		std::println("SquareQuad: {}", elm);
	}

	std::println("Default Comparison test: {}", (modelgen::direction::Front == modelgen::direction::Back));

	using enum vrtx::Vert;
	std::println("Vrtx.math Quad {}", vrtx::Quad(1.1875f, 6.75f).skew<tl>([](Vec3& v) { v.x += 1.0f; }));
	
	if (auto r = modelgen::WriteObj("./.out/obj/genSlab.obj", modelgen::SlabModel(36, 84, 1.75)); !r) {
		std::println("Failed: {}", r.error());
	} else {
		std::println("Success: ./out/obj/genSlab.obj");
	}
}