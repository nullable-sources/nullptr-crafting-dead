#include <hooks/hooks.h>
#include <null-input.h>
#include <null-render.h>
#include <null-renderer-directx11.h>
#include <functions/visuals/visuals.h>

namespace hooks {
    HRESULT __stdcall swap_chain_t::hook(IDXGISwapChain* swap_chain, UINT sync_interval, UINT flags) {
        static std::once_flag initialize{ };
        std::call_once(initialize, [&]() {
            sdk::window.time_data.initialize();
            sdk::dx11_data.initialize();
            null::render::directx11::initialize(sdk::dx11_data.device, sdk::dx11_data.context);
            });

        sdk::window.time_data.begin_frame();
        null::render::directx11::begin_frame();
        null::render::begin_frame(sdk::window);
        null::input::begin_frame(sdk::window); {
            mono::thread_t* thread{ mono::thread_t::attach() }; {
                functions::visuals::handle();
            } thread->detach();
        } null::render::end_frame();
        null::render::setup_draw_data();

        sdk::dx11_data.context->OMSetRenderTargets(1, &sdk::dx11_data.render_target, nullptr);
        null::render::directx11::render_draw_data();
        return original(swap_chain, sync_interval, flags);
    }
}