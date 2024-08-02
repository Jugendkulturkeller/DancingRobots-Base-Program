/*
 * Dancing Robots 0.5
 * VILLA gGmbH - JugendKulturKeller
 * Dirk Tschentscher-Trinks
 * dirk.tschentscher@villa-leipzig.de
 * 
 * Roboter mit zwei iR-Sensoren
 */
#define ONBOARDLED 2 // LED auf dem Board
/*
 * Array der Motorsteuerung 
 * Pin 32 steuert linken Motor vorwärts
 * Pin 33 steuert linken Motor rückwärts
 * Pin 18 steuert rechten Motor vorwärts
 * Pin 19 steuert rechten Motor rückwärts
 */
int motoren[4] = {32,33,18,19};

/*
* IR-Sensoren
* Pin 34 - Trigger des linken Sensors
* Pin 35 - Trigger des rechten Sensors
*/

int irSensoren[2] ={34,35};


void setup()
{
    Serial.begin(115200); //Verbindung zum Seriellen Monitor der Arduino IDE für Statusnachrichten
    pinMode(ONBOARDLED,OUTPUT);
  
    Serial.println("Roboter 0.5");
    statusBlinke();
    Serial.println("Motoren initialisiert");
    initMotoren();
    statusBlinke();
    Serial.println("Motoren testen");
    linksMotoren(500);
    rechtsMotoren(500);
    statusBlinke();
    Serial.println("Initialisiere iR-Sensoren");
    initIrSensoren();
}

/*
 * LED-Sígnale
 */
void statusBlinke(){digitalWrite(ONBOARDLED,HIGH);delay(100);digitalWrite(ONBOARDLED,LOW);delay(100);digitalWrite(ONBOARDLED,HIGH);delay(100);digitalWrite(ONBOARDLED,LOW);}

/*
 * IR-Sensoren
 */
void initIrSensoren(){for(int i=0;i<2;i++){pinMode(irSensoren[i],INPUT);}}
bool irSensorLinks(){if(digitalRead(irSensoren[0])==LOW){Serial.println("Hindernis links"); return true;}else{return false;};}
bool irSensorRechts(){if(digitalRead(irSensoren[1])==LOW){Serial.println("Hindernis rechts"); return true;}else {return false;};}

/**
 * Definition der Prozeduren für die Motoren
 */
void initMotoren(){for(int i=0;i<4;i++){pinMode(motoren[i],OUTPUT);digitalWrite(motoren[i],HIGH);Serial.print("Starte: ");Serial.println(motoren[i]);delay(500);digitalWrite(motoren[i],LOW);}}
void stopMotoren() {for(int i=0;i<4;i++){digitalWrite(motoren[i],LOW);}}
void linksMotoren(int d){stopMotoren();digitalWrite(motoren[2],HIGH);if(d!=0){delay(d);stopMotoren();}}
void scharfLinksMotoren(int d){stopMotoren();digitalWrite(motoren[2],HIGH);digitalWrite(motoren[1],HIGH);if(d!=0){delay(d);stopMotoren();}}
void rechtsMotoren(int d){stopMotoren();digitalWrite(motoren[0],HIGH);if(d!=0){delay(d);stopMotoren();}}
void scharfRechtsMotoren(int d){stopMotoren();digitalWrite(motoren[0],HIGH);digitalWrite(motoren[3],HIGH);if(d!=0){delay(d);stopMotoren();}}
void vorwaertsMotoren(int d){stopMotoren();digitalWrite(motoren[0],HIGH);digitalWrite(motoren[2],HIGH);if(d!=0){delay(d);stopMotoren();}}
void rueckwaertsMotoren(int d){stopMotoren();digitalWrite(motoren[1],HIGH);digitalWrite(motoren[3],HIGH);if(d!=0){delay(d);stopMotoren();}}
void schuettelnMotoren(){stopMotoren();scharfLinksMotoren(100);scharfRechtsMotoren(100);}



void loop()
{
  //Auf Hindernisse prüfen
  if(irSensorLinks()){stopMotoren();delay(200);schuettelnMotoren();schuettelnMotoren(); delay(200); rueckwaertsMotoren(500);scharfRechtsMotoren(500);}
  else if(irSensorRechts()){stopMotoren();delay(200); schuettelnMotoren();schuettelnMotoren(); delay(200); delay(200); rueckwaertsMotoren(500);scharfLinksMotoren(500);delay(200);}
  //Bewegungen
  vorwaertsMotoren(200);
}
