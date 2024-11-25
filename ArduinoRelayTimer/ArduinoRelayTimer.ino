#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;

const int relayPin = 8;   // Pin connected to relay
const int buzzerPin = 7;  // Pin connected to buzzer
const int targetHour = 9; // Target time (10 AM)
const int targetMinute = 40;
const int targetSecond = 0;
const int holdTime = 30000; // Time the relay will stay on in milliseconds

bool relayActive = false; // To track if the relay is active
unsigned long relayStartTime = 0; // To track when the relay was activated

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure relay is off initially
  digitalWrite(buzzerPin, LOW); // Ensure buzzer is off initially

  Serial.begin(9600);

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Check if the RTC is running
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, setting the time...");
    // Uncomment the following line to set the RTC time
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Sets to compile time
  }

  // Print header
  Serial.println("Target Time: HH:MM:SS || Current Time: HH:MM:SS || Trigger Status: ACTIVE/INACTIVE");
}

void loop() {
  DateTime now = rtc.now(); // Get current time

  // Format and print output to Serial Monitor
  Serial.print("Target Time: ");
  if (targetHour < 10) Serial.print("0");
  Serial.print(targetHour);
  Serial.print(":");
  if (targetMinute < 10) Serial.print("0");
  Serial.print(targetMinute);
  Serial.print(":");
  if (targetSecond < 10) Serial.print("0");
  Serial.print(targetSecond);

  Serial.print(" || Current Time: ");
  if (now.hour() < 10) Serial.print("0");
  Serial.print(now.hour());
  Serial.print(":");
  if (now.minute() < 10) Serial.print("0");
  Serial.print(now.minute());
  Serial.print(":");
  if (now.second() < 10) Serial.print("0");
  Serial.print(now.second());

  Serial.print(" || Trigger Status: ");

  // Check if it's the target time
  if (now.hour() == targetHour && now.minute() == targetMinute && now.second() == targetSecond && !relayActive) {
    digitalWrite(relayPin, HIGH); // Turn on relay
    digitalWrite(buzzerPin, HIGH); // Activate buzzer
    relayActive = true; // Set relay as active
    relayStartTime = millis(); // Record the start time
    Serial.println("ACTIVE");
  } 
  // Check if the relay has been active for Hold time
  else if (relayActive && millis() - relayStartTime >= holdTime) {
    digitalWrite(relayPin, LOW); // Turn off relay
    digitalWrite(buzzerPin, LOW); // Deactivate buzzer
    relayActive = false; // Reset relay status
    Serial.println("INACTIVE");
  } 
  else {
    // Keep the relay state and status unchanged
    if (relayActive) {
      Serial.println("ACTIVE");
    } else {
      Serial.println("INACTIVE");
    }
  }

  delay(1000); // Check every second
}
