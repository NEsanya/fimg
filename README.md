# FIMG
FIMG is [suckless](https://suckless.org/) like file manager, inspired by [vifm](https://vifm.info/).

# Building
Install [ncurses](https://invisible-island.net/ncurses/#downloads) library to your sistem, and then run:

``` sh
$ git clone https://github.com/nesanya/fimg.git
$ cd fimg
$ make # You can use -jn flag to multithread compiling
$ ./fimg
```

# Configurate
Because it's suckless like (see [suckless philosophy](https://suckless.org/philosophy/)), there is not configuration file. You can use patches and `config.h` to change fimg. `config.h` created automaticly by `config.def.h` when you make fimg.
