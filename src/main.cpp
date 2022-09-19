#include <null-sdk.h>
#include <null-input.h>
#include <hooks/hooks.h>
#include <sdk/sdk.h>

namespace commands {
    struct help_t : public utils::console::i_command {
    public:
        virtual bool execute(const std::vector<std::string>&) {
            for(auto& command : registered_commands) {
                std::cout << command->name() << " " << command->description() << std::endl;
            }
            return true;
        }

        virtual std::string name() { return "/help"; }
        virtual std::string description() { return "{ wtihe all commands }"; }
    } inline help{ };

    struct clear_t : public utils::console::i_command {
    public:
        virtual bool execute(const std::vector<std::string>&) {
            system("cls");
            return true;
        }

        virtual std::string name() { return "/clear"; }
        virtual std::string description() { return "{ clear command window }"; }
    } inline clear{ };

    struct detach_t : public utils::console::i_command {
    public:
        bool state{ };

    public:
        virtual bool execute(const std::vector<std::string>&) {
            state = true;
            return true;
        }

        virtual std::string name() { return "/detach"; }
        virtual std::string description() { return "{ detach dll }"; }
    } inline detach{ };
}

void attach(HMODULE module) {
    try {
        utils::console::attach();
        null::render::global_atlas.add_font_from_file_ttf("C:\\Windows\\fonts\\Tahoma.ttf", 13.f, nullptr, null::render::c_font::glyph_t::ranges_cyrillic());

        sdk::initialize();
        hooks::initialize();
    } catch(const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    while(!commands::detach.state) {
        std::string line{ };
        std::getline(std::cin, line);
        utils::console::i_command::handle(line);

        std::this_thread::sleep_for(std::chrono::milliseconds{ 200 });
    }

    FreeLibrary(module);
}

void detach() {
    hooks::destroy();
    sdk::destroy();
    utils::console::detach();
}

BOOL APIENTRY DllMain(HMODULE module, DWORD  reason_for_call, LPVOID reserved) {
    switch(reason_for_call) {
        case DLL_PROCESS_ATTACH: { std::thread{ attach, module }.detach(); } break;
        case DLL_PROCESS_DETACH: detach(); break;
    } return true;
}

