Diamond Square terrain generator
================================
This plugin is tested to work on 3ds Max 2014.
The project files use Visual Studio 2012, but the compiler is set to the VS
2010 compiler. The project will *not* compile with the 2012 compiler; 3ds Max
2014 plugins must be compiled with the 2010 compiler. My build environment was
Windows 8.1; you may have to tinker to get compilation to work otherwise.

Most of the interesting things are in `Grid.cpp`, which generates terrain
using the diamond-square algorithm over a grid.

The plugin will generate UV coordinates covering the grid; if you want a
different mapping, apply the UVW Mapping modifier on top of this object.

License
=======
The MIT License (MIT)

Copyright (c) Steven Dao 2014

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
