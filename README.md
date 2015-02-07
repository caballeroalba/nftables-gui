# nftables-gui
Interfaz grafica para nftables escrita en c usando ncurses

Nftables es un nuevo framework que sustituye al antiguo iptables.
Este nuevo software aun no esta desarrollado al 100% pero ya es operativo
en gran parte de sus funciones, tenemos la problemática de la implantación,
que aunque se incluye desde el kernel 3.13, las personas aun no están acostumbra
das a su uso y por tanto siguen usando iptables o en su defecto la nomenclatura
de sus reglas.
En pocas palabras:

    Esta disponible desde el kernel 3.13 en adelante
    Trae una la nueva utilidad nft con una sintaxis diferente a la de iptables.
    Tiene compatibilidad con las instrucciones de iptables.
    Infraestructura genérica de conjuntos que permite construir mapas entre
    asignaciones y acciones para mejorar las búsquedas.
    Aún esta bajo desarrollo.
    Las diferencias con iptables son notables, estas serían las proporcionadas
    por su pagina oficial:

        Maquina de pseudo-estados en el espacio del kernel, nftables interpreta
        el mapa de reglas proporcionadas por el usuario (con la nueva sintaxis)
        , esta se compila y entra en la maquina de estados como bytecode y esta
        misma la transfiere al kernel por la api Netlink’s de netfilter.
        La nueva sintaxis permite tener un conjunto de reglas.
         Se puede elegir que selectores de paquetes de todos los protocolos existentes
        puede usar la maquina de pseudo-estados, esto significa que no necesitamos
        una extensión en espacio de kernel para cada protocolo si queremos soportarlo.
        Esto supone una ventaja, ya que no necesitamos actualizar el kernel para
        obtener nuevas características y esto a sido diseñado para trabajar en
        el espacio lógico de usuario.
        Interfaz unificada para reemplazar las utilidades iptables/ip6tables/arptables/ebtables

La solución aporta consistirá en una interfaz gráfica escrita en c y usando
ncurses para poder manejar nftables y que de esta manera sea mas fácil
su uso.

Esto implica una mejora sustancial para aquellas personas que quieran dejar
de la iptables y puedan utilizar nftables con todas la características
nuevas y así poder sacar mas rendimiento a los sistemas de cortafuegos
que usen en la actualidad.
La interfaz gráfica deberá de proporcionar una implementación de la utilidad
nft para su uso amigable y por tanto su curva de aprendizaje sera menor,
esto incluye que pueda explorar todas las posibilidades de la utilidad
nft, mejorar tiempos de configuración, etc.


BLOG: http://caballeroalba.cf/wordpress/
