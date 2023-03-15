#include <WiFi.h> // Wifi
#include <WiFiUdp.h>
#include <NTPClient.h> // Time with NTP (Network Time Protocol)
#include <Wire.h>
#include "SSD1306Wire.h"

//wifi varible
WiFiServer server(80);
WiFiUDP ntpUDP;
NTPClient timec(ntpUDP, "fr.pool.ntp.org", 3600);
const char* def_ssid="Test";
const char* def_pass="factorio";


//  internal stuff
int act;
String currentLine;
String local;
unsigned long preMili = 0;
const int maxtemp = 3900; //en ms, 2000 = 2s
int preMili2 = 0;
const int broke = 5000;
int aff; // act pour l'affichage instern
String header = "";
int pg;
int temp;
int X_aff=0;
int Y_aff=0;

//screen variable
SSD1306Wire screen(0x3c, 5, 4);

void bar(int bar) {
  screen.clear();
  bar%=101;
  int nw=(bar-pg)/10;
  while (pg <= bar) {
  screen.clear();
  screen.drawProgressBar(20, 20, 100, 20, pg);
  screen.display();
  pg+=nw;
  delay(50);
  }
  delay(500);
  screen.display();
}

void setup() {
  //init
  Serial.begin(115200);
  Serial.println("Init:");
  //screen init
  
  screen.init();
  screen.displayOn();
  screen.clear();
  screen.setFont(ArialMT_Plain_10);
  bar(20);
  //end init

  
  // wifi init 
  WiFi.begin(def_ssid, def_pass);
  screen.drawString(50, 0, "Wifi Init");
  screen.display();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  local=WiFi.localIP().toString();
  server.begin();
  bar(100);
    timec.begin();
  //end wifi 


  //pin i/o
  pinMode(36, INPUT); // https://www.mischianti.org/wp-content/uploads/2020/11/ESP32-WeMos-LOLIN32-pinout-mischianti.png
  pinMode(39, INPUT); //temp
  
  

}

void loop() {
  
  //loop init
  unsigned long mili = millis();
  screen.display();
  WiFiClient cli = server.available();
  //----------------------------------//



  
  if (cli){
    Serial.print("Client: ");
    Serial.println(cli.localIP());
    while (cli.connected()){
      char c = cli.read();             
      Serial.write(c);                    
      header += c;
      if (c == '\n') {                    
        if (currentLine.length() == 0) {
          if (header.indexOf("GET / HTTP/1.1")){
            //digitalWrite(35, LOW);
            //digitalWrite(36, LOW);
            act = 0;
          }
          if (header.indexOf("GET /Controle-manuel.html HTTP/1.1")>=0){
            //digitalWrite(35, LOW);
            //digitalWrite(36, LOW);
            act = 1;
          }
          if (header.indexOf("GET /ouvrir.html HTTP/1.1")>=0){
            //digitalWrite(35, HIGH);
            //digitalWrite(36, LOW);
            act = 2;
          }
          if (header.indexOf("GET /fermer.html HTTP/1.1")>=0){
            //digitalWrite(35, LOW);
            //digitalWrite(36, HIGH);
            act = 3;
          }


          cli.println("HTTP/1.1 200 OK");
          cli.println("Content-type: text/html");
          cli.println();


          Serial.print("act:");
          Serial.println(act);


          switch (act) {
            case 1: //controle-manuel
              cli.println("<!DOCTYPE html><html style=\"font-size: 16px;\" lang=\"fr\"><head><link rel=\"icon\" href=\"http://images01.nicepagecdn.com/f59aa51e12f00d19951fa32b/c0932810b4e652cf92e19c39/maisonconnecte_orange.png\" type=\"image/x-icon\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><meta charset=\"utf-8\"><meta name=\"keywords\" content=\"Controle manuel\"><meta name=\"description\" content=\"\"><title>Controle manuel</title><link rel=\"stylesheet\" href=\"http://capp.nicepage.com/9afaf170b86701c5f7507f813250e585a6b39559/nicepage.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/nicepage-site.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/Controle-manuel.css\" media=\"screen\"><script class=\"u-script\" type=\"text/javascript\" src=\"http://capp.nicepage.com/assets/jquery-3.5.1.min.js\" defer=\"\"></script><script class=\"u-script\" type=\"text/javascript\" src=\"http://capp.nicepage.com/9afaf170b86701c5f7507f813250e585a6b39559/nicepage.js\" defer=\"\"></script><meta name=\"generator\" content=\"Nicepage 5.5.0, nicepage.com\"><link id=\"u-theme-google-font\" rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css?family=Roboto:100,100i,300,300i,400,400i,500,500i,700,700i,900,900i|Open+Sans:300,300i,400,400i,500,500i,600,600i,700,700i,800,800i\"><script type=\"application/ld+json\">{\"@context\": \"http://schema.org\",\"@type\": \"Organization\",\"name\": \"\"}</script><meta name=\"theme-color\" content=\"#478ac9\"><meta property=\"og:title\" content=\"Controle manuel\"><meta property=\"og:type\" content=\"website\"></head><body class=\"u-body u-xl-mode\" data-lang=\"fr\"><section class=\"u-clearfix u-section-1\" id=\"sec-31df\"><div class=\"u-clearfix u-sheet u-sheet-1\"><h2 class=\"u-align-center-xs u-text u-text-1\">Controle manuel<br></h2><img class=\"u-image u-image-contain u-image-default u-preserve-proportions u-image-1\" src=\"http://images01.nicepagecdn.com/f59aa51e12f00d19951fa32b/c0932810b4e652cf92e19c39/maisonconnecte_orange.png\" alt=\"\" data-image-width=\"3334\" data-image-height=\"3334\" data-href=\"/Accueil.html\" title=\"Accueil\"><div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-1\" data-href=\"/ouvrir.html\" title=\"ouvrir\"></div><div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-2\"></div><div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-3\"></div>        <div class=\"u-rotation-parent u-rotation-parent-1\"><div class=\"u-rotate-270 u-shape u-shape-svg u-text-palette-1-light-2 u-shape-4\" data-href=\"/ouvrir.html\" title=\"ouvrir\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 140\" style=\"\"><use xlink:href=\"#svg-0768\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 140\" x=\"0px\" y=\"0px\" id=\"svg-0768\" style=\"enable-background:new 0 0 160 140;\"><path d=\"M90,45H0v50h90v45l70-70L90,0V45z\"></path></svg></div></div><div class=\"u-rotation-parent u-rotation-parent-2\"><div class=\"u-rotate-90 u-shape u-shape-svg u-text-palette-1-light-2 u-shape-5\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 140\" style=\"\"><use xlink:href=\"#svg-871d\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 140\" x=\"0px\" y=\"0px\" id=\"svg-871d\" style=\"enable-background:new 0 0 160 140;\"><path d=\"M90,45H0v50h90v45l70-70L90,0V45z\"></path></svg></div></div><div class=\"u-shape u-shape-svg u-text-palette-1-light-2 u-shape-6\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 160\" style=\"\"><use xlink:href=\"#svg-9769\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 160\" x=\"0px\" y=\"0px\" id=\"svg-9769\" style=\"enable-background:new 0 0 160 160;\"><path d=\"M105.7,80L160,0h-51.4L80,42.2L51.4,0H0l54.3,80L0,160h51.4L80,117.8l28.6,42.2H160L105.7,80z\"></path></svg></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-7\" data-href=\"/Controle-manuel.html\" title=\"Controle manuel\"></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-8\" data-href=\"/fermer.html\" title=\"fermer\"></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-9\" data-href=\"/ouvrir.html\"></div><h2 class=\"u-align-center-xs u-text u-text-2\">Ouvrir</h2><h2 class=\"u-align-center u-text u-text-3\">Stop</h2><h2 class=\"u-align-center-xs u-text u-text-4\">Fermer</h2></div></section></body></html>");
              break;
            case 2: //ouvrir
              cli.println("<!DOCTYPE html><html style=\"font-size: 16px;\" lang=\"fr\"><head><link rel=\"icon\" href=\"http://images01.nicepagecdn.com/f59aa51e12f00d19951fa32b/c0932810b4e652cf92e19c39/maisonconnecte_orange.png\" type=\"image/x-icon\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><meta charset=\"utf-8\"><meta name=\"keywords\" content=\"Controle manuel\"><meta name=\"description\" content=\"\"><title>ouvrir</title><link rel=\"stylesheet\" href=\"http://capp.nicepage.com/9afaf170b86701c5f7507f813250e585a6b39559/nicepage.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/nicepage-site.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/ouvrir.css\" media=\"screen\"><script class=\"u-script\" type=\"text/javascript\" src=\"http://capp.nicepage.com/assets/jquery-3.5.1.min.js\" defer=\"\"></script><script class=\"u-script\" type=\"text/javascript\" src=\"http://capp.nicepage.com/9afaf170b86701c5f7507f813250e585a6b39559/nicepage.js\" defer=\"\"></script><meta name=\"generator\" content=\"Nicepage 5.5.0, nicepage.com\"><link id=\"u-theme-google-font\" rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css?family=Roboto:100,100i,300,300i,400,400i,500,500i,700,700i,900,900i|Open+Sans:300,300i,400,400i,500,500i,600,600i,700,700i,800,800i\"><script type=\"application/ld+json\">{\"@context\": \"http://schema.org\",\"@type\": \"Organization\",\"name\": \"\"}</script><meta name=\"theme-color\" content=\"#478ac9\"><meta property=\"og:title\" content=\"ouvrir\"><meta property=\"og:type\" content=\"website\"></head><body class=\"u-body u-xl-mode\" data-lang=\"fr\"><section class=\"u-clearfix u-section-1\" id=\"sec-31df\"><div class=\"u-clearfix u-sheet u-sheet-1\"><h2 class=\"u-align-center-xs u-text u-text-1\">Controle manuel<br></h2><img class=\"u-image u-image-contain u-image-default u-preserve-proportions u-image-1\" src=\"http://images01.nicepagecdn.com/f59aa51e12f00d19951fa32b/c0932810b4e652cf92e19c39/maisonconnecte_orange.png\" alt=\"\" data-image-width=\"3334\" data-image-height=\"3334\" data-href=\"/Accueil.html\" title=\"Accueil\"><div class=\"u-palette-1-light-2 u-preserve-proportions u-shape u-shape-circle u-shape-1\" data-href=\"/Controle-manuel.html\" title=\"Controle manuel\"></div><div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-2\"></div>        <div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-3\"></div><div class=\"u-rotation-parent u-rotation-parent-1\"><div class=\"u-rotate-270 u-shape u-shape-svg u-text-palette-1-base u-shape-4\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 140\" style=\"\"><use xlink:href=\"#svg-0768\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 140\" x=\"0px\" y=\"0px\" id=\"svg-0768\" style=\"enable-background:new 0 0 160 140;\"><path d=\"M90,45H0v50h90v45l70-70L90,0V45z\"></path></svg></div></div><div class=\"u-rotation-parent u-rotation-parent-2\"><div class=\"u-rotate-90 u-shape u-shape-svg u-text-palette-1-light-2 u-shape-5\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 140\" style=\"\"><use xlink:href=\"#svg-871d\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 140\" x=\"0px\" y=\"0px\" id=\"svg-871d\" style=\"enable-background:new 0 0 160 140;\"><path d=\"M90,45H0v50h90v45l70-70L90,0V45z\"></path></svg></div></div><div class=\"u-shape u-shape-svg u-text-palette-1-light-2 u-shape-6\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 160\" style=\"\"><use xlink:href=\"#svg-9769\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 160\" x=\"0px\" y=\"0px\" id=\"svg-9769\" style=\"enable-background:new 0 0 160 160;\"><path d=\"M105.7,80L160,0h-51.4L80,42.2L51.4,0H0l54.3,80L0,160h51.4L80,117.8l28.6,42.2H160L105.7,80z\"></path></svg></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-7\" data-href=\"/Controle-manuel.html\" title=\"Controle manuel\"></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-8\" data-href=\"/fermer.html\" title=\"fermer\"></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-9\" data-href=\"/Controle-manuel.html\" title=\"Controle manuel\"></div><h2 class=\"u-align-center-xs u-text u-text-2\">Ouvrir</h2><h2 class=\"u-align-center u-text u-text-3\">Stop</h2><h2 class=\"u-align-center-xs u-text u-text-4\">Fermer</h2></div></section></body></html>");
              break;
            case 3: //fermer
              cli.println("<!DOCTYPE html><html style=\"font-size: 16px;\" lang=\"fr\"><head><link rel=\"icon\" href=\"http://images01.nicepagecdn.com/f59aa51e12f00d19951fa32b/c0932810b4e652cf92e19c39/maisonconnecte_orange.png\" type=\"image/x-icon\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><meta charset=\"utf-8\"><meta name=\"keywords\" content=\"Controle manuel\"><meta name=\"description\" content=\"\">    <title>fermer</title><link rel=\"stylesheet\" href=\"http://capp.nicepage.com/9afaf170b86701c5f7507f813250e585a6b39559/nicepage.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/nicepage-site.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/fermer.css\" media=\"screen\"><script class=\"u-script\" type=\"text/javascript\" src=\"http://capp.nicepage.com/assets/jquery-3.5.1.min.js\" defer=\"\"></script><script class=\"u-script\" type=\"text/javascript\" src=\"http://capp.nicepage.com/9afaf170b86701c5f7507f813250e585a6b39559/nicepage.js\" defer=\"\"></script><meta name=\"generator\" content=\"Nicepage 5.5.0, nicepage.com\"><link id=\"u-theme-google-font\" rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css?family=Roboto:100,100i,300,300i,400,400i,500,500i,700,700i,900,900i|Open+Sans:300,300i,400,400i,500,500i,600,600i,700,700i,800,800i\"><script type=\"application/ld+json\">{\"@context\": \"http://schema.org\",\"@type\": \"Organization\",\"name\": \"\"}</script><meta name=\"theme-color\" content=\"#478ac9\"><meta property=\"og:title\" content=\"fermer\"><meta property=\"og:type\" content=\"website\"></head><body class=\"u-body u-xl-mode\" data-lang=\"fr\"><section class=\"u-clearfix u-section-1\" id=\"sec-31df\"><div class=\"u-clearfix u-sheet u-sheet-1\"><h2 class=\"u-align-center-xs u-text u-text-1\">Controle manuel<br></h2><img class=\"u-image u-image-contain u-image-default u-preserve-proportions u-image-1\" src=\"http://images01.nicepagecdn.com/f59aa51e12f00d19951fa32b/c0932810b4e652cf92e19c39/maisonconnecte_orange.png\" alt=\"\" data-image-width=\"3334\" data-image-height=\"3334\" data-href=\"/Accueil.html\" title=\"Accueil\"><div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-1\"></div>        <div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-2\"></div><div class=\"u-palette-1-light-2 u-preserve-proportions u-shape u-shape-circle u-shape-3\"></div><div class=\"u-rotation-parent u-rotation-parent-1\"><div class=\"u-rotate-270 u-shape u-shape-svg u-text-palette-1-light-2 u-shape-4\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 140\" style=\"\"><use xlink:href=\"#svg-0768\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 140\" x=\"0px\" y=\"0px\" id=\"svg-0768\" style=\"enable-background:new 0 0 160 140;\"><path d=\"M90,45H0v50h90v45l70-70L90,0V45z\"></path></svg></div></div><div class=\"u-rotation-parent u-rotation-parent-2\">          <div class=\"u-rotate-90 u-shape u-shape-svg u-text-palette-1-base u-shape-5\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 140\" style=\"\"><use xlink:href=\"#svg-871d\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 140\" x=\"0px\" y=\"0px\" id=\"svg-871d\" style=\"enable-background:new 0 0 160 140;\"><path d=\"M90,45H0v50h90v45l70-70L90,0V45z\"></path></svg></div></div><div class=\"u-shape u-shape-svg u-text-palette-1-light-2 u-shape-6\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 160\" style=\"\"><use xlink:href=\"#svg-9769\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 160\" x=\"0px\" y=\"0px\" id=\"svg-9769\" style=\"enable-background:new 0 0 160 160;\"><path d=\"M105.7,80L160,0h-51.4L80,42.2L51.4,0H0l54.3,80L0,160h51.4L80,117.8l28.6,42.2H160L105.7,80z\"></path></svg></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-7\" data-href=\"/ouvrir.html\" title=\"ouvrir\"></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-8\" data-href=\"/Controle-manuel.html\" title=\"Controle manuel\"></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-9\" data-href=\"/Controle-manuel.html\" title=\"Controle manuel\"></div><h2 class=\"u-align-center-xs u-text u-text-2\">Ouvrir</h2><h2 class=\"u-align-center u-text u-text-3\">Stop</h2><h2 class=\"u-align-center-xs u-text u-text-4\">Fermer</h2></div></section></body></html>");
              break;
            default:
              cli.println("<!DOCTYPE html><html style=\"font-size: 16px;\" lang=\"fr\"><head><link rel=\"icon\" href=\"http://images01.nicepagecdn.com/f59aa51e12f00d19951fa32b/c0932810b4e652cf92e19c39/maisonconnecte_orange.png\" type=\"image/x-icon\">s<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><meta charset=\"utf-8\"><meta name=\"keywords\" content=\"Volet connecté\"><meta name=\"description\" content=\"\"><title>Accueil</title><link rel=\"stylesheet\" href=\"http://capp.nicepage.com/9afaf170b86701c5f7507f813250e585a6b39559/nicepage.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/nicepage-site.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/Accueil.css\" media=\"screen\"><script class=\"u-script\" type=\"text/javascript\" src=\"http://capp.nicepage.com/assets/jquery-3.5.1.min.js\" defer=\"\"></script><script class=\"u-script\" type=\"text/javascript\" src=\"http://capp.nicepage.com/9afaf170b86701c5f7507f813250e585a6b39559/nicepage.js\" defer=\"\"></script><meta name=\"generator\" content=\"Nicepage 5.5.0, nicepage.com\"><link id=\"u-theme-google-font\" rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css?family=Roboto:100,100i,300,300i,400,400i,500,500i,700,700i,900,900i|Open+Sans:300,300i,400,400i,500,500i,600,600i,700,700i,800,800i\"><script type=\"application/ld+json\">{\"@context\": \"http://schema.org\",\"@type\": \"Organization\",\"name\": \"\",\"url\": \"/\"}</script><meta name=\"theme-color\" content=\"#478ac9\"><meta property=\"og:title\" content=\"Accueil\"><meta property=\"og:type\" content=\"website\"><link rel=\"canonical\" href=\"/\"></head><body class=\"u-body u-xl-mode\" data-lang=\"fr\"><section class=\"u-clearfix u-section-1\" id=\"sec-1046\"><div class=\"u-clearfix u-sheet u-sheet-1\"><img class=\"u-image u-image-contain u-image-default u-preserve-proportions u-image-1\" src=\"http://images01.nicepagecdn.com/f59aa51e12f00d19951fa32b/c0932810b4e652cf92e19c39/maisonconnecte_orange.png\" alt=\"\" data-image-width=\"3334\" data-image-height=\"3334\"><h2 class=\"u-text u-text-default u-text-1\">Volet connecté<br></h2><a href=\"https://www.youtube.com/watch?v=dQw4w9WgXcQ\" class=\"u-btn u-button-style u-btn-1\">Mode automatique</a><a href=\"/Controle-manuel.html\" class=\"u-btn u-button-style u-btn-2\">Mode manuel</a><a href=\"https://www.youtube.com/watch?v=dQw4w9WgXcQ\" class=\"u-btn u-button-style u-btn-3\">État des volets</a></div></section></body></html>");
              break; 
          }
          
          cli.stop();
        } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
      }else if (c != '\r') { 
            currentLine += c;    
          }
    }
  }

  header = "";
    
  if (mili - preMili >= maxtemp) {
    preMili = mili;
    screen.clear();
    switch (aff) {
      case 1:
        timec.update();
        screen.drawString(X_aff,Y_aff,timec.getFormattedTime());
        break;
      case 2:
      {
        int Btemp = analogRead(39);
        float Vtemp = (float)(Btemp/1024.0*5.0-0.5)*100; // Badis
        screen.drawString(X_aff,Y_aff,String(Vtemp) + " °C");
        break;
      }
      default:
        screen.drawString(X_aff,Y_aff,local);
        Serial.println(local);
        break;    
    }
    
    aff++;
    aff %= 4;
  }
  delay(100);
}
