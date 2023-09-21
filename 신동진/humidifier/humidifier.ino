int humpin = 5;
void setup() {
  // put your setup code here, to run once:
  pinMode(humpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(humpin,HIGH);
  delay(4000);
  digitalWrite(humpin,LOW);
  delay(1500);

}
