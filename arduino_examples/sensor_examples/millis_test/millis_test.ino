uint8_t flag;

void setup(){
  Serial.begin(9600);
}
void loop(){
  Serial.print("Time: ");
  flag = millis();
  //prints time since program started
  Serial.println(flag);
  // wait a second so as not to send massive amounts of data
  delay(100);
  flag=0;
}
