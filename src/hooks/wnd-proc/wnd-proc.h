#pragma once
#include <null-sdk.h>

namespace hooks {
	struct wnd_proc_t : memory::minhook::hook_t<wnd_proc_t, LRESULT(__fastcall*)(HWND, UINT, WPARAM, LPARAM)> {
		static int __fastcall hook(HWND window, std::uint32_t msg, std::uint64_t w_param, std::int64_t l_param);
	};
}