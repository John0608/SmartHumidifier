#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Thread.h>
#include <ThreadController.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#include <assert.h>
#include <ArduinoJson.h>

#define Encoder_CLK 5
#define Encoder_DT 7
#define Encoder_SW 6

#define DetectHum_Pin A1

#define Hum_PIN 8

#define BT_TX 2
#define BT_RX 3

LiquidCrystal_I2C display(0x27, 16, 2);
DHT hum = DHT(DetectHum_Pin, DHT11);
SoftwareSerial BTSerial(BT_TX, BT_RX);

//Thread init
Thread t_display = Thread();
Thread t_hum = Thread();
Thread t_rt = Thread();
Thread t_proc = Thread();
Thread bt_proc = Thread();
Thread bt_receive = Thread();
ThreadController controller = ThreadController();


int hum_target = 40;
int tem_now = hum.readTemperature();
int hum_now = hum.readHumidity();
int pre_hum_target = 0;
int pre_hum_now = 0;

int RT_CLK_STATUS = digitalRead(Encoder_CLK);
int RT_DT_STATUS = digitalRead(Encoder_DT);
bool RT_SW_STATUS = false;

bool hum_status = false;

bool Power = true;
bool pre_Power = false;




void setup() {

  Serial.begin(9600);
  BTSerial.begin(9600);
  hum.begin();

  pinMode(Encoder_CLK, INPUT);
  pinMode(Encoder_SW, INPUT_PULLUP);
  pinMode(Encoder_DT, INPUT);
  pinMode(Hum_PIN, OUTPUT);

  //Display
  display.init();
  display.backlight();

  //Thread
  t_display.onRun(print);
  t_display.setInterval(50);
  t_hum.onRun(hum_update);
  t_hum.setInterval(1000);
  t_rt.onRun(rt_update);
  t_rt.setInterval(0);
  t_proc.onRun(Process);
  t_proc.setInterval(10);
  bt_proc.onRun(BT_Proc);
  bt_proc.setInterval(500);
  bt_receive.onRun(BT_Revice);
  bt_receive.setInterval(50);

  controller.add(&t_display);
  controller.add(&t_hum);
  controller.add(&t_rt);
  controller.add(&t_proc);
  controller.add(&bt_proc);
  controller.add(&bt_receive);
}

void loop() {
  // put your main code here, to run repeatedly:
  controller.run();
}

void print() {
  if (pre_hum_now != hum_now || pre_hum_target != hum_target) {
    display.clear();

    display.setCursor(0, 0);
    display.print("N_HUM : ");
    display.print(hum_now);
    display.print("%");

    display.setCursor(0, 1);
    display.print("T_HUM : ");
    display.print(hum_target);
    display.print("%");

    pre_hum_now = hum_now;
    pre_hum_target = hum_target;
  }
}

void hum_update() {
  hum_now = hum.readHumidity();
  tem_now = hum.readTemperature();
}

void rt_update() {

  if (digitalRead(Encoder_CLK) == RT_CLK_STATUS) {
    boolean TurnDetected = false;
    boolean up = (digitalRead(Encoder_DT) == digitalRead(Encoder_CLK));

    if (up) {
      Serial.println("LEFT");
      if (hum_target > 40 && Power) {
        --hum_target;
      }
    } else {
      // 오른쪽으로 돌렸을 때
      Serial.println("RIGHT");
      if (hum_target < 80 && Power) {
        ++hum_target;
      }
    }
    TurnDetected = true;

    if (TurnDetected) TurnDetected = false;
    RT_CLK_STATUS = digitalRead(digitalRead(Encoder_CLK));
  }

  if (digitalRead(Encoder_SW) == LOW) {
    if (RT_SW_STATUS == false) {
      RT_SW_STATUS = true;
      Serial.println("눌림");
      if (Power == true) {
        Power = false;
      } else {
        Power = true;
      }
    }
  } else RT_SW_STATUS = false;
}

void Process() {
  if (Power == false) {
    if (pre_Power == true) {
      display.noDisplay();
      display.noBacklight();
      digitalWrite(Hum_PIN, LOW);
      hum_status = false;
      pre_Power = false;
    }

  } else {
    if (pre_Power == false) {
      display.display();
      display.backlight();
      pre_Power = true;
    } else {
      if (hum_now < hum_target) {
        if (hum_status == false) {
          digitalWrite(Hum_PIN, HIGH);
          Serial.println("가습기 켬");
          hum_status = true;
        }
      } else {
        if (hum_status == true) {
          digitalWrite(Hum_PIN, LOW);
          Serial.println("가습기 끔");
          hum_status = false;
        }
      }
    }
    if (hum_now < hum_target) {
      if (hum_status == false) {
        digitalWrite(Hum_PIN, HIGH);
        Serial.println("가습기 켬");
        hum_status = true;
      }
    } else {
      if (hum_status == true) {
        digitalWrite(Hum_PIN, LOW);
        Serial.println("가습기 끔");
        hum_status = false;
      }
    }
  }
}

void BT_Proc() {
  StaticJsonDocument<600> json;
  json["now_hum"] = (int)hum_now;
  json["now_tem"] = (int)tem_now;
  json["target_hum"] = (int)hum_target;
  // JSON 데이터를 문자열로 직렬화합니다.
  String jsonString;
  serializeJson(json, jsonString);
  BTSerial.write(jsonString.c_str());
}

void BT_Revice() {
  if(BTSerial.available() > 0) {
    String data = BTSerial.readString();
    Serial.println(data);
    DynamicJsonDocument doc(200);
    DeserializationError error = deserializeJson(doc, data);
    if (error) {
      return;
    }
    if(doc["t"] == "p") {
      if(Power == true) { Power = false; }
      else { Power = true;}
    }
    else if(doc["t"] == "h") {
      int hum_int = doc["h"];
      hum_target = hum_int;
    }
  }
}
