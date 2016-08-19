#define params_count 6
#include <EEPROM.h>
#include <SPI.h>
#include <UIPEthernet.h>
#include <avr/pgmspace.h>
#include "Configuration_web_server.h";


  

Configuration_web_server * CWS = new Configuration_web_server;
//String inputString = "";         // a string to hold incoming data
//bool stringComplete = false;  // whether the string is complete
//bool alrady_printed = false;
uint8_t web_count_count = 7;
uint8_t lines_begin     = 5;     //((char)buf[i])
uint8_t income_size= 0;
char income_buf[255];
 

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 169, 88, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);


void setup(){
  // initialize serial communication at 9600 bits per second:

  Serial.begin(115200);
  //inputString.reserve(200);
  //uint8_t t= 12323;

  //

  CWS->init_CWS(0);

    // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  //const char * = "";
  //char c[10] = "";
  //uint8_t b = strtoul(c, 0, 16);
  //itoa(255,c,16); 
  //c=ultostr(255,16);
  //Serial.println("");
  //Serial.print("b=");
  //Serial.println(c);
// Serial.println("[BEGIN!]");//*/  
/*for (uint8_t u3 =0;u3<(params_count+web_count_count);u3++){
//  for (uint8_t u3 =0;u3<(params_count);u3++){
       const char * s ;
      // s = CWS->print_one_parameter( u3);
      if (u3>=lines_begin){
         
           if (u3<lines_begin+ params_count){
               int curr_line = u3-lines_begin;
               //Serial.println(curr_line);
               s = CWS->print_one_parameter(curr_line); 
           }else{
               s = CWS->print_main_text3(u3-params_count);  
           }         
       }else{
          s = CWS->print_main_text3(u3);   
       }//*///
   /*    Serial.println(s);
    }
     Serial.println("[END!]");//*/

 }
// the loop routine runs over and over again forever:



void loop(){
 
  //delay(5000);        // delay in between reads for stability
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        income_buf[income_size] = c;
        income_size++;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          if (income_size>2){
            income_buf[income_size] = '\0';
            income_size = 0;
            Serial.println("");
            //Serial.print((char)10);
            //Serial.print((char)13);
            Serial.println(income_buf);
            // CWS->save_new_parameters_from_GET_url_string(income_buf);
            //Serial.print((char)10);
            //Serial.print((char)13);
          }
          // client.println("HTTP/1.1 200 OK");
          // client.println("Content-Type: text/html");
          // client.println("Connection: close");  // the connection will be closed after completion of the response
          // client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          // client.println();
          // client.println("<!DOCTYPE HTML>");
          // client.println("<html>");
          // // output the value of each analog input pin
          // for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
          //   int sensorReading = analogRead(analogChannel);
          //   client.print("analog input ");
          //   client.print(analogChannel);
          //   client.print(" is ");
          //   client.print(sensorReading);
          //   client.println("<br />");
          // }
          // client.println("</html>");
          // break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
      const char * new_str = CWS->get_next_string_for_print();
      if (new_str[0]>0){
        Serial.println(new_str);
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }




  // if  (Serial.available() > 0) {
  //   while   (Serial.available() > 0){
  //     // get incoming byte:
  //     uint8_t ch = Serial.read();
  //     if ((ch == 10)||(ch == 13)){
  //       if (income_size>2){
  //         income_buf[income_size] = '\0';
  //         income_size = 0;
  //         Serial.println("");
  //         //Serial.print((char)10);
  //         //Serial.print((char)13);
  //         Serial.println(income_buf);
  //         CWS->save_new_parameters_from_GET_url_string(income_buf);
  //         //Serial.print((char)10);
  //         //Serial.print((char)13);
  //       }
  //     }else{
  //       income_buf[income_size] = ch;
  //       income_size++;
  //       Serial.print((char)ch);
  //       //Serial.print(ch);
  //     }
  //   }
    
  // }
  // const char * new_str = CWS->get_next_string_for_print();
  // if (new_str[0]>0){
  //   Serial.println(new_str);
  // }//*/
  
  //Serial.println();
   //Serial.println("asdasdasd");
}

  //Serial.println("END!");
 /*for (uint8_t u3 =0;u3<(web_count_count+params_count);u3++){
       const char * s ;
       if (u3>=lines_begin){
           if (u3<lines_begin+ params_count){
               int curr_line = u3-lines_begin;
               //Serial.println(curr_line);
               s = CWS->print_one_parameter(curr_line); 
           }else{
               s = CWS->print_main_text3(u3-params_count);  
           }         
       }else{
          s = CWS->print_main_text3(u3);   
       }
       Serial.println(s);
    }
     Serial.println("END!");//*/

  
  



  // read the input on analog pin 0:
  //int sensorValue = analogRead(A0);
  // print out the value you read:
  //Serial.println(sensorValue);
  /* if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }//*/
  

 /* void serialEvent() {
if (alrady_printed){
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read();
      // add it to the inputString:
      inputString += inChar;
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      if (inChar == '\n') {
        //stringComplete = true;
      }
    }
  }
}*/
