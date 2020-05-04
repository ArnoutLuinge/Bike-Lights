
// Arnout Luinge
// 18/05/2019

#include <FastLED.h>
#define NUM_LEDS 40
#define DATA_PIN 13
CRGB leds[NUM_LEDS];

unsigned long currentMillis, previousBlueMillis, previousBlinkMillis, previousHardBrakeMillis, previousHazardMillis;

int light_switch_pin = 12;
int l_blinker_switch_pin = 10;
int r_blinker_switch_pin = 11;
int switch1_pin = 9;
int switch2_pin = 8;
int switch3_pin = 7;
int switch4_pin = 6;
int r_blinker_pin = 5;
int l_blinker_pin = 4;
int r_blue_pin = 3;
int l_blue_pin = 2;
int analog_brake_pin = 0;

bool debug, startBlink_off, hardBrake,
l_blinker_switch, r_blinker_switch, light_switch, bluelights_switch, hazards_switch, brake_switch, switch1, switch2, switch3, switch4,
prev_brake_switch, prev_right_blink_switch, prev_left_blink_switch, prev_hazards_switch, prev_bluelights_switch, prev_light_switch;

int hazardCounter, blinkCounter, startBlinkCounter, HardBrakeCounter,
startBlinkInterval, blinkInterval, blueLightsInterval, hazardsInterval, hardBrakeInterval, intervalBlue,
brightness, brakeBrightness, deacceleration, hue;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
  pinMode(switch1_pin, INPUT_PULLUP);
  pinMode(switch2_pin, INPUT_PULLUP);
  pinMode(switch3_pin, INPUT_PULLUP);
  pinMode(switch4_pin, INPUT_PULLUP);
  pinMode(l_blinker_pin, OUTPUT);
  pinMode(l_blue_pin, OUTPUT);
  pinMode(r_blue_pin, OUTPUT);
  pinMode(r_blinker_pin, OUTPUT);
  pinMode(l_blinker_switch_pin, INPUT_PULLUP);
  pinMode(r_blinker_switch_pin, INPUT_PULLUP);
  pinMode(light_switch_pin, INPUT_PULLUP);

  startBlinkInterval = 150;
  hazardsInterval = 17;
  blinkInterval = 17;
  blueLightsInterval = 50;
  hardBrakeInterval = 60;
  
  brightness = 180;
  FastLED.setBrightness(brightness);

  debug = 0;
}

void loop() {
  currentMillis = millis();
  
  switch1 = (digitalRead(switch1_pin) == 0);
  switch2 = (digitalRead(switch2_pin) == 0);
  switch3 = (digitalRead(switch3_pin) == 0);
  switch4 = (digitalRead(switch4_pin) == 0);
  l_blinker_switch = (digitalRead(l_blinker_switch_pin) == 0);
  r_blinker_switch = (digitalRead(r_blinker_switch_pin) == 0);
  light_switch = (digitalRead(light_switch_pin) == 0);
  if (analogRead(analog_brake_pin) > 1000){
    brake_switch = 0;
  } else if (analogRead(analog_brake_pin) < 1000){
    brake_switch = 1;
  }
  deacceleration = 1; //is gonna be a sensor read
//  brightness = brightness; //is gonna be a sensor read
  if (brightness > 205){
    brakeBrightness = 255;
  } else if (brightness <= 205){
    brakeBrightness = brightness + 50;
  }

//  l_blinker_switch = 0;
//  r_blinker_switch = 0;
  hazards_switch = switch1;
  bluelights_switch = switch2;
//  light_switch = switch3;
//  brake_switch = switch4;

//  fun1_rainbow();
//  fun2_strobe();


  if (debug){
    Serial.println();
    Serial.print(" switch1:");
    Serial.print(switch1);
    Serial.print(" switch2:");
    Serial.print(switch2);
    Serial.print(" switch3:");
    Serial.print(switch3);
    Serial.print(" switch4:");
    Serial.print(switch4);
    Serial.print(" l_blinker_switch:");
    Serial.print(l_blinker_switch);  
    Serial.print(" r_blinker_switch:");
    Serial.print(r_blinker_switch);
    Serial.print(" light_switch:");
    Serial.print(light_switch);
    Serial.print(" brake_switch:");
    Serial.print(brake_switch);
    Serial.print(" bluelights_switch:");
    Serial.print(bluelights_switch);
    Serial.print(" analog_brake_pin:");
    Serial.print(analogRead(analog_brake_pin));
  }

  startblink();

  if (light_switch == 1){
    lights();
  } else if (light_switch == 0 && prev_light_switch == 1){
    fill_solid( & leds [0], 40, CRGB(0 ,0 ,0));   //turn leds 0-39 from ledstrip OFF 
    FastLED.show();
    prev_light_switch = 0;
  }

  if (l_blinker_switch == 1){
    blinkerLeftV3();
  } else if (l_blinker_switch == 0 && prev_left_blink_switch == 1){
    digitalWrite(l_blinker_pin, LOW);
    fill_solid( & leds [0], 15, CRGB(0 ,0 ,0));
    FastLED.show();
    prev_left_blink_switch = 0;
    blinkCounter = 0;
  }
  
  if (r_blinker_switch == 1){
    blinkerRightV3();
  } else if (r_blinker_switch == 0 && prev_right_blink_switch == 1){
    digitalWrite(r_blinker_pin, LOW);
    fill_solid( & leds [25], 15, CRGB(0 ,0 ,0));
    FastLED.show();
    prev_right_blink_switch = 0;
    blinkCounter = 0;
  }

  if (bluelights_switch == 1){
    blueLights1();
  } else if (bluelights_switch == 0 && prev_bluelights_switch ==1){
      fill_solid( & leds [0], 40, CRGB(0 ,0 ,0));   //turn leds 0-39 from ledstrip OFF 
      digitalWrite(l_blue_pin, LOW);
      digitalWrite(r_blue_pin, LOW);
      FastLED.show();
      prev_bluelights_switch = 0;
  }

  if (hazards_switch == 1){
    hazardsV2();
  } else if (hazards_switch == 0 && prev_hazards_switch == 1){
      digitalWrite(r_blinker_pin, LOW);
      digitalWrite(l_blinker_pin, LOW);
      fill_solid( & leds [0], 15, CRGB(0 ,0 ,0));
      fill_solid( & leds [25], 15, CRGB(0 ,0 ,0));
      FastLED.show();
      prev_hazards_switch = 0;
      hazardCounter = 0;
  }
  
  if (brake_switch == 1){
    brakeLights();
  } else if (brake_switch == 0 && prev_brake_switch == 1){
    fill_solid( & leds [0], 40, CRGB(0 ,0 ,0));   //turn leds 0-39 from ledstrip OFF
    FastLED.show();
    FastLED.setBrightness(brightness);
    prev_brake_switch = 0;
    hardBrake = 0;
  }

  delay(1);
}

void blinkerLeftV3() {
  if (currentMillis - previousBlinkMillis > blinkInterval){
    previousBlinkMillis = currentMillis;
    
    if (blinkCounter == 0){
      digitalWrite(l_blinker_pin, HIGH);
    }
  
    if (blinkCounter < 15){
      leds[(14 - blinkCounter)] = CRGB(255, 120, 0);
      FastLED.show();
    }
  
    if (blinkCounter == 22){
      digitalWrite(l_blinker_pin, LOW);
      
      fill_solid( & leds [0], 15, CRGB(0 ,0 ,0));
      FastLED.show();
    }
    
    blinkCounter++;
    
    if (blinkCounter == 44){
      blinkCounter = 0;
    }
  }
  prev_left_blink_switch = 1;
}

void blinkerRightV3() {
  if (currentMillis - previousBlinkMillis > blinkInterval){
    previousBlinkMillis = currentMillis;
    
    if (blinkCounter == 0){
      digitalWrite(r_blinker_pin, HIGH);
    }
  
    if (blinkCounter < 15){
      leds[(25 + blinkCounter)] = CRGB(255, 120, 0);
      FastLED.show();
    }
  
    if (blinkCounter == 22){
      digitalWrite(r_blinker_pin, LOW);
      
      fill_solid( & leds [25], 15, CRGB(0 ,0 ,0));
      FastLED.show();
    }
    
    blinkCounter++;
    
    if (blinkCounter == 44){
      blinkCounter = 0;
    }
  }
  prev_right_blink_switch = 1;
}

void blueLights1(){
  //blue flshing lights, like the dutch emergency vehicles
  if (currentMillis - previousBlueMillis > blueLightsInterval){
    previousBlueMillis = currentMillis;
    if (intervalBlue < 6){
      //flash left 3 times
      switch (intervalBlue){
        case 0:
          fill_solid( & leds [0], 15, CRGB(0 ,0 ,255)); //left blue on
          digitalWrite(l_blue_pin, HIGH);
          break;
        case 1:
          fill_solid( & leds [0], 15, CRGB(0 ,0 ,0)); //left blue off
          digitalWrite(l_blue_pin, LOW);
          break;
        case 2:
          fill_solid( & leds [0], 15, CRGB(0 ,0 ,255)); //left blue on
          digitalWrite(l_blue_pin, HIGH);
          break;
        case 3:
          fill_solid( & leds [0], 15, CRGB(0 ,0 ,0)); //left blue off
          digitalWrite(l_blue_pin, LOW);
          break;
        case 4:
          fill_solid( & leds [0], 15, CRGB(0 ,0 ,255)); //left blue on
          digitalWrite(l_blue_pin, HIGH);
          break;
        case 5:
          fill_solid( & leds [0], 15, CRGB(0 ,0 ,0)); //left blue off
          digitalWrite(l_blue_pin, LOW);
          break;   
      }
    }
    else if (intervalBlue > 5){
      switch (intervalBlue){
        case 6:
          fill_solid( & leds [25], 15, CRGB(0 ,0 ,255)); //right blue on
          digitalWrite(r_blue_pin, HIGH);
          break;
        case 7:
          fill_solid( & leds [25], 15, CRGB(0 ,0 ,0)); //right blue off
          digitalWrite(r_blue_pin, LOW);
          break;
        case 8:
          fill_solid( & leds [25], 15, CRGB(0 ,0 ,255)); //right blue on
          digitalWrite(r_blue_pin, HIGH);
          break;
        case 9:
          fill_solid( & leds [25], 15, CRGB(0 ,0 ,0)); //right blue off
          digitalWrite(r_blue_pin, LOW);
          break;
        case 10:
          fill_solid( & leds [25], 15, CRGB(0 ,0 ,255)); //right blue on
          digitalWrite(r_blue_pin, HIGH);
          break;
        case 11:
          fill_solid( & leds [25], 15, CRGB(0 ,0 ,0)); //right blue off
          digitalWrite(r_blue_pin, LOW);
          break;   
      }
    }
  
    intervalBlue ++;
    if (intervalBlue > 11){
      intervalBlue =0;
    }
    
    FastLED.show();
    prev_bluelights_switch = 1;
  }
}

void lights(){
  fill_solid( & leds [15], 10, CRGB(180 ,0 ,0));   //turn leds 15-25 from ledstrip ON (slightly dimmed)

  if (r_blinker_switch == 0 && bluelights_switch == 0 && hazards_switch == 0 && hardBrake == 0 && startBlink_off == 1){
    fill_solid( & leds [25], 15, CRGB(60 ,0 ,0));   //turn leds 25-39 from ledstrip ON (dimmed)
  }
  if (l_blinker_switch == 0 && bluelights_switch == 0 && hazards_switch == 0 && hardBrake == 0 && startBlink_off == 1){
    fill_solid( & leds [0], 15, CRGB(60 ,0 ,0));   //turn leds 0-15 from ledstrip ON (dimmed)
  }
  FastLED.show();
  prev_light_switch = 1;
}

void brakeLights(){
  if (deacceleration < 10){
    FastLED.setBrightness(brakeBrightness);
    fill_solid( & leds [15], 10, CRGB(255 ,0 ,0));   //turn leds 15-25 from ledstrip fully ON
    fill_solid( & leds [0], 2, CRGB(255 ,0 ,0));   //turn leds 0-2 from ledstrip fully ON
    fill_solid( & leds [38], 2, CRGB(255 ,0 ,0));   //turn leds 38-39 from ledstrip fully ON  
  
    if (r_blinker_switch == 0 && bluelights_switch == 0 && hazards_switch == 0){
      fill_solid( & leds [25], 15, CRGB(255 ,0 ,0));   //turn leds 25-39 from ledstrip ON
    }
    if (l_blinker_switch == 0 && bluelights_switch == 0 && hazards_switch == 0){
      fill_solid( & leds [0], 15, CRGB(255 ,0 ,0));   //turn leds 0-15 from ledstrip ON
    }
    FastLED.show();
    FastLED.setBrightness(brightness);
  } else if (deacceleration >= 10){
      FastLED.setBrightness(255);
      hardBrake = 1;
      if (currentMillis - previousHardBrakeMillis > hardBrakeInterval){
        previousHardBrakeMillis = currentMillis;
        switch (HardBrakeCounter){
          case 0:
            fill_solid( & leds [0], 40, CRGB(255 ,0 ,0));   //turn leds 0-39 from ledstrip ON
            FastLED.show();
            break;
          case 1:
            fill_solid( & leds [0], 40, CRGB(0 ,0 ,0));   //turn leds 0-39 from ledstrip OFF
            fill_solid( & leds [0], 2, CRGB(255 ,0 ,0));   //turn leds 0-2 from ledstrip fully ON
            fill_solid( & leds [38], 2, CRGB(255 ,0 ,0));   //turn leds 38-39 from ledstrip fully ON  
            FastLED.show();
            break;
        }
        HardBrakeCounter++;
        if (HardBrakeCounter >= 2){
          HardBrakeCounter = 0;
        }
      }
  }
  prev_brake_switch = 1;
}

void hazardsV2(){
  if (debug){
    Serial.print(" currentMillis - previousHazardMillis:");
    Serial.print(currentMillis - previousHazardMillis);
  }

  if (currentMillis - previousHazardMillis > hazardsInterval){
    previousHazardMillis = currentMillis;
    
    if (debug){
      Serial.print(" hazardCounter:");
      Serial.print(hazardCounter);
    }
    if (hazardCounter == 0){
      digitalWrite(r_blinker_pin, HIGH);
      digitalWrite(l_blinker_pin, HIGH);
    }
  
    if (hazardCounter < 15){
      leds[(14 - hazardCounter)] = CRGB(255, 120, 0);
      leds[(25 + hazardCounter)] = CRGB(255, 120, 0);
      FastLED.show();
    }
  
    if (hazardCounter == 22){
      digitalWrite(r_blinker_pin, LOW);
      digitalWrite(l_blinker_pin, LOW);
      
      fill_solid( & leds [0], 15, CRGB(0 ,0 ,0));
      fill_solid( & leds [25], 15, CRGB(0 ,0 ,0));
      FastLED.show();
    }
    
    hazardCounter++;
    
    if (hazardCounter == 44){
      hazardCounter = 0;
    }
  }
  prev_hazards_switch = 1;
}

void startblink(){
  //turn on blinkers solid burning for a short time on startup(unlock)
  if (startBlinkCounter < startBlinkInterval){
//    FastLED.setBrightness(255);
    digitalWrite(l_blinker_pin, HIGH);
    digitalWrite(r_blinker_pin, HIGH);
    fill_solid( & leds [0], 15, CRGB(255 ,120 ,0));
    fill_solid( & leds [25], 15, CRGB(255 ,120 ,0));
    FastLED.show();
    startBlinkCounter++;
  } else if (startBlinkCounter >= startBlinkInterval && startBlink_off == 0){
    FastLED.setBrightness(brightness);
    digitalWrite(l_blinker_pin, LOW);
    digitalWrite(r_blinker_pin, LOW);
    fill_solid( & leds [0], 15, CRGB(0 ,0 ,0));
    fill_solid( & leds [25], 15, CRGB(0 ,0 ,0));
    startBlink_off = 1;
    FastLED.show();
  }
}

void fun1_rainbow(){
  fill_rainbow( leds, NUM_LEDS, hue, 5);
  FastLED.show();
  hue++;
  delay(5);
}

void fun2_strobe(){
  FastLED.setBrightness(255);
  fill_solid( & leds [0], 40, CRGB(255 ,255 ,255));
  delay(60);
  FastLED.show();
  fill_solid( & leds [0], 40, CRGB(0 ,0 ,0));
  delay(60);
  FastLED.show();
}

void fun3_bounce(){
  
}

