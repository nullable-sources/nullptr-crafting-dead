#include <functions/visuals/visuals.h>

namespace commands {
    struct visuals_t : public utils::console::i_command {
    public:
        bool state{ };

    public:
        virtual bool execute(const std::vector<std::string_view>& args) {
            if(args.empty()) return false;
            state = std::stoi(std::string(args[0]));
            return true;
        }

        virtual std::string name() { return "/visuals"; }
        virtual std::string description() { return "<int:state> { enable and disable visual functions, 1 - enable, 0 - disable }"; }
    } inline visuals{ };
}

namespace functions::visuals {
    void handle() {
        if(!bolt::c_bolt_network::is_connected() || !sdk::c_entity_player::local_player() || !commands::visuals.state) return;

        draw_hud();
        draw_zombies();
    }

    void draw_hud() {
        if(!sdk::c_entity_player::local_player()->is_alive()) return; //@note: im too lazy to do the correct is_connected check, so it will crash when reconnecting.
        sdk::c_player_controller* component{ (sdk::c_player_controller*)sdk::c_entity_player::local_player()->get_component(mono::class_t::parse("[Assembly-CSharp.dll] PlayerController")->type()) };
        
        null::render::background_layer.draw_text(std::format("name: {}\njump: {}\ncrouch: {}\nsprint: {}", sdk::c_entity_player::local_player()->user_name()->to_utf8(), component->jump(), component->crouch(), component->sprint()), { 100 }, { }, null::e_text_flags::outline);
    }

    void draw_zombies() {
        vec2_t screen_centre{ vec2_t{ unity::c_screen::get_width(), unity::c_screen::get_height() } / 2.f };

        bolt::c_bolt_double_list<bolt::c_entity*>* entities{ bolt::c_bolt_core::entities() };
        for(bolt::c_entity* entity{ entities->first() }; entity != entities->last(); entity = entities->next(entity)) {
            bolt::c_bolt_entity* bolt_entity{ entity->unity_object() };
            switch(bolt_entity->prefab_id()) {
                case bolt::e_prefabs::zombie: {
                    vec2_t foot_screen{ };

                    vec3_t foot_pos{ bolt_entity->transform()->get_position() };
                    if(unity::c_camera::main()->world_to_screen(foot_pos, foot_screen))
                        null::render::background_layer.draw_line(screen_centre, foot_screen, { });
                    
                    vec2_t eye_screen{ };
                    if(unity::c_camera::main()->world_to_screen(foot_pos + vec3_t{ 0.f, 1.5f, 0.f }, eye_screen))
                        null::render::background_layer.draw_text("zombie", eye_screen, { }, null::e_text_flags{ null::e_text_flags::aligin_center | null::e_text_flags::outline });
                } break;

                case bolt::e_prefabs::airdrop: {
                    vec2_t screen{ };
                    if(!unity::c_camera::main()->world_to_screen(bolt_entity->transform()->get_position(), screen))
                        continue;

                    null::render::background_layer.draw_text("airdrop", screen, { }, null::e_text_flags{ null::e_text_flags::aligin_center | null::e_text_flags::outline });
                } break;
            }
        }
    }
}