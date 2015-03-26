# nftables-gui
Nftables-gui es una interfaz gráfica para nftables* escrita en c usando ncurses para facilitar el uso de la herramienta nft.


Para poder compilar es necesario tener los siguientes requisitos :
La librería de ncurses (disponible desde los repositorios de tu distribución)
kernel superior al 3.13
nftables instalado en el sistema http://wiki.nftables.org/wiki-nftables/index.php/Building_and_installing_nftables_from_sources

Una vez hecho, basta con ejecutar los siguentes comandos

./configure

make

Esto generará el ejecutable nftables-gui el cual necesita permisos de root para poder ejecutarse



BLOG: http://caballeroalba.cf/wordpress/

* http://www.netfilter.org/projects/nftables/index.html
