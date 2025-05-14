#include <own_stdio.h>

LiquidCrystal_I2C lcd(DISPLAY_ADRESS, DISPLAY_COLS, DISPLAY_ROWS);

static FILE stream = {0};

int own_putchar(char c, FILE *stream)
{
    Serial.write(c);
    return 0;
}

int own_getchar(FILE *stream)
{
    while (!Serial.available());
    return Serial.read();
}

int own_lcd_putchar(char ch, FILE *stream)
{
    static uint8_t currentRow = 0;

    if (ch == '\f')
    {
        lcd.clear();
        currentRow = 0;
        lcd.setCursor(0, currentRow);
        return 0;
    }
    if (ch == '\n')
    {
        lcd.setCursor(0, ++currentRow);
        if(currentRow > 3)
        {
            currentRow = 0;
        }
        return 0;
    }
    lcd.write(ch);
    return 0;
}

void own_stdio_setup()
{
    Serial.begin(BAUD_RATE);
    
    lcd.init();
    lcd.backlight();
    lcd.clear();

    fdev_setup_stream(&stream, own_lcd_putchar, own_getchar, _FDEV_SETUP_RW);
    stdin = stdout = &stream;
}