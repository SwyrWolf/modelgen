module;
#include <vector>
#include <ranges>

export module hinge;
import weretype;

export namespace hinge {
	
} 

export auto HingeCTC(f32 height, u64 hingeQty) -> std::vector<f32> {
	std::vector<f32> prepLoc(hingeQty);
	f32 ctc = (height - (9*2)) / (hingeQty - 1);

	for (int i : std::views::iota(0, as<int>(hingeQty))) {
		prepLoc[i] = 9 + (ctc * i);
	}

	return prepLoc;
}