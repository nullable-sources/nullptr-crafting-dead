#pragma once
#include <null-sdk.h>
#include <dxgi.h>

namespace hooks {
	struct swap_chain_t : memory::minhook::hook_t<swap_chain_t, HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT)> {
		static HRESULT __stdcall hook(IDXGISwapChain* swap_cain, UINT sync_interval, UINT flags);
	};
}