rpn: src/rpn/rpn.c
	$(CC) src/rpn/rpn.c -o rpn

.PHONY: clean
clean:
	rm rpn