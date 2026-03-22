module;

#include <array>
#include <vector>
#include <ranges>

export module door;
import weretype;
import werevec;

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
		f32 hinge_depth_padding{};
	};

	auto Calc_HingeGap(f32 slabHeight, f32 margin, size_t qty) -> f32 {
		return (slabHeight - (margin * 2)) / (qty - 1);
	}

	struct CloneOffset_adapter {
		f32 Vec3::* axis;
		f32 offset;

		template <std::ranges::input_range R>
		friend auto operator|(R&& r, CloneOffset_adapter fn) -> std::array<Vec3, 2> {
			std::array<Vec3, 2> out{};
			for (auto&& [i, src] : r | std::views::enumerate) {
				out[i] = src;
				out[i].*fn.axis += fn.offset;
			}
			return out;
		}
	};

	constexpr auto CloneOffset(f32 Vec3::* axis, f32 offset) -> CloneOffset_adapter {
		return {axis, offset};
	}

	auto Create_SquareQuad(f32 width, f32 height) -> std::array<Vec3, 4> {
		std::array<Vec3, 4> out{};
		size_t half{2};
		
		out[1].x = width;
		auto top = 
			out
			| std::views::take(half)
			| std::views::reverse
			| CloneOffset(&Vec3::y, height);
		std::ranges::copy(top, out.begin() + half);

		return out;
	}

	auto Gen_HingeVrts(Door door) -> std::vector<Vec3> {
		std::vector<Vec3> pos{};
		pos.emplace_back(Vec3{});

		return pos;
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
		.hinge_depth_padding = 0.125,
	};
}