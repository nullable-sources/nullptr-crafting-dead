#pragma once
#include <Windows.h>
#include <format>
#include <fstream>
#include <iostream>
#include <ranges>
#include <chrono>

#include <data-types/vec2.h>
#include <data-types/callbacks.h>

namespace utils {
	enum class e_window_callbacks {
		on_create, //@note: void()
		on_destroy, //@note: void()
		on_main_loop, //@note: void()
		on_wnd_proc //@note: int(HWND, UINT, WPARAM, LPARAM). If callback returns != -1 then DefWindowProc call will be skipped.
	};

	namespace win {
		class c_window {
		public:
			struct time_data_t {
				std::chrono::steady_clock::time_point last_frame{ };
				float delta_time{ };
				
			public:
				void initialize();
				void begin_frame();
			} time_data{ };

		public:
			array_callbacks_t<e_window_callbacks> callbacks{ };

			HWND wnd_handle{ nullptr };
			HINSTANCE instance{ };
			WNDCLASSA wnd_class{
				CS_CLASSDC,
				&c_window::wnd_proc,
				0,
				sizeof(c_window*),
				instance,
				LoadIcon(instance, MAKEINTRESOURCE(107)),
				LoadCursor(nullptr, IDC_ARROW),
				(HBRUSH)(COLOR_WINDOW),
				MAKEINTRESOURCEA(109),
				"null"
			};

			std::string name{ "null" };
			vec2_t pos{ 100, 100 }, size{ 800, 600 };

			std::uint32_t styles{ WS_OVERLAPPEDWINDOW };

		public:
			c_window() : wnd_handle(GetActiveWindow()) { }
			c_window(const HINSTANCE& _instance) : instance(_instance) { }
			c_window(const HWND& _wnd_handle) : wnd_handle(_wnd_handle) { }

		public:
			bool create();
			void destroy();

			void main_loop();

			//@note: use for get size from wnd_handle
			vec2_t get_window_size() const;

			template<typename char_t>
			void write_clipboard(std::basic_string_view<char_t> str) {
				if(!OpenClipboard(wnd_handle)) throw std::runtime_error{ "cant open clipboard" };

				EmptyClipboard();
				HGLOBAL data{ GlobalAlloc(GMEM_DDESHARE, sizeof(char_t) * (str.length() + 1)) };
				std::memcpy(GlobalLock(data), str.data(), sizeof(char_t) * (str.length() + 1));
				GlobalUnlock(data);

				SetClipboardData(std::is_same_v<char_t, wchar_t> ? CF_UNICODETEXT : CF_TEXT, data);
				if(!CloseClipboard()) throw std::runtime_error{ "cant clise clipboard" };
			}

			template <typename char_t>
			std::basic_string<char_t> read_clipboard() {
				if(!OpenClipboard(wnd_handle)) throw std::runtime_error{ "cant open clipboard" };

				std::basic_string<char_t> clipboard{ };
				if(HANDLE data{ GetClipboardData(std::is_same_v<char_t, wchar_t> ? CF_UNICODETEXT : CF_TEXT) }) {
					clipboard = (char_t*)GlobalLock(data);
				} else throw std::runtime_error{ "cant get clipboard data" };

				if(!CloseClipboard()) throw std::runtime_error{ "cant clise clipboard" };
				return clipboard;
			}

			virtual void on_create() { callbacks.call<void()>(e_window_callbacks::on_create); }
			virtual void on_destroy() { callbacks.call<void()>(e_window_callbacks::on_destroy); }
			virtual void on_main_loop() { callbacks.call<void()>(e_window_callbacks::on_main_loop); }
			virtual std::vector<std::any> on_wnd_proc(HWND _wnd_handle, UINT msg, WPARAM w_param, LPARAM l_param) { return callbacks.call<int(HWND, UINT, WPARAM, LPARAM)>(e_window_callbacks::on_wnd_proc, _wnd_handle, msg, w_param, l_param); }

		private:
			static LRESULT WINAPI wnd_proc(HWND _wnd_handle, UINT msg, WPARAM w_param, LPARAM l_param);
		};
	}

	namespace console {
		inline FILE* old_out{ }, *old_in{ };

		void attach();
		void detach();

		template <typename... args_t>
		static void print(std::string_view text, args_t&&... args) {
			std::cout << std::vformat(text, std::make_format_args(args...));
		}

		class i_command {
		public:
			static inline std::vector<i_command*> registered_commands{ };

			static bool handle(std::string_view str);

		public:
			i_command() { registered_commands.push_back(this); }

		public:
			virtual bool execute(const std::vector<std::string_view>& args) = 0;

			virtual std::string name() = 0;
			virtual std::string description() = 0;
		};
	}
}