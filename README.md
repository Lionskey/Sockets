This project was a fun way to learn C in highschool. It is not operationally sound, do not use it. 

## Dependencies
mingw-w64 (For cross compilation to Windows)

gcc

make

objdump (For shellcode generation)

## Installation 

1. Clone the repository
``` 
git clone https://github.com/Lionskey/HeadHunter.git
```

2. Change directory to source tree
``` 
cd HeadHunter/
```

3. Install HeadHunter binary and payload source
```
make && sudo make install
```

4. Enjoy
``` 
headhunter --help
```
