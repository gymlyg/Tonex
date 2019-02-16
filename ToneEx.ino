/*
  ToneEx
  
  Multi-parameter tone generator

  Generate tones based on some random parameters.
  Current version has feature-bug - parameters are not set by potentiometer but the noise from A3 pin!

  modified 14 Feb 2019
  by gymlyg
*/

const int BUZZER = 9;
const int V1 = 8; // 1 or 0 input "V1-parameter" pin
const int V2 = 7; // 1 or 0 input "V2-parameter" pin

const int R1 = A3; // voltage regulator must be connect to A3

/* group of input values */
int r = 0;
int v1_mode = 0;
int v2_mode = 0;

int t_delta = 100; // tone step value
int t_dir = 1; // can be 1 or -1 to up or down tone's

int t_st = 10; //start tone freq
int t_fin = 200; //final tone freq

int t_cur = 0; // current tone frreq
int t_delay = 0; // tone impulse period 

int t_mel_level = 0; //unknown param
int t_r_level = 0;	//tone random value

void setup() {

  pinMode(BUZZER, OUTPUT);
  pinMode(V1, INPUT);
  pinMode(V2, INPUT);
  t_cur = t_st;
}

void loop() {

  v1_mode = digitalRead(V1);
  v2_mode = digitalRead(V2);
  r = analogRead(R1);

  if(v1_mode == 1) {

    if(v2_mode == 1) {
        t_delta = r;
    } else {
        t_delay = r;
    }  
  } else {
    
    if(v2_mode == 1) {
       t_mel_level = r;
    } else {
       t_r_level = r;
    }
  }
  
  t_cur += t_dir*t_delta;

  if(v2_mode == 1) {
    if(t_cur > t_fin || t_cur < t_st) {
      t_dir *= -1;  
    }
  } else {
    t_cur = random(t_fin, t_r_level);  
  }
  
  tone(BUZZER, t_cur);
  delay(t_delay/5);
  noTone(BUZZER);
  delay(t_delay/5);

}
