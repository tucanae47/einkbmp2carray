# Waveshare generate 7 color bmp image with floydSteingberg Dithering. 

To generate the bmp [imagemagick](https://imagemagick.org/index.php) is required installed in your computer, the process here is an alternative to [waveshare](https://www.waveshare.com/wiki/5.65inch_e-Paper_Module_(F)_Manual#Picture_Production) Picture production process in windows, and is also based on the source provided by waveshare

`convert xc:red xc:white xc:black xc:green xc:orange xc:blue xc:yellow +append palette.gif`

`convert image.png -dither FloydSteinberg -define dither:diffusion-amount=99% -remap palette.gif image.bmp`

## Usage
`./scripts/dithering.sh image.png image.bmp`

## Building Manually

```bash
❯ rm -rf build && mkdir build
❯ cd build
❯ cmake ..
❯ make && make install
❯ cd ..
```

## Running, generate byte array 

Without arguments, it prints out its usage:

```bash
❯ bin/bmp2arr image.bmp image.c
```

