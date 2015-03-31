# nftables-gui
Nftables-gui es una interfaz gráfica para nftables[1] escrita en c usando ncurses para facilitar el uso de la herramienta nft.

Forma parte del proyecto de fin de carrera, por lo cual el estado de este software se seguirá

desarrollando a lo largo del curso 14/15 hasta junio. Lo cual no quiere decir que no se seguirá después.


Para poder compilar es necesario tener los siguientes requisitos :


La librería de ncurses (disponible desde los repositorios de tu distribución)


linux kernel superior al 3.13


nftables instalado en el sistema

http://wiki.nftables.org/wiki-nftables/index.php/Building_and_installing_nftables_from_sources

Una vez hecho, basta con ejecutar los siguentes comandos

./configure

make

Esto generará el ejecutable nftables-gui el cual necesita permisos de root para poder ejecutarse

Como nftables-gui esta en aún en un estado alfa, nftables-gui aún no puede leer las reglas actuales 

en el sistema, por lo cual, antes de empezar la ejecución principal, nftables-gui borra las reglas 

actuales para que no interfieran en el correcto funcionamiento de la aplicación. Por lo tanto

Se recomienda guardar las reglas actuales del sistema con los siguientes pasos:

* nft list [nombre_tabla] > fichero.txt

Y para restaurar:

* nft -f fichero.txt



BLOG: http://caballeroalba.cf/wordpress/
[1] http://www.netfilter.org/projects/nftables/index.html
