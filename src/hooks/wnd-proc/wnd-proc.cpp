#include <null-input.h>
#include <hooks/hooks.h>

namespace hooks {
	int __fastcall wnd_proc_t::hook(HWND window, std::uint32_t msg, std::uint64_t w_param, std::int64_t l_param) {
		null::input::wnd_proc(window, msg, w_param, l_param);
		return original(window, msg, w_param, l_param);
	}
}