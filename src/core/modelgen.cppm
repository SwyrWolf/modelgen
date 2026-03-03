module;

#include <vector>
#include <string>
#include <fstream>
#include <expected>
#include <algorithm>
#include <array>

export module modelgen;
import weretype;
import werevec;

export namespace modelgen {
	struct VecIdx  { u32    p, t, n;    };
	struct VecQuad { VecIdx a, b, c, d; };

	struct Model {
		std::vector<Vec3>    pos;
		std::vector<Vec3>    nor;
		std::vector<Vec2>    tex;
		std::vector<VecQuad> face;
	};

	namespace direction {
		constexpr Vec3 Front  {  0,  0, -1 };
		constexpr Vec3 Back   {  0,  0,  1 };
		constexpr Vec3 Left   { -1,  0,  0 };
		constexpr Vec3 Right  {  1,  0,  0 };
		constexpr Vec3 Top    {  0,  1,  0 };
		constexpr Vec3 Bottom {  0, -1,  0 };
	}

	constexpr auto CubeNormals = std::to_array<Vec3>({
		direction::Front,
		direction::Back,
		direction::Left,
		direction::Right,
		direction::Top,
		direction::Bottom,
	});

	// 80" (6'8") height door hinge placement - 9" + 31" + 31"
	// 84" (7'0") height door hinge placement - 9" + 33" + 33"
	// 86" height door hinge placement - 9" + 34" + 34"

	auto SlabModel(f32 w, f32 h, f32 d) -> Model {
		Model slab;
		f32 n = std::max((w+d), (h+d));

		slab.pos.reserve(8);
		slab.pos.emplace_back(Vec3{ -w/2, 0.0f, -d/2 }); // front - bottom - left
		slab.pos.emplace_back(Vec3{  w/2, 0.0f, -d/2 }); // front - bottom - right
		slab.pos.emplace_back(Vec3{  w/2, h,    -d/2 }); // front - top - right
		slab.pos.emplace_back(Vec3{ -w/2, h,    -d/2 }); // front - top - left
		slab.pos.emplace_back(Vec3{ -w/2, 0.0f,  d/2 }); // back - bottom - left
		slab.pos.emplace_back(Vec3{  w/2, 0.0f,  d/2 }); // back - bottom - right
		slab.pos.emplace_back(Vec3{  w/2, h,     d/2 }); // back - top - right
		slab.pos.emplace_back(Vec3{ -w/2, h,     d/2 }); // back - top - left

		slab.nor.append_range(CubeNormals);

		slab.tex.emplace_back(Vec2{ 0,     0     });
		slab.tex.emplace_back(Vec2{ (w/n), 0     });
		slab.tex.emplace_back(Vec2{ (w/n), (d/n) });
		slab.tex.emplace_back(Vec2{ 0,     (d/n) });

		slab.tex.emplace_back(Vec2{ ((w+d)/n), (d/n)     });
		slab.tex.emplace_back(Vec2{ ((w+d)/n), ((h+d)/n) });
		slab.tex.emplace_back(Vec2{ ((w)/n),   ((h+d)/n) });
		slab.tex.emplace_back(Vec2{ 0,         ((h+d)/n) });

		slab.face.emplace_back(
			VecQuad{ {4,8,1}, {3,7,1}, {2,3,1}, {1,4,1} } // front - ftl/ftr/fbr/fbl
		);
		slab.face.emplace_back(
			VecQuad{ {7,8,2}, {8,7,2}, {5,3,2}, {6,4,2} } // back
		);
		slab.face.emplace_back(
			VecQuad{ {8,6,3}, {4,7,3}, {1,3,3}, {5,5,3} } // left - btl/ftl/fbl/bbl
		);
		slab.face.emplace_back(
			VecQuad{ {3,7,4}, {7,6,4}, {6,5,4}, {2,3,4} } // right - ftr/btr/bbr/fbr
		);
		slab.face.emplace_back(
			VecQuad{ {8,4,5}, {7,3,5}, {3,2,5}, {4,1,5} } // top - btl/btr/ftr/ftl
		);
		slab.face.emplace_back(
			VecQuad{ {1,4,6}, {2,3,6}, {6,2,6}, {5,1,6} } // bottom - fbl/fbr/bbr/bbl
		);

		return slab;
	}

	auto WriteObj(std::string_view path, const Model& m) 
	-> std::expected<void, std::string> {
		std::ofstream file(std::string(path), std::ios::binary);

		if (!file) return std::unexpected("Failed to open file!");

		file << "# C++ model gen!\n";
		for (const auto& v : m.pos) {
			file << "v "
				<< v.x << ' '
				<< v.y << ' '
				<< v.z << '\n';
		}
		file << "\n";

		for (const auto& v : m.nor) {
			file << "vn "
				<< v.x << ' '
				<< v.y << ' '
				<< v.z << '\n';
		}
		file << "\n";

		for (const auto& v : m.tex) {
			file << "vt "
				<< v.u << ' '
				<< v.v << '\n';
		}
		file << "\n";
		file << "s off\n";
		
		for (const auto& quad : m.face) {
			file << "\n";
			file << "f "
				<< quad.a.p << '/'
				<< quad.a.t << '/'
				<< quad.a.n << ' '

				<< quad.b.p << '/'
				<< quad.b.t << '/'
				<< quad.b.n << ' '

				<< quad.c.p << '/'
				<< quad.c.t << '/'
				<< quad.c.n << ' '

				<< quad.d.p << '/'
				<< quad.d.t << '/'
				<< quad.d.n;
		}

		return {};
	}
}