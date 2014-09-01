

#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include <Time.h>
#include <stdarg.h>
#include "SystemFont5x7.h"
#include "Arial_black_16.h"
#include "Arial14.h"

//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
--------------------------------------------------------------------------------------*/
void setup(void)
{
   pinMode(4, INPUT);
   Serial.begin(9600);
   setTime(0,0,0,18,18,2014);
   //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
   Timer1.initialize( 5215 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
   Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()

   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
  
}

  

////////// VARIABLES ///////////
    int segundo=0;
    int mili_segundo=0;
    int bandera=0;
    int bandera2=0;
    int bandera_limpiar=0;
    int hora2=0;
    int minuto2=0;
    int segundo2=0;
    String str;
    char hora_char[3];
    char minuto_char[3];
    char segundo_char[3];
    char segundo_reg[3];
    int segundo_inv=10;
    int boton=0;
    int buffer_hora;
    int buffer_minuto;
    int buffer_segundo;
    int i=0;
    int j=0;
    char val[200];
//////////////////////////////

void Reloj_Normal (void){
   dmd.selectFont(Arial_Black_16);
   if (hour()<10){
     dmd.drawString(  0, 1 ,"0", 1, GRAPHICS_NORMAL );
     dmd.drawString(  9, 1 , hora_char, 2, GRAPHICS_NORMAL );
   }
   else{
       dmd.drawString(  0, 1 , hora_char, 2, GRAPHICS_NORMAL );
   }
   
   dmd.drawBox( 19,9 , 20, 10, GRAPHICS_NORMAL );
   dmd.drawBox( 19,5 , 20, 6, GRAPHICS_NORMAL );
   
   if (minute()<10){
     dmd.drawString( 22, 1 ,"0", 1, GRAPHICS_NORMAL );
     dmd.drawString( 31, 1 ,minuto_char, 2, GRAPHICS_NORMAL );          
   }
   else{
       dmd.drawString( 22, 1 , minuto_char, 2, GRAPHICS_NORMAL );
   }
   
   
   dmd.drawBox( 42,9 , 43, 10, GRAPHICS_NORMAL );
   dmd.drawBox( 42,5 , 43, 6, GRAPHICS_NORMAL );
   
  
   if(segundo<10){
     dmd.drawString(  45, 1 ,"0", 1, GRAPHICS_NORMAL );
     dmd.drawString(  54, 1 ,segundo_char, 2, GRAPHICS_NORMAL );
   }
   else{

       dmd.drawString(  45, 1 , segundo_char, 2, GRAPHICS_NORMAL );
   }
}


void Reloj_Largada(void){
   segundo_inv=60-segundo;
   str=String(segundo_inv);
   str.toCharArray(segundo_reg,3);
   
   if(segundo<50 && segundo>0){
     Reloj_Normal();
   }
   else if(segundo<=55 && segundo>0){
    if (bandera_limpiar==0){
      dmd.clearScreen( true );
      bandera_limpiar=1;
    } 
    
    dmd.drawCircle( 4, 8, 3, GRAPHICS_NORMAL );
    dmd.drawFilledBox( 3, 6, 5,10, GRAPHICS_NORMAL );
    dmd.drawFilledBox( 2, 7, 6,9, GRAPHICS_NORMAL );
    
    dmd.drawCircle( 13, 8, 3, GRAPHICS_NORMAL );
    dmd.drawFilledBox( 12, 6, 14,10, GRAPHICS_NORMAL );
    dmd.drawFilledBox( 11, 7, 15,9, GRAPHICS_NORMAL );
    
    dmd.drawCircle( 22, 8, 3, GRAPHICS_NORMAL );
    dmd.drawFilledBox( 21, 6, 23,10, GRAPHICS_NORMAL );
    dmd.drawFilledBox( 20, 7, 24,9, GRAPHICS_NORMAL );

    dmd.drawCircle( 31, 8, 3, GRAPHICS_NORMAL );
    dmd.drawFilledBox( 30, 6, 32,10, GRAPHICS_NORMAL );
    dmd.drawFilledBox( 29, 7, 33,9, GRAPHICS_NORMAL );
    
    dmd.drawCircle( 40, 8, 3, GRAPHICS_NORMAL );
    dmd.drawFilledBox( 39, 6, 41,10, GRAPHICS_NORMAL );
    dmd.drawFilledBox( 38, 7, 42,9, GRAPHICS_NORMAL );
    
    dmd.drawString(  47, 1 , segundo_reg, 2, GRAPHICS_NORMAL );
   }
   else if (segundo==56){
    if (bandera_limpiar==0){
      dmd.clearScreen( true );
      bandera_limpiar=1;
    } 
    dmd.drawCircle( 4, 8, 3, GRAPHICS_INVERSE );
    dmd.drawFilledBox( 3, 6, 5,10, GRAPHICS_INVERSE );
    dmd.drawFilledBox( 2, 7, 6,9, GRAPHICS_INVERSE );
    
    dmd.drawCircle( 13, 8, 3, GRAPHICS_NORMAL );
    dmd.drawCircle( 22, 8, 3, GRAPHICS_NORMAL );
    dmd.drawCircle( 31, 8, 3, GRAPHICS_NORMAL );
    dmd.drawCircle( 40, 8, 3, GRAPHICS_NORMAL );
    
    dmd.drawString(  47, 1 , segundo_reg, 2, GRAPHICS_NORMAL );
   }
   else if (segundo==57){
     if (bandera_limpiar==0){
      dmd.clearScreen( true );
      bandera_limpiar=1;
    } 
     dmd.drawCircle( 4, 8, 3, GRAPHICS_INVERSE );
     
     dmd.drawCircle( 13, 8, 3, GRAPHICS_INVERSE );
     dmd.drawFilledBox( 12, 6, 14,10, GRAPHICS_INVERSE );
     dmd.drawFilledBox( 11, 7, 15,9, GRAPHICS_INVERSE );
    
     dmd.drawCircle( 22, 8, 3, GRAPHICS_NORMAL );
     dmd.drawCircle( 31, 8, 3, GRAPHICS_NORMAL );
     dmd.drawCircle( 40, 8, 3, GRAPHICS_NORMAL );
    
     dmd.drawString(  47, 1 , segundo_reg, 2, GRAPHICS_NORMAL );
   }
   else if (segundo==58){
     if (bandera_limpiar==0){
       dmd.clearScreen( true );
       bandera_limpiar=1;
     } 
     dmd.drawCircle( 4, 8, 3, GRAPHICS_INVERSE );
     
     dmd.drawCircle( 13, 8, 3, GRAPHICS_INVERSE );
     
     dmd.drawCircle( 22, 8, 3, GRAPHICS_INVERSE );
     dmd.drawFilledBox( 21, 6, 23,10, GRAPHICS_INVERSE );
     dmd.drawFilledBox( 20, 7, 24,9, GRAPHICS_INVERSE );
     
     dmd.drawCircle( 31, 8, 3, GRAPHICS_NORMAL );
     dmd.drawCircle( 40, 8, 3, GRAPHICS_NORMAL );
    
     dmd.drawString(  47, 1 , segundo_reg, 2, GRAPHICS_NORMAL );
   }
   else if (segundo==59){
     if (bandera_limpiar==0){
       dmd.clearScreen( true );
       bandera_limpiar=1;
     } 
     dmd.drawCircle( 4, 8, 3, GRAPHICS_INVERSE );
     dmd.drawCircle( 13, 8, 3, GRAPHICS_INVERSE );
     dmd.drawCircle( 22, 8, 3, GRAPHICS_INVERSE );
     dmd.drawCircle( 31, 8, 3, GRAPHICS_INVERSE );
     dmd.drawFilledBox( 30, 6, 32,10, GRAPHICS_INVERSE );
     dmd.drawFilledBox( 29, 7, 33,9, GRAPHICS_INVERSE );
     
     dmd.drawCircle( 40, 8, 3, GRAPHICS_NORMAL );
     dmd.drawLine( 54, 0, 54, 16,GRAPHICS_INVERSE );
     
     dmd.drawString(  47, 1 , segundo_reg, 2, GRAPHICS_NORMAL );
   }
   else if (segundo==0){
      dmd.drawFilledBox(0, 0, 64, 16, GRAPHICS_INVERSE );
      bandera_limpiar=0;
   }
} 


/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
   
void loop(void)
{
   boton=digitalRead(4);
   
   if (mili_segundo>=25){
     mili_segundo=0;
     segundo=segundo+1;
   }
   else{
     mili_segundo=mili_segundo+1;
     if(segundo>=50 && boton==1 && segundo!=0){
       delay(17);
     }
     else{
       delay(5);
     }
   }
   if (segundo>=60){
     segundo=0; 
   }
   //segundo=second();
      
  
 /////////// CONVERSIONES DE INT A CONST CHAR ////////
   str=String(hour());
   str.toCharArray(hora_char,3);
   str=String(minute());
   str.toCharArray(minuto_char,3);
   str=String(segundo);
   str.toCharArray(segundo_char,3);
////////////////////////////////////////////////////
   
   if (boton==1){
     Reloj_Largada(); 
   }
   else{
    
       Reloj_Normal();

     bandera_limpiar=0;
   }
   
     
   if ((segundo==1 || segundo==21 || segundo==31 || segundo==41 || segundo==51 || segundo==10) && bandera2==0){
     dmd.clearScreen(true);
     bandera2=1;
   }
   else if(segundo==11 && bandera2==1){
      dmd.clearScreen(true);
      bandera2=0; 
   }
   else if(segundo!=1 && segundo!=11 && segundo!=21 && segundo!=31 && segundo!=41 && segundo!=51 && segundo!=10 && bandera2==1){
     bandera2=0; 
   }
   
   if( Serial.available()>0 ){       
      val[i]=Serial.read();  
      i++;
    }
    else{
      i=0;
    }
    
    ////////// IGUALAR EL RELOJ AL GPS /////////////////
    if (val[49]=='A'){   
        buffer_hora=(int)(val[39]);
        hora2=((buffer_hora-48)*10+((int)(val[40])-48))-5;
        if(hora2<0){
          hora2=hora2+24;
        }
        else{
          hora2=hora2;
        }
        buffer_minuto=(int)(val[41]);
        minuto2=(buffer_minuto-48)*10+((int)(val[42])-48);
        buffer_segundo=(int)(val[43]);
        segundo2=((buffer_segundo-48)*10+((int)(val[44])-48));
        setTime(hora2,minuto2,segundo2,5,9,2014);
        segundo=segundo2;
        mili_segundo=0;
        for (j=0;j<200;j++){
          val[j]=0;
        }     
  }
  
}

  
   
   


