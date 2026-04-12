module;

#include <vector>
#include <array>
#include <utility>

export module direction;
import weretype;
import werevec;

export {
	enum struct eDirection : u8 { 
		x,y,z,
		n=0b1000
	};

	constexpr eDirection operator|(eDirection a, eDirection b) {
		return as<eDirection>(
			std::to_underlying(a) | std::to_underlying(b)
		);
	}

	constexpr eDirection operator&(eDirection a, eDirection b) {
		return as<eDirection>(
			std::to_underlying(a) & std::to_underlying(b)
		);
	}

	constexpr auto CubicDir(eDirection dir) -> Vec3 {
		std::array<f32,3> v{};
		auto i = std::to_underlying(dir);

		auto axis = i & 0b11; // X, Y, Z
		auto sign = (i & 0b1000) ? -1.f : 1.f; // negative or positive

		v[axis] = sign;

		return Vec3(v[0], v[1], v[2]);
	};

	constexpr auto CubicDir_Array() -> std::vector<Vec3> {
		using enum eDirection;
		std::vector<Vec3> dir{};
		dir.emplace_back(CubicDir(x));
		dir.emplace_back(CubicDir(x | n));
		dir.emplace_back(CubicDir(y));
		dir.emplace_back(CubicDir(y | n));
		dir.emplace_back(CubicDir(z));
		dir.emplace_back(CubicDir(z | n));

		return dir;
	}
}