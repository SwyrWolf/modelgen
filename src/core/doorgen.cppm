module;

#include <array>
#include <vector>
#include <vector>
#include <ranges>

export module door;
import weretype;
import werevec;
import vrtx;

export namespace door {

	enum struct Swing { LH, RH, LHR, RHR };
	struct Slab { f32 width, height, depth; };
	struct Hinge { f32 width, height, depth, radius; };
	
	struct Door {
		Slab slab{};
		Swing handing{Swing::RH};
		
		size_t hinge_qty{};
		Hinge hinge{};
		f32 hinge_margin{};
		f32 hinge_depth_margin{};
	};

	auto Calc_HingeGap(f32 slabHeight, f32 margin, size_t qty) -> f32 {
		return (slabHeight - (margin * 2)) / (qty - 1);
	}

	auto Calc_MidHingeGap(f32 gap, f32 margin, size_t qty) -> std::vector<f32> {
		std::vector<f32> v(qty - 1);

		auto halfGap = (gap/2);
		for (auto [i, val] : std::views::enumerate(v)) {
			v[i] = (margin + (gap * i) + halfGap);
		}

		return v;
	}	

	auto Gen_HingeQuads(Door& door) -> std::vector<vrtx::Quad> {
		using enum vrtx::Vert;
		auto midHingeGap = Calc_MidHingeGap(Calc_HingeGap(door.slab.height, door.hinge_margin, door.hinge_qty), door.hinge_margin, door.hinge_qty);
		auto bottomQuad = vrtx::Quad(1.1875f, 6.75f).skew<tl>([](Vec3& v) { v.x += 1.0f; });
		
		auto topAdjust = [midHingeGap](Vec3& v){ v.y = midHingeGap[0]; };
		auto topQuad = bottomQuad;
		topQuad.mirror(&Vec3::x).move(&Vec3::y, (6.75f + 4.5f))
		.skew<tl>(topAdjust)
		.skew<tr>(topAdjust);

		auto middleQuad = vrtx::Quad{
			bottomQuad.get<bl>(),
			bottomQuad.get<tl>(),
			topQuad.get<bl>(),
			topQuad.get<tl>()
		};

		return std::vector<vrtx::Quad>{bottomQuad, middleQuad, topQuad};
	}

	Door exampleDoor {
		.slab = { 
			.width  = 36,
			.height = 84,
			.depth  = 1.75
		},
		.handing = Swing::RH,
		
		.hinge_qty = 3,
		.hinge = {
			.width  = 4.5,
			.height = 4.5,
			.depth  = .1875,
			.radius = 0,
		},
		.hinge_margin = 9,
		.hinge_depth_margin = 0.125,
	};
}