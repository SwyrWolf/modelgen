## CubicGen() Examples
Version 1:
```cpp
constexpr auto CubicGen(f32 w, f32 h, f32 d) -> std::array<Vec3, 8> {
	std::array<Vec3, 8> out{};

	f32 width = w/2;
	f32 depth = d/2;
	for (u8 i : std::views::iota(0, 2)) {
		u8 elm = i * 4;
		f32 height = h * i;
		out[0 + elm] = Vec3(-width, height, -depth);
		out[1 + elm] = Vec3( width, height, -depth);
		out[2 + elm] = Vec3( width, height,  depth);
		out[3 + elm] = Vec3(-width, height,  depth);
	}
	return out;
}
```
Version 2:
```cpp
constexpr auto CubicGen(f32 w, f32 h, f32 d) -> std::array<Vec3, 8> {
	std::array<Vec3, 8> out{};

	auto r1 = out | std::views::take(1) | std::views::transform([](Vec3 p){ p.x *= -1; return p; });
	auto r2 = out | std::views::take(2) | std::views::reverse | std::views::transform([](Vec3 p){ p.z *= -1; return p; });
	auto r3 = out | std::views::take(4) | std::views::transform([h](Vec3 p){ p.y = h; return p; });
	
	std::ranges::copy(r1, out.begin() + 1); // out[1] = *r1.begin();
	std::ranges::copy(r2, out.begin() + 2);
	std::ranges::copy(r3, out.begin() + 4);
	return out;
}
```

## SlabModel() Snippet
```cpp
	slab.pos.reserve(8);
	slab.pos.emplace_back(Vec3{ -w/2, 0.0f, -d/2 }); // front - bottom - left
	slab.pos.emplace_back(Vec3{  w/2, 0.0f, -d/2 }); // front - bottom - right
	slab.pos.emplace_back(Vec3{  w/2, h,    -d/2 }); // front - top - right
	slab.pos.emplace_back(Vec3{ -w/2, h,    -d/2 }); // front - top - left
	slab.pos.emplace_back(Vec3{ -w/2, 0.0f,  d/2 }); // back - bottom - left
	slab.pos.emplace_back(Vec3{  w/2, 0.0f,  d/2 }); // back - bottom - right
	slab.pos.emplace_back(Vec3{  w/2, h,     d/2 }); // back - top - right
	slab.pos.emplace_back(Vec3{ -w/2, h,     d/2 }); // back - top - left
```