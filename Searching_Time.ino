/*
The following code searches for a specific time introduced by the user in a CSV file
logged by different sensors. The code checks if the time exists and if so it prints 
out the reading values associated with that date

Created, edited, and modified Jorge Salazar Sanchez
in June 2019
*/

#include <SPI.h>
#include <SD.h>
#include <string.h>

File myFile;

int arrayPointer = 0;
int n=0;
int number = 6;
int q=0;
int counter=0;

long month_=0;
long day_=0;
long year_=0;
long hour_=0;
long minute_1=0;

char* strings[20];

String my_date;
String my_hour;
String minute_;



///////////////////////////////////////////////////////////////////
// Setting up Communications (SETUP)
//////////////////////////////////////////////////////////////////

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


///////////////////////////////////////////////////////////////////
// Setting up Serial Port and the SD Card
//////////////////////////////////////////////////////////////////
  
  Serial.print(F("Initializing SD card..."));
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  

  if (!SD.begin(10)) {
    Serial.println(F("initialization failed!"));
    return;
  }
  Serial.println(F("initialization done."));
  delay(2000);

Serial.println("");



///////////////////////////////////////////////////////////////////
// Searching for the time
//////////////////////////////////////////////////////////////////

// Function that returns the introduced time by the user
my_hour=readingtime();

delay(3000);

Serial.println(F("These are the readings related to the selected time:"));
Serial.println("");




    // re-open the file for reading:
  myFile = SD.open("421pm60_.csv");

  if (myFile) {
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {

    // Place the reading value in a String variable
      String line1 = myFile.readStringUntil('\n');
      String line2 = line1;

    // Break a string value into tokens
      char* a = (char*) line1.c_str();
      //char* c = a;
      char* b = NULL;
      b = strtok(a, ",");    

    // Place the tokens into a characters array
     while(b != NULL){
        
            strings[arrayPointer] = b;
            arrayPointer++;
            b = strtok(NULL, ",");
    }    

    /////////////////////////////////////////////////////////////////////////
    // Convert each character array value into string values to compare it //
    // with the introduced value (date) by the user //
    /////////////////////////////////////////////////////////////////////////

     for (n=0; n<arrayPointer; n++){

       String str(strings[n]);

         if (str.substring(0,number) == my_hour) {
             Serial.println(line2);
             counter += 1; 
         }else{
          }  
      }

     ///////////////////////////////////////////
     //// Clear (initialize) existing array ////
     ///////////////////////////////////////////
      memset(strings,0, sizeof(strings));
             arrayPointer = 0;
             n = 0;
 }
 
////////////////////////////////////////////////////////////////////////////
// Checking if there have been reading values. If not, print out a message
////////////////////////////////////////////////////////////////////////////

  if (n == arrayPointer && counter == 0) {
      Serial.println(F("No readings values found for that TIME. Please, introduce again the time."));    
   }else {}

}

  else {
    // if the file didn't open, print an error:
    Serial.println(F("error opening test.txt"));
  }

    // Close the file
    myFile.close();
    Serial.println("");
    Serial.println(F("finished"));
}




void loop() {

//Nothing to do

}




///////////////////////////////////////////////////////////////////////
// Fucntion that asks for and returns the time introduced by the user 
///////////////////////////////////////////////////////////////////////

String readingtime() {

// Introduce the HOUR:
Serial.println(F("Introduce the HOUR"));

while (Serial.available()==0);
hour_ = Serial.parseInt();  
Serial.println(hour_);


// Ckeck and validation of the HOUR:
while ((hour_>=24) || (hour_<0)) {

        Serial.println(F("Please, Introduce the HOUR again. This is not a valid HOUR"));
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        while (Serial.available()==0);
        hour_ = Serial.parseInt();  

}


/////////////////////////////////////////////////////////////////////////////////////////////////
// In case the HOUR_ variable is less than ten, the index "to" of the substring function updates
// because the default hour provided by the sensor has only one digit
/////////////////////////////////////////////////////////////////////////////////////////////////

 if (hour_ < 10) {
     number =  number - 1; 
 }

 else {}

        Serial.println("");
        Serial.print(F("You introduced the HOUR = "));
        Serial.print(hour_);
        Serial.println(F("h"));
        Serial.println("");
        delay(2000);

// Introduce the MINUTE/s:
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        Serial.println(F("Introduce the minute/s"));
        while (Serial.available()==0);
        minute_1 = Serial.parseInt();  
        Serial.println(minute_1);


// Ckeck and validation of the MINUTE/s:
while ((minute_1 > 59) || (minute_1 < 0)) {

        Serial.println(F("Please, Introduce the MINUTE/s again. This is not a valid MINUTE"));
        Serial.end();
        Serial.flush();
        Serial.begin(9600);
        while (Serial.available()==0);
        minute_1 = Serial.parseInt();  

}
       

/////////////////////////////////////////////////////////////////////////////////////////////////
// In case the value of the MINUTE_1 variable introduced by the user is less than ten, that is, 
// only one digit, the value of the MINUTE_ variable is updated to two digits (adding a zero (0))
/////////////////////////////////////////////////////////////////////////////////////////////////

 if (minute_1 < 10){
   minute_ =  ((String)"0"+minute_1);
   goto jump;
 }  

 else {
   minute_= (String) minute_1;
   goto jump;
 }


// The algorithm keeps on executing the code once the MINUTE_1 variable updated
jump:
        Serial.println("");
        Serial.print(F("You introduced the MINUTE = "));
        Serial.print(minute_);
        Serial.println(F("min"));
        Serial.println("");
        delay(2000);


        String myhour = ((String)hour_+":"+minute_+":");

        Serial.print(F("The TIME to search is: "));
        Serial.print((String)hour_+":"+minute_);
        Serial.println(F("h"));
        Serial.println("");

return myhour;

}
 


