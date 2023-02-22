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
source=('arg.h' 'boxdraw.c' 'boxdraw_data.h'
    'config.h' 'config.keys.h' 'config.mk'
    'keycodes.patch' 'LICENSE' 'Makefile'
    'README' 'README.terminfo.rst' 'st.1' 'st.c' 'st.h'
    'st.info' 'terminfo.patch' 'win.h' 'x.c')

prepare() {
    : # sed -i -E 's/^(\s*)it#8,/\1it#4,/' st.info
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

sha256sums=('1a10fac42d03b3a1231cd6998a73fb4ab4f191694628953e7229f6de2053a985'
            'e8366b6b7840759157761b4d311028fa29b846f393b9e928a2587b3ac9bffdd1'
            '808dbefe40e81b88da173985e1bd5c0a0d88d517b7cc1c6d68753e586ffe1698'
            'bee23a20e689c008164a54dc0dfb826142e48d843ea83798d741c57f013b3a51'
            '4515e787d7f379761fedbb15690131fed6d33a22565974e80f2920187b0abdaf'
            'ed03d3204efa38d831315f876fc4bb743e58447caffd67a146a7ae9be67aabda'
            '5c18adcf729d316578864797882cec9e0e475c04b1ff5063cc75d9150f07e818'
            '5c25b701b4482ccc8d5ea0770e553ad8a8c5c87650df07543b3b3f9456726d54'
            '32f76ab3c9ad5f05b068669a10e268d50100d5ae5324c5e73a7e207c2b557b0d'
            'f767c242485eb537f0df13cbcc182980d29152a6e25036cf65f334fb3ae8b29e'
            '0ebcbba881832adf9c98ce9fe7667c851d3cc3345077cb8ebe32702698665be2'
            'bad340ce6212686ce90b93d48e7949e8eaff69be16518e86406cfc3fd395f155'
            'da19cf63bc53a67b3fa2c1b4300b665bbbb6ffdfaa82aeace8979ae0bd731ee8'
            'b0bd278616c631dc87b562439dc0946d6c9a31b97c7bb1f17660120aee90fb94'
            'd1fe0b11fd6eb668b068a8f811c27500d93cdc9f509bf2225ea50ab8d79f8dea'
            'f9deea445a5c6203a0e8e699f3c3b55e27275f17fb408562c4dd5d649edeea23'
            '1beda4e9b02069c5dce51e66a590ab87a646138dfa3187c6c5e5178690bf6a85'
            '9404788be4b9af115bdd66e71f8dae3fb3cefd1e179aaa3a3f77a0155af43858')
