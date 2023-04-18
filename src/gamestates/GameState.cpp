#include "Gamestate.h"
#include "raylib.h"
#include "../sprites/SpriteManager.h"

void GameState::init(){}
void GameState::update(){}
void GameState::clear(){}

void UIManager::update(){
    for (int i = 0; i < buttons.size(); i++){
        draw_button(i); 
    }

    handle_item_scaling();
    handle_player_input();
    draw_menu_selector();
    

    
}



void UIManager::draw_button(int button_index){
    
    float button_scale = currently_scaled_item == button_index ? 1 + (current_item_scale * max_item_scale_bonus) : 1;
    float button_x = button_x_pos - buttons[button_index].text.length() * 16 * button_scale;
    float button_y = button_y_pos + (button_offset * button_index) - ((button_scale - 1) * 30);


    SpriteManager::getInstance()->drawText(buttons[button_index].text, button_x, button_y , button_scale, true);

    // draw check box
    if (buttons[button_index].is_checkbox){
        std::string sprite = buttons[button_index].chekcbox_value ? "menu_indicator_1" : "menu_indicator_2";
        
        
        SpriteManager::getInstance()->drawTexture({sprite, 
        {button_x + (buttons[button_index].text.length() * 45 * button_scale), button_y + (select_icon_offset_y * button_scale)}
        , 4 * button_scale, 0, WHITE, false, layer_priority, true});
    }

    

}



void UIManager::on_button_activate(int button_index){
    buttons[button_index].function();

    if (buttons[button_index].is_checkbox){
        buttons[button_index].chekcbox_value = !buttons[button_index].chekcbox_value;
    }

    // button scale animation
    currently_scaled_item = button_index;
    current_item_scale = 2.5f;
}



void UIManager::handle_item_scaling(){
    if (currently_scaled_item == currently_selected_button && current_item_scale != 1){
        
        if (current_item_scale < 1){
            current_item_scale += item_scale_speed;
            if (current_item_scale > 1) current_item_scale = 1;
        }else{
            current_item_scale -= item_scale_speed;
            if (current_item_scale < 1) current_item_scale = 1;
        }
        
    
    }else if (current_item_scale > 0 && currently_scaled_item != currently_selected_button){
        
        current_item_scale -= item_scale_speed;
        if (current_item_scale < 0) current_item_scale = 0;

    }else{
        currently_scaled_item = currently_selected_button;
    }
}


void UIManager::draw_menu_selector(){
    // drawing
    SpriteManager::getInstance()->drawTexture(RenderData{"menu_select", {button_x_pos + select_icon_offset + 32, button_y_pos + (button_offset * select_icon_pos) + select_icon_offset_y}, 4, 0, WHITE, false, layer_priority, true});
    SpriteManager::getInstance()->drawTexture(RenderData{"menu_select", {button_x_pos - select_icon_offset + 32, button_y_pos + (button_offset * select_icon_pos) + select_icon_offset_y}, 4, 0, WHITE, false, layer_priority, true});


    // movement
    if (select_icon_pos < currently_selected_button){
        select_icon_pos += select_icon_speed;
        if (select_icon_pos > currently_selected_button) select_icon_pos = currently_selected_button;
    }else if (select_icon_pos > currently_selected_button){
        select_icon_pos -= select_icon_speed;
        if (select_icon_pos < currently_selected_button) select_icon_pos = currently_selected_button;
    }

    // change offset
    desired_select_icon_offset = (buttons[currently_selected_button].text.length() * 30) + select_icon_additional_offset;

    if (select_icon_offset < desired_select_icon_offset){
        select_icon_offset += select_icon_horizontal_speed;
        if (select_icon_offset > desired_select_icon_offset) select_icon_offset = desired_select_icon_offset;
    }else if (select_icon_offset > desired_select_icon_offset){
        select_icon_offset -= select_icon_horizontal_speed;
        if (select_icon_offset < desired_select_icon_offset) select_icon_offset = desired_select_icon_offset;
    }
}


void UIManager::handle_player_input(){

    // move cursor
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        currently_selected_button--;
        Sound_manager::get_instance()->play_sound("click");
        if (currently_selected_button < 0)
            currently_selected_button = buttons.size() - 1;
    }

    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
        currently_selected_button++;
        Sound_manager::get_instance()->play_sound("click");

        if (currently_selected_button >= buttons.size()) 
            currently_selected_button = 0;
    }
    // activate button
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)){
        Sound_manager::get_instance()->play_sound("click");

        on_button_activate(currently_selected_button);
    } 

}


void UIManager::addButton(Button button){
    buttons.push_back(button);
}



void UIManager::clear(){
    buttons.clear();
    currently_selected_button = 0;
}



UIManager* UIManager::getInstance(){
    if (!instance) instance = new UIManager();
    return instance;
}

UIManager* UIManager::instance = 0;

void UIManager::dispose(){
    clear();
    delete instance;
}

