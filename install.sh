#!/usr/bin/env bash

: "${PREFIX:="$HOME/.lv2"}"

meson builddir
ninja -C builddir

rm -rf $PREFIX/dynamite.lv2
mkdir -p $PREFIX/dynamite.lv2
cp {dynamite,manifest}.ttl builddir/dynamite.{so,dylib,dll} $PREFIX/dynamite.lv2/