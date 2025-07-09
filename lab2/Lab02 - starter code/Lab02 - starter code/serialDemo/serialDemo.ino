int counter = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {

  Serial.print("counter: ");
  Serial.println(counter);
  counter++;
}
