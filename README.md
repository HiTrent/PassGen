![Untitled](https://user-images.githubusercontent.com/46074546/57019081-1057dd80-6c2e-11e9-8d6f-44a05762b15a.png)

Build instructions (Windows only):
```
windres -i resources.rc -o resources.o
gcc main.c resources.o -lgdi32 -lcomctl32 -s
```
