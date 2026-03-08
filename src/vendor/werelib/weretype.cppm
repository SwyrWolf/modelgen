module;

export module weretype;

export {

	// [DATA ALIASES]
	using byte = unsigned char;

	using u8 = unsigned char;
	using u16 = unsigned short;
	using u32 = unsigned int;
	using u64 = unsigned long long;

	using i8 = signed char;
	using i16 = signed short;
	using i32 = signed int;
	using i64 = signed long long;

	using f32 = float;
	using f64 = double;

	// as<T>(V) -- static_cast alias at compile time
	template <typename ToType, typename From>
	[[nodiscard]] constexpr ToType as(From&& value) {
		return static_cast<ToType>(value);
	}

	// raw<T>(V) -- reinterpret_cast alias at compile time
	template <typename ToType, typename From>
	[[nodiscard]] constexpr ToType raw(From&& value) {
		return reinterpret_cast<ToType>(value);
	}
}