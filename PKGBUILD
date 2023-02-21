# Maintainer:  ivanp7
# Contributor: ivanp7

_pkgname=st
pkgname=$_pkgname-ivanp7
pkgver=0.9
pkgrel=1
pkgdesc="A simple virtual terminal emulator for X."
url="https://st.suckless.org"
arch=('i686' 'x86_64' 'armv7h')
license=('MIT')
depends=(libxft)
makedepends=('ncurses' 'libxext')
provides=($_pkgname)
conflicts=($_pkgname)
source=('arg.h' 'config.h' 'config.mk'
    'keycodes.patch' 'LICENSE' 'Makefile'
    'README' 'README.terminfo.rst' 'st.1' 'st.c' 'st.h'
    'st.info' 'terminfo.patch' 'win.h' 'x.c')
sha256sums=('1a10fac42d03b3a1231cd6998a73fb4ab4f191694628953e7229f6de2053a985'
            '11b04e599835e397b2bdf26dcb232cf469ebbf5b2110127ae86d271b4230afc2'
            '83bf92895bac2c67c1a920e99292d13dba0775973dad6a45700135379221434d'
            '5c18adcf729d316578864797882cec9e0e475c04b1ff5063cc75d9150f07e818'
            '5c25b701b4482ccc8d5ea0770e553ad8a8c5c87650df07543b3b3f9456726d54'
            'e044cdf7af1c672ed40f84a2bbebf20ca257ba78b72ea9d0bf5bd4ae6edb410c'
            'f767c242485eb537f0df13cbcc182980d29152a6e25036cf65f334fb3ae8b29e'
            '0ebcbba881832adf9c98ce9fe7667c851d3cc3345077cb8ebe32702698665be2'
            '5b0d65d135fcc3d51f60e4fe4d86c5bbd1331266f9b38ecfb86914668c03921c'
            'd163c7f0c96097664523610224b19b5d21c6163bb92a21c590a28398f06cb0c8'
            '283e9b43ae2128a208c5d764f2b9057b5bb29aab9d4f80d6f10ec3e884343d86'
            '2eb2f15957b8132a2d25129c24bb97f64657bd821447f36ef2cf0526b42846e8'
            'f9deea445a5c6203a0e8e699f3c3b55e27275f17fb408562c4dd5d649edeea23'
            '69f068262ea55eca8dd7a3ec148e778f7ca71971eac80ea85bba220758ddc61f'
            '0e3d708ad7d91cc9cc6e4357ed0d7434ee94abfe3ca7b58f878b6a090c30f25b')

prepare() {
    patch < terminfo.patch
    patch < keycodes.patch
    sed -i -E 's/^(\s*)it#8,/\1it#4,/' st.info
}

build() {
  make PREFIX=/usr DESTDIR="$pkgdir" X11INC=/usr/include/X11 X11LIB=/usr/lib/X11
}

package() {
  make PREFIX=/usr DESTDIR="$pkgdir" install

  local shrdir="$pkgdir/usr/share"
  local licdir="$shrdir/licenses/$pkgname"
  local docdir="$shrdir/doc/$pkgname"
  local installopts='--mode 0644 -D --target-directory'

  install $installopts "$licdir" "$srcdir/LICENSE"
  install $installopts "$docdir" "$srcdir/README"
  install $installopts "$docdir" "$srcdir/README.terminfo.rst"
  install $installopts "$shrdir/$pkgname" "$srcdir/st.info"
}

