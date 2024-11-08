TARGET = ac.exe

CFLAGS = -Wall -O3 -march=native -mtune=native -funroll-loops -fomit-frame-pointer -flto

SRC = ac.c

$(TARGET): $(SRC)
	gcc $(CFLAGS) $(SRC) -o $(TARGET) -luser32

clean:
	rm -f $(TARGET)

#gcc -Wall -O3 -march=native -mtune=native -funroll-loops -fomit-frame-pointer -flto ac.c -o ac.exe -luser32