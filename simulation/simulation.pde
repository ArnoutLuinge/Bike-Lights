boolean lights, brake, leftBlink, rightBlink, reverse, switch1, switch2, switch3, switch4;
int leftBlueColor, rightBlueColor, leftBlinkColor, rightBlinkColor, lightsColor, brakeColor;
int leds = 40;
int[] colorsArray = new int[leds];

int blinkColor, blinkOffColor, blueColor, blueOffColor;


void setup() {
    size(1800, 500);
    background(150);
    fill(0);
    noStroke();
    
    blinkColor = color(255,150,0);
    blinkOffColor = color(100,60,0);
    blueColor = color(0,0,255);
    blueOffColor = color(80,80,80);
    lightsColor = color(150,0,0);
    brakeColor = color(255,0,0);
}

void draw() {
  
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
    leftBlinkerV1();
  }
  
  if (rightBlink == true) {
    rightBlinkerV1();
  }
  
  if (brake == true) {
    brake();
  }

  //draw rear leds
  for (int i = 0; i < leds; i++){
    fill(colorsArray[i]);
    circle(100+40*i,400, 20);
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
    for (int i = 0; i < 5; i++){
      fill(leftBlueColor); //dynamic
      circle(550 + 15*i,70,10);
      fill(rightBlueColor); //dynamic      
      circle(1200 + 15*i,70,10);
    }
}

void random() {
  for (int i = 0; i < leds; i++) {
    colorsArray[i] = color(int(random(255)),int(random(255)),int(random(255)));
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

void lights() {
  for (int i = 0; i < leds; i++) {
    colorsArray[i] = lightsColor;
  }
}

void clear() {
  //all rear lights to black
  for (int i = 0; i < leds; i++) {
    colorsArray[i] = color(0,0,0);
  }
  
  //front blue lights off
  leftBlueColor = blueOffColor;
  rightBlueColor = blueOffColor;  
  
  //front blinkers off
  leftBlinkColor = blinkOffColor;
  rightBlinkColor = blinkOffColor;
}

void brake() {
  for (int i = 0; i < leds; i++) {
    colorsArray[i] = brakeColor; 
  }
}

void police1() {
  leftBlueColor = blueColor;
  rightBlueColor = blueColor;  
}

void hazards() {
  
}

void knightRider() {
  
}

void keyPressed() {
  if (key == 's' ) {
    brake = true;
  }
  if (key == 'a' ) {
    leftBlink = true;
  }
  if (key == 'd' ) {
   rightBlink = true;
  }
  if (key == 'x' ) {
    reverse = true;
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
  if (key == 'a' ) {
    leftBlink = false;
  }
  if (key == 'd' ) {
   rightBlink = false;
  }
}
