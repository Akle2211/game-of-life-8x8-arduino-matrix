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

const byte rows[] = {ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8};
const byte cols[] = {COL_1, COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8};

void setup() {
  Serial.begin(9600);
    
  for (byte i = 0; i <= 13; i++){pinMode(i, OUTPUT);}
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  
  randomSeed(12);

}



byte matrix[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}};
byte new_matrix[8][8];
byte timer = 0;
bool q = false;

void loop() {

  if(q == false){
    q = true;
    for(byte i =0;i<8;i++){
      for(byte j = 0;j<8;j++){
        matrix[i][j] = random(0,2);
      }
    }
  }
  
  for(byte i =0;i<8;i++){
    for(byte j = 0;j<8;j++){
      if(checkEnv(matrix,i,j) == 2){new_matrix[i][j] = matrix[i][j];}
      else if (checkEnv(matrix,i,j) == 3){new_matrix[i][j] = 1;}
      else {new_matrix[i][j] = 0;}
    }
  }
  
  if(timer % 32 == 0){
    //q = true;
    for(byte i =0;i<8;i++){
      for(byte j = 0;j<8;j++){
        matrix[i][j] = new_matrix[i][j];
      }
    }
  }
  drawArray(new_matrix); 
  timer++;  
  delay(1);
}

byte checkEnv(byte matrix[8][8],byte i, byte j){
  byte temp = 0;
  
  temp += matrix[nicePos(i-1)][nicePos(j-1)];
  temp += matrix[nicePos(i)][nicePos(j-1)];
  temp += matrix[nicePos(i+1)][nicePos(j-1)];
  temp += matrix[nicePos(i-1)][nicePos(j)];
  //temp += matrix[nicePos(i)][nicePos(j)];
  temp += matrix[nicePos(i+1)][nicePos(j)];
  temp += matrix[nicePos(i-1)][nicePos(j+1)];
  temp += matrix[nicePos(i)][nicePos(j+1)];
  temp += matrix[nicePos(i+1)][nicePos(j+1)];

  return temp;
  
  
  
}

byte nicePos(int x){
  return (x + 8)%8; 
}

//DRAW ARRAY DRAWS ARRAY.
void drawArray(byte matrix[8][8]){
  // Turn on each row in series
  for (byte i = 0; i < 8; i++) {
    setColumnsArray(matrix[i]);           // Set columns for this specific row
    digitalWrite(rows[i], HIGH);      //set that row to high for (delay), which will be in phase with the columns
    delay(1);                         // Set this to 50 or 100 if you want to see the multiplexing effect
    digitalWrite(rows[i], LOW);       //after displaying the row, put it low, to pass on to the next row.
    
  }
}

//SET COLUMNS
void setColumnsArray(byte matrix[8]) {
  for(int i = 0; i < 8;i++) {
    if (matrix[i] == 1) {digitalWrite(cols[i], 0);}
    else {digitalWrite(cols[i], 1);}
  }
} 





