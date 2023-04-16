#ifndef SETTINGS_MANAGER
#define SETTINGS_MANAGER

#include <filesystem>
#include <iostream>
#include <fstream>





struct Persistent_Data{
    bool gore = true;
    bool screen_shake = true;
    int high_score = 0;
};


class Persistent_Data_Manager{
    private:
        Persistent_Data data;
        static Persistent_Data_Manager* instance;

        const std::filesystem::path data_file_path = {"data.txt"};

        void create_new_data_file();
        void load_data_file();
        void save_data_file();

    public:
        void init();
        static Persistent_Data_Manager* get_instance();
        Persistent_Data* get_data();
        void dispose();
};

#endif