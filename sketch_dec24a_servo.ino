#include <Servo.h>

// Définition des broches
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

Servo monServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  monServo.attach(servoPin);
  
  Serial.begin(9600); // Pour voir la distance sur le moniteur série
  monServo.write(0);  // Position initiale
}

void loop() {
  // 1. Mesure de la distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duree = pulseIn(echoPin, HIGH);
  int distance = duree * 0.034 / 2; // Calcul de la distance en cm

  // 2. Logique du servo
  if (distance > 0 && distance < 20) {
    monServo.write(90); // Action : tourne à 90 degrés
  } else {
    monServo.write(0);  // Repos : revient à 0 degré
  }

  // Affichage pour le débogage
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100); // Petite pause pour la stabilité
}