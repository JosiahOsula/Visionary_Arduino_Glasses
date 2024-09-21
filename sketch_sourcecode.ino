

const int MAX_DIST = 10000;// initialize infinite large distance as const for later use 
class Buzzer{// declare buzzer class for usage with each US.sensor.
private:
  bool isBuzzing;
  int Dummie_var;//dummy var used in the constructor.
  int pin_number;// pin number assosicated with thebuzzer class

public:
  Buzzer(){// default constructoe
    Dummie_var = 0; 
  }

  Buzzer(int pin_number){//constructor using the pin number to write to the buzzer
    this->pin_number = pin_number;
    pinMode(pin_number,OUTPUT);
    digitalWrite(pin_number,0);
  }

  void buzzMe(){// we pass the loop variable to the function here 
    digitalWrite(pin_number,200);// this function is buzzing the buzzer
  }

  void noBuzz(){// this function stops the buzzer from buzzing if no significttn distnce is assessed.
    digitalWrite(pin_number,0);
  }
};
class UltrasonicSensor {// ultrasonic sensor class implimentaion 

private:

  int trigpin;
  int echopin;
  long time;
  long distance;
  int dummie_var;

public:
  UltrasonicSensor(){// default constructor used 
    dummie_var=0;
  }
  UltrasonicSensor(int trigpin, int echopin) {// constructir where the pins are initialized and the private is equal to the public 
    this->echopin = echopin;
    this->trigpin = trigpin;
    this->time = time;
    this->distance = distance;

    pinMode(trigpin, OUTPUT);// pin mode initialization 
    pinMode(echopin, INPUT);
    digitalWrite(trigpin, LOW);
  }


  long Measure() {
    digitalWrite(trigpin, LOW);// routine for US to get a distance
    delayMicroseconds(2);
    digitalWrite(trigpin, HIGH);
    pulseIn(echopin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);

    time = pulseIn(echopin, HIGH); 

    distance = (time / 29.1)/ 2.0; // calculate distance

    return distance;// return the distance calculated from the sensor 
  }

  void Read() { // debugging tool for distance and reading 
    Serial.println(distance);
  }
};
Buzzer buzzer_one(11);// These can be changed to suit which pin you would like to use.
Buzzer buzzer_two(6);
UltrasonicSensor sensor_one(9, 10);
UltrasonicSensor sensor_two(12, 13);
Buzzer buzzers[2] = {buzzer_one,buzzer_two};// place the objects in an array to later iterate through it
UltrasonicSensor sensors[2] = {sensor_one,sensor_two};// important to note the repsective positions of objects in the arrays




void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
  delayMicroseconds(100);
}


void loop() {
  delayMicroseconds(500);
  int distance_assessed= MAX_DIST;// assume maximum distance, no buzzers or sensors are active
  for (int i = 0; i < 2; i++) {// important to note the I'th object can only be accessed at a time. this is to prevent writing multiple if statements.
  //for the Ith object in 1 arry the same numbered object corresponds to the next. the physical construction of the project should follow this same design
  // for example in the loop below, when i= 0, sensor_one is accessed and buzzer_one can be either active or inactive.
    distance_assessed = sensors[i].Measure();
    if(distance_assessed<35){
      buzzers[i].buzzMe();
      delayMicroseconds(250);
    }
    else if(distance_assessed>=35){
      buzzers[i].noBuzz();
      delayMicroseconds(250);
    }
}
}
