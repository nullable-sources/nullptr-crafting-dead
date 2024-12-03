#include <hooks/hooks.h>
#include <sdk/sdk.h>

struct log_t : memory::minhook::hook_t<log_t, void(__fastcall*)(mono::object_t*)> {
	static void __fastcall hook(mono::object_t* object) {
		std::cout << "[ log ] | " << object->to_string()->to_utf8() << std::endl;
	} 
};

struct handle_command_t : memory::minhook::hook_t<handle_command_t, void(__thiscall*)(void*, void*, mono::string_t*)> {
	static void __stdcall hook(void* _this, void* sender, mono::string_t* message) {
		utils::console::i_command::handle(message->to_utf8());
		return original(_this, sender, message);
	}
};

namespace hooks {
	void initialize() {
		memory::minhook::initialize();

		wnd_proc_t::setup(memory::signature_t{ sdk::unityplayer.pe_image, "40 55 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B F1" }.find());
		swap_chain_t::setup((*(std::uintptr_t**)sdk::dx11_data.swap_chain)[8]);
		mono::thread_t* thread{ mono::thread_t::attach() }; {
			log_t::setup(mono::method_t::parse("[UnityEngine.CoreModule.dll] UnityEngine:Debug->Log(object)")->address());
			handle_command_t::setup(mono::method_t::parse("[Assembly-CSharp.dll] ChatManager->HandleCommand(ICommandSender, string)")->address());
		} thread->detach();
	}

	void destroy() {
		memory::minhook::destroy();
	}
}