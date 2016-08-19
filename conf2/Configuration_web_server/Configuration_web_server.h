
#ifndef Configuration_web_server_h
#define Configuration_web_server_h

#define params_count     8
#define web_page_lines   7
#define params_begin     5 

#include <arduino.h>
#include <EEPROM.h>
#include <SPI.h>

#include <UIPEthernet.h>

#include <avr/pgmspace.h>





class Configuration_web_server
{
  public:
    int beg_EEPROM_address;
    IPAddress  ip;
    byte       mac[];
    // properties
    char big_str[255];
    char buff[255];
    char buff35[35];
    char buff3[3];
    //char buffer_val[params_count][255];
    //char buffer_about[255];
    char buffer_num [11];
    char buffer_num2[11];
    bool need_restart;
    bool need_defaults;
    bool changed_some_value_in_CWS[params_count];
    bool parameter_present        [params_count];
    void restart_if_need();

    //String main_text[255]; //= {"asdasd","sdsdds"};
    uint8_t count_string_for_print;
    void (*new_parameters_Callback)();
    // methods
    void init_CWS(int  start_EEPROM_address , bool reset_to_default_data = false);
    // get parameters values from EEPROM metods
    //uint8_t get_param_as_uint8_t(uint8_t par_num);
    const char *  get_value_as_byte_array_in_buff (uint8_t str_num);
    const char *  get_value_as_string             (uint8_t str_num);
    long          get_value_as_integer_long       (uint8_t str_num);
    
    //uint8_t get_param_as_IP     (uint8_t par_num);
    
    void save_new_parameters_from_GET_url_string(char * qerry);
    void reset_to_defaults();
    void update_value_in_buff(uint8_t par_num,const char * new_value);

    const char * print_main_text3(uint8_t str_num);
    const char * print_one_parameter(uint8_t str_num);
    const char * get_next_string_for_print();
    char *replace_str( char *str, const char *f, const char *t );
    char buffer_tmp[255];
    
    uint8_t get_parameter_EEPROM_begin_address(uint8_t str_num);
     
    
    //uint8_t add_new_par(uint8_t id,String p_name, String about = "no description", char * default_value = "",bool can_be_modify = true, uint8_t type_p = 0);
};



//extern Configuration_web_server CWS;
#endif
