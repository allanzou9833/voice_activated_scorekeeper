#include <uspeech.h>
#define team_1 4
#define team_2 13
signal voice(A0);
char prev;
boolean newline=false;
int sum = 0;
int team = 0;
bool teamSaid = false;
bool process = false;
syllable s;
void setup(){
  voice.f_enabled = true;
  //Calibrate these values.
  voice.minVolume = 1200;
  voice.fconstant = 235;
  voice.econstant = 2;
  voice.aconstant = 4;
  voice.vconstant = 3;
  voice.shconstant = 6;
  voice.calibrate();
  Serial.begin(9600);
  pinMode(team_1, OUTPUT); 
  pinMode(team_2, OUTPUT);
  digitalWrite(team_1, HIGH);
  digitalWrite(team_2, HIGH);
}
void loop(){
    char p = voice.getPhoneme();
    Serial.println(p);
//    if(p!=' '){
//      if(p=='e' && !teamSaid){
//          team = 0;
//          teamSaid = true;
//      }
//      if(p=='o' && !teamSaid){
//        team = 1;
//        teamSaid = true;
//      }
//      if(p=='s' && teamSaid){
//        if(team==0) digitalWrite(team_1, HIGH);
//        if(team==1) digitalWrite(team_2, HIGH);
//
//        digitalWrite(team_1, LOW);
//        digitalWrite(team_2, LOW);
//        teamSaid = false;
//        delay(3000);
//      }
//    }

   if(p == ' '){
      if(process){
        int sum = s.e + s.o + s.s;
        if(sum > 30){
          if(s.e > 4 && !teamSaid){
            Serial.println("team1");
            team = 0;
            teamSaid = true;
          }
//          else if(s.o > 4 && !teamSaid) {
//            Serial.println("team2");
//            team = 1;
//            teamSaid = true;
//          }
          else if(s.s > 4) {
            Serial.println("inc");
            Serial.println(team);
            if(team==0) {
              digitalWrite(team_1, LOW);
              digitalWrite(team_1, HIGH);
            }
             else if(team==1) {
              digitalWrite(team_2, LOW);
              digitalWrite(team_2, HIGH);
            }
            delay(3000);
          }
          else {
            if(!teamSaid){
              Serial.println("team2");
              team = 1;
              teamSaid = true;
            }
          }
        }
        s.f = 0;
        s.e = 0;
        s.o = 0;
        s.v = 0;
        s.s = 0;
        s.h = 0;
        process = false;
      }
   }
   else {
    s.classify(p);
    process = true;
   }
}
