/*
Implement the "paint fill" function that one might see on many image editing pro-
grams. That is, given a screen (represented by a 2-dimensional array of Colors), a
point, and a new color, fill in the surrounding area until you hit a border of that color.
*/

#include <iostream>

static const int N = 5; // screen dimensions

struct Color
{
    char R, G, B;
    Color(char r, char g, char b) : R(r), G(g), B(b) {}
    bool operator==(Color &c2)
    {
        return (R == c2.R && G == c2.G && B == c2.B);
    }
    bool operator!=(Color &c2)
    {
        return !(*this == c2);
    }
};

void PrintScreen(Color screen[N][N])
{
    for (int r = 0; r < N; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            // '+' promotes the char to a printable number so we can print it
            std::cout << +screen[r][c].R << +screen[r][c].G << +screen[r][c].B << " ";
        }
        std::cout << "\n";
    }
}

// Solution: Expand out from original pixel recursively.  We stop when we hit a
// different colored pixel from the original or we leave the screen.
void PaintFillRecursive(Color screen[N][N], int x, int y, Color orig, Color newer)
{
    if (x < 0 || x >= N || y < 0 || y >= N) return;
    if (screen[x][y] != orig) return;
    
    screen[x][y] = newer;
    PaintFillRecursive(screen, x+1, y, orig, newer);
    PaintFillRecursive(screen, x-1, y, orig, newer);
    PaintFillRecursive(screen, x, y+1, orig, newer);
    PaintFillRecursive(screen, x, y-1, orig, newer);
}

void PaintFill(Color screen[N][N], int x, int y, Color newer)
{
    Color orig = screen[x][y];
    if (orig == newer) return;
    PaintFillRecursive(screen, x, y, orig, newer);
}

int main()
{

    Color screen[N][N] = {
        {Color(0,0,0), Color(0,0,0), Color(0,0,0), Color(0,0,0), Color(0,0,0)},
        {Color(0,0,0), Color(1,0,0), Color(1,0,0), Color(1,0,0), Color(0,0,0)},
        {Color(0,0,0), Color(1,0,0), Color(0,0,0), Color(1,0,0), Color(0,0,0)},
        {Color(0,0,0), Color(1,0,0), Color(1,0,0), Color(1,0,0), Color(1,0,0)},
        {Color(1,0,0), Color(0,0,0), Color(0,0,0), Color(0,0,0), Color(1,0,0)}};

    PrintScreen(screen); std::cout << "\n";
    PaintFill(screen, 1, 2, Color(0, 1, 0));
    std::cout << "Use paint fill function on pixel (1,2):\n";
    PrintScreen(screen);
}
