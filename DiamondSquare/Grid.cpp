#include "Grid.h"


Grid::Grid(float width, float length, int widthSegs, int lengthSegs)
    : _width(width), _length(length), _widthSegs(widthSegs), _lengthSegs(lengthSegs), _widthVtex(widthSegs + 1), _lengthVtex(lengthSegs + 1)
{
    _vertices = new float[_widthSegs * _lengthSegs];
}

Grid::Grid(float width, float length, int widthSegs, int lengthSegs, float* vertexHeights)
    : _width(width), _length(length), _widthSegs(widthSegs), _lengthSegs(lengthSegs), _widthVtex(widthSegs + 1), _lengthVtex(lengthSegs + 1)
{
    _vertices = vertexHeights;
}

Grid::~Grid(void)
{
    delete [] _vertices;
}

float Grid::GetWidth() const
{
    return _width;
}

float Grid::GetLength() const
{
    return _length;
}

int Grid::GetWidthSegs() const
{
    return _widthSegs;
}

int Grid::GetLengthSegs() const
{
    return _lengthSegs;
}

int Grid::GetWidthVertices() const
{
    return _widthVtex;
}

int Grid::GetLengthVertices() const
{
    return _lengthVtex;
}

int Grid::GetTotalVertices() const
{
    return _widthVtex * _lengthVtex;
}

float* Grid::GetVertexHeights() const
{
    return _vertices;
}

void Grid::SetVertexHeightWrap(int u, int v, float height)
{
    u = u % _widthSegs;
    v = v % _lengthSegs;

    *(_vertices + u * _lengthSegs + v) = height;
}

float Grid::GetVertexHeightWrap(int u, int v)
{
    u = u % _widthSegs;
    v = v % _lengthSegs;

    return *(_vertices + u * _lengthSegs + v);
}

void Grid::Clear()
{
    int total = _widthSegs * _lengthSegs;
    for (int i = 0; i < total; i++)
    {
        _vertices[i] = 0.0;
    }
}
