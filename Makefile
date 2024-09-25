all:  calculator.c go.c user.c
	gcc calculator.c  -o calc
	gcc user.c -o user
	gcc go.c -o go

clean:
	rm -f calc user go