#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C: 0x27, 16x2 LCD

const int buttonON = LOW;    // ボタンが押されているとピンの値はLOW
const int buttonOFF = HIGH;  // ボタンが押されていないとピンの値はHIGH

const int buttonPinWhite = 2;
const int buttonPinGreen = 3;
const int buttonPinBlue = 4;
const int buttonPinYellow = 5;
const int buttonPinRed = 6;
const int ledPin =  13;
int buttonStateWhite = 0;
int buttonStateGreen = 0;
int buttonStateBlue = 0;
int buttonStateYellow = 0;
int buttonStateRed = 0;
String inputData = "";
String outputData = "";
unsigned long microtime;
long load;
long actuatorPosition;
int Temprature1;
int Temprature2;
String str_microtimeh;
byte chksum = 0;

void setup() {
    Serial.begin(115200);

    // I2C通信の開始宣言
    Wire.begin();

    // ディスプレイセットアップ
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Data waiting..");

    pinMode(ledPin, OUTPUT);      
    pinMode(buttonPinWhite, INPUT_PULLUP);     
    pinMode(buttonPinGreen, INPUT_PULLUP);     
    pinMode(buttonPinBlue, INPUT_PULLUP);     
    pinMode(buttonPinYellow, INPUT_PULLUP);     
    pinMode(buttonPinRed, INPUT_PULLUP);     
}

void loop(){
    buttonStateWhite = digitalRead(buttonPinWhite);
    if (buttonStateWhite == buttonON) {     // 白ボタンが押されていたら
        digitalWrite(ledPin, HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("===> 05h");
        delay(300);
        Serial.println("05h");
        delay(200);
    } 
    else {
        digitalWrite(ledPin, LOW); 
    }

    buttonStateGreen = digitalRead(buttonPinGreen);
    if (buttonStateGreen == buttonON) {     // 緑ボタンが押されていたら
        digitalWrite(ledPin, HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("===> 0001h");
        delay(300);
        makeRandomData_0001h();
        Serial.println(outputData);
        delay(200);
    } 
    else {
        digitalWrite(ledPin, LOW); 
    }

    buttonStateBlue = digitalRead(buttonPinBlue);
    if (buttonStateBlue == buttonON) {     // 青ボタンが押されていたら
        digitalWrite(ledPin, HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("===> 0010h");
        delay(300);
        Serial.println(outputData);
        delay(200);
    } 
    else {
        digitalWrite(ledPin, LOW); 
    }

    buttonStateYellow = digitalRead(buttonPinYellow);
    if (buttonStateYellow == buttonON) {     // 黄ボタンが押されていたら
        digitalWrite(ledPin, HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("===> 0020h");
        delay(300);
        Serial.println(outputData);
        delay(200);
    } 
    else {
        digitalWrite(ledPin, LOW); 
    }

    buttonStateRed = digitalRead(buttonPinRed);
    if (buttonStateRed == buttonON) {     // 赤ボタンが押されていたら
        digitalWrite(ledPin, HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("===> 0030h");
        delay(300);
        Serial.println(outputData);
        delay(200);
    } 
    else {
        digitalWrite(ledPin, LOW); 
    }

    if(Serial.available() > 0) {
        inputData = Serial.readStringUntil(';');
        lcd.clear();
        lcd.setCursor(0,0);
        delay(300);

        if(inputData == "04h") {
            lcd.setCursor(0,1);
            lcd.print(inputData);
            lcd.print("  <===");
            for(int i=0;i<8;i++){
                digitalWrite(ledPin, HIGH);
                delay(100);
                digitalWrite(ledPin, LOW);
                delay(100);
            }
        }
        else{
            for(int i=0;i<3;i++){
            lcd.setCursor(0,1);
            lcd.print(inputData);
            lcd.print("  <===");
                digitalWrite(ledPin, HIGH);
                delay(500);
                digitalWrite(ledPin, LOW);
                delay(300);
            }
        }
    }
}

void makeRandomData_0001h(){
    outputData = "";
    outputData += "0001h";
    microtime = 0;
    load = 0.0;
    actuatorPosition = 0.0;
    Temprature1 = 0;
    Temprature2 = 0;

    for(int i=0;i<125;i++){
        microtime = random(0, 0xffff);    // microtime
        // str_hex_microtime[i] = String(microtime[i], HEX);
        Serial.print("microtime["); Serial.print(i);    Serial.print("] = ");
        Serial.print(microtime);
        Serial.print(" , (byte)=");
        //Serial.println((byte)microtime[i]);
        Serial.print(microtime, HEX);
        str_microtimeh = String(microtime, HEX);
        Serial.print("  , HEX = "); Serial.print(str_microtimeh);
        charMicrotime1 = 
        Serial.println("");
        outputData += microtime;
        load = random(-2147483648, 2147483647);
        outputData += load;
        actuatorPosition = random(-2147483648, 2147483647);
        outputData += actuatorPosition;
        Temprature1 = random(-200, 500);
        outputData += Temprature1;
        Temprature2 = random(-200, 500);
        outputData += Temprature2;
    }
}