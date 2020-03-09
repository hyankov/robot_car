/*
    -------------------------------------------------------
    The module which controls the display of the robot car.
    Note: Still work in progress!
    -------------------------------------------------------

    See: https://github.com/olikraus/u8glib
    See: http://www.dsdtech-global.com/2018/05/iic-oled-lcd-u8glib.html
    See: http://henrysbench.capnfatz.com/henrys-bench/u8glib-graphics-library-user-guide/u8glib-arduino-oled-tutorial-1-hello-world-on-steroids
*/

// 2nd party includes
#include "Arduino.h"

// 1st party includes
#include "Pins.hh"      // Pin layout. Set pins according to your wiring
#include "Settings.hh"  // Include settings
#include "Display.hh"   // Responsible for display

// 3rd party includes
#include <U8glib.h>

/* -----------------------
    Private methods
----------------------- */

// For 0.91" (128 * 32)
U8GLIB_SSD1306_128X32 _u8g(U8G_I2C_OPT_NONE);
String _displayMsg = "";

void _draw()
{
    _u8g.setFont(u8g_font_unifont);
    _u8g.setPrintPos(0, 10);
    _u8g.print(_displayMsg);
}

/* -----------------------
    Public methods
----------------------- */

void setupDisplay()
{
    // flip screen, if required
    _u8g.setRot180();

    // assign default color value
    if (_u8g.getMode() == U8G_MODE_R3G3B2)
    {
        _u8g.setColorIndex(255); // white
    }
    else if (_u8g.getMode() == U8G_MODE_GRAY2BIT)
    {
        _u8g.setColorIndex(3); // max intensity
    }
    else if (_u8g.getMode() == U8G_MODE_BW)
    {
        _u8g.setColorIndex(1); // pixel on
    }
    else if (_u8g.getMode() == U8G_MODE_HICOLOR)
    {
        _u8g.setHiColorByRGB(255, 255, 255);
    }
}

void loopDisplay()
{
    _u8g.firstPage();
    do { _draw(); } while (_u8g.nextPage());
}

void displayMsg(String msg)
{
    _displayMsg = msg;
}