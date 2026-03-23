module;

#include <format>
#include <array>

export module vrtx;
import weretype;
import werevec;

export namespace vrtx {
	enum struct Vert : size_t { bl, br, tr, tl };
	struct Quad {
		std::array<Vec3, 4> m_vert{};
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