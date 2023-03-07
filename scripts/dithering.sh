#! /usr/bin/bash
convert xc:red xc:white xc:black xc:green xc:orange xc:blue xc:yellow +append palette.gif 
convert $1 -dither FloydSteinberg -define dither:diffusion-amount=99% -remap palette.gif $2