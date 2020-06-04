## How to convert assets (fonts, images, sounds) to binary and load into SDL
1. Download bin2h.exe here: http://www.deadnode.org/sw/bin2h
2. Put your assets in the same folder as bin2h
3. Open cmd terminal
4. Let's say you have **image.png**, and you'd like the binary array output to be called **image** and placed into **image.h**
5. > bin2h image < image.png > image.h
6. Go into **image.h**, copy the array to your code
7. Use the **SDL_RWops** methods to load the array and use it. Look through the code in this project for examples
