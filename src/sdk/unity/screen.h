#pragma once
#include <null-mono.h>

namespace unity {
	class c_screen {
	public:
		static int get_width() {
			static mono::method_t::invoker_t<int()> invoker{ mono::property_t::parse("[UnityEngine.CoreModule.dll] UnityEngine:Screen->width")->getter() };
			return invoker();
		}

		static int get_height() {
			static mono::method_t::invoker_t<int()> invoker{ mono::property_t::parse("[UnityEngine.CoreModule.dll] UnityEngine:Screen->height")->getter() };
			return invoker();
		}
	};
}