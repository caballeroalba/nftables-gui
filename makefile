all: nftables-gui

nftables-gui: nftables-gui
	gcc main.c -o nftables-gui -lncurses -lsqlite3 -lform


clean:
	rm nftables-gui
