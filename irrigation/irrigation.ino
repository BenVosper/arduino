#include <LowPower.h>

// ~~~~~~~~~~~~ SETUP ~~~~~~~~~~~~~

const int POWER_LED_PIN = 9;
const int PUMP_RELAY_PIN = 8;
const int PUMP_OVERRIDE_PIN = 7;
const int TANK_LEVEL_PIN = A0;

const int INTERVAL_HOURS = 6;
const int PUMP_DURATION_MINS = 1;

const int LOW_POWER_SECS = 8;
const int EMPTY_TANK = 500;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


const int interval_seconds = INTERVAL_HOURS * 3600;
const int pump_duration_seconds = PUMP_DURATION_MINS * 60;

const int interval_sleeps = interval_seconds / LOW_POWER_SECS;
int sleeps_remaining = interval_sleeps;

void setup() {
  pinMode(POWER_LED_PIN, OUTPUT);
  pinMode(PUMP_RELAY_PIN, OUTPUT);
  pinMode(PUMP_OVERRIDE_PIN, INPUT_PULLUP);
  digitalWrite(PUMP_RELAY_PIN, HIGH);
  digitalWrite(POWER_LED_PIN, HIGH);
}




void low_power(int seconds) {
  const int sleeps = seconds / LOW_POWER_SECS;
  int current_sleeps = 0;
  while (current_sleeps < sleeps) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    current_sleeps ++;
  }
}


void pump() {
  if (analogRead(TANK_LEVEL_PIN) > EMPTY_TANK) {
    digitalWrite(PUMP_RELAY_PIN, LOW);
    low_power(pump_duration_seconds);
    digitalWrite(PUMP_RELAY_PIN, HIGH);
  }
}

void loop() {

  switch (digitalRead(PUMP_OVERRIDE_PIN)) {
    case HIGH:
      digitalWrite(PUMP_RELAY_PIN, LOW);
      break;
    case LOW:
      digitalWrite(PUMP_RELAY_PIN, HIGH);
    default:
      if (sleeps_remaining <= 0) {
        pump();
        sleeps_remaining = interval_sleeps;
      } else {
        LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
        sleeps_remaining --;
      }
  }  
}
