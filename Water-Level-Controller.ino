//Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;
int travelTime;
float distance;

//Water Pump Control
const int dryRunPin = 3;
const int relayPin = 2;
String state = "Full";

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(dryRunPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(dryRunPin) == 1) {
    //Dry Run Protection
    digitalWrite(relayPin, HIGH); //turn off water pump

  } else {

    sendSoundWave();                       //Send a sound Wave
    travelTime = pulseIn(echoPin, HIGH);   //Get Travel Time
    distance = travelTime * 0.034 / 2;     //Calculate Distance in cm

    //Open and Close Logic
    if (state == "Empty") {
      //turn on water pump
      digitalWrite(relayPin, LOW);
      if (distance < 4) {
        state = "Full";
      }

    } else if (state == "Full") {
      //turn off water pump
      digitalWrite(relayPin, HIGH);
      if (distance > 12) {
        state = "Empty";
      }

    }
  }

  delay(100);
}

void sendSoundWave() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}
