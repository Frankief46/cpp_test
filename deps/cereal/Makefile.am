PACKAGE=cereal
REPO_TAG=v1.2.2

if DEBUG
BUILD_TYPE=debug
BUILD_DIR=debug
else
BUILD_TYPE=release
BUILD_DIR=release
endif

all-local:
	if [ ! -d $(PACKAGE) ]; then \
		git clone -b $(REPO_TAG) --single-branch --depth 1 https://github.com/USCiLab/cereal.git $(PACKAGE); \
	fi
	mkdir -p $(abs_top_builddir)/include;
	cp -R $(PACKAGE)/include/cereal $(abs_top_builddir)/include;

check-local:
	if [ -f $(PACKAGE)/Makefile ]; then \
		cd $(PACKAGE) && $(TOOLCHAIN_OPTS) cmake -DCMAKE_INSTALL_PREFIX=$(abs_top_builddir) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE); \
		cd $(PACKAGE) && cmake --build .;\
	fi

install-exec-local:
	if [ -f $(PACKAGE)/Makefile ] && [ ! -d $(abs_top_builddir)/include/cereal ]; then \
		cd $(PACKAGE) && $(TOOLCHAIN_OPTS) cmake --build . --target install; \
	fi

uninstall-local:
	if [ -d $(abs_top_builddir)/include/cereal ]; then \
		rm -rf $(abs_top_builddir)/include/cereal; \
	fi

clean-local:
	if [ -f $(PACKAGE)/Makefile ]; then \
		cd $(PACKAGE) && $(TOOLCHAIN_OPTS) cmake --build . --target clean; \
	fi

distclean-local:
	if [ -f $(PACKAGE)/Makefile ]; then \
		cd $(PACKAGE) && $(TOOLCHAIN_OPTS) cmake --build . --target clean; \
	fi
	rm -rf $(PACKAGE)

