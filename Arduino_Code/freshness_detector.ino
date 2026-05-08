#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ================= LCD CONFIG =================
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ================= HARDWARE PINS =================
const int SENSOR_PIN = A0;
const int GREEN_LED = 7;
const int RED_LED   = 4;
const int BUZZER    = 8;

// ================= SENSOR CALIBRATION =================
// R0 value obtained during calibration phase
const float R0 = 2.56;

// =====================================================
// ================= AI MODEL (Decision Tree) ===========
// =====================================================

// Decision Tree trained in Python (scikit-learn)
// and converted manually to embedded C++ for inference
class DecisionTree {
public:
    int predict(float ratio) {

        if (ratio <= 0.322149395942688) {

            if (ratio <= 0.09936778992414474) {
                return 2; // Spoiled
            }
            else {
                if (ratio <= 0.11093186214566231) {
                    return 1; // Warning
                }
                else {
                    if (ratio <= 0.2663399428129196) {
                        if (ratio <= 0.24475368857383728) {
                            return 1; // Warning
                        } else {
                            return 2; // Spoiled
                        }
                    } else {
                        return 2; // Spoiled
                    }
                }
            }
        }
        else {
            if (ratio <= 0.38857822120189667) {
                return 0; // Fresh
            }
            else if (ratio <= 0.42448200285434723) {
                return 2; // Spoiled
            }
            else if (ratio <= 0.47143931686878204) {
                return 1; // Warning
            }
            else {
                return 0; // Fresh
            }
        }
    }
};

// Create model instance
DecisionTree model;

// =====================================================
// ================= UTILITY FUNCTIONS ==================
// =====================================================

// Apply moving average filter to reduce sensor noise
float readFilteredSensor(int samples = 20, int delayMs = 30) {
    float total = 0;

    for (int i = 0; i < samples; i++) {
        total += analogRead(SENSOR_PIN);
        delay(delayMs); // simple filtering (can be improved using millis)
    }

    return total / samples;
}

// Convert raw sensor reading to gas ratio (RS/R0)
float computeGasRatio(float rawValue) {

    // Convert analog reading to voltage
    float voltage = rawValue * (5.0 / 1023.0);

    // Avoid division by zero
    if (voltage == 0) return 0;

    // Calculate sensor resistance
    float RS_gas = (5.0 - voltage) / voltage;

    // Normalize using calibration baseline
    float ratio = RS_gas / R0;

    return ratio;
}

// =====================================================
// ======================= SETUP ========================
// =====================================================

void setup() {

    Serial.begin(9600);

    lcd.init();
    lcd.backlight();

    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);

    lcd.setCursor(0, 0);
    lcd.print("Fruit AI System");

    delay(2000);
    lcd.clear();
}

// =====================================================
// ======================== LOOP ========================
// =====================================================

void loop() {

    // ===== 1. Read Sensor (Filtered) =====
    float rawSensorValue = readFilteredSensor();

    // ===== 2. Compute Feature =====
    float ratio = computeGasRatio(rawSensorValue);

    // ===== 3. Run AI Model =====
    int prediction = model.predict(ratio);

    // ===== 4. Debug Output =====
    Serial.print("Ratio: ");
    Serial.println(ratio);

    Serial.print("Prediction: ");
    Serial.println(prediction);

    // ===== 5. Display Ratio =====
    lcd.setCursor(0, 0);
    lcd.print("Q:");
    lcd.print(ratio);
    lcd.print("    ");

    // ===== 6. Output Result =====

    // 0 = Fresh
    if (prediction == 0) {

        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(RED_LED, LOW);
        noTone(BUZZER);

        lcd.setCursor(0, 1);
        lcd.print("Status:FRESH  ");
    }

    // 1 = Warning
    else if (prediction == 1) {

        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, LOW);
        noTone(BUZZER);

        lcd.setCursor(0, 1);
        lcd.print("Status:WARNING");
    }

    // 2 = Spoiled
    else {

        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        tone(BUZZER, 1000);

        lcd.setCursor(0, 1);
        lcd.print("Status:SPOILED");
    }

    delay(1000); // can be replaced with non-blocking timing
}
