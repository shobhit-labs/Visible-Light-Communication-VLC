##include <LiquidCrystal.h>

// LCD Pins: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A1; 
const int threshold = 500; // Isse Serial Monitor dekh kar adjust karein

unsigned long signalStart, signalDuration, lastGapTime;
bool isSignalActive = false;
String currentMorse = ""; 
String decodedText = "";  

String morseToChar(String m) {
  if (m == ".-") return "A";   if (m == "-...") return "B";
  if (m == "-.-.") return "C"; if (m == "-..") return "D";
  if (m == ".") return "E";    if (m == "..-.") return "F";
  if (m == "--.") return "G";  if (m == "....") return "H";
  if (m == "..") return "I";   if (m == ".---") return "J";
  if (m == "-.-") return "K";  if (m == ".-..") return "L";
  if (m == "--") return "M";   if (m == "-.") return "N";
  if (m == "---") return "O";  if (m == ".--.") return "P";
  if (m == "--.-") return "Q"; if (m == ".-.") return "R";
  if (m == "...") return "S";  if (m == "-") return "T";
  if (m == "..-") return "U";  if (m == "...-") return "V";
  if (m == ".--") return "W";  if (m == "-..-") return "X";
  if (m == "-.--") return "Y"; if (m == "--..") return "Z";
  if (m == " ") return " ";    // Space handling
  return "";
}

void setup() {
  lcd.begin(16, 2);
  lcd.print("VLC Ready...");
  delay(2000);
  lcd.clear();
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);

  if (sensorValue > threshold) {
    if (!isSignalActive) {
      signalStart = millis();
      isSignalActive = true;
    }
    lastGapTime = millis();
  } else {
    if (isSignalActive) {
      signalDuration = millis() - signalStart;
      isSignalActive = false;

      // App 200ms par hai, toh:
      // Dot approx 200ms, Dash approx 600ms
      if (signalDuration >= 100 && signalDuration < 400) {
        currentMorse += ".";
      } else if (signalDuration >= 400) {
        currentMorse += "-";
      }
    }

    // Letter Gap (approx 800ms - 1 sec gap)
    if (currentMorse != "" && (millis() - lastGapTime > 800)) {
      String letter = morseToChar(currentMorse);
      decodedText += letter;
      currentMorse = "";
      
      updateLCD();
      Serial.print(letter);
    }
    
    // Word Gap / Space (approx 2.5 sec gap)
    if (millis() - lastGapTime > 2500 && decodedText != "" && !decodedText.endsWith(" ")) {
       decodedText += " ";
       updateLCD();
    }
  }
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  // Agar text 16 char se bada ho toh second line use karein
  if (decodedText.length() > 16) {
    lcd.print(decodedText.substring(0, 16));
    lcd.setCursor(0, 1);
    lcd.print(decodedText.substring(16));
  } else {
    lcd.print(decodedText);
  }
}
