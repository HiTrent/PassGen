![ ](https://user-images.githubusercontent.com/46074546/55676109-7c1c8400-58d6-11e9-98aa-f42d61ae2fea.png)

Build instructions (Windows only):
```
windres -i resources.rc -o resources.o
gcc main.c resources.o -lgdi32 -lcomctl32 -s
```
