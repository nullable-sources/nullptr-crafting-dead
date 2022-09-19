#include <iostream>
#include <iomanip>

#include <sdk/sdk.h>

#define print_info(name, object) std::cout << "[ sdk ] | " << std::left << std::setw(20) << name << std::setw(10) << " = " << std::nouppercase << std::showbase << std::hex << (std::uintptr_t)object << std::endl;

namespace sdk {
	void initialize() {
		std::cout << "[ sdk ] initialization..." << std::endl;

		print_info("dxgi", dxgi.pe_image.base_address.address);
		print_info("unityplayer", unityplayer.pe_image.base_address.address);

		window.wnd_handle = memory::signature_t{ unityplayer.pe_image, "48 89 3D ? ? ? ? 48 83 F8 01" }.find().jump(0x3).deref();
		print_info("window handle", window.wnd_handle);

		std::cout << "[ sdk ] initializated" << std::endl << std::endl;
	}

	void destroy() {
		//mono::thread_t::detach_all();
	}
}