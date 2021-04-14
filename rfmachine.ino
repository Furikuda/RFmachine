/* 
 * Emulate F-Machines remotes.
 *
 * Currently supports:
 *  - Gigolo (remote type 'A') https://f-machine.com/index.php/gigolo-detail
 *  - Tremblr (remote type 'A')  https://f-machine.com/index.php/tremblr-detail
 */

/*
 * Sets the data pin to talk to the H34A transmitter.
 */

int data = 0;

/*
 * Code here
 */

int SHORT_WAIT_US = 500;
int LONG_WAIT_US = 3 * SHORT_WAIT_US;

int DEFAULT_REPEAT = 7; // How many time to repeat a command

void send_bit(int b) {
  if (b == 0) {
    digitalWrite(data, 1);
    delayMicroseconds(SHORT_WAIT_US);
    digitalWrite(data, 0);
    delayMicroseconds(LONG_WAIT_US);
    digitalWrite(data, 1);
    delayMicroseconds(SHORT_WAIT_US);
    digitalWrite(data, 0);
    delayMicroseconds(LONG_WAIT_US);
    
  } else if ( b == 1 ) {
    digitalWrite(data, 1);
    delayMicroseconds(LONG_WAIT_US);
    digitalWrite(data, 0);
    delayMicroseconds(SHORT_WAIT_US);
    digitalWrite(data, 1);
    delayMicroseconds(LONG_WAIT_US);
    digitalWrite(data, 0);
    delayMicroseconds(SHORT_WAIT_US);
  } else {
    digitalWrite(data, 1);
    delayMicroseconds(SHORT_WAIT_US);
    digitalWrite(data, 0);
    delayMicroseconds(LONG_WAIT_US);
    digitalWrite(data, 1);
    delayMicroseconds(LONG_WAIT_US);
    digitalWrite(data, 0);
    delayMicroseconds(SHORT_WAIT_US);
  }
}

void send_command(String command, int repeat=DEFAULT_REPEAT) {
  char c;
  for (int r = 0; r < repeat; r++) {
    for (int i = 0; i < command.length(); i++ ) {
      c = command[i];
      if (c == '1') {
        send_bit(1);
      } else if (c == '0') {
        send_bit(0);
      } else {
        send_bit(-1);
      }
    }
    // send the "Sync bit"
    digitalWrite(data, 1);
    delayMicroseconds(SHORT_WAIT_US);
    digitalWrite(data, 0);
    delayMicroseconds(SHORT_WAIT_US * 42 ); // per 2262 doc
  }
}

/*
 * Commands for the Gigolo "A" remote
 */
void gigolo_a_up() {
  String command = "FFFFF1111000";
  send_command(command);
  Serial.println("Gigolo (A) Speed UP");
}

void gigolo_a_ok() {
  String command = "FFFFF1110010";
  send_command(command);
  Serial.println("Gigolo (A) ON/OFF");
}

void gigolo_a_down() {
  String command = "FFFFF1110100";
  send_command(command);
  Serial.println("Gigolo (A) Speed Down");
}

/*
 * Commands for the Tremblr "A" remote
 */
void tremblr_a_up() {
  String command = "11FFFF001000";
  send_command(command);
  Serial.println("Tremblr (A) Speed Up");
}

void tremblr_a_ok() {
  String command = "11FFFF000010";
  send_command(command);
  Serial.println("Tremblr (A) ON/OFF");
}

void tremblr_a_down() {
  String command = "11FFFF000100";
  send_command(command);
  Serial.println("Tremblr (A) Speed Down");
}
void tremblr_a_suck_up() {
  String command = "11FFFF000001";
  send_command(command, 15);
  Serial.println("Tremblr (A) Suck Up");
}

void tremblr_a_suck_down() {
  String command = "11FFFF010000";
  send_command(command, 15);
  Serial.println("Tremblr (A) Suck Down");
}

void setup() {
  Serial.begin(9600);
  pinMode(data, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}
