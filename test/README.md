# Test Utilities

This folder will be used for testing out your applications. It contains a few tools for generating visualizing, and comparing the input/output data for the binaries associated with this project. Following is a short documentation on how to use these tools.


## Input image sets

Here you can find subfolders containing the input images in PPM P3 format. If you want to add your own image set create a subfolder here, and if you are using Git, do not forget to mark it out from `.gitignore`.

## Utility scripts

All scripts are found in the [`scripts`](scripts) folder. We recommend running them from _this_ location (i.e. `<path/to/>il2212-lab/test`), rather from their own folder, so that the generated files do not mix up with the scripts. The following examples will assume that they are executed from the `test` folder, using the current project structure. 

Most scripts are dependent on [ImageMagick](https://www.imagemagick.org/) tools so make sure you have it installed:

	sudo apt install imagemagick

### `ppm2gif`

Converts a set of PPM P3 images found at a given path into a GIF animation.

**Usage:** `ppm2gif PATH`

`PATH` is the relative path to the folder containing PPM images

**Output**: a GIF file in the current folder.

Example:

    ./scripts/ppm2gif test-ppm/
	
### `ppm2h`

Converts a set of PPM P3 images found at a given path into a C header file, imported by your Nios2 MPSoC projects.

**Usage:** `ppm2h PATH`

`PATH` is the relative path to the folder containing PPM images

**Outputs:**: a C header file called `images.h` in the current folder.

Example:

    ./scripts/ppm2h test-ppm/
	
### `execute`

Executes binaries, grabs the required outputs and builds a GIF animation based on the chosen inputs and resulted outputs. 

**Usage:** `ppm2h [-c=COLOR|-a=APP_PATH|-m] PATH`

`PATH` is the relative path to the folder containing PPM images

**Options:**

* `-c= --hide-color=COLOR` : RGB colour value in hexadecimal format, e.g. `fffffff` for white. Default `000000`

* `-a= --app=APP_PATH` : if active, this option executes a NiosII MPSoC app after creating and including a header file from the chosen image set, grabs the output coordinates, and creates a input vs output GIF animation in the current folder. **ATTENTION:** the script expects that yout NiosII MPSoC dumps the debug output into a file called `debug.out` in the same folder, so you need to modify the `run.sh` script accordingly. Also the application needs to be written in such a way that the DEBUG mode prints out coordinates one per line in the following format:

		@coordinate: [X,Y]

* `-m= --model` : if active, this option executes the ForSyDe-Haskell model with the chosen image set, grabs the output coordinates, and creates a input vs output GIF animation in the current folder.

**Outputs:**: if `-m` active, a folder with PPM images and a GIF animation resulting from running the ForSyDe model in the current directory;  if `-a` active, a folder with PPM images and a GIF animation resulting from running the chosen app, in the current directory; 

Example:

    ./scripts/execute -m test-ppm/
    ./scripts/execute -c=1399aa -a=../app/il2212-single-bare/ -m test-ppm/
	

### `compare`

**not yet available** Compares the generated output of the chosen app against the output of the ForSyDe model.
