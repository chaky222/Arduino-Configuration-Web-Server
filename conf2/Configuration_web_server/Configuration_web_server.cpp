
#ifndef Configuration_web_server_cpp
#define Configuration_web_server_cpp

#include "Configuration_web_server.h"


#define p_string   1
#define p_uint8_t  2
#define p_IP       3
#define p_MACarray 4
#define p_bool     5
#define p_reset    6
#define p_long32   7  //Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647. 



//-------------------------------------PARAMETERS HERE!------------------------------
//----------------------------parameter name-----------------------------default value---------------------------------------about this parameter------------------------------------parameter int_params[0]=max_length (in eeprom it will take this count of bytes)------int_params[1]=param_type. 1=String, 2=uint8_t,3=IPadres,4=mac array,5=bool.
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------third value - bool for is parameter for cofig_server or not. 1 = for_config_server
const char par_0[] PROGMEM = "MachineName";  const char def_0[] PROGMEM = "arduino2560";                  const char about_0[] PROGMEM = "Name of your Arduino board in LAN. Max length=35chars";                         const char int_params_0[] PROGMEM = {35,p_string  ,1};
const char par_1[] PROGMEM = "IPAddress";    const char def_1[] PROGMEM = {192,169,88,33,0};              const char about_1[] PROGMEM = "IPAddress of your Arduino board in LAN.";                                       const char int_params_1[] PROGMEM = {4, p_IP      ,1}; 
const char par_2[] PROGMEM = "MACAddress";   const char def_2[] PROGMEM={0xDE,0xAD,0xBE,0xEF,0xFE,0xED,0};const char about_2[] PROGMEM = "MACAddress this server in LAN.";                                                const char int_params_2[] PROGMEM = {6, p_MACarray,1};
const char par_3[] PROGMEM = "String demo";  const char def_3[] PROGMEM = "demo str";                     const char about_3[] PROGMEM = "This is demo string parameter for your Arduino board with LAN web server.";     const char int_params_3[] PROGMEM = {35,p_string  ,0};
const char par_4[] PROGMEM = "uint8 demo";   const char def_4[] PROGMEM = {200,0};                        const char about_4[] PROGMEM = "This is demo2 uint8_t 0..255 numeric parameter.";                               const char int_params_4[] PROGMEM = {1, p_uint8_t ,0};
const char par_5[] PROGMEM = "int32 long";   const char def_5[] PROGMEM = {5,5,5,5,0};                    const char about_5[] PROGMEM = "This is demo for long(+-2,147,483,647) int value.";                             const char int_params_5[] PROGMEM = {10,p_long32  ,0};
const char par_6[] PROGMEM = "bool demo";    const char def_6[] PROGMEM = {1,0};                          const char about_6[] PROGMEM = "This is demo for bool value.";                                                  const char int_params_6[] PROGMEM = {1, p_bool    ,0};
const char par_7[] PROGMEM = "Reset to def"; const char def_7[] PROGMEM = {0,0};                          const char about_7[] PROGMEM = "Reset EEPROM values to default.";                                               const char int_params_7[] PROGMEM = {1, p_reset   ,1};


PGM_P  const string_table99[][4] PROGMEM = 	   // change "string_table" name to suit
{   
  {par_0,def_0,about_0,int_params_0},
  {par_1,def_1,about_1,int_params_1},
  {par_2,def_2,about_2,int_params_2},
  {par_3,def_3,about_3,int_params_3},
  {par_4,def_4,about_4,int_params_4},
  {par_5,def_5,about_5,int_params_5},
  {par_6,def_6,about_6,int_params_6},
  {par_7,def_7,about_7,int_params_7},
};//*/

//-------------------------------------WEB PAGE HERE! ------------------------------
const char string_0[] PROGMEM = "[BEGIN!]<!DOCTYPE HTML><html><head><title>Configuration web server.</title><style type=\"text/css\">td, tr, a,p,span{margin: 10px;padding:10px; }</style></head>";  
const char string_1[] PROGMEM = "<body style = \"margin:0; padding:0;\"><table width = 100%><tr><td colspan = \"5\" align = \"left\"><a style=\"font-size:20pt;\" href = \"http://www.google.com\" >Configuration web server.</a> </td></tr>";
const char string_2[] PROGMEM = "<tr><td style =\"background-color: #3366CC;\" colspan=\"5\">&nbsp;</td></tr><tr><td  width=\"25%\" align = \"center\"><table width = 100% border=\"1\"><tr><th align=\"center\" width=100%>About</th></tr>";
const char string_3[] PROGMEM = "<tr><td>From this page you can remotely manage the configuration of your arduino board.</td></tr></table></td><td align = \"center\" colspan = \"4\" width = \"75%\"><form method=\"Get\" action=\"http:\\\\google.com?\">";
const char string_4[] PROGMEM = "<table width = 100% border=\"1\" ><tr><th width = 1%>id</th><th align = \"center\" width = 1%>Parameter name</th><th width = 1%>Parameter value</th><th width = 100%>About this parameter</th></tr>";
const char string_5[] PROGMEM = "<tr><td> </td><td>Save settings: </td><td><input type = \"submit\" value = \"Save\"/></td></tr></table>";
const char string_6[] PROGMEM = "</form></td></tr></table></body></html>[END!]";
const char string_7[] PROGMEM = "<END>";

PGM_P  const string_table5[] PROGMEM = 	   // change "string_table" name to suit
{   
  string_0,
  string_1,
  string_2,
  string_3,
  string_4,
  string_5, 
  string_6,
  string_7
};//*/



long  Configuration_web_server::get_value_as_integer_long (uint8_t str_num){
  long result = 0;
  strncpy_P(buff3,(PGM_P)pgm_read_word(&(string_table99[str_num][3])) ,2);  
  uint8_t max_len = buff3[0];     
  uint8_t par_type= buff3[1];
  int address = get_parameter_EEPROM_begin_address(str_num);  
  buff[0] = 0;    
  if ((!(par_type==p_bool))&&(!(par_type==p_reset))){
    
    //TEXT
    if (par_type==p_string){
      uint8_t end_tmp =  max_len+address;
      uint8_t index = 0;
      for (address;address<end_tmp; address=address+sizeof(uint8_t)){   
        byte u_old = EEPROM.read(address);          
        buff[index]=u_old;        
        if (u_old==0) break;
        index++;
      }
      char* end_ptr;
      result = strtol(buff, &end_ptr, 10);      
    }
    if (par_type==p_uint8_t){//uint8_t
      byte u_old = EEPROM.read(address);  
      result = u_old;
    }
    if (par_type==p_long32){//long32
        long four  = EEPROM.read(address);
        long three = EEPROM.read(address + 1);
        long two   = EEPROM.read(address + 2);
        long one   = EEPROM.read(address + 3);        
        result   =  ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
    }    
  }else{
    //CHECKBOX      
    uint8_t u_old = EEPROM.read(address);    
    if (u_old>0){
      result = 1;
    } 
  }
  return result;
}
const char *Configuration_web_server::get_value_as_byte_array_in_buff  (uint8_t str_num)
{
  strncpy_P(buff3,(PGM_P)pgm_read_word(&(string_table99[str_num][3])) ,2);  
  uint8_t max_len = buff3[0];     
  int address = get_parameter_EEPROM_begin_address(str_num);  
  buff[0] = 0;    
  uint8_t end_tmp =  max_len+address;
  uint8_t index=0;
  for (address;address<end_tmp; address=address+sizeof(uint8_t)){ 
    uint8_t u_old = EEPROM.read(address);
    buff[index] = u_old;
  }
 return buff; 
}

const char *Configuration_web_server::get_value_as_string (uint8_t str_num)
{
  strncpy_P(buff3,(PGM_P)pgm_read_word(&(string_table99[str_num][3])) ,2);  
  uint8_t max_len = buff3[0];     
  uint8_t par_type= buff3[1];
  int address = get_parameter_EEPROM_begin_address(str_num);  
  buff[0] = 0;    
  if ((!(par_type==p_bool))&&(!(par_type==p_reset))){
    //TEXT 
    uint8_t index=strlen(buff);
    uint8_t end_tmp =  max_len+address;
    for (address;address<end_tmp; address=address+sizeof(uint8_t)){   
      byte u_old = EEPROM.read(address);
      if (par_type==p_string){
        if (u_old==0) break;
        buff[index]=u_old;        
        index++;        
      }
      if (par_type==p_uint8_t){//uint8_t
        itoa(u_old,buffer_num,10); 
        strcat(buff,buffer_num);
        index = strlen(buff);
        break;
        //buff[index]=u_old;
      }
      if (par_type==p_long32){//long32
        long four  = EEPROM.read(address);
        long three = EEPROM.read(address + 1);
        long two   = EEPROM.read(address + 2);
        long one   = EEPROM.read(address + 3);        
        long l_old =  ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
        ltoa(l_old,buffer_num,10); 
        strcat(buff,buffer_num);
        index = strlen(buff);
        break;
        //buff[index]=u_old;
      }
      if (par_type==p_IP){//IP
        //if (u_old==255)u_old=0;
        itoa(u_old,buffer_num,10);         
        strcat(buff,buffer_num); 
        strcat(buff,".");         
        index = strlen(buff)-1;         
      }
      if (par_type==p_MACarray){//MAC
        itoa(u_old,buffer_num,16); 
        if (u_old<16){
           strcat(buff,"0");         
        }               
        strcat(buff,buffer_num); 
        strcat(buff,":");        
        index = strlen(buff)-1;         
      }          
    }
    address = end_tmp+1;
    buff[index]='\0';       
  }else{ 
    //CHECKBOX      
    uint8_t u_old = EEPROM.read(address);    
    if (u_old>0){
      strcat(buff,"checked ");
    } 
  }  
  return buff; 
}

char *Configuration_web_server::replace_str( char *str, const char *f, const char *t ) {
   char *tmpPtr = strstr( str, f );
   while ( tmpPtr != 0 && strlen( f ) >= strlen( t )) {
      uint8_t sizeDiff = strlen( f ) - strlen( t );
      
      strncpy( tmpPtr, t, strlen( t ));
      
      if ( sizeDiff > 0 )
         for ( tmpPtr += strlen( t ); *tmpPtr != '\0'; tmpPtr++ )
            *tmpPtr = *( tmpPtr + sizeDiff );
            
      tmpPtr = strstr( str, f );
   }    
   return str;
}

void Configuration_web_server::save_new_parameters_from_GET_url_string(char * qerry)
{
  big_str[0]  = '\0'; 
  replace_str (qerry, "%3A","") ;
  strcat(big_str, replace_str (qerry, "+"," ") );  
  qerry[0]    = '\0'; 
  strcat(qerry , big_str);  
  big_str[0]  = '\0'; 
  buff[0]     = '\0'; 
  buff35[0]   = '\0';
  strcat(buff, strrchr (qerry, '?')+(sizeof(char)) );//*/
  qerry[0]    = '\0';
  strcat(qerry , buff);  
  while (strlen(qerry)>2){
    big_str[0]  = '\0'; 
    buff[0]     = '\0'; 
    buff35[0]   = '\0';
    //Serial.print("qerry=");
    //Serial.println(qerry);
    if (strchr (qerry,'&')!=NULL){
      strcat (buff,   strchr (qerry,'&')+(sizeof(char)) );//*/
      if (strlen(buff)>0){
        strncat(buff35, qerry,strlen(qerry)-strlen(buff)-1);
      }
      qerry[0]    = '\0';
      strcat(qerry , buff);  
    }else{
      strcat(buff35 , qerry);
      qerry[0]    = '\0';
    }
    // now in buff35 val_n=new_val
    buff[0]       = '\0';
    big_str[0]    = '\0';
    strcat (buff, strrchr (buff35, '=')+(sizeof(char)) ); //now in buf new value in string.
    //Serial.print("NEW VAL buff=");
    //Serial.println(buff);
    strncat(big_str, buff35,strlen(buff35)-strlen(buff)-1);
    buff35[0]     = '\0';
    strcat (buff35, strrchr (big_str, '_')+(sizeof(char)) );
    uint8_t str_num = atoi(buff35)-1;
    //Serial.print("NEW str_num=");
    //Serial.println(str_num);
    big_str[0]    = '\0';
     strncpy_P(buff3,(PGM_P)pgm_read_word(&(string_table99[str_num][3])) ,2);  
     uint8_t max_len = buff3[0];     
     uint8_t par_type= buff3[1];
     if (par_type == p_string){
         update_value_in_buff(str_num,buff);
     }
     if (par_type == p_long32){ 
       char* end_ptr;
       long value = strtol(buff, &end_ptr, 10);      
       //long value = atol(buff);
       buff[0] = (value & 0xFF);
       buff[1] = ((value >> 8) & 0xFF);
       buff[2] = ((value >> 16) & 0xFF);
       buff[3] = ((value >> 24) & 0xFF);  
       update_value_in_buff(str_num,buff);  
     }
     if (par_type == p_uint8_t){
         char* end_ptr;
         long u_new = strtol(buff, &end_ptr, 10);
         buff[0] = u_new;  
         update_value_in_buff(str_num,buff);       
     }
     if (par_type == p_reset){
         uint8_t reset_to_default_data = buff[0];
         if (reset_to_default_data>0){
           Serial.println("TRY DEfAULT!");
           need_defaults=true;         
           init_CWS(beg_EEPROM_address, true );
         } 
     }
     if (par_type == p_bool){
         update_value_in_buff(str_num,buff);         
     }
     
     if (par_type == p_IP){
       bool have_error = 0;
       for (uint8_t u = 0;u<4;u++){
          if (strlen(buff)>0){
            big_str[0]  = '\0'; 
            buff35[0]   = '\0'; 
            strcat (buff35, strchr (buff, '.')+(sizeof(char)) ); 
            if (strchr (buff35, '.')>0){
              strncat(big_str, buff,strlen(buff)-strlen(buff35)-1);
            }else{
              strncat(big_str, buff,strlen(buff)-strlen(buff35));
            }
            buff[0]     = '\0';
            strcat(buff , buff35);  
            char* end_ptr;
            long u_new = strtol(big_str, &end_ptr, 10);
            if ( ((u_new>=0)&&(u_new<255))&&(!((u_new==0)&&( (u==0 )||(u==3)) ) ))   {
               //if (u_new ==0) u_new = 255;
               uint8_t t1= u_new;               
               buffer_num[u] = t1;//(byte)t1; 
            }else{
              have_error =1;
            }
            
          }else{
            have_error =1;
          }  
          if (have_error)  break;      
       }
       if (!(have_error)){
         update_value_in_buff(str_num,buffer_num);          
       }else{
         Serial.print(" ERROR!!! in IP!");
       }               
     }
     
     if (par_type == p_MACarray){
       bool have_error = 0;
       for (uint8_t u = 0;u<6;u++){
          if (strlen(buff)>0){
            big_str[0]   = '\0'; 
            buff3[0]     = '\0';             
            //buff35[0]    = '\0'; 
            //buffer_num[0]= '\0'; 
            strncat(buff3,   buff,2);
            strncat(big_str, buff+2,strlen(buff)-2);
            buff[0]  = '\0';
            strcat(buff , big_str); 
            char* end_ptr;
            long u_new = strtol(buff3, &end_ptr, 16);
            //Serial.print("MAC u_new=");
            //Serial.print(u_new,DEC);
            if  ((u_new>=0)&&(u_new<=255))   {
               //if (u_new ==0) u_new = 255;
               //uint8_t t1= (uint8_t)u_new;               
               buff35[u] = (uint8_t)u_new;
               //Serial.print(" MAC hex=");
               //uint8_t u3 = buff35[u];
               //Serial.println(u3,HEX);           
            }else{
              have_error =1;
            }            
          }else{
            have_error =1;
          }  
          if (have_error)  break;      
       }
       if (!(have_error)){
         update_value_in_buff(str_num,buff35);          
       }else{
         Serial.print(" ERROR!!! in MAC!");
       }               
     }
 }  
 for (uint8_t u = 0 ;u<params_count;u++){
   strncpy_P(buff3,(PGM_P)pgm_read_word(&(string_table99[u][3])) ,2);     
   uint8_t par_type= buff3[1];
   if ((par_type==p_bool)&&(!parameter_present[u])){
       update_value_in_buff(u,'\0'); 
   }
   parameter_present[u] =false; 
 }
  count_string_for_print = params_count+web_page_lines;
}

void Configuration_web_server::restart_if_need(){
  if (need_defaults){
    need_defaults = false;
    Serial.println("RESET TO DEFAULTS!!!!");    
    reset_to_defaults();  
  }
  
}


void Configuration_web_server::update_value_in_buff(uint8_t par_num,const char * new_value)
{
     uint8_t address = get_parameter_EEPROM_begin_address(par_num);
     strncpy_P(buff3,(PGM_P)pgm_read_word(&(string_table99[par_num][3])) ,3);  
     uint8_t max_len           = uint8_t(buff3[0]); 
     uint8_t par_type          = uint8_t(buff3[1]); 
     uint8_t for_config_changes= uint8_t(buff3[2]);
     parameter_present[par_num] = true;
     //uint8_t len = strlen(new_value);   
     for (uint8_t u =0; u<= max_len ;u++ ){
       //check does we have different bytes.... if have - rewrite it and set flag that we made changes in some parameter...
        uint8_t u_old = EEPROM.read(address);         
        uint8_t u_new = new_value[u];          
        if (!(u_old==u_new)){        
          //have some changes in some parameter     
          EEPROM.write(address, u_new);
          changed_some_value_in_CWS[par_num] = true;
          if (for_config_changes>0){
            //if have changes in options of our server - must restart it.
            need_restart = true;
          }else{
            //made some changes in parameters, that not use our web server. Here we can make and Callback function too
            
          }
        }       
        if ((par_type==p_string)&&(u_new==0)){ break;}
        if ( par_type==p_uint8_t){             break;}
        address=address+sizeof(uint8_t);
     }
}

void Configuration_web_server::reset_to_defaults(){
 for (uint8_t par_num=0;par_num<params_count;par_num++){
     strncpy_P(buff3,(PGM_P)pgm_read_word(&(string_table99[par_num][3])) ,3);  
     uint8_t max_len = buff3[0];     
     uint8_t par_type= buff3[1];
     buff[0] = '\0';
     if (par_type == p_string){
       strcpy_P(buff,       (PGM_P)pgm_read_word(&(string_table99[par_num][1])));
     }else{
       strncpy_P(buff,       (PGM_P)pgm_read_word(&(string_table99[par_num][1])),max_len+1);
     }
     update_value_in_buff(par_num,buff);
  }  
}


void Configuration_web_server::init_CWS(int  start_EEPROM_address, bool reset_to_default_data )
{
  need_restart             =false;
  need_defaults            =false;
  for (uint8_t u = 0 ;u<params_count;u++) {
    changed_some_value_in_CWS[u] =false;
    parameter_present[u] = false;
  }
  beg_EEPROM_address = start_EEPROM_address;
  Serial.println("INIT");
  uint8_t value = EEPROM.read(start_EEPROM_address);
  if ((value==1)&&(!reset_to_default_data)){
    //reset_to_defaults();     
  }else{
    Serial.println("RESET TO DEFAULTS!!!!");
    reset_to_default_data = 0;
    reset_to_defaults();  
    EEPROM.write(start_EEPROM_address,1);    
  }
  count_string_for_print = params_count+web_page_lines;  
  //count_of_main_text = sizeof(main_text)/sizeof(main_text[0]);  
}

uint8_t Configuration_web_server::get_parameter_EEPROM_begin_address(uint8_t str_num)
{
   uint8_t address = (beg_EEPROM_address+1)*sizeof(uint8_t);
   uint8_t max_len; 
   for (uint8_t par_num=0;par_num<str_num;par_num++){
      strncpy_P(buff3,(PGM_P)pgm_read_word(&(string_table99[par_num][3])) ,2);  
      max_len = uint8_t(buff3[0]);
      address  = address+(max_len+1)*sizeof(uint8_t);
  }
  return address;
}
const char * Configuration_web_server::get_next_string_for_print(){
  if (count_string_for_print>0){
    uint8_t u3 = web_page_lines + params_count - count_string_for_print;
    count_string_for_print--;
    const char * s ;
    if (u3>=params_begin){         
       if (u3<params_begin+ params_count){
           int curr_line = u3-params_begin;
           //Serial.println(curr_line);
           s = print_one_parameter(curr_line); 
       }else{
           s = print_main_text3(u3-params_count);  
       }         
     }else{
        s = print_main_text3(u3);   
     }//*///
     return s; 
  }else{
    buff3[0] = '\0';
    return buff3;
  }
  
}
const char * Configuration_web_server::print_one_parameter(uint8_t str_num)
{
  big_str[0] = '\0';
  int i2 = str_num+1;
  itoa(i2,buffer_num2,10); 
  strcat(big_str,"<tr><td>");
  strcat(big_str,buffer_num2);  
  strcat(big_str,"</td><td>");
  strcpy_P(buff,  (PGM_P)pgm_read_word(&(string_table99[str_num][0]))); 
  buff35[0] = 0;
  strcat(buff35, buff );
  strcat(big_str,buff );
  strcat(big_str,"</td><td><input name = \"val_");
  strcat(big_str,buffer_num2);  
  strcat(big_str,"\" type = \"");
  
  int address = get_parameter_EEPROM_begin_address(str_num);  
  strncpy_P(buff3,(PGM_P)pgm_read_word(&(string_table99[str_num][3])) ,2);
  uint8_t max_len         = uint8_t(buff3[0]);
  uint8_t par_type= uint8_t(buff3[1]);    
  buff[0] = 0;    
  if ((!(par_type==p_bool))&&(!(par_type==p_reset))){
    //TEXT 
    strcat(big_str,"text\" value=\""); 
    strcat(big_str,get_value_as_string(str_num)); 
    strcat(big_str,"\"");   
  }else{ 
    //CHECKBOX   
    strcat(big_str,"checkbox\" id=\"val_"); 
    strcat(big_str,buffer_num2); 
    strcat(big_str,"\" "); 
    strcat(big_str,get_value_as_string(str_num)); 
    strcat(big_str,"/><label for=\"val_"); 
    strcat(big_str,buffer_num2); 
    strcat(big_str,"\">"); 
    strcat(big_str,buff35); 
    strcat(big_str,"</label");
  }
  strcat(big_str,"></td><td>");
  strcpy_P(buff,       (PGM_P)pgm_read_word(&(string_table99[str_num][2])));
  strcat(big_str,buff);  
  strcat(big_str,"</td></tr>");
  return  big_str;
}

const char * Configuration_web_server::print_main_text3(uint8_t str_num)
{ 
  //big_str[0] = '\0';
  //char ** ch3 = big_str;
  strcpy_P(big_str, (PGM_P)pgm_read_word(&(string_table5[str_num])));
  return big_str;
}



 




#endif
