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

	auto hingeQuads = door::Gen_HingeQuads(door::exampleDoor);
	for (auto elm : hingeQuads) {
		std::println("Hinge Quad: {}", elm);
	}

	auto hingeGap = door::Calc_HingeGap(84,9,3);
	std::println("Test HingeGap: {}", hingeGap);
	auto hingeGapCntrs = door::Calc_MidHingeGap(hingeGap, 9, 3);
	std::println("Test HingeGapCntrs: {}", hingeGapCntrs);
	
	if (auto r = modelgen::WriteObj("./.out/obj/genSlab.obj", modelgen::SlabModel(36, 84, 1.75)); !r) {
		std::println("Failed: {}", r.error());
	} else {
		std::println("Success: ./out/obj/genSlab.obj");
	}

	auto myObj = modelgen::CubicGen_vrtx(36,84,1.75);
	modelgen::CubicGen_faces(myObj);

	auto indx = myObj.face[0].idxNormal;
	std::println("normal dierction of face 0: {}", modelgen::CubeNormals[indx]);
	std::println("normal dierction of face 0: {}", indx);
}