#include <iostream>
#include <iomanip>

#include <sdk/sdk.h>

#define print_info(name, object) std::cout << "[ sdk ] | " << std::left << std::setw(20) << name << std::setw(10) << " = " << std::nouppercase << std::showbase << std::hex << (std::uintptr_t)object << std::endl;

struct internal_unityplayer_structure_t {
public:
    void* get_swap_chain() {
        return memory::address_t(this).offset(0x320).deref();
    }
};

namespace sdk {
	void initialize() {
		std::cout << "[ sdk ] initialization..." << std::endl;

		print_info("dxgi", dxgi.pe_image.base_address.address);
		print_info("unityplayer", unityplayer.pe_image.base_address.address);

        auto sig = memory::signature_t(unityplayer.pe_image, "49 8B 4E 20 48 8B 05 ? ? ? ?").find();
        internal_unityplayer_structure_t* structure = sig.jump(0x7).deref();
        dx11_data.swap_chain = (IDXGISwapChain*)structure->get_swap_chain();

		window.wnd_handle = memory::signature_t{ unityplayer.pe_image, "48 89 3D ? ? ? ? 48 83 F8 01" }.find().jump(0x3).deref();
		print_info("window handle", window.wnd_handle);

		std::cout << "[ sdk ] initializated" << std::endl << std::endl;
	}

	void destroy() {
		//mono::thread_t::detach_all();
	}
}