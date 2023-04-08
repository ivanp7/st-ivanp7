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
    'LICENSE' 'Makefile' 'README' 'README.terminfo.rst'
    'st.1' 'st.c' 'st.h' 'st.info' 'win.h' 'x.c')
sha256sums=('1a10fac42d03b3a1231cd6998a73fb4ab4f191694628953e7229f6de2053a985'
            'e8366b6b7840759157761b4d311028fa29b846f393b9e928a2587b3ac9bffdd1'
            '808dbefe40e81b88da173985e1bd5c0a0d88d517b7cc1c6d68753e586ffe1698'
            '8c9ed900541522213d29619a8fe0919c244170017747856e064602151a25227e'
            '230ea5509543fa0c9b3b0ffeccc58abd9db5e4f7f45b3f6091b3abd858f84881'
            'ed03d3204efa38d831315f876fc4bb743e58447caffd67a146a7ae9be67aabda'
            '5c25b701b4482ccc8d5ea0770e553ad8a8c5c87650df07543b3b3f9456726d54'
            '32f76ab3c9ad5f05b068669a10e268d50100d5ae5324c5e73a7e207c2b557b0d'
            'f767c242485eb537f0df13cbcc182980d29152a6e25036cf65f334fb3ae8b29e'
            '0ebcbba881832adf9c98ce9fe7667c851d3cc3345077cb8ebe32702698665be2'
            'd7f6b3524d518d9da0f14cbd85cecf241396b329aaa1ad0d0b3c92a98c56d596'
            '55ae5fc9a79cde078f6c12c46fe5a8451a946f3a0462f304138bbcdfbd4cd100'
            'eefd1a36b7a993a3f3f8458537746dc654bafcbb1e7b82e76058ccf06dd34b16'
            'e0c32f2f2640c0ef4ce1f77c56dd0155d568a741c121735eff66715283af52fd'
            '1beda4e9b02069c5dce51e66a590ab87a646138dfa3187c6c5e5178690bf6a85'
            '301c627035aa0f825c3adfeee029744accbb2c860a1fb47c9833b0319feb371c')

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

