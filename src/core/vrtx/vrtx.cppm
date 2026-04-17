module;

#include <format>
#include <array>
#include <ranges>
#include <utility>

export module vrtx;
import weretype;
import werevec;

export namespace vrtx {
	enum struct Vert : size_t { bl, br, tr, tl };
	struct Quad {
		std::array<Vec3, 4> m_vert{};
		Quad(Vec3 bl, Vec3 br, Vec3 tr, Vec3 tl) 
			: m_vert{{ bl, br, tr, tl }} 
		{}
		Quad(f32 w, f32 h)
			: m_vert{{
				{0.0f, 0.0f, 0.0f},
				{w,    0.0f, 0.0f},
				{w,    h,    0.0f},
				{0.0f, h,    0.0f},
			}}
		{}

		template<Vert V>
		Quad& skew(Vec3 val) {
			std::get<std::to_underlying(V)>(m_vert) = val;
			return *this;
		}
		template<Vert V>
		Quad& skew(auto fn) {
			fn(std::get<std::to_underlying(V)>(m_vert));
			return *this;
		}
		template<Vert V>
		constexpr const Vec3& get() const noexcept {
			return std::get<std::to_underlying(V)>(m_vert);
		}

		Quad& move(f32 Vec3::* axis, f32 amount) {
			for (Vec3& v : m_vert) {
				v.*axis += amount;
			}
			return *this;
		}

		Quad& mirror(f32 Vec3::* axis) {
			auto src = m_vert;
			auto rev = src | std::views::reverse;
			for (auto [i, v] : were::thru(rev)) {
				m_vert[i].*axis = v.*axis;
			}

			return *this;
		}
	};
}

namespace std {
	template<>
	struct tuple_size<vrtx::Quad> : integral_constant<size_t, 4> {};

	template<size_t I>
	struct tuple_element<I, vrtx::Quad> {
		using type = Vec3;
	};

	template<>
	struct formatter<vrtx::Quad> : formatter<string_view> {
		auto format(const vrtx::Quad& q, format_context& ctx) const {
			return format_to(
				ctx.out(),
				"[{}, {}, {}, {}]",
				q.m_vert[0],
				q.m_vert[1],
				q.m_vert[2],
				q.m_vert[3]
			);
		}
	};
}