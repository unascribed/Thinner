# Thinner
Simple tool that removes a given color from an image. Written to remove the
red background from my avatar. Inspired by the Grim Color Reaper plugin for
paint.net, and is effectively a port of it from C# to C.

Fair warning: I do not program in C very often. This code may be horrid.

This program is only confirmed to compile on Linux.

## Usage
`thinner <color> <input> [output]`

## Examples
Remove the color red (#FF0000) from foo.png and write it to bar.png:  
`thinner FF0000 foo.png bar.png`

Remove the color green (#00FF00) from baz.png and overwrite it:  
`thinner 00FF00 baz.png`

## Compilation
`make`

You must have the DevIL headers installed.
