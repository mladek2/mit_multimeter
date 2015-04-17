/* 
 * File:   lcd.h
 * Author: student
 *
 * Created on 10. duben 2015, 11:17
 */

#ifndef LCD_H
#define	LCD_H

#define LCD_DISPLAY_CLEAR 0b1
#define LCD_RETURN_HOME 0b11
#define LCD_ENTRY_MODE_SET 0b110
#define LCD_DISPLAY_ON_OFF_CONTROL 0b1111
#define LCD_CURSOR_OR_DISPLAY_SHIFT 0b11100
#define LCD_FUNCTION_SET 0b111000
#define LCD_SET_CGRAM_ADDRESS 0b1000000
#define LCD_SET_DDRAM_ADDRESS 0b10000000
#define LCD_RS RE0
#define LCD_RW RE1
#define LCD_DATA PORTD
#define LCD_EN RE2
#define _XTAL_FREQ 3276800
/*
 *
 */

void lcd_cmd(unsigned char cmd){
    LCD_RS = LCD_RW = 0;
    LCD_EN=1;
    LCD_DATA = cmd;
    LCD_EN=0;

    if(cmd==LCD_DISPLAY_CLEAR||cmd==LCD_RETURN_HOME){
    __delay_us(1530);//lcd_wait_us(1530);
    }else{
    __delay_us(39);// lcd_wait_us(39);
    }
    //kdy? cmd = clear nebo return tak ?ekáme 1530us jinak ?ekáme 39us
}

void lcd_data(unsigned char znak){
     LCD_RW = 0;
     LCD_RS =1;
    LCD_EN=1;
    LCD_DATA = znak;
    LCD_EN=0;
    __delay_us(43);
    /*if(cmd==LCD_DISPLAY_CLEAR||cmd==LCD_RETURN_HOME){
    __delay_us(1530);//lcd_wait_us(1530);
    }else{
    __delay_us(39);// lcd_wait_us(39);
    }*/
    //kdy? cmd = clear nebo return tak ?ekáme 1530us jinak ?ekáme 39us
}

/*void lcd_wait_us(unsigned short pocet){

    //posun pocet 2b vpravo
    for(unsigned short i=0;i<pocet/4;i++){
        asm("NOP");
    }
}*/


/*void lcd_wait_ms(unsigned char pocet){
    for(unsigned char i=0;i<pocet;i++) lcd_wait_us(1000) ;
}*/



void lcd_init(void){
    //LCD_POWER=ON;
    //LCD_POWER > 4.5
    __delay_ms(30);//lcd_wait_ms(30);
    lcd_cmd(LCD_FUNCTION_SET);
    lcd_cmd(LCD_DISPLAY_ON_OFF_CONTROL);
    lcd_cmd(LCD_DISPLAY_CLEAR);
    lcd_cmd(LCD_ENTRY_MODE_SET);


}



void lcd_def_char (unsigned char ascii_code,unsigned char znak[]){
    ascii_code=ascii_code&0b111;
    ascii_code=ascii_code << 3;
    lcd_cmd(LCD_SET_CGRAM_ADDRESS|ascii_code);
    for(unsigned char i=0;i<8;i++){
        lcd_data(znak[i]);

    }
   lcd_cmd(LCD_SET_DDRAM_ADDRESS);


}
void lcd_write(unsigned char radek, unsigned char sloupec, char retez[])
{
    radek=radek&0b1;
    sloupec=sloupec%40;
    //nastavíme pozici kurzoru
    if(radek){
        sloupec+=0x40;
    }
    lcd_cmd(LCD_SET_DDRAM_ADDRESS|sloupec);
    for(unsigned char i=0;retez[i];i++){
        lcd_data(retez[i]);

    }


}

void lcd_write_c(unsigned char radek, unsigned char sloupec, const char retez[])
{
    radek=radek&0b1;
    sloupec=sloupec%40;
    //nastavíme pozici kurzoru
    if(radek){
        sloupec+=0x40;
    }
    lcd_cmd(LCD_SET_DDRAM_ADDRESS|sloupec);
    for(unsigned char i=0;retez[i];i++){
        lcd_data(retez[i]);

    }


}

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

