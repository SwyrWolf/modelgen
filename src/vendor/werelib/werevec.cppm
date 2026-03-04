module;

#include <format>
#include <span>
#include <array>

export module werevec;
import weretype;

constexpr u64 hash_combine(u64 h, u64 k) noexcept {
	return h ^ (k + 0x9e3779b97f4a7c15ull + (h << 6) + (h >> 2));
}
constexpr u64 f32_hash(f32 f) noexcept {
	u32 bits = std::bit_cast<u32>(f);
	return as<u64>(bits);
}

export {
	
	struct Vec3 {
		f32 x{}, y{}, z{};

		constexpr Vec3() = default;
		constexpr Vec3(f32 X, f32 Y, f32 Z) : x(X), y(Y), z(Z) {}
		constexpr Vec3(std::array<f32, 3> arr) : x(arr[0]), y(arr[1]), z(arr[2]) {}

		constexpr explicit operator std::array<f32,3>() const { return {x,y,z}; }
		auto operator<=>(const Vec3&) const = default;
	};
	template<>
	struct std::formatter<Vec3> : std::formatter<std::string_view> {
		auto format(const Vec3& val, std::format_context& ctx) const {
			return std::format_to(ctx.out(), "({}, {}, {})", val.x, val.y, val.z);
		}
	};
	template<>
	struct std::hash<Vec3> {
		u64 operator()(const Vec3& val) const noexcept {
			u64 h{};
			h = hash_combine(h, f32_hash(val.x));
			h = hash_combine(h, f32_hash(val.y));
			h = hash_combine(h, f32_hash(val.z));
			return h;
		}
	};
	
	struct Vec2 {
		f32 u{}, v{};

		constexpr Vec2() = default;
		constexpr Vec2(f32 U, f32 V) : u(U), v(V) {}
		constexpr Vec2(std::array<f32, 2> arr) : u(arr[0]), v(arr[1]) {}

		constexpr explicit operator std::array<f32,2>() const { return {u,v}; }
		auto operator<=>(const Vec2&) const = default;
	};
	template<>
	struct std::formatter<Vec2> : std::formatter<std::string_view> {
		auto format(const Vec2& val, std::format_context& ctx) const {
			return std::format_to(ctx.out(), "({}, {})", val.u, val.v);
		}
	};
	template<>
	struct std::hash<Vec2> {
		u64 operator()(const Vec2& val) const noexcept {
			u64 h{};
			h = hash_combine(h, f32_hash(val.u));
			h = hash_combine(h, f32_hash(val.v));
			return h;
		}
	};

}