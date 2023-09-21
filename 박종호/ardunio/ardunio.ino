int AA = 10;  // AA를 연결한 디지털 핀
int AB = 6;   // AB를 연결한 디지털 핀



 
void setup()
{
  pinMode(AA, OUTPUT);  // AA를 출력 핀으로 설정
  pinMode(AB, OUTPUT);  // AB를 출력 핀으로 설정
}
 
void loop()
{
  
  digitalWrite(AA, HIGH);  // 정방향으로 모터 회전
  digitalWrite(AB, LOW);
  
  delay(2000);  // 
 
  digitalWrite(AA, LOW);  // 모터 정지
  digitalWrite(AB, LOW);
  delay(2000);  
}