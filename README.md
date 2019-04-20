# PPM Contour Generator
Generating contour of [PPM](https://en.wikipedia.org/wiki/Netpbm_format) image. 

Supports P3 and P6 format. In P6, colors can be represented as 1-byte or 2-byte value (both are supported).

## Example
![valve](https://github.com/Lvameht/INNO2019OMP_TrialAssignment/blob/master/readme_pics/valve.png)
![valve_c](https://github.com/Lvameht/INNO2019OMP_TrialAssignment/blob/master/readme_pics/valve_cont.png)

More can be found [here](https://github.com/Lvameht/INNO2019OMP_TrialAssignment/tree/master/readme_pics).

## Running
There are 2 versions: command-line and GUI that runs command-line app

Run `make` to compile both of them. Note, that GUI requires `qt5-default` package installed. Run `make` in `cli` directory if you want only CLI to be compiled.

Run `make run` to open GUI application.

Run `./cli/cont --help` to see help of command-line app. 

## CLI
Usage: `cont SOURCE DESTINATION [-t threads_n] [--abs] [-i DEST_IMAGE_H DEST_IMAGE_V] [-f FORMAT]`

`SOURCE` and `DESTINATION` - path to input PPM image and desired path for saving contour picture.

`-t threads_n` - set threads number (available multithreaded operations: rgb->gray, sobel). Default - 1.

`--abs` - use absolute value for calculating gradient approximation instead of square root (faster, but might be less accurate)

`-i DEST_IMAGE_H DEST_IMAGE_V` - this will save intermediately generated images (results of vertical and horizontal convolutions) to the specified destinations

`-f FORMAT` - set the desired output format, e.g. `-f P3` or `-f P6`. By default, the source image's format is kept.


## GUI
![GUI](https://github.com/Lvameht/INNO2019OMP_TrialAssignment/blob/master/readme_pics/cat_gui.png)

Open the file by `...` button. Application can view any images, but the application can generate the contour of **PPM images only**.

You can zoom the image by **scrolling mouse wheel** as well as pan it using your mouse.

GUI allows you to set all the settings that CLI provide, except the destination path. For simplicity, 
you need only set the filename **postfix**, so that the destination image will be stored in the same folder 
as the original, and will have a name like `ORIGINALNAME_POSTFIX.ppm`

Hover your mouse arrow to see tip texts.

![](https://github.com/Lvameht/INNO2019OMP_TrialAssignment/blob/master/readme_pics/tips.png)

Click `Generate Contour` once all settings are good.

Please wait until generation is finished.

Once it is done, you will see a window containing running time information:

![](https://github.com/Lvameht/INNO2019OMP_TrialAssignment/blob/master/readme_pics/benchmarks.png)

And you will see the generated contour image in the main window.
