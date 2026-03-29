#include <math.h>
#include "horizontalDistanceSensor.h"
#include "verticalDistanceSensor.h"
#include "waterSensor.h"
#include "motor.h"
#include "buzzer.h"

constexpr uint8_t FOOT_TRIG_PIN  = 2;
constexpr uint8_t FOOT_ECHO_PIN  = 3;
constexpr uint8_t FRONT_TRIG_PIN = 4;
constexpr uint8_t FRONT_ECHO_PIN = 5;
constexpr uint8_t BUZZER_PIN     = 8;
constexpr uint8_t MOTOR_PIN      = 9;
constexpr uint8_t WATER_PIN      = A0;

constexpr int WATER_THRESHOLD = 150;

constexpr float FOOT_STABLE_BAND_CM      = 3.0f;
constexpr float FOOT_DELTA_THRESHOLD_CM  = 10.0f;
constexpr uint8_t FOOT_CONFIRM_READS     = 2;

constexpr float FRONT_CLEAR_DISTANCE_CM  = 150.0f;
constexpr uint8_t FRONT_MISS_RESET_COUNT = 3;

constexpr unsigned long FRONT_SAMPLE_MS         = 120;
constexpr unsigned long FOOT_SAMPLE_MS          = 140;
constexpr unsigned long WATER_SAMPLE_MS         = 200;
constexpr unsigned long DEBUG_PRINT_INTERVAL_MS = 1200;
constexpr unsigned long GROUND_COOLDOWN_MS      = 1200;
constexpr unsigned long WATER_COOLDOWN_MS       = 1500;

HorizontalDistanceSensor frontSensor(FRONT_TRIG_PIN, FRONT_ECHO_PIN);
VerticalDistanceSensor footSensor(FOOT_TRIG_PIN, FOOT_ECHO_PIN);
WaterLevelSensor waterSensor(WATER_PIN, WATER_THRESHOLD);
Motor motor(MOTOR_PIN);
RobotVoice buzzer(BUZZER_PIN);

unsigned long lastFrontMs = 0;
unsigned long lastFootMs = 0;
unsigned long lastWaterMs = 0;
unsigned long lastDebugMs = 0;

float filteredFrontCm = -1.0f;
float filteredFootCm = -1.0f;
float footBaselineCm = -1.0f;

float lastRawFrontCm = -1.0f;
float lastRawFootCm = -1.0f;
float lastFootDeltaCm = 0.0f;

uint8_t frontMissCount = 0;

uint8_t groundConfirmCount = 0;
bool groundAlertLatched = false;
bool groundAlertEvent = false;
unsigned long lastGroundAlertMs = 0;

bool waterWasDetected = false;
unsigned long lastWaterAlertMs = 0;
int lastWaterLevel = 0;
bool lastWaterState = false;

float smoothValue(float previous, float current, float alpha) {
  if (current < 0.0f) return previous;
  if (previous < 0.0f) return current;
  return previous + alpha * (current - previous);
}

void printFloatOrNA(float value) {
  if (value < 0.0f) {
    Serial.print("NA");
  } else {
    Serial.print(value, 1);
  }
}

void updateFrontObstacle() {
  unsigned long now = millis();
  if (now - lastFrontMs < FRONT_SAMPLE_MS) return;
  lastFrontMs = now;

  float rawFront = frontSensor.readDistanceCm();
  lastRawFrontCm = rawFront;

  if (rawFront < 0.0f) {
    frontMissCount++;

    if (frontMissCount >= FRONT_MISS_RESET_COUNT) {
      filteredFrontCm = -1.0f;
      motor.off();
    }
    return;
  }

  frontMissCount = 0;

  if (rawFront > FRONT_CLEAR_DISTANCE_CM) {
    filteredFrontCm = rawFront;
    motor.off();
    return;
  }

  filteredFrontCm = smoothValue(filteredFrontCm, rawFront, 0.25f);
  motor.updateFromDistance((long)filteredFrontCm);
  // motor.off();
}

void updateGroundChange() {
  unsigned long now = millis();
  if (now - lastFootMs < FOOT_SAMPLE_MS) return;
  lastFootMs = now;

  float rawFoot = footSensor.readDistanceCm();
  lastRawFootCm = rawFoot;

  if (rawFoot < 0.0f) return;

  filteredFootCm = smoothValue(filteredFootCm, rawFoot, 0.25f);

  if (footBaselineCm < 0.0f) {
    footBaselineCm = filteredFootCm;
    return;
  }

  float delta = filteredFootCm - footBaselineCm;
  lastFootDeltaCm = delta;
  float absDelta = fabs(delta);

  groundAlertEvent = false;

  if (absDelta <= FOOT_STABLE_BAND_CM) {
    groundConfirmCount = 0;
    groundAlertLatched = false;
    footBaselineCm = footBaselineCm * 0.92f + filteredFootCm * 0.08f;
  } else if (absDelta >= FOOT_DELTA_THRESHOLD_CM) {
    groundConfirmCount++;

    if (!groundAlertLatched &&
        groundConfirmCount >= FOOT_CONFIRM_READS &&
        now - lastGroundAlertMs >= GROUND_COOLDOWN_MS) {
      buzzer.alertGroundChange();
      Serial.println("[ALERT] Ground change detected");
      lastGroundAlertMs = now;
      groundAlertLatched = true;
      groundAlertEvent = true;
    }
  } else {
    groundConfirmCount = 0;
  }
}

void updateWater() {
  unsigned long now = millis();
  if (now - lastWaterMs < WATER_SAMPLE_MS) return;
  lastWaterMs = now;

  lastWaterLevel = waterSensor.readLevel();
  lastWaterState = (lastWaterLevel >= WATER_THRESHOLD);

  static bool previousWaterState = false;

  if (lastWaterState != previousWaterState) {
    Serial.print("[WATER] level=");
    Serial.print(lastWaterLevel);
    Serial.print(" threshold=");
    Serial.print(WATER_THRESHOLD);
    Serial.print(" -> ");
    Serial.println(lastWaterState ? "WET" : "DRY");
    previousWaterState = lastWaterState;
  }

  if (lastWaterState) {
    if (!waterWasDetected || now - lastWaterAlertMs >= WATER_COOLDOWN_MS) {
      Serial.print("[WATER ALERT] level=");
      Serial.println(lastWaterLevel);

      buzzer.alertWater();

      lastWaterAlertMs = now;
    }
    waterWasDetected = true;
  } else {
    waterWasDetected = false;
  }
}

void printDebugStatus() {
  unsigned long now = millis();
  if (now - lastDebugMs < DEBUG_PRINT_INTERVAL_MS) return;
  lastDebugMs = now;

  Serial.print("[DBG] frontRaw=");
  printFloatOrNA(lastRawFrontCm);
  Serial.print(" frontFilt=");
  printFloatOrNA(filteredFrontCm);
  Serial.print(" miss=");
  Serial.print(frontMissCount);
  Serial.print(" motor=");
  Serial.print(motor.getModeName());
  Serial.print(" pwm=");
  Serial.print(motor.getIntensity());

  Serial.print(" | footRaw=");
  printFloatOrNA(lastRawFootCm);
  Serial.print(" base=");
  printFloatOrNA(footBaselineCm);
  Serial.print(" dY=");
  Serial.print(lastFootDeltaCm, 1);
  Serial.print(" ground=");
  Serial.print(groundAlertLatched ? "ARMED" : "OK");

  Serial.print(" | water=");
  Serial.print(lastWaterLevel);
  Serial.print("/");
  Serial.print(WATER_THRESHOLD);
  Serial.print(" state=");
  Serial.print(lastWaterState ? "WET" : "DRY");

  Serial.println();
}

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("Testing water buzzer in 2 seconds...");
  delay(2000);
  buzzer.alertWater();
  Serial.println("Buzzer test done");

  Serial.println("=== Smart Cane Boot ===");

  frontSensor.begin();
  footSensor.begin();
  waterSensor.begin();
  motor.begin();
  buzzer.begin();

  Serial.println("Front sensor ready");
  Serial.println("Foot sensor ready");
  Serial.println("Motor ready");
  Serial.println("=======================");
}

void loop() {
  updateFrontObstacle();
  updateGroundChange();
  updateWater();

  printDebugStatus();
}