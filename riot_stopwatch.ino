// Arduino 4 Players Chess StopWatch
// Author: Ilario Gelmetti
// Originally used for Riot Board Game - www.riotboardgame.com
// Players' name: aut, ana, naz, pol
// Donwloadable from: https://github.com/ilario/Arduino-4PlayersChessStopWatch

#include <StopWatch.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

StopWatch sw_aut(StopWatch::SECONDS);
StopWatch sw_ana(StopWatch::SECONDS);
StopWatch sw_naz(StopWatch::SECONDS);
StopWatch sw_pol(StopWatch::SECONDS);

char t_aut_s_zero[3];
char t_ana_s_zero[3];
char t_naz_s_zero[3];
char t_pol_s_zero[3];
unsigned int t_aut_m;
unsigned int t_aut_s;
unsigned int t_ana_m;
unsigned int t_ana_s;
unsigned int t_naz_m;
unsigned int t_naz_s;
unsigned int t_pol_m;
unsigned int t_pol_s;
const int autPin = A5;
const int anaPin = A4;
const int nazPin = A3;
const int polPin = A2;
const int stopPin = 7;
unsigned int stopState = 0;
unsigned int previousStopState = 0;
unsigned int autValue = 0;
unsigned int autState = 0;
unsigned int previousAutState = 0;
unsigned int anaValue = 0;
unsigned int anaState = 0;
unsigned int previousAnaState = 0;
unsigned int nazValue = 0;
unsigned int nazState = 0;
unsigned int previousNazState = 0;
unsigned int polValue = 0;
unsigned int polState = 0;
unsigned int previousPolState = 0;
long swTotElapsed = 0;
long previousSwTotElapsed = 0;
const int buzzerSwitchPin = 2;
unsigned int buzzerSwitchState = 0;
unsigned int previousBuzzerSwitchState = 0;
const int buzzerNoisePin = 4;
unsigned int buzzerOnOff = 1;
unsigned int t_m[4] = {0, 0, 0, 0};
unsigned int previousT_m[4] = {0, 0, 0, 0};
unsigned int currentPlayer = 0;
unsigned int buzzerStartMinute = 14;
unsigned int note = 0;
const int redPin = 6;
const int bluePin = 5;
const int greenPin = 3;
unsigned int maxLight = 100;

void setup() {
    lcd.begin(16,2);
    Serial.begin(9600);
    pinMode(stopPin,INPUT);
    pinMode(buzzerSwitchPin,INPUT);
    pinMode(buzzerNoisePin,OUTPUT);
    pinMode(redPin,OUTPUT);
    pinMode(bluePin,OUTPUT);
    pinMode(greenPin,OUTPUT);
    lcd.clear();
    lcd.print(" RiotBoardGame");
    lcd.setCursor(0, 1);
    lcd.print("   Testing Team");
    delay(200);
    for(unsigned int a = 0; a < 254; a++){
      analogWrite(redPin, a);
      delay(8);
    }
    for(unsigned int b = 254; b > 0; b--){
      analogWrite(redPin, b);
      delay(8);
    }
    for(unsigned int c = 0; c < 254; c++){
      analogWrite(greenPin, c);
      delay(8);
    }
    for(unsigned int d = 254; d > 0; d--){
      analogWrite(greenPin, d);
      delay(8);
    }    
    for(unsigned int e = 0; e < 254; e++){
      analogWrite(bluePin, e);
      delay(8);
    }
    for(unsigned int f = 254; f > 0; f--){
      analogWrite(bluePin, f);
      delay(8);
    }
    analogWrite(redPin, 0);
    analogWrite(bluePin, 0);
    analogWrite(greenPin, 0);
    delay(500);
    lcd.clear();
    lcd.print("Bottoni:");    
    lcd.setCursor(0, 1);
    lcd.print("aut ana naz sbi");    
}


void loop() {
    stopState = digitalRead(stopPin);
    if(stopState != previousStopState){
      sw_aut.stop();
      sw_ana.stop();
      sw_naz.stop();
      sw_pol.stop();
      analogWrite(redPin, 0);
      analogWrite(bluePin, 0);
      analogWrite(greenPin, 0);
    }
    if(analogRead(autPin) < 500){
      autState = 0;
    }else{
      autState = 1;
    }
    if(analogRead(anaPin) < 500){
      anaState = 0;
    }else{
      anaState = 1;
    } 
    if(analogRead(nazPin) < 500){
      nazState = 0;
    }else{
      nazState = 1;
    }
    if(analogRead(polPin) < 500){
      polState = 0;
    }else{
      polState = 1;
    }
    if(autState != previousAutState){
      sw_aut.start();
      sw_ana.stop();
      sw_naz.stop();
      sw_pol.stop();
      currentPlayer = 0;
      analogWrite(redPin, maxLight);
      analogWrite(bluePin, 0);
      analogWrite(greenPin, 0);
      Serial.print("Tempo partita: ");
      Serial.println(swTotElapsed);
      Serial.print("Tempo Ana: ");
      Serial.print(sw_ana.elapsed());
      Serial.print(" Tempo Naz: ");
      Serial.print(sw_naz.elapsed());
      Serial.print(" Tempo Pol: ");
      Serial.println(sw_pol.elapsed());
      Serial.print("Inizia a giocare Aut, tempo giocatore: ");
      Serial.println(sw_aut.elapsed());
    }    
    if(anaState != previousAnaState){
      sw_ana.start();
      sw_aut.stop();
      sw_naz.stop();
      sw_pol.stop();
      currentPlayer = 1;
      analogWrite(redPin, 0);
      analogWrite(bluePin, 0);
      analogWrite(greenPin, maxLight*.5);
      Serial.print("Tempo partita: ");
      Serial.println(swTotElapsed);
      Serial.print("Tempo Aut: ");
      Serial.print(sw_aut.elapsed());
      Serial.print(" Tempo Naz: ");
      Serial.print(sw_naz.elapsed());
      Serial.print(" Tempo Pol: ");
      Serial.println(sw_pol.elapsed());
      Serial.print("Inizia a giocare Ana, tempo giocatore: ");
      Serial.println(sw_ana.elapsed());      
    }    
    if(nazState != previousNazState){
      sw_naz.start();
      sw_aut.stop();
      sw_ana.stop();
      sw_pol.stop();
      currentPlayer = 2;
      analogWrite(redPin, maxLight*.8);
      analogWrite(bluePin, maxLight*.1);
      analogWrite(greenPin, maxLight*.1); 
      Serial.print("Tempo partita: ");
      Serial.println(swTotElapsed);
      Serial.print("Tempo Aut: ");
      Serial.print(sw_aut.elapsed());
      Serial.print(" Tempo Ana: ");
      Serial.print(sw_ana.elapsed());
      Serial.print(" Tempo Pol: ");
      Serial.println(sw_pol.elapsed());
      Serial.print("Inizia a giocare Naz, tempo giocatore: ");
      Serial.println(sw_naz.elapsed());     
    }  
    if(polState != previousPolState){
      sw_pol.start();
      sw_aut.stop();
      sw_ana.stop();
      sw_naz.stop();
      currentPlayer = 3;
      analogWrite(redPin, 0);
      analogWrite(bluePin, maxLight*.5);
      analogWrite(greenPin, 0);
      Serial.print("Tempo partita: ");
      Serial.println(swTotElapsed);
      Serial.print("Tempo Aut: ");
      Serial.print(sw_aut.elapsed());
      Serial.print(" Tempo Ana: ");
      Serial.print(sw_ana.elapsed());
      Serial.print(" Tempo Naz: ");
      Serial.println(sw_naz.elapsed());
      Serial.print("Inizia a giocare Pol, tempo giocatore: ");
      Serial.println(sw_pol.elapsed());
    }
    buzzerSwitchState = digitalRead(buzzerSwitchPin);
    if(buzzerSwitchState != previousBuzzerSwitchState){
      buzzerOnOff = 0;
    }
    swTotElapsed = sw_aut.elapsed() + sw_ana.elapsed() + sw_naz.elapsed() + sw_pol.elapsed();

    if(swTotElapsed != previousSwTotElapsed){
      previousSwTotElapsed = swTotElapsed;
      
      lcd.clear();
      lcd.print("aut");
      t_aut_m = sw_aut.elapsed()/60;
      t_aut_s = sw_aut.elapsed()%60;
      lcd.print(t_aut_m);
      lcd.print(":");
      sprintf(t_aut_s_zero, "%02u", t_aut_s);
      lcd.print(t_aut_s_zero);
      
      lcd.setCursor(8, 0);
      
      lcd.print("ana");
      t_ana_m = sw_ana.elapsed()/60;
      t_ana_s = sw_ana.elapsed()%60;
      lcd.print(t_ana_m);
      lcd.print(":");
      sprintf(t_ana_s_zero, "%02u", t_ana_s);
      lcd.print(t_ana_s_zero);    
      
      lcd.setCursor(0, 1);
      lcd.print("naz");
      t_naz_m = sw_naz.elapsed()/60;
      t_naz_s = sw_naz.elapsed()%60;
      lcd.print(t_naz_m);
      lcd.print(":");
      sprintf(t_naz_s_zero, "%02u", t_naz_s);
      lcd.print(t_naz_s_zero);
      
      lcd.setCursor(8, 1);
      
      lcd.print("sbi");
      t_pol_m = sw_pol.elapsed()/60;
      t_pol_s = sw_pol.elapsed()%60;
      lcd.print(t_pol_m);
      lcd.print(":");
      sprintf(t_pol_s_zero, "%02u", t_pol_s);
      lcd.print(t_pol_s_zero);
      
      if(buzzerOnOff == 1){
        t_m[0] = t_aut_m;
        t_m[1] = t_ana_m;
        t_m[2] = t_naz_m;
        t_m[3] = t_pol_m;
        if(t_m[currentPlayer] != previousT_m[currentPlayer]){
          if(t_m[currentPlayer] > buzzerStartMinute){
            note = (200 + (t_m[currentPlayer] - buzzerStartMinute) * 300);
            tone(buzzerNoisePin, note);
            delay(100 + (t_m[currentPlayer] - buzzerStartMinute) * 300);
            noTone(buzzerNoisePin);
          }
        }
        previousT_m[0] = t_m[0];
        previousT_m[1] = t_m[1];
        previousT_m[2] = t_m[2];
        previousT_m[3] = t_m[3];
      }  
    }
    
    previousBuzzerSwitchState = buzzerSwitchState;
    previousStopState = stopState;
    previousAutState = autState;
    previousAnaState = anaState;
    previousNazState = nazState;
    previousPolState = polState;
}
