# 📟 WiFi Based Notice Board (WNB)

This project is a **WiFi-enabled LED Notice Board** built using the **ESP8266** microcontroller and the **DMDESP LED display driver**.  
It allows users to send messages from a web browser, which are then displayed as text on the LED panel.

---

## ✨ Features
- ✅ Connects ESP8266 to a WiFi network  
- ✅ Hosts a **web server** for text input  
- ✅ Displays scrolling messages on an **LED panel**  
- ✅ Default welcome text:  
  ```
  WELCOME to ARKERE POLYTECHNIC COLLEGE
  ```
- ✅ Supports updating messages in **real time** from any device connected to the same WiFi  

---

## 📂 Project Structure
```
WNB/
├── Code/
│   └── arkere_p10_NEW/
│       └── arkere_p10_NEW.ino   # Main Arduino sketch
├── Libriiers_For_WNB_Project/
│   ├── DMDESP.zip               # LED display library
│   ├── ESPAsynTCP.zip            # Async TCP library
│   └── ESPWebbrowser.zip         # Async Web Server library
└── IMG20220803013643.jpg         # Project image (LED display setup)
```

---

## 🛠️ Requirements

### Hardware
- ESP8266 board (e.g., NodeMCU / Wemos D1 Mini)  
- LED Matrix Panels (configured as 4 panels wide × 1 high)  
- Power supply for LED panels  

### Software
- **Arduino IDE** with ESP8266 board support installed  
- Required libraries (provided in `Libriiers_For_WNB_Project/`):
  - `DMDESP`  
  - `ESPAsyncTCP`  
  - `ESPAsyncWebServer`

---

## 🚀 Setup & Installation

1. Install **Arduino IDE** and add support for **ESP8266 boards**.  
2. Extract and install the required libraries from `Libriiers_For_WNB_Project/`.  
3. Open the Arduino sketch:  
   ```
   WNB/Code/arkere_p10_NEW/arkere_p10_NEW.ino
   ```
4. Update WiFi credentials in the code if needed:
   ```cpp
   const char* ssid = "YourWiFiSSID";
   const char* password = "YourWiFiPassword";
   ```
5. Connect your ESP8266 and upload the sketch.  
6. Open the **Serial Monitor** to find the assigned IP address.  
7. Enter the IP address in a web browser → You’ll see a web form to submit text.  
8. Enter your desired text → It will scroll on the LED display.  

---

## 🌐 Web Interface
The ESP8266 serves a simple web page:  

```html
<!DOCTYPE HTML>
<html>
  <head>
    <title>GOVT. POLYTECHNIC ARKERE</title>
    <meta name="viewport" content="width=device-width, initial-scale=5">
    <p> 
      <font size="9" face="sans-serif"> 
        <marquee> GOVT. POLYTECHNIC ARKERE </marquee> 
      </font> 
    </p>
  </head>
  <body>
    <center>
      <form action="/get">
        Enter Text to Display: <input type="text" name="input1">
        <input type="submit" value="Send">
      </form>
    </center>
  </body>
</html>
```

- Input box for entering new text  
- Submit button to send it to the LED display  

---

## 📸 Project Preview
![Project Setup](IMG20220803013643.jpg)

---

