CC=g++
PARAM=-g

BinaryTreeNode: BinaryTreeNode.cpp
	$(CC) -std=c++11 $(PARAM) -o $@ $^

.PHTOY:clean
clean:
	rm -f *.o BinaryTreeNode
