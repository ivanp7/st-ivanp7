#!/bin/sh

cd -- "$(dirname -- "$0")"

DIR="$PWD"

git clone "https://github.com/LukeSmithxyz/st.git" st-luke-git && cd st-luke-git || exit 1
sed -i 's/^pkgname=.*$/pkgname=st-ivanp7/' PKGBUILD
makepkg --noconfirm -o

cd src/st/

install -m 644 -t . "$DIR/config.h" "$DIR/st.1" "$DIR/keycodes.patch"
patch < keycodes.patch
sed -i -E 's/^(\s*)it#8,/\1it#4,/' st.info

cd ../..

makepkg --noconfirm -efsr && mv *.pkg.tar.zst ../

