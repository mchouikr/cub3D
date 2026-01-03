# cub3D

Projet 42 de raycasting en C avec MiniLibX.

## Tutoriel Docker + X11 (macOS)
Objectif: compiler et executer sous Linux tout en affichant la fenetre MLX.

Etapes pour tout demarrer:
1) Construire l'image:
```
docker build -t cub3d .
```
2) Installer XQuartz (si besoin):
```
brew install --cask xquartz
```
3) Autoriser l'ecoute TCP et demarrer XQuartz:
```
defaults write org.xquartz.X11 nolisten_tcp -bool false
killall XQuartz 2>/dev/null || true
open -a XQuartz
sleep 2
```
4) Autoriser le conteneur:
```
DISPLAY=:0 xhost + 127.0.0.1
```
5) Lancer le conteneur avec DISPLAY:
```
docker run --rm -it -e DISPLAY=host.docker.internal:0 -v "$PWD":/workspace cub3d
```
6) Compiler et lancer (dans le conteneur):
```
make
./cub3D maps/ma_map.cub
```

Si besoin, ajouter le socket X:
```
docker run --rm -it -e DISPLAY=host.docker.internal:0 \
  -v /private/tmp/.X11-unix:/tmp/.X11-unix \
  -v "$PWD":/workspace cub3d
```

Linux (X11):
```
xhost +local:
docker run --rm -it -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v "$PWD":/workspace cub3d
```

## Cleaning / Arret
Etapes pour tout arreter et nettoyer:
1) Quitter le conteneur:
```
exit
```
2) Retirer l'autorisation X11:
```
DISPLAY=:0 xhost - 127.0.0.1
```
3) Fermer XQuartz:
```
killall XQuartz
```
4) Revenir a l'option TCP par defaut:
```
defaults write org.xquartz.X11 nolisten_tcp -bool true
```

Note: a la sortie du conteneur, un `make fclean` est lance automatiquement.
Pour le desactiver: `-e CUB3D_AUTO_FCLEAN=0`.

## Commandes utiles
Compilation:
```
make
make bonus
make clean
make fclean
make re
```

Valgrind:
```
make valgrind
```
Flags par defaut:
```
--leak-check=full --show-leak-kinds=all --track-origins=yes
```
Exemple avec une map:
```
make valgrind VALGRIND_ARGS="maps/ma_map.cub"
```

Docker (raccourcis Makefile):
```
make docker-build
make docker-shell
make docker-make
```

Docker (commandes directes):
```
docker build -t cub3d .
docker run --rm -it -v "$PWD":/workspace cub3d
```

## Auteurs
- [Eric Delplancq](https://github.com/erdelp)
- [Mabrouk Chouikri](https://github.com/mchouikr)