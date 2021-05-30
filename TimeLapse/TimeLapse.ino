#include <WiFi.h>
#include "file.h"
#include "camera.h"
#include "lapse.h"

const char* ssid = "CabaneOiseaux";
const char* password = "Bonjour01.+";
IPAddress adresseIPInterne(192, 168, 23, 1);
IPAddress passerelle(192, 168, 23, 1);
IPAddress masqueReseau(255, 255, 255, 0);

void startCameraServer();

void setup()
{
	Serial.begin(115200);
	Serial.setDebugOutput(true);
	Serial.println();
	initFileSystem();
	initCamera();

        WiFi.softAPConfig(adresseIPInterne, passerelle, masqueReseau);
	WiFi.softAP(ssid, password);
	Serial.print("Adresse IP du point d'accès : ");
	Serial.println(WiFi.softAPIP());
  
	Serial.println("");
	Serial.println("WiFi connected");
	startCameraServer();
	Serial.print("Camera Ready! Use 'http://");
	Serial.print(WiFi.softAPIP());
	Serial.println("' to connect");
}

void loop()
{
	unsigned long t = millis();
	static unsigned long ot = 0;
	unsigned long dt = t - ot;
	ot = t;
	processLapse(dt);
}
