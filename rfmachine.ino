/* 
 * Emulate F-Machines remotes.
 *
 * Currently supports:
 *  - Gigolo https://f-machine.com/index.php/gigolo-detail
 *  - Tremblr https://f-machine.com/index.php/tremblr-detail
 */

/*
 * Sets the data pin to talk to the H34A transmitter.
 */
int data = 0;


/*
 * Code here
 */

int SHORT_WAIT_US = 500;
int LONG_WAIT_US = 1500;

int COMMAND_DELAY_MS = 20;

int DEFAULT_REPEAT = 6;

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

void send_command(const char* command, int repeat=DEFAULT_REPEAT) {
  for (int r = 0; r < repeat; r++) {
    for (int i = 0; i < strlen(command); i++ ) {
      char c = command[i];
      if (c == '1') {
        send_bit(1);
      } else if (c == '0') {
        send_bit(0);
      } else {
        send_bit(-1);
      }
      // Doesn't look very standard, but there is always a short spike
      // being sent at the end of every command.
      digitalWrite(data, 1);
      delayMicroseconds(SHORT_WAIT_US);
      digitalWrite(data, 0);
      delay(COMMAND_DELAY_MS);
    }
  }
}

/*
 * Commands for the Gigolo "A" remote
 */
void gigolo_a_up() {
  const char* command = "FFFFF1111000";
  send_command(command);
  Serial.println("Speed UP");
}

void gigolo_a_ok() {
  const char* command = "FFFFF1110010";
  send_command(command);
  Serial.println("ON/OFF");
}

void gigolo_a_down() {
  const char* command = "FFFFF1110100";
  send_command(command);
  Serial.println("Speed Down");
}

/*
 * Commands for the Tremblr "A" remote
 */
void tremblr_a_up() {
  const char* command = "11FFFF001000";
  send_command(command, 6);
  Serial.println("Speed Up");
}

void tremblr_a_ok() {
  const char* command = "11FFFF000010";
  send_command(command)
  Serial.println("ON/OFF");
}

void tremblr_a_down() {
  const char* command = "11FFFF000100";
  send_command(command)
  Serial.println("Sent Down");
}
void tremblr_a_suck_up() {
  const char* command = "11FFFF000001";
  send_command(command)
  Serial.println("Suck Up");
}

void tremblr_a_suck_down() {
  const char* command = "11FFFF010000";
  send_command(command)
  Serial.println("Suck Down");
}

void setup() {
  Serial.begin(9600);
  pinMode(data, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}
