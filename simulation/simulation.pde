/*
06/05/2020
Arnout Luinge
simulation of my bikelights

Key bindings:
  a = toggle left blinker
  d = toggle right blinker
  s = brake light
  l = toggle lights
  r = switch1 = hazards
  t = switch2 = police lights
  y = switch3
  u = switch4

*/


boolean lights, brake, leftBlink, rightBlink, reverse, switch1, switch2, switch3, switch4, leftUsed, rightUsed;
int leftBlueColor, rightBlueColor, leftBlinkColor, rightBlinkColor, lightsColor, lightsColor2, brakeColor;
int leds = 40;
int[] colorsArray = new int[leds];
int blinkCounter, policeCounter;


int blinkColor, blinkOffColor, blueColor, blueOffColor;

PFont debugFont;

void setup() {
  size(1800, 500);
  background(30);
  fill(0);
  noStroke();

  debugFont = createFont("Arial Bold", 30);

  blinkColor = color(255, 150, 0);
  blinkOffColor = color(100, 60, 0);
  blueColor = color(0, 0, 255);
  blueOffColor = color(80, 80, 80);
  lightsColor = color(120, 0, 0);
  lightsColor2 = color(180,0,0);
  brakeColor = color(255, 0, 0);
}

void draw() {

  delay(20);

  clear();

  if (lights == true) {
    lights();
  }

  if (switch1 == true) {
    hazards();
  }

  if (switch2 == true) {
    police1();
  }

  if (switch3 == true) {
    knightRider();
  }

  if (leftBlink == true) {
    leftBlinkerV4();
  }

  if (rightBlink == true) {
    rightBlinkerV4();
  }

  if (brake == true) {
    brake();
  }

  //draw rear leds
  for (int i = 0; i < leds; i++) { //<>//
    fill(colorsArray[i]);
    circle(100+40*i, 400, 20);
  }

  //draw dashboard
    //draw box
    fill(50);
    rect(750, 160, 300, 150, 10);
  
    //draw blinkers
    fill(leftBlinkColor); //dynamic
    circle(870, 220, 15);
    fill(rightBlinkColor); //dynamic    
    circle(1000, 220, 15);
  
    //draw blue lights
    fill(leftBlueColor); //dynamic
    circle(890, 220, 10);
    fill(rightBlueColor); //dynamic    
    circle(980, 220, 10);



  //draw front lights
    //draw bar
    fill(20);
    rect(500, 50, 800, 40, 5);
  
    //draw blinkers
    stroke(0);
    strokeWeight(3);
    fill(leftBlinkColor); //dynamic
    ellipse(460, 70, 100, 60);
    fill(rightBlinkColor); //dynamic    
    ellipse(1340, 70, 100, 60);
    noStroke();
  
    //draw blue lights
    for (int i = 0; i < 5; i++) {
      fill(leftBlueColor); //dynamic
      circle(550 + 15*i, 70, 10);
      fill(rightBlueColor); //dynamic      
      circle(1200 + 15*i, 70, 10);
    }
}

void lights() {
  if (leftUsed == false) {
    for (int i = 0; i < 15; i++) {
      colorsArray[i] = lightsColor;
    }
  }

  for (int i = 15; i < 25; i++) {
    colorsArray[i] = lightsColor;
  }
  
  for (int i = 18; i < 22; i++) {
    colorsArray[i] = lightsColor2;
  }

  if (rightUsed == false) {
    for (int i = 25; i < leds; i++) {
      colorsArray[i] = lightsColor;
    }
  }
}

void clear() {
  //all rear lights to black
  for (int i = 0; i < leds; i++) {
    colorsArray[i] = color(0, 0, 0);
  }

  //front blue lights off
  leftBlueColor = blueOffColor;
  rightBlueColor = blueOffColor;  

  //front blinkers off
  leftBlinkColor = blinkOffColor;
  rightBlinkColor = blinkOffColor;
}

void brake() {
  if (leftUsed == false) {
    for (int i = 0; i < 15; i++) {
      colorsArray[i] = brakeColor;
    }
  } else {
    for (int i = 0; i < 2; i++) {
      colorsArray[i] = brakeColor;
    }
  }

  for (int i = 15; i < 25; i++) {
    colorsArray[i] = brakeColor;
  }

  if (rightUsed == false) {
    for (int i = 25; i < leds; i++) {
      colorsArray[i] = brakeColor;
    }
  } else {
    for (int i = 38; i < 40; i++) {
      colorsArray[i] = brakeColor;
    }
  }
}


void random() {
  for (int i = 0; i < leds; i++) {
    colorsArray[i] = color(int(random(255)), int(random(255)), int(random(255)));
  }
}

void leftBlinkerV1() {
  leftBlinkColor = blinkColor;
  for (int i = 0; i < 15; i++) {
    colorsArray[i] = blinkColor;
  }
}

void rightBlinkerV1() {
  rightBlinkColor = blinkColor;
  for (int i = 25; i < 40; i++) {
    colorsArray[i] = blinkColor;
  }
}

void leftBlinkerV3() {
  leftUsed = true;
  //  if (currentMillis - previousBlinkMillis > blinkInterval){
  //  previousBlinkMillis = currentMillis;

  if (blinkCounter == 0) {
    leftBlinkColor = blinkColor;
  }

  if (blinkCounter < 15) {
    for (int i = 14-blinkCounter; i < 15; i++) {
      colorsArray[i] = blinkColor;
    } 
    leftBlinkColor = blinkColor;
  }

  if (blinkCounter >=15 && blinkCounter < 22) {
    leftBlinkColor = blinkColor;
    for (int i = 0; i < 15; i++) {
      colorsArray[i] = blinkColor;
    }
  }

  if (blinkCounter >= 22) {
    leftBlinkColor = blinkOffColor;

    for (int i = 0; i < 15; i++) {
      colorsArray[i] = color(0, 0, 0);
    }
  }

  color(255);
  textFont(debugFont);
  text(blinkCounter, 650 - 40*blinkCounter, 380);

  blinkCounter++;

  if (blinkCounter == 45) {
    blinkCounter = 0;
  }
  // }
}

void leftBlinkerV4() {
  leftUsed = true;
  //  if (currentMillis - previousBlinkMillis > blinkInterval){
  //  previousBlinkMillis = currentMillis;

  if (blinkCounter == 0) {
    leftBlinkColor = blinkColor;
  }

  if (blinkCounter < 15) {
    for (int i = 14-blinkCounter; i < 15; i++) {
      colorsArray[i] = blinkColor;
    } 
    leftBlinkColor = blinkColor;
  }

  if (blinkCounter >= 15 && blinkCounter < 20) {
    leftBlinkColor = blinkColor;
    for (int i = 0; i < 15; i++) {
      colorsArray[i] = blinkColor;
    }
  }

  if (blinkCounter >=20 && blinkCounter < 35) {
    leftBlinkColor = blinkColor;      
    for (int i = 0; i < 35-blinkCounter; i++) {
      colorsArray[i] = blinkColor; //<>//
    }
  }

  if (blinkCounter >= 22) {
    leftBlinkColor = blinkOffColor;
  }

  if (blinkCounter >= 35) {
    leftBlinkColor = blinkOffColor;

    for (int i = 0; i < 15; i++) {
      colorsArray[i] = color(0, 0, 0);
    }
  }
/*
  fill(255);
  textFont(debugFont);
  text(blinkCounter, 650 - 40*blinkCounter, 380);
*/
  blinkCounter++;

  if (blinkCounter == 45) {
    blinkCounter = 0;
  }
  // }
}

void rightBlinkerV4() {
  rightUsed = true;
  //  if (currentMillis - previousBlinkMillis > blinkInterval){
  //  previousBlinkMillis = currentMillis;

  if (blinkCounter == 0) {
    rightBlinkColor = blinkColor;
  }

  if (blinkCounter < 15) {
    for (int i = 25; i < 25+blinkCounter; i++) {
      colorsArray[i] = blinkColor;
    } 
    rightBlinkColor = blinkColor;
  }

  if (blinkCounter >= 15 && blinkCounter < 20) {
    rightBlinkColor = blinkColor;
    for (int i = 25; i < 40; i++) {
      colorsArray[i] = blinkColor;
    }
  }

  if (blinkCounter >=20 && blinkCounter < 35) {
    rightBlinkColor = blinkColor;      
    for (int i = 5+blinkCounter; i < 40; i++) {
      colorsArray[i] = blinkColor;
    }
  }

  if (blinkCounter >= 22) {
    rightBlinkColor = blinkOffColor;
  }

  if (blinkCounter >= 35) {
    rightBlinkColor = blinkOffColor;

    for (int i = 25; i < 40; i++) {
      colorsArray[i] = color(0, 0, 0);
    }
  }
  
  if (leftBlink == false) {
    blinkCounter++;
  }
  
  if (blinkCounter == 45) {
    blinkCounter = 0;
  }
  // }
}

void police1() { //<>//
  leftUsed = true;
  rightUsed = true;
  
  switch (policeCounter) {
    
    case (0) :
      leftBlueColor = blueColor;
      for (int i = 0; i < 15; i++) {
        colorsArray[i] = blueColor;
      }
      break;
      
    case (3) :  
      rightBlueColor = blueColor;
      for (int i = 25; i < 40; i++) {
        colorsArray[i] = color(0, 0, 255);
      }
      break;
  }
  
  policeCounter++;

  if (policeCounter == 4) {
    policeCounter = 0;
  } //<>//
  
}

void hazards() {
}

void knightRider() {
}

void keyPressed() {
  if (key == 's' ) {
    brake = true;
  }
  
  if (key == 'd' ) {
    if (rightBlink == false) {
      rightBlink = true;
    } else if (rightBlink == true) {
      rightBlink = false;
      blinkCounter = 0;
      rightUsed = false;
    }
  }
  
  if (key == 'x' ) {
    reverse = true;
  }

  if (key == 'a' ) {
    if (leftBlink == false) {
      leftBlink = true;
    } else if (leftBlink == true) {
      leftBlink = false;
      blinkCounter = 0;
      leftUsed = false;
    }
  }  

  if (key == 'l' ) {
    if (lights == false) {
      lights = true;
    } else if (lights == true) {
      lights = false;
    }
  }

  if (key == 'r' ) {
    if (switch1 == false) {
      switch1 = true;
    } else if (switch1 == true) {
      switch1 = false;
    }
  }

  if (key == 't' ) {
    if (switch2 == false) {
      switch2 = true;
    } else if (switch2 == true) {
      switch2 = false;
    }
  }

  if (key == 'y' ) {
    if (switch3 == false) {
      switch3 = true;
    } else if (switch3 == true) {
      switch3 = false;
    }
  }
}

void keyReleased() {
  if (key == 's' ) {
    brake = false;
  }

}
