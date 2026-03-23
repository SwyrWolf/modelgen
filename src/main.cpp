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

	using enum vrtx::Vert;
	auto quad1 = vrtx::Quad(1.1875f, 6.75f).skew<tl>([](Vec3& v) { v.x += 1.0f; });
	std::println("Vrtx original Quad {}", quad1);

	quad1.mirror(&Vec3::x);
	std::println("Vrtx mirrored Quad {}", quad1);

	door::Door myDoor{};
	auto hingeQuads = door::Gen_HingeQuads(myDoor);
	for (auto elm : hingeQuads) {
		std::println("Hinge Quad: {}", elm);
	}
	
	if (auto r = modelgen::WriteObj("./.out/obj/genSlab.obj", modelgen::SlabModel(36, 84, 1.75)); !r) {
		std::println("Failed: {}", r.error());
	} else {
		std::println("Success: ./out/obj/genSlab.obj");
	}
}