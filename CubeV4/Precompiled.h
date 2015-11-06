// windows
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// sdl
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_syswm.h>

// d3d
#include <d3d11.h>
#include <dxgi1_2.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// std
#include <type_traits>
#include <utility>
#include <atomic>
#include <algorithm>
#include <assert.h>

//
using u8 = uint8_t;
using u16 = uint16_t;
using i16 = int16_t;
using u32 = uint32_t;
using i32 = int32_t;
using u64 = uint64_t;
using i64 = int64_t;
using f32 = float;
using f64 = double;
