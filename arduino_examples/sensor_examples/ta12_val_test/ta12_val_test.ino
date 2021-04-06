#define  sensorTA12  A0
void setup() 
{
   Serial.begin(9600); 
   pinMode(sensorTA12, INPUT);
}
uint16_t val=0;
void loop() 
{
  val= getVPP();
  Serial.println(val);

}
float getVPP()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0; 
  
  uint32_t start_time =0;
   while(start_time < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorTA12);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       start_time+=1;
       delay(1);
   }
   start_time = 0;
   // Convert the digital data to a voltage
   
  
   return maxValue;
 }
