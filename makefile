CC:=gcc
MTM_DIR:=/home/mtm/public/2122b/
HW_DIR:=$(MTM_DIR)ex1/
TOOL:=tool/
OBJS=RLEList.o $(TOOL)AsciiArtTool.o $(TOOL)main.o
EXEC=AsciiArtTool
DEBUG_FLAG:=-DNDEBUG#assign -g for debug, or -DNDEBUG to turnoff assert
HW_FLAG=-I/home/mtm/public/2122b/ex1 -Itool
COMP_FLAG=-std=c99 -g -Wall -pedantic-errors -Werror $(HW_FLAG)

$(EXEC) : $(OBJS)
		$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $(OBJS) -o $@
RLEList.o : RLEList.c $(HW_DIR)RLEList.h
		$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
$(TOOL)AsciiArtTool.o : $(TOOL)AsciiArtTool.c $(TOOL)AsciiArtTool.h $(HW_DIR)RLEList.h
		$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $(TOOL)AsciiArtTool.o
$(TOOL)main.o : $(TOOL)main.c $(TOOL)AsciiArtTool.h $(HW_DIR)RLEList.h
		$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $(TOOL)main.o
clean:
	rm -f $(OBJS) $(EXEC)
