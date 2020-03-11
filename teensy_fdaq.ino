/* Test port manipulation for fast data acquisition (timing the delay between two pulses on a single pin)

Nathan smith edit; Sunday 24/11/19
edited on wednesday 12/02/2020

*/
//#include<SD.h>
//#include<SPI.h>

//File myFile;
const int chipSelect = 4;
const int decaypin = 2;     //see D1trigpin func description 

//int yourpin=5      //add in yourpin for timing the timing process on an oscilliscope    

volatile byte Dbytes[256];

bool second_hit{};
double clock_time{1};
double base_delay{0};
volatile int savej;
double decay_time{};
volatile byte saveshit;

void pinD2trig(){
  //if the port and the pin is high
  // if this is called that is the first entry so want to re-initialise Dbytes
   if(GPIOD_PDIR == B00000001){
    // don't want to restart this function when the second pulse occurs
   noInterrupts();
    //check pin D1 256 times
    for(int i=0;i<256;i++){
      //Double check if this is right(I think it is but nathan doesth protest)
      Dbytes[i]=GPIOD_PDIR & B00000001;
      };
    //now read through to give location on the list of the rise
    for(int j=0;j<256;j++){
      //find when the pin changes
       if(Dbytes[j+1]& !Dbytes[j]){
        Serial.print(j+1);
        Serial.println("");
        decay_time = (j+1+base_delay)*clock_time;
        
        // from here, have line of code registering that there has been a muon hit registered.  
        }
      }
    //};
  return decay_time;
  }
} 
void setup(){
  //this means that it'll mark the pin as an interrupt
  pinMode(decaypin, INPUT_PULLUP);
  //sets up serial communication to the laptop
  Serial.begin(38400);
  Serial.println("helllloooo...");
  //light up the LED so we know it's working
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  //good practice
  if(Serial.available()){
    Serial.println("Initialising serial...");
    }
   //connect the interrupt pin to the function we want to call when it triggers (particle entering the scintillator)
  attachInterrupt(decaypin,pinD2trig,RISING);
  if( decaypin != RISING){
    Serial.println("is the fuckup here?");
  }
  //setting up sd card
  //if(!SD.begin(chipSelect)){
   // Serial.println("Initialisation failed");
   // return;
  
  Serial.println("Initialisation done.");
}
/*
volatile byte myInts[256];
void trigpin(){
    if (PINB & B00010000) {
           noInterrupts();
           //digitalWrite(yourpin, HIGH);
           for(int i = 0; i < 256; i++) {
              myInts[i] = PIND & B00010000;
             }
           //digitalWrite(yourpin, LOW);
           interrupts();
           for(int j = 0 ;j < 255; j ++) {
               if(myInts[j+1] & !myInts[j]) {
                   Serial.print(j + 1);
                   Serial.println(" ");
                 };
           };
    };
};
*/
/*need to rewrite the trigpin function to use the Teensy GPIO ports, currently trying
the Teensy 3 layout hoping that the higher pins 23-onwards are in their own portss,
see:
port manipulation 3.x
https://forum.pjrc.com/threads/17532-Tutorial-on-digital-I-O-ATMega-PIN-PORT-DDR-D-B-registers-vs-ARM-GPIO_PDIR-_PDOR?p=21228&viewfull=1#post21228
General info:
https://www.pjrc.com/teensy/teensyLC.html
schemaitcs:
https://forum.pjrc.com/threads/28400-Teensy-LC-schematic-posted
Using the schematics is cumbersome, check the text document in the folder with this code
PortD initial pin- is 2 so use that amd osn not iseniternally
*/

void loop(){
  //myFile = SD.open("teensy_test", FILE_WRITE);
  //if(myFile){
    Serial.print("decay time: ");
    Serial.println(String(decay_time));
    Serial.println(String(GPIOD_PDIR));
    //myFile.print(decay_time);
    //myFile.print(',');
    //myFile.print()//time
    //myFile.print('\n');
    //myFile.close();
    delay(1000);
    //}
  }
