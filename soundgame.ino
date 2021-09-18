    #include "pitches.h"
#include "LedControl.h"
LedControl lc=LedControl(12,10,11,1);
const int SW_pin=5; 
const int X_pin=0; 
const int Y_pin=1;
const int PinCLK=2;
const int PinDT=3;
const int PinSW=4;
int i,col,cur_flame=0,node[6]={0},sound=0,flag[6]={0},good=0,bad=0;
int m_m[]={
0,NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4,
NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5,
NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6,
NOTE_C7
};
int next_node[6][20];
int next_node_0[20]={//2800は初期化されてないnodeを読まないためのダミー
  100,470,1000,
  740,990,1340,
  1380,1640,1720,
  2080,2280,2500
  ,2800,2800,2800,2800,2800,2800
};
int next_node_1[20]={
  220,580,1000,
  820,1050,1260,
  1580,1860,1920,
  2200,2360,2800,2800,2800,2800,2800,2800
};
int next_node_2[20]={
  290,380,610,1000,
  860,1030,1220,
  1600,1890,
  2240,2410,2560,2800,2800,2800,2800,2800,2800
};
int next_node_3[20]={
  350,640,
  780,1010,1300,
  1680,1760,1840,
  2100,2320,2530,2800,2800,2800,2800,2800,2800
};
int next_node_4[20]={
  260,1000,1000,
  900,1100,
  1460,1520,1980,
  2140,2800,2800,2800,2800,2800,2800
};
int next_node_5[20]={
  180,1000,1000,
  940,1140,1180,
  1500,1540,1950,
  2020,2160,2800,2800,2800,2800,2800,2800
};
int sound_flame[256]={
  100,160,170,
  180,190,220,230,240,250,
  260,270,280,290,310,320,330,
  350,360,370,380,390,400,410,
  430,440,450,470,480,490,
  510,550,560,570,
  580,600,610,630,640,
  670,700,1000,
  740,750,780,790,
  820,830,860,870,
  900,910,940,950,
  990,1000,1010,1020,1030,1040,1050,
  1060,1070,1100,1110,
  1140,1150,1180,1190,
  1220,1230,1260,1270,
  1300,1310,1340,1350,
  1380,1440,1450,
  1460,1470,1500,1510,1520,1530,
  1540,1550,1560,1570,1590,1600,1610,
  1630,1640,1650,1660,1670,1680,1690,
  1710,1720,1730,1750,1760,1770,
  1790,1830,1840,1850,
  1860,1880,1890,1910,1920,
  1950,1980,
  2020,2080,2090,
  2100,2140,2150,2160,2170,
  2180,2190,2200,2210,2230,2240,2250,
  2270,2280,2290,2300,2310,2320,2330,
  2350,2360,2370,2390,2400,2410,
  2470,2480,2490,
  2500,2520,2530,2550,2560,
  2620,2800,2800
  
};
int music_pitch[256]={
  m_m[12],m_m[12],m_m[16],
  m_m[15],m_m[5],m_m[12],m_m[8],m_m[9],m_m[8],
  m_m[12],m_m[15],m_m[16],m_m[15],m_m[12],m_m[9],m_m[10],
  m_m[8],m_m[9],m_m[10],m_m[12],m_m[8],m_m[9],m_m[8],
  m_m[8],m_m[9],m_m[8],m_m[12],m_m[16],m_m[15],
  m_m[5],m_m[12],m_m[15],m_m[16],
  m_m[17],m_m[16],m_m[15],m_m[20],m_m[19],
  m_m[5],m_m[2],
  m_m[3],m_m[3],m_m[3],m_m[3],
  m_m[5],m_m[5],m_m[5],m_m[5],
  m_m[3],m_m[3],m_m[3],m_m[3],
  m_m[10],m_m[9],m_m[8],m_m[5],m_m[8],m_m[9],m_m[12],
  m_m[3],m_m[3],m_m[3],m_m[3],
  m_m[5],m_m[5],m_m[5],m_m[5],
  m_m[3],m_m[3],m_m[3],m_m[3],
  m_m[2],m_m[2],m_m[2],m_m[2],
  m_m[8],m_m[5],m_m[9],
  m_m[8],m_m[5],m_m[5],m_m[1],m_m[2],m_m[1],
  m_m[5],m_m[8],m_m[9],m_m[8],m_m[5],m_m[2],m_m[3],
  m_m[1],m_m[2],m_m[3],m_m[5],m_m[1],m_m[2],m_m[1],
  m_m[1],m_m[2],m_m[1],m_m[5],m_m[9],m_m[8],
  m_m[5],m_m[5],m_m[8],m_m[9],
  m_m[10],m_m[9],m_m[8],m_m[13],m_m[12],
  m_m[5],m_m[2],
  m_m[15],m_m[12],m_m[16],
  m_m[15],m_m[12],m_m[8],m_m[9],m_m[8],
  m_m[12],m_m[15],m_m[16],m_m[15],m_m[12],m_m[9],m_m[10],
  m_m[8],m_m[9],m_m[10],m_m[12],m_m[8],m_m[9],m_m[8],
  m_m[8],m_m[9],m_m[8],m_m[12],m_m[16],m_m[15],
  m_m[5],m_m[8],m_m[9],
  m_m[10],m_m[9],m_m[8],m_m[13],m_m[12],
  m_m[19],2800,2800
};


int check(int node_flame,int col,int cur_flame,int flag){
  if(node_flame-cur_flame<=16){//GOOD
    switch(col){
      case 0:
        if(analogRead(X_pin)<=250){
          good++;
          Serial.println("GOOD");
          return 0;
        }
        break;
      case 1:
        if(analogRead(Y_pin)>=760){
          good++;
          Serial.println("GOOD");
          return 0;
        }
        break;
      case 2:
        if(analogRead(Y_pin)<=250){
          good++;
          Serial.println("GOOD");
          return 0;
          }
        break;
      case 3:
        if(analogRead(X_pin)>=760){
          good++;
          Serial.println("GOOD");
          return 0;
        }
        break;
      case 4:
        if(digitalRead(PinCLK)==0){
          good++;
          Serial.println("GOOD");
          return 0;
        }
        break;
      case 5:
        if(digitalRead(PinDT)==0){
          good++;
          Serial.println("GOOD");
          return 0;
        }
        break;
    }
  }else{//BAD
    switch(col){
      case 0:
        if(analogRead(X_pin)<=250){
          bad++;
          Serial.println("BAD");
          return 0;
        }
        break;
      case 1:
        if(analogRead(Y_pin)>=760){
          bad++;
          Serial.println("BAD");
          return 0;
        }
        break;
      case 2:
        if(analogRead(Y_pin)<=250){
          bad++;
          Serial.println("BAD");
          return 0;
        }
        break;
      case 3:
        if(analogRead(X_pin)>=760){
          bad++;
          Serial.println("BAD");
          return 0;
        }
        break;
        case 4:
        if(digitalRead(PinCLK)==0){
          bad++;
          Serial.println("BAD");
          return 0;
        }
        break;
      case 5:
        if(digitalRead(PinDT)==0){
          bad++;
          return 0;
        }
        break;
    }
  }
  return flag;
}

int sound_play(int music_pitch){
  tone(7, music_pitch, 100);
}

int LED_animation(int col,int flag) {//flagノーツの進み具合、colがノーツの配置列
  if(col<4){
    switch(flag){
      case 0:
        lc.setColumn(0,col,B10000001);
        return 1;
        break;
      case 1:
        lc.setColumn(0,col,B01000001);
        return 2;
        break;
      case 2:
        lc.setColumn(0,col,B00100001);
        return 3;
        break;
      case 3:
        lc.setColumn(0,col,B00010001);
        return 4;
        break;
      case 4:
        lc.setColumn(0,col,B00001001);
        return 5;
        break;
      case 5:
        lc.setColumn(0,col,B00000101);
        return 6;
        break;
      case 6:
        lc.setColumn(0,col,B00000011);
        return 7;
        break;
      case 7:
        lc.setColumn(0,col,B00000001);
        return 0;
        break;
    }
  }else if(col==4){
    switch(flag){
      case 0:
        lc.setColumn(0,col,B10000001);
        lc.setColumn(0,col+1,B10000001);
        return 1;
        break;
      case 1:
        lc.setColumn(0,col,B01000001);
        lc.setColumn(0,col+1,B01000001);
        return 2;
        break;
      case 2:
        lc.setColumn(0,col,B00100001);
        lc.setColumn(0,col+1,B00100001);
        return 3;
        break;
      case 3:
        lc.setColumn(0,col,B00010001);
        lc.setColumn(0,col+1,B00010001);
        return 4;
        break;
      case 4:
        lc.setColumn(0,col,B00001001);
        lc.setColumn(0,col+1,B00001001);
        return 5;
        break;
      case 5:
        lc.setColumn(0,col,B00000101);
        lc.setColumn(0,col+1,B00000101);
        return 6;
        break;
      case 6:
        lc.setColumn(0,col,B00000011);
        lc.setColumn(0,col+1,B00000011);
        return 7;
        break;
      case 7:
        lc.setColumn(0,col,B00000001);
        lc.setColumn(0,col+1,B00000001);
        return 0;
        break;
    }
  }else if(col==5){
    switch(flag){
      case 0:
        lc.setColumn(0,col+2,B10000001);
        lc.setColumn(0,col+1,B10000001);
        return 1;
        break;
      case 1:
        lc.setColumn(0,col+2,B01000001);
        lc.setColumn(0,col+1,B01000001);
        return 2;
        break;
      case 2:
        lc.setColumn(0,col+2,B00100001);
        lc.setColumn(0,col+1,B00100001);
        return 3;
        break;
      case 3:
        lc.setColumn(0,col+2,B00010001);
        lc.setColumn(0,col+1,B00010001);
        return 4;
        break;
      case 4:
        lc.setColumn(0,col+2,B00001001);
        lc.setColumn(0,col+1,B00001001);
        return 5;
        break;
      case 5:
        lc.setColumn(0,col+2,B00000101);
        lc.setColumn(0,col+1,B00000101);
        return 6;
        break;
      case 6:
        lc.setColumn(0,col+2,B00000011);
        lc.setColumn(0,col+1,B00000011);
        return 7;
        break;
      case 7:
        lc.setColumn(0,col+2,B00000001);
        lc.setColumn(0,col+1,B00000001);
        return 0;
        break;
    }
  }
}



void setup() {
  Serial.begin(9600);
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  lc.setRow(0,7,B11111111);
  for(i=0;i<13;i++){
    next_node[0][i]=next_node_0[i];
  }
  for(i=0;i<13;i++){
    next_node[1][i]=next_node_1[i];
  }
  for(i=0;i<13;i++){
    next_node[2][i]=next_node_2[i];
  }
  for(i=0;i<13;i++){
    next_node[3][i]=next_node_3[i];
  }
  for(i=0;i<13;i++){
    next_node[4][i]=next_node_4[i];
  }
  for(i=0;i<13;i++){
    next_node[5][i]=next_node_5[i];
  }
}

void loop(){
  for(col=0;col<6;col++){
    if(next_node[col][node[col]]-cur_flame==0){
        node[col]++;
      }
    if(next_node[col][node[col]]-cur_flame<=64){
      if((next_node[col][node[col]]-cur_flame)%8==0){
        flag[col]=LED_animation(col,flag[col]);
      }
    }
    if(next_node[col][node[col]]-cur_flame<=32){
      flag[col]=check(next_node[col][node[col]],col,cur_flame,flag[col]);
      if(flag[col]==0){
        LED_animation(col,7);
        node[col]++;
        
      }
    }
  if(sound_flame[sound]-cur_flame==0){
    sound_play(music_pitch[sound]);
    sound++;
  }
 }
  cur_flame++;
  if(cur_flame==2650){
    Serial.println("FINISH!!!!");
    Serial.print("GOOD  ");
    Serial.println(good);
    Serial.print("BAD  ");
    Serial.println(bad);
    cur_flame=0;
    good=0;
    bad=0;
    sound=0;
    for(col=0;col<6;col++){
      node[col]=0;
      flag[col]=0;
      LED_animation(col,7);
    }
    while(analogRead(Y_pin)<=250||analogRead(X_pin)>=760){
      delay(100);
    }
  }
  delay(18);
}
