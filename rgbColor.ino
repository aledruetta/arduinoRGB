/**
 * 24-bit color spectrum - RGB led
 * @author: Alejandro Druetta
 * @date  : 05/22/16
 */

// Led pins
#define RED   6
#define GREEN 5
#define BLUE  3

#define DEBUG false

// Color hexadecimal values
const unsigned long red   = 0xFF0000;
const unsigned long green = 0x00FF00;
const unsigned long blue  = 0x0000FF;

const unsigned long yellow  = red + green;
const unsigned long cyan    = green + blue;
const unsigned long magenta = blue + red;

const unsigned long colors[] = {red, yellow, green, cyan, blue, magenta};

void setup() {
  pinMode(RED,   OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE,  OUTPUT);

  Serial.begin(9600);
  Serial.println("Starting Serial...");
  if (!Serial);
  Serial.println("Started!");
 }

void loop() {
  // Sequence blinks
  for (size_t i=0; i<6; i++) {
    blinkColor(colors[i], 4);
  }
  blinkColor(red, 4);

  delay(1000);

  // Sequence transitions
  transition(red,   green);
  transition(green, blue);
  transition(blue,  red);

  delay(500);

  transition(red,   blue);
  transition(blue,  green);
  transition(green, red);

  delay(1000);
}

void blinkColor(unsigned long color, int n) {
  for (int i=0; i<n+1; i++) {
    digitalWrite(RED,   LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE,  LOW);
    delay(30);
    writeColor(color);
    delay(30);
  }
  delay(1000);
}

void writeColor(unsigned long color) {
  analogWrite(RED,   color >> 16);
  analogWrite(GREEN, color >> 8);
  analogWrite(BLUE,  color);
  if (DEBUG)
    Serial.println(color, HEX);
  delay(10);
}

void transition(long a, long b) {
  unsigned long pass = abs(a - b) / 0xFF;

  if (a < b)
    for (unsigned long i=a; i<b; i+=pass) {
      writeColor(i);
    }
  else if (a > b)
    for (unsigned long i=a; i>b; i-=pass) {
      writeColor(i);
    }
  else
    writeColor(a);
}

