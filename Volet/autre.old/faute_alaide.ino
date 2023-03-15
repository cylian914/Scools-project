#include <WiFi.h> // Wifi
#include <WiFiUdp.h>
#include <NTPClient.h> // Time with NTP (Network Time Protocol)
#include <Wire.h>
#include "SSD1306Wire.h"

SSD1306Wire screen(0x3c, 5, 4);

const char* def_ssid="Test";
const char* def_pass="factorio";
WiFiServer server(80);
String ip;
WiFiUDP ntpUDP;
int act;
NTPClient timec(ntpUDP, "fr.pool.ntp.org");
String currentLine;
String local;

void setup() {
  Serial.begin(115200);
  timec.begin();
  screen.init();
  screen.displayOn();
  WiFi.begin(def_ssid, def_pass);
  screen.clear();
  screen.setFont(ArialMT_Plain_10);
  delay(5000);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  local=WiFi.localIP().toString();
  Serial.print(local);
  screen.drawString(0,26,local);
  pinMode(35, OUTPUT); //-
  pinMode(36, OUTPUT); //+
  pinMode(38, OUTPUT); //pwd
  Serial.println(timec.getFormattedTime());
}

void loop() {
   WiFiClient cli = server.available();
   Serial.print("cli");
   if (cli){
    Serial.print("Cli: ");
    Serial.print(cli);
    if (currentLine.endsWith("GET /")){
      digitalWrite(35, LOW);
      digitalWrite(36, LOW);
      act = 0;
    }
    if (currentLine.endsWith("GET /Controle-manuel")){
       digitalWrite(35, LOW);
       digitalWrite(36, LOW);
       act = 1;
    }
    if (currentLine.endsWith("GET /ouvrir")){
       digitalWrite(35, HIGH);
       digitalWrite(36, LOW);
       act = 2;
    }
    if (currentLine.endsWith("GET /fermer")){
       digitalWrite(35, LOW);
       digitalWrite(36, HIGH);
       act = 3;
    }
    cli.println("HTML/1.1 200 OK");
    cli.print("Content-Type: text/html");
    
    if (act == 1){
      cli.println("<!DOCTYPE html><html style=\"font-size: 16px;\" lang=\"fr\"><head><title>Controle manuel</title><link rel=\"stylesheet\" href=\"https://capp.nicepage.com/0bcad38c69dcfd90c4459a4d49a057db8404895c/nicepage.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/nicepage-site.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/Controle-manuel.css\" media=\"screen\"></head><body class=\"u-body u-xl-mode\" data-lang=\"fr\"><section class=\"u-clearfix u-section-1\" id=\"sec-31df\"><div class=\"u-clearfix u-sheet u-sheet-1\"><h2 class=\"u-align-center-xs u-text u-text-1\">Controle manuel<br></h2><img class=\"u-image u-image-contain u-image-default u-preserve-proportions u-image-1\" src=\"https:///images01.nicepagecdn.com/f59aa51e12f00d19951fa32b/c0932810b4e652cf92e19c39/maisonconnecte_orange.png\" alt=\"\" data-image-width=\"3334\" data-image-height=\"3334\" data-href=\"/Accueil.html\" title=\"Accueil\"><div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-1\" data-href=\"/ouvrir.html\" title=\"ouvrir\"></div><div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-2\"></div><div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-3\"></div><div class=\"u-rotation-parent u-rotation-parent-1\"><div class=\"u-rotate-270 u-shape u-shape-svg u-text-palette-1-light-2 u-shape-4\" data-href=\"/ouvrir.html\" title=\"ouvrir\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 140\" style=\"\"><use xlink:href=\"#svg-0768\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 140\" x=\"0px\" y=\"0px\" id=\"svg-0768\" style=\"enable-background:new 0 0 160 140;\"><path d=\"M90,45H0v50h90v45l70-70L90,0V45z\"></path></svg></div></div><div class=\"u-rotation-parent u-rotation-parent-2\"><div class=\"u-rotate-90 u-shape u-shape-svg u-text-palette-1-light-2 u-shape-5\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 140\" style=\"\"><use xlink:href=\"#svg-871d\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 140\" x=\"0px\" y=\"0px\" id=\"svg-871d\" style=\"enable-background:new 0 0 160 140;\"><path d=\"M90,45H0v50h90v45l70-70L90,0V45z\"></path></svg></div></div><div class=\"u-shape u-shape-svg u-text-palette-1-light-2 u-shape-6\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 160\" style=\"\"><use xlink:href=\"#svg-9769\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 160\" x=\"0px\" y=\"0px\" id=\"svg-9769\" style=\"enable-background:new 0 0 160 160;\"><path d=\"M105.7,80L160,0h-51.4L80,42.2L51.4,0H0l54.3,80L0,160h51.4L80,117.8l28.6,42.2H160L105.7,80z\"></path></svg>z</div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-7\" data-href=\"/Controle-manuel.html\" title=\"Controle manuel\"></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-8\" data-href=\"/fermer.html\" title=\"fermer\"></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-9\" data-href=\"/ouvrir.html\"></div><h2 class=\"u-align-center-xs u-text u-text-2\">Ouvrir</h2><h2 class=\"u-align-center u-text u-text-3\">Stop</h2><h2 class=\"u-align-center-xs u-text u-text-4\">Fermer</h2></div></section></body></html>");
      Serial.print("atc 1");
    } 
    if (act == 2) {
      cli.println("<!DOCTYPE html><html style=\"font-size: 16px;\" lang=\"fr\"><head><title>Controle manuel</title><link rel=\"stylesheet\" href=\"https://capp.nicepage.com/0bcad38c69dcfd90c4459a4d49a057db8404895c/nicepage.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/nicepage-site.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/Controle-manuel.css\" media=\"screen\"></head><body class=\"u-body u-xl-mode\" data-lang=\"fr\"><section class=\"u-clearfix u-section-1\" id=\"sec-31df\"><div class=\"u-clearfix u-sheet u-sheet-1\"><h2 class=\"u-align-center-xs u-text u-text-1\">Controle manuel<br></h2><img class=\"u-image u-image-contain u-image-default u-preserve-proportions u-image-1\" src=\"https://images01.nicepagecdn.com/f59aa51e12f00d19951fa32b/c0932810b4e652cf92e19c39/maisonconnecte_orange.png\" alt=\"\" data-image-width=\"3334\" data-image-height=\"3334\" data-href=\"/Accueil.html\" title=\"Accueil\"><div class=\"u-palette-1-light-2 u-preserve-proportions u-shape u-shape-circle u-shape-1\" data-href=\"/Controle-manuel.html\" title=\"Controle manuel\"></div><div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-2\"></div><div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-3\"></div><div class=\"u-rotation-parent u-rotation-parent-1\"><div class=\"u-rotate-270 u-shape u-shape-svg u-text-palette-1-base u-shape-4\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 140\" style=\"\"><use xlink:href=\"#svg-0768\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 140\" x=\"0px\" y=\"0px\" id=\"svg-0768\" style=\"enable-background:new 0 0 160 140;\"><path d=\"M90,45H0v50h90v45l70-70L90,0V45z\"></path></svg></div></div><div class=\"u-rotation-parent u-rotation-parent-2\"><div class=\"u-rotate-90 u-shape u-shape-svg u-text-palette-1-light-2 u-shape-5\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 140\" style=\"\"><use xlink:href=\"#svg-871d\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 140\" x=\"0px\" y=\"0px\" id=\"svg-871d\" style=\"enable-background:new 0 0 160 140;\"><path d=\"M90,45H0v50h90v45l70-70L90,0V45z\"></path></svg></div></div><div class=\"u-shape u-shape-svg u-text-palette-1-light-2 u-shape-6\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 160\" style=\"\"><use xlink:href=\"#svg-9769\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 160\" x=\"0px\" y=\"0px\" id=\"svg-9769\" style=\"enable-background:new 0 0 160 160;\"><path d=\"M105.7,80L160,0h-51.4L80,42.2L51.4,0H0l54.3,80L0,160h51.4L80,117.8l28.6,42.2H160L105.7,80z\"></path></svg></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-7\" data-href=\"/Controle-manuel.html\" title=\"Controle manuel\"></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-8\" data-href=\"/fermer.html\" title=\"fermer\"></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-9\" data-href=\"/Controle-manuel.html\" title=\"Controle manuel\"></div><h2 class=\"u-align-center-xs u-text u-text-2\">Ouvrir</h2><h2 class=\"u-align-center u-text u-text-3\">Stop</h2><h2 class=\"u-align-center-xs u-text u-text-4\">Fermer</h2></div></section></body></html0>");
      Serial.print("atc 2");
    }
    if (act == 3) {
      cli.println("<!DOCTYPE html><html style=\"font-size: 16px;\" lang=\"fr\"><head><title>Controle manuel</title><link rel=\"stylesheet\" href=\"https://capp.nicepage.com/0bcad38c69dcfd90c4459a4d49a057db8404895c/nicepage.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/nicepage-site.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/Controle-manuel.css\" media=\"screen\"></head><body class=\"u-body u-xl-mode\" data-lang=\"fr\"><section class=\"u-clearfix u-section-1\" id=\"sec-31df\"><div class=\"u-clearfix u-sheet u-sheet-1\"><h2 class=\"u-align-center-xs u-text u-text-1\">Controle manuel<br></h2><img class=\"u-image u-image-contain u-image-default u-preserve-proportions u-image-1\" src=\"https://images01.nicepagecdn.com/f59aa51e12f00d19951fa32b/c0932810b4e652cf92e19c39/maisonconnecte_orange.png\" alt=\"\" data-image-width=\"3334\" data-image-height=\"3334\" data-href=\"/Accueil.html\" title=\"Accueil\"><div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-1\"></div><div class=\"u-palette-1-base u-preserve-proportions u-shape u-shape-circle u-shape-2\"></div><div class=\"u-palette-1-light-2 u-preserve-proportions u-shape u-shape-circle u-shape-3\"></div><div class=\"u-rotation-parent u-rotation-parent-1\"><div class=\"u-rotate-270 u-shape u-shape-svg u-text-palette-1-light-2 u-shape-4\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 140\" style=\"\"><use xlink:href=\"#svg-0768\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 140\" x=\"0px\" y=\"0px\" id=\"svg-0768\" style=\"enable-background:new 0 0 160 140;\"><path d=\"M90,45H0v50h90v45l70-70L90,0V45z\"></path></svg></div></div><div class=\"u-rotation-parent u-rotation-parent-2\"><div class=\"u-rotate-90 u-shape u-shape-svg u-text-palette-1-base u-shape-5\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 140\" style=\"\"><use xlink:href=\"#svg-871d\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 140\" x=\"0px\" y=\"0px\" id=\"svg-871d\" style=\"enable-background:new 0 0 160 140;\"><path d=\"M90,45H0v50h90v45l70-70L90,0V45z\"></path></svg></div></div><div class=\"u-shape u-shape-svg u-text-palette-1-light-2 u-shape-6\"><svg class=\"u-svg-link\" preserveAspectRatio=\"none\" viewBox=\"0 0 160 160\" style=\"\"><use xlink:href=\"#svg-9769\"></use></svg><svg class=\"u-svg-content\" viewBox=\"0 0 160 160\" x=\"0px\" y=\"0px\" id=\"svg-9769\" style=\"enable-background:new 0 0 160 160;\"><path d=\"M105.7,80L160,0h-51.4L80,42.2L51.4,0H0l54.3,80L0,160h51.4L80,117.8l28.6,42.2H160L105.7,80z\"></path></svg></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-7\" data-href=\"/ouvrir.html\" title=\"ouvrir\"></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-8\" data-href=\"/Controle-manuel.html\" title=\"Controle manuel\"></div><div class=\"u-preserve-proportions u-shape u-shape-rectangle u-shape-9\" data-href=\"/Controle-manuel.html\" title=\"Controle manuel\"></div><h2 class=\"u-align-center-xs u-text u-text-2\">Ouvrir</h2><h2 class=\"u-align-center u-text u-text-3\">Stop</h2><h2 class=\"u-align-center-xs u-text u-text-4\">Fermer</h2></div></section></body></html>");
      Serial.print("atc 3");
    }
    if (!act){ //home
      cli.println("<!DOCTYPE html><html style=\"font-size: 16px;\" class=\"u-responsive-xl\" lang=\"fr\"><head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\">  <link rel=\"stylesheet\" href=\"https://capp.nicepage.com/e114254c99f86fecb8db371d56b85297e054d92f/nicepage.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/nicepage-site.css\" media=\"screen\"><link rel=\"stylesheet\" href=\"https://website3910851.nicepage.io/Accueil.css\" media=\"screen\"></head><body class=\"u-body u-xl-mode\"><section id=\"sec-1046\" class=\"u-clearfix u-section-1\"><div class=\"u-clearfix u-sheet u-sheet-1\"><img class=\"u-image u-image-contain u-image-default u-preserve-proportions u-image-1\" src=\"https://images01.nicepagecdn.com/f59aa51e12f00d19951fa32b/c0932810b4e652cf92e19c39/maisonconnecte_orange.png\" alt="" data-image-width=\"3334\" data-image-height=\"3334\"><h2 class=\"u-text u-text-default u-text-1\">Volet connecté<br></h2><a href=\"https://nicepage.dev/\" class=\"u-btn u-button-style u-btn-1\">Mode automatique</a><a href=\"https://website3910851.nicepage.io/Controle-manuel.html\" class=\"u-btn u-button-style u-btn-2\">Mode manuel</a><a href=\"https://nicepage.dev/\" class=\"u-btn u-button-style u-btn-3\">État des volets</a></div></section></body</html>");
      Serial.print("atc home");
    }
   }
   delay(100);
}
