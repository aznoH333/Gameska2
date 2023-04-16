#include "Settings_Manager.h"
#include <filesystem>
#include <fstream>
#include <string>

Persistent_Data_Manager* Persistent_Data_Manager::get_instance(){
    if (!instance) instance = new Persistent_Data_Manager();
    return instance;
}

Persistent_Data_Manager* Persistent_Data_Manager::instance = 0;

void Persistent_Data_Manager::init(){
    if (std::filesystem::exists(data_file_path)){
        create_new_data_file();
    }
    load_data_file();
}

Persistent_Data* Persistent_Data_Manager::get_data(){
    return &data;
}

void Persistent_Data_Manager::dispose(){
    save_data_file();
    delete instance;
}

void Persistent_Data_Manager::create_new_data_file(){

}

void Persistent_Data_Manager::load_data_file(){
    std::ifstream data_file(data_file_path);
    
    std::string load_data;

    //load screen shake
    std::getline(data_file, load_data);
    data.screen_shake = std::stoi(load_data);
    
    
    // load gore
    std::getline(data_file, load_data);
    data.gore = std::stoi(load_data);

    //load score
    std::getline(data_file, load_data);
    data.high_score = std::stoi(load_data);

    data_file.close();
}



void Persistent_Data_Manager::save_data_file(){
    std::ofstream data_file;
    
    data_file.open(data_file_path);
    
    data_file.clear();
    data_file << data.screen_shake << std::endl;
    data_file << data.gore << std::endl;
    data_file << data.high_score << std::endl;
    

    data_file.close();
}
