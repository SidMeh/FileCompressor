final:
	gcc main.c trie.c sequence.c -o lzw
	gcc huffman.c -o bit_encode1
	gcc stack.c Circular_Queue.c code_tree.c zipper.c -o bit_encode2
	gcc audio.c -o audio_compress -lm
	gcc main_pgm.c functions_pgm.c stack.c max_heap.c linked_list.c -o image -lm
