//using pin 2 (can be changed to any pin)
int trig = 2;
 
void setup() {                
  // initialize the digital pins as output.
  pinMode(trig, OUTPUT);         
 
//turn on the camera, must have this
 digitalWrite(trig, HIGH); 
}
 
// Hold HIGH and trigger quick (<250ms) LOW to take a photo. Holding LOW and trigger HIGH starts/stops video recording
 
void loop() {
//takes a 7 second video, when red light is on, video is recording!
  digitalWrite(trig, LOW);   
  
  delay(7000);               
 
  digitalWrite(trig, HIGH);    
 
  //Delay between pictures
  delay(9000);               
  
}
