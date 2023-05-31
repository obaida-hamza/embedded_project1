#include "mbed.h"
//#include "mbed2/299/TARGET_KL25Z/TARGET_Freescale/TARGET_KLXX/TARGET_KL25Z/PinNames.h"
//Create a BusOut connected to the 7 segments
BusOut Disp1(PTC6,PTC5,PTC16,PTA16,PTA17,PTC10,PTC11,PTC13);  //Define many output pins:  dpGFEDCBA

//Create a DigitalOut connected to 7-seg anode
DigitalOut vdd(PTC17); 

void setvdd(); // to set CA to 3.3V
int numb=0;
int numb1=0;
int op=0;
int numb2=0;
int res=0;


//.............................................................
//Display the digit on 7-seg  dpGFEDCBA
void key_1();
void key_2() ;
void key_3() ;
void key_4() ;
void key_5();
void key_6() ;
void key_7();
void key_8() ;
void key_9() ;

void key_equal();

//Display nothing on 7-seg
void key_nope(); 



//..........................................................................
//create keypad 8 pins
//Create DigitalIns to probe rows
DigitalIn row1(PTE5, PullUp);	// row1 Input
DigitalIn row2(PTE4, PullUp);	// row2 Input
DigitalIn row3(PTE3, PullUp);	// row3 Input
DigitalIn row4(PTE2, PullUp);	// row4 Input

//Create DigitalOuts to scan columns
DigitalOut col1(PTB11);// col1 output
DigitalOut col2(PTB10);// col2 output
DigitalOut col3(PTB9);//  col3 output
DigitalOut col4(PTB8);//  col4 output


//............................................................................
//Pull all columns Hi
void setColsHi();
//Pul a single column Lo
void setCol1Lo();
void setCol2Lo();
void setCol3Lo();
void setCol4Lo() ;


void write_7_seg();
//.........................................................
// Key scan function
void keyscan() ;
void calculator ();




//.............................................
// main program routine
int main()  {
    setvdd();  // to set CA to 3.3V
    while (1) {    
        calculator();
        //keyscan();  //only scanes keypad and assign pressed number to global variable numb
        
        wait(0.1);
        
        

    }
}





void setvdd() // to set CA to 3.3V
{
vdd=1; //Set CA On.
}

//.............................................................
//Display the digit on 7-seg  dpGFEDCBA
void key_0()  {
      Disp1=0xC0;      
}
void key_1()  {
      Disp1=0xF9;       //0xF9=11111001 =dpGFEDCBA
}
void key_2()  {
      Disp1=0xA4;
}
void key_3()  {
      Disp1=0xB0;
}
void key_4()  {
      Disp1=0x99;
}
void key_5()  {
      Disp1=0x92;
}
void key_6()  {
      Disp1=0x82;
}
void key_7()  {
      Disp1=0xF8;
}
void key_8()  {
      Disp1=0x80;      //0x80=10000000,  so only dp is OFF.
}
void key_9()  {
      Disp1=0x90;       //0x90=10010000,  so only E dp are FF.
}

void key_pluse()  {         //+
      Disp1=0xB9;       
}
void key_minus()  {
      Disp1=0xBF;       //-
}
void key_F()  {         // false
      Disp1=0x8E;       
}
void key_A()  {         //+
      Disp1=0x08;       
}
void key_B()  {
      Disp1=0xC6;       //-
}
void key_equal()  {
      Disp1=0xB7;       //-
}

//Display nothing on 7-seg
void key_nope()  {
      Disp1=0xFF;
}




//............................................................................
//Pull all columns Hi
void setColsHi() {
        col1=1;
        col2=1;
        col3=1;
        col4=1;
}
//Pul a single column Lo
void setCol1Lo() {
        col1=0;
        col2=1;
        col3=1;
        col4=1;
}
void setCol2Lo() {
        col1=1;
        col2=0;
        col3=1;
        col4=1;
}
void setCol3Lo() {
        col1=1;
        col2=1;
        col3=0;
        col4=1;
}
void setCol4Lo() {
        col1=1;
        col2=1;
        col3=1;
        col4=0;
}

//.........................................................
// Key scan function only scanes keypad and assign pressed number to global variable numb
void keyscan() {
    setColsHi();        //Pull all columns Hi
    wait(0.1);
    for(int i=0 ; i<3 ;i++)
    {
    while(1)
    {
        setCol1Lo();        //Pul column 1 Lo
        wait(0.2);
        if (row1==0) { numb= 1;  break;}       //1
        if (row2==0) { numb= 4;  break;}       //4
        if (row3==0) { numb= 7;  break;}       //7
        if (row4==0) { numb= 100;  break;}       //F
        setCol2Lo();        //Pul column 2 Lo
        wait(0.2);
        if (row1==0) { numb= 2; break;}        //2
        if (row2==0) { numb= 5; break;}        //5
        if (row3==0) { numb= 8; break;}        //8
        if (row4==0) { numb= 0; break;}        //0
        setCol3Lo();        //Pul column 3 Lo
        wait(0.2);
        if (row1==0) { numb= 3; break;}        //3
        if (row2==0) { numb= 6; break;}       //6
        if (row3==0) { numb= 9; break;}        //9
        if (row4==0) { numb= 100; break;}        //E
        setCol4Lo();        //Pul column 4 Lo
        wait(0.2);
        if (row1==0) { numb= 150; break;}         //A=+
        if (row2==0) { numb= 200; break;}         //B=-
        if (row3==0) {numb= 100; break;}         //C
        if (row4==0) {numb= 100; break;}         //D
    }
    }
    wait(0.1);
    write_7_seg(); // display the pressed number
}


void write_7_seg()   // display the assigned number numb 
{
     
        if (numb==0) {key_0(); }            //0
        else if (numb==1) {key_1(); }       //1
        else if (numb==2) {key_2(); }       //2
        else if (numb==3) {key_3(); }       //3
        else if (numb==4) {key_4(); }       //4
        else if (numb==5) {key_5(); }        //5
        else if (numb==6) {key_6(); }        //6
        else if (numb==7) {key_7(); }        //7
        else if (numb==8) {key_8(); }        //8
        else if (numb==9) {key_9();  }       //9
        else if (numb==150) {key_pluse();  }        //+
        else if (numb==200) {key_minus();  }        //-
        else if (numb==100) {key_F();  }        //unused botton 
        else if (numb==101) {key_A();  }  
        else if (numb==102) {key_B();  }    
        else if (numb==103) {key_equal();  }        
}



void calculator()
{
    for (int i=0 ;i<3 ; i++) // call keyscan function  3 times , to assign  numb1  op nunb2
    {
        keyscan();
        //write_7_seg();  //display pressed number
        if (i==0 ){numb1= numb; } // assign first value to numb1
        else if  (i==1){ op=numb; }// assign 150=+ or 200=- value to op
        else if  (i==2){ numb2= numb;}// assign 2nd value to numb2
    }
    //numb=103;
    //write_7_seg();
    //wait(0.5);
    
    
    if (op == 150) {res = numb1 + numb2;}// if op = 150 ==>  operation=+
    else if (op == 200) {res = numb1 - numb2 ;}      // if op = 200 ==>  operation=-
    else {numb=100;}

    if (res <10  && res >0  ){numb=res;}   // check if result is betwwn 0 and 9
    else if  (res >=10 ) {numb =101; }//  if result is above 9  ==> numb =10=A =above
    else if  (res <0 ) { numb =102; }//  if result is below 0  ==> numb =11=B =bellow
    else{numb=100;}
   
    
    for (int i=0 ;i<5 ; i++) // display result with blinking
    {  
        key_nope();
        wait(1);       
        write_7_seg();
        wait(1);
        
    }
}


