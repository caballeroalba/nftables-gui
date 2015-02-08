all: nftables-gui

nftables-gui: nftables-gui
	gcc main.c -o nftables-gui -lncurses -lsqlite3


clean:
	rm nftables-gui
