![image](https://user-images.githubusercontent.com/46074546/55914816-c5c7e000-5bf0-11e9-88c1-2579aeb16eec.png)

Build instructions (Windows only):
```
windres -i resources.rc -o resources.o
gcc main.c resources.o -lgdi32 -lcomctl32 -s
```
