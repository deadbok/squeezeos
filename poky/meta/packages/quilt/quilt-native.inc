require quilt_${PV}.inc

SRC_URI_append_build-darwin = "?   file://non-gnu.patch;patch=1 "
RDEPENDS_${PN} = "diffstat-native patch-native bzip2-native util-linux-native"

SRC_URI += "file://patch-version-fix.patch;patch=1 "

INHIBIT_AUTOTOOLS_DEPS = "1"

inherit autotools native

PATCHTOOL = "patch"
EXTRA_OECONF = "--disable-nls"

do_configure () {
	autoconf
	oe_runconf
}

# Dummy quiltrc file for patch.bbclass
do_install_append () {
	install -d ${STAGING_BINDIR_NATIVE}/
	touch ${STAGING_BINDIR_NATIVE}/quiltrc
}
