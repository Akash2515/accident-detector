#include <SerialGSM.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

SerialGSM cell(2,3);

float lat, lng; 
int vib=8;

TinyGPS gps;


String myPhoneNumber = "+919786493150";

void setup(){
  
  Serial.begin(9600);
  cell.begin(9600);
  cell.Verbose(true);
  cell.Boot();
  cell.DeleteAllSMS();
  cell.FwdSMS2Serial();
  pinMode(vib,INPUT);
}


void loop() {
	while(Serial.available()>0) {
		if(gps.encode(Serial.read())) {
		  gps.f_get_position(&lat,&lng);  
		  int val;
		  val=analogRead(vib);
		  delay(2000);
		  Serial.println(val);
		  
		  if (val>=300)
		  {
		     Serial.println("Latitude:");

		      
		      Serial.println(lat);
		      
		      Serial.println("Longitude:");
		       
		      Serial.println(lng);

		    sendLocation();
		    
		  }
		  cell.DeleteAllSMS();
	  
  
    }
  }
  

  
 
}

void sendLocation() {
      String tempStr = "Latitude: " + String(lat) + "\n" + "Longitude: " + String(lng);
      const char *mes = tempStr.c_str();
      const char *phoneTemp = myPhoneNumber.c_str();
      cell.Rcpt(phoneTemp);
      cell.Message(mes);
      cell.SendSMS();  
}
