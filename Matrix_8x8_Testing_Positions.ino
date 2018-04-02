/*for the pins connection to the 8x8 led matrix, see: 
* https://create.arduino.cc/projecthub/SAnwandter1/programming-8x8-led-matrix-23475a?ref=user&ref_id=157202&offset=1
* 
* Any help to improve this design is greatly helpful !
* thanks a lot :)
*/


//Name the pins connections for clarity
#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 13
#define COL_5 A0
#define COL_6 A1
#define COL_7 A2
#define COL_8 A3


void setup() {
  Serial.begin(9600);
  //set pins 2 -> 13 as output:
  for (byte i = 2; i <= 13; i++){pinMode(i, OUTPUT);}

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  
  //change this for different result !
  randomSeed(12);
}


//make arrays for clarity
const byte rows[] = {ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8};
const byte cols[] = {COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8};

//you can choose how to start the game of life here, if you set "q" as true:
byte matrix[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}};
//this is the array which will hold the next generation:
byte new_matrix[8][8];

int timer = 0;

bool q = false;


void loop() {
  //initialize the matrix with random dots:
  if(q == false){
    q = true;
    for(byte i =0;i<8;i++) {
      for(byte j = 0;j<8;j++) {
        matrix[i][j] = random(0,2);
      }
    }
  }
  
  //calculate the next generation:
  for(byte i =0;i<8;i++){
    for(byte j = 0;j<8;j++){
      if(checkEnv(matrix,i,j) == 2){new_matrix[i][j] = matrix[i][j];}
      else if (checkEnv(matrix,i,j) == 3){new_matrix[i][j] = 1;}
      else {new_matrix[i][j] = 0;}
    }
  }
  
  //the child gen. becomes the parents.
  //you can change the timer division to increase or decrease speed.
  if(timer % 32 == 0){
    //q = true;
    for(byte i =0;i<8;i++){
      for(byte j = 0;j<8;j++){
        matrix[i][j] = new_matrix[i][j];
      }
    }
  }
  
  //draw the parent generation:
  drawArray(matrix); 
  //timer helps sets the rate of change
  timer++;  
  
  //keep the delay below 5 to prevent epilepsy.
  //1 is perfect
  delay(1);
}


//check how many "alive" cells there are around a unit:
byte checkEnv(byte matrix[8][8],byte i, byte j){
  byte temp = 0;
  //  A  D  D
  //  A  U  D   -->there are 3 Alive A cells around the Unit U !
  //  D  D  A
  
  //the matrix are either ones or zeros, so we can simply add the value to temp 
  //to know how many ones (Alive) cells there is around a Unit.
  temp += matrix[nicePos(i-1)][nicePos(j-1)];
  temp += matrix[nicePos(i)][nicePos(j-1)];
  temp += matrix[nicePos(i+1)][nicePos(j-1)];
  temp += matrix[nicePos(i-1)][nicePos(j)];
  //this is the position of the led we're studying. no need to include it !
  //temp += matrix[nicePos(i)][nicePos(j)];  
  temp += matrix[nicePos(i+1)][nicePos(j)];
  temp += matrix[nicePos(i-1)][nicePos(j+1)];
  temp += matrix[nicePos(i)][nicePos(j+1)];
  temp += matrix[nicePos(i+1)][nicePos(j+1)];
  return temp;
}

//NICEPOS() ELIMINATES SOLID EDGES.
byte nicePos(int x) {return (x + 8)%8; }
  //+8 to get rid of (-) values, %8 to keep values below 8.
  //if a Unit is at the border, this helps calculate the other 
  //sides position of its environment. (the Unit's environment)


//DRAWARRAY() DRAWS THE MATRIX.
void drawArray(byte matrix[8][8]){
  // Turn on each row in series
  for (byte i = 0; i < 8; i++) {
    setColumnsArray(matrix[i]);           // Set the columns for this specific row
    digitalWrite(rows[i], HIGH);      //set that row to high for (delay), which will be in phase with the columns
    delay(1);                         // Set this to 50 or 100 if you want to see the multiplexing effect
    digitalWrite(rows[i], LOW);       //after displaying the row, put it low, to pass on to the next row.
  }
}

//SET COLUMNS
void setColumnsArray(byte matrix[8]) {
  for(int i = 0; i < 8;i++) {
    //set cell as alive if one
    if (matrix[i] == 1) {digitalWrite(cols[i], 0);}
    //else it's dead
    else {digitalWrite(cols[i], 1);}
  }
} 








//nothing to see down here
