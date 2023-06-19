# Building H4 from individual parts

## Printed circuit boards

H4 consists of 2 PCBs - main one with ESP32 and keypad with push switches.

[Gerber, BOM, pick and place files](https://github.com/kachurovskiy/nanoels/tree/main/h4/pcbs) can be found in the `pcbs` folder. EasyEDA source files are also provided.

An edit I would make for the next batch is remove the `R7` resistor as it makes the buzzer quieter making it hard to hear when the lathe is running.

Additionally, the following parts need to be ordered as they're not included in the PCB BOM:

- https://www.lcsc.com/product-detail/_XFCN-_C2915256.html (2x)
- https://www.lcsc.com/product-detail/_XFCN-_C2889983.html (2x)
- https://www.lcsc.com/product-detail/_DIBO-_C395832.html (5x)

## Front panel

I ordered the front panels on https://www.jrpanel.com/panel/buy/ with the following settings:

![image](https://github.com/kachurovskiy/nanoels/assets/517919/b5996640-de97-49c5-95d1-c8edcc0a8471)

Provide them with [h4-go-1.png](https://github.com/kachurovskiy/nanoels/blob/main/h4/graphics/h4-go-1.png) as a design guidance and [h4-go-2.pdf](https://github.com/kachurovskiy/nanoels/blob/main/h4/graphics/h4-go-2.pdf) for printing purposes.

If you'd like to make modifications to the panel design, open [h4.fig](https://github.com/kachurovskiy/nanoels/blob/main/h4/graphics/h4.fig) using [figma.com](https://www.figma.com) editor.

## Rear sticker

I ordered the rear stickers on [Sticker Mule](https://www.stickermule.com/de/products/rechteck-sticker) using [h4-labels.pdf](https://github.com/kachurovskiy/nanoels/blob/main/h4/graphics/h4-labels.pdf) in 75x30mm size. It's doubled up due to their minimum size requirements. 

## Case

Plastic case consists of front and back piece which can be found in the [case folder](https://github.com/kachurovskiy/nanoels/tree/main/h4/case) as `STL` files ready for printing. If you'd like to modify the models, FreeCAD source file is also provided.

Front piece is designed to accept nine M3 threaded inserts, each 4mm long (4 to connect the back piece, 5 to hold the keypad). You would also need 9 M3 screws, each 8mm long.

Back piece accepts two M5 threaded inserts, each 5mm long with 8mm outside diameter.

![h4 inserts](https://github.com/kachurovskiy/nanoels/assets/517919/cbd8e03d-1b62-4468-b9c5-03e033c54698)

An optional small plastic shim model is also provided that is intended to be placed between the display and the keypad PCB to make the top row of buttons supported from the back.

Prints can also be ordered online e.g. on https://3d.jlcpcb.com/3d-printing-quote.

## Display

5V [HD44780 2004 LCD display](https://www.azdelivery.de/en/products/copy-of-hd44780-2004-lcd-display-bundle-4x20-zeichen) or similar is required. 16-pin 2.54mm header is used to connect it to the main PCB.
