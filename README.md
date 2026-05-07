# AI-Food-Freshness-Detection
# 🍎 AI-Based Food Freshness Detection System (Embedded ML)

## 🚀 Overview

This project presents an **AI-powered embedded system** that detects food freshness using a gas sensor and a Decision Tree model deployed on Arduino.

The system analyzes gas emissions from food and classifies it into:

* 🟢 Fresh
* 🟡 Warning
* 🔴 Spoiled

---

## ✨ Key Highlights

* Embedded **Machine Learning model deployed on Arduino (C++)**
* Real-time **food spoilage detection**
* End-to-end system (**sensor → ML → output**)
* Hardware + AI integration

---

## 🧠 AI Model

* Model: **Decision Tree Classifier**
* Trained using: **Python (scikit-learn)**
* Deployed on: **Arduino (C++)**
* Input feature: **Gas sensor ratio (RS/R0)**

> The trained model was converted into embedded logic and runs directly on the microcontroller for real-time predictions.

---

## ⚙️ How It Works

1. Gas sensor detects volatile compounds from food
2. Readings are smoothed using a **moving average filter**
3. Sensor values are converted into a **ratio (RS/R0)**
4. The embedded AI model predicts freshness
5. Output is displayed via:

   * LCD screen
   * LEDs (Green/Red)
   * Buzzer alert

---

## 🧪 Results

* Achieved **~[80–85%] accuracy** on test samples
* Improved stability using **signal filtering and calibration**
* Reliable real-time classification into 3 categories

---

## 🔧 Hardware Components

* Arduino Uno
* MQ Gas Sensor
* LCD (I2C) Display
* Red & Green LEDs
* Buzzer

---

## 🖥️ Software & Tools

* Arduino IDE
* Python (for model training)
* scikit-learn

---

## 📸 Demo

*Add your images here*

![System Setup](images/setup.jpg)

---

## ▶️ How to Run

1. Connect components as per circuit diagram
2. Upload Arduino code using Arduino IDE
3. Power the system
4. Place food near the sensor
5. Observe classification on LCD and LEDs

---

## 📁 Project Structure

AI-Food-Freshness-Detection/
│
├── Arduino_Code/
│   └── freshness_detector.ino
│
├── Model_Training/
│   └── train_model.py
│
├── images/
│   └── setup.jpg
│
├── README.md

---

## 📌 Future Improvements

* Use more sensors for higher accuracy
* Replace Decision Tree with more advanced models (e.g., Random Forest)
* Add mobile app for remote monitoring

---

## 🤝 Contributing

Feel free to fork this repo and improve the system!

---

## 📬 Contact

[Your Name]
[Your LinkedIn]
[Your Email]

---
