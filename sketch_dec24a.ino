// Capteur poubelle
#define TRIG_POUBELLE 21
#define ECHO_POUBELLE 22

// Blynk
#define BLYNK_TEMPLATE_ID "TMPL2D6nqipIG"
#define BLYNK_TEMPLATE_NAME "Smart City Bacs"
#define BLYNK_AUTH_TOKEN "---------------"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Informations WiFi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "----------";        // <-- remplace par ton WiFi 2.4GHz
char pass[] = "----------";        // <-- remplace par ton mot de passe

void setup() {
  Serial.begin(115200);
  delay(1500);

  // Initialisation capteur
  pinMode(TRIG_POUBELLE, OUTPUT);
  pinMode(ECHO_POUBELLE, INPUT);

  Serial.println("Capteur poubelle initialisé");

  // Connexion WiFi
  WiFi.begin(ssid, pass);
  Serial.print("Connexion au WiFi");
  unsigned long startAttemptTime = millis();
  const unsigned long WIFI_TIMEOUT = 10000; // 10 secondes max

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connecté !");
    Serial.print("IP: "); Serial.println(WiFi.localIP());
    // Connexion Blynk
    Blynk.begin(auth, ssid, pass);
  } else {
    Serial.println("\nWiFi non connecté, continuer quand même");
  }
}

// Fonction de lecture distance (cm)
float lireDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long d = pulseIn(echo, HIGH, 30000); // timeout 30 ms
  if (d == 0) return -1;
  return d * 0.034 / 2;
}

void loop() {
  Blynk.run(); // Nécessaire pour Blynk

  float dPoubelle = lireDistance(TRIG_POUBELLE, ECHO_POUBELLE);

  if (dPoubelle != -1) {
    Serial.print("Capteur poubelle : ");
    Serial.print(dPoubelle);
    Serial.println(" cm");

    // Conversion distance en pourcentage pour le gauge (V0)
    float niveauPourcentage = map(dPoubelle, 5, 20, 100, 0);
    niveauPourcentage = constrain(niveauPourcentage, 0, 100);
    Blynk.virtualWrite(V0, niveauPourcentage);

    // Alertes texte sur Value Display (V1)
    if (dPoubelle < 5) {
      Serial.println(">>> POUBELLE PLEINE <<<");
      Blynk.virtualWrite(V7, "⚠️ Poubelle presque pleine !");
    } else {
      Blynk.virtualWrite(V7, "");
    }
  } else {
    Serial.println("Aucune mesure détectée");
    // Optionnel : remettre gauge à 0 si pas de mesure
    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V7, "");
  }

  delay(500);
}
