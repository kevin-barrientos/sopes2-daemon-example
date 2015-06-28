# sopes2-daemon-example

### Acerca de
Este es un ejemplo de un demonio (daemon) para sistemas linux. Para el cual se ha elaborado un archivo de configuración, el cual sera responsable de iniciar el servicio al momento de arrancar el sistema operativo.

###Instalación
  - Para correr el proyecto primero debemos de compilar el programa **ds201212631.c**, otorgale permisos y situarlo en el directorio **/usr/sbin/**
```sh
gcc -o ds201212631 ds201212631.c
chmod 751 ds201212631
mv ds201212631 /usr/sbin/
```
  - Ahora debemos de manipular el archivo de configuración **ini-ds201212631**
```sh
chmod 751 ini-ds201212631
mv ini-ds201212631 /etc/init.d/
```
  - Por último debemos de generar los links simbólicos en los directorios **/etc/rcN.d**  hacia **/etc/init.d/ini-ds201212631**
  - **Nota: el siguiente comando genera los links automáticamente dependiendo de la configuración del archivo sin embargo el comando puede variar segun la distribución linux. En este caso se está trabajando sobre Ubuntu 12.10. **
```sh
cd /etc/init.d/
update-rc.d ini-ds201212631 defaults
```
### Configuración 
El servidor por defecto escucha en el puerto 5000 sin embargo se puede modificar dicho puerto de la siguiente manera:
```sh
mkdir /etc/ds201212631/port.conf
nano /etc/ds201212631/port.conf
# Escribimos el puerto que se desea por ejemplo 8080 y guardamos
service ini-ds201212631 restart
```
