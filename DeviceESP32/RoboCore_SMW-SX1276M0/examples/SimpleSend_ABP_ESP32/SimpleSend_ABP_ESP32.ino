/*******************************************************************************
* SMW_SX1276M0 Simple Send - ABP (v1.0)
* 
* Simple program to test sending a message with ABP.
* This program uses the ESP32 to communicate with the LoRaWAN module.
* 
* Copyright 2020 RoboCore.
* Written by Francois (24/08/20).
* 
* 
* This file is part of the SMW_SX1276M0 library ("SMW_SX1276M0-lib").
* 
* "SMW_SX1276M0-lib" is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* "SMW_SX1276M0-lib" is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public License
* along with "SMW_SX1276M0-lib". If not, see <https://www.gnu.org/licenses/>
*******************************************************************************/

#if !defined(ARDUINO_ESP32_DEV) // ESP32
#error Use this example with the ESP32
#endif

// --------------------------------------------------
// Libraries

#include "RoboCore_SMW_SX1276M0.h"

// --------------------------------------------------
// Variables

#include <HardwareSerial.h>
HardwareSerial LoRaSerial(2);
#define RXD2 16
#define TXD2 17

SMW_SX1276M0 lorawan(LoRaSerial);

CommandResponse response;

const char DEVADDR[] = "00000000";
const char APPSKEY[] = "00000000000000000000000000000000";
const char NWKSKEY[] = "00000000000000000000000000000000";

const unsigned long PAUSE_TIME = 300000; // [ms] (5 min)
unsigned long timeout;
int count = 0;

// --------------------------------------------------
// Prototypes

void event_handler(Event);

// --------------------------------------------------
// --------------------------------------------------

void setup() {
  // Start the UART for debugging
  Serial.begin(115200);
  Serial.println(F("--- SMW_SX1276M0 Uplink (ABP) ---"));
  
  // start the UART for the LoRaWAN Bee
  LoRaSerial.begin(115200, SERIAL_8N1, RXD2, TXD2);

  // set the event handler
  lorawan.event_listener = &event_handler;
  Serial.println(F("Handler set"));

  // read the Device EUI
  char deveui[16];
  response = lorawan.get_DevEUI(deveui);
  if(response == CommandResponse::OK){
    Serial.print(F("DevEUI: "));
    Serial.write((uint8_t *)deveui, 16);
    Serial.println();
  } else {
    Serial.println(F("Error getting the Device EUI"));
  }

  // set the Device Address
  response = lorawan.set_DevAddr(DEVADDR);
  if(response == CommandResponse::OK){
    Serial.print(F("Device Address set ("));
    Serial.write((uint8_t *)DEVADDR, 8);
    Serial.println(')');
  } else {
    Serial.println(F("Error setting the Device Address"));
  }

  // set the Application Session Key
  response = lorawan.set_AppSKey(APPSKEY);
  if(response == CommandResponse::OK){
    Serial.print(F("Application Session Key set ("));
    Serial.write((uint8_t *)APPSKEY, 32);
    Serial.println(')');
  } else {
    Serial.println(F("Error setting the Application Session Key"));
  }

  // set the Network Session Key
  response = lorawan.set_NwkSKey(NWKSKEY);
  if(response == CommandResponse::OK){
    Serial.print(F("Network Session Key set ("));
    Serial.write((uint8_t *)NWKSKEY, 32);
    Serial.println(')');
  } else {
    Serial.println(F("Error setting the Network Session Key"));
  }

  // set join mode to ABP
  response = lorawan.set_JoinMode(SMW_SX1276M0_JOIN_MODE_ABP);
  if(response == CommandResponse::OK){
    Serial.println(F("Mode set to ABP"));
  } else {
    Serial.println(F("Error setting the join mode"));
  }

  // join the network (not really necessary in ABP)
  Serial.println(F("Joining the network"));
  lorawan.join();
}

// --------------------------------------------------
// --------------------------------------------------

void loop() {
  // listen for incoming data from the module
  lorawan.listen();

  // send a message
  if(lorawan.isConnected()){
    if(timeout < millis()){
      // update the counter
      count++;
      if(count > 255){
        count = 0; // reset
      }
  
      // convert to HEX
      char data[] = { '0', '0', 0};
      data[0] += (count / 16);
      if(data[0] > '9'){
        data[0] += 7;
      }
      data[1] += (count % 16);
      if(data[1] > '9'){
        data[1] += 7;
      }
  
      // send the message
      Serial.print(F("Data: "));
      Serial.println(data);
      response = lorawan.sendX(1, data);
  
      // update the timeout
      timeout = millis() + PAUSE_TIME;
    }
  } else {
    if(timeout < millis()){
      // show some activity
      Serial.println('.');
    
      // update the timeout
      timeout = millis() + 5000; // 5 s
    }
  }
}

// --------------------------------------------------
// --------------------------------------------------

// Handle the events of the module
//  @param (type) : the type of the event [Event]
void event_handler(Event type){
  // check if join event
  if(type == Event::JOINED){
    Serial.println(F("Joined"));
  }
}

// --------------------------------------------------
