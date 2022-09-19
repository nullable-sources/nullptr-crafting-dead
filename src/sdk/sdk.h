#pragma once
#include <sdk/crafting-dead/entity-player.h>
#include <sdk/crafting-dead/player-camera.h>
#include <sdk/crafting-dead/entity-util.h>
#include <sdk/crafting-dead/player-controller.h>

#include <sdk/bolt/bolt-network.h>
#include <sdk/bolt/bolt-core.h>
#include <sdk/bolt/bolt-double-list.h>
#include <sdk/bolt/bolt-entity.h>
#include <sdk/bolt/entity.h>
#include <sdk/bolt/prefabs.h>

#include <null-render.h>
#include <null-renderer-directx11.h>
#include <dxgi.h>

namespace sdk {
	struct dx11_data_t {
	public:
		ID3D11Device* device{ };
		ID3D11DeviceContext* context{ };
		ID3D11RenderTargetView* render_target{ };
		ID3D11Texture2D* back_buffer{ };

	public:
		~dx11_data_t() { destroy(); }

	public:
		void initialize(IDXGISwapChain* swap_chain) {
			swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&device);

			device->GetImmediateContext(&context);

			ID3D11Texture2D* back_buffer{ };
			swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&back_buffer);
			device->CreateRenderTargetView(back_buffer, NULL, &render_target);
			back_buffer->Release();
		}

		void destroy() {
			if(device) { device->Release(); device = nullptr; }
			if(context) { context->Release(); context = nullptr; }
			if(render_target) { render_target->Release(); render_target = nullptr; }
			if(back_buffer) { back_buffer->Release(); back_buffer = nullptr; }
		}
	} inline dx11_data{ };

	inline utils::win::c_window window{ };
	inline memory::c_module unityplayer{ "UnityPlayer.dll" }, dxgi{ "dxgi.dll" };

	void initialize();
	void destroy();
}