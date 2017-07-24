REPO_TAG=v1.8.2

if DEBUG
BUILD_DIR=debug
else
BUILD_DIR=release
endif

all-local:
	if [ ! -d catch ]; then \
		git clone https://github.com/philsquared/Catch.git catch; \
		cd catch; \
		git checkout $(REPO_TAG); \
	fi
	cp ./catch/single_include/catch.hpp $(abs_top_builddir)/include;
	cp ./catch/include/reporters/catch_reporter_automake.hpp $(abs_top_builddir)/include;
	
check-local:
	if [ -f catch/single_include/catch.hpp ]; then \
	fi

install-exec-local:
	if [ -f catch/single_include/catch.hpp ]; then \
		cd catch && cp single_include/catch.hpp $(abs_top_builddir)/include; \
	fi

uninstall-local:
	if [ -f catch/single_include/catch.hpp ]; then \
		cd catch && rm -f $(abs_top_builddir)/include/catch.hpp; \
	fi

clean-local:
	if [ -f catch/single_include/catch.hpp ]; then \
		cd catch && rm -f $(abs_top_builddir)/include/catch.hpp; \
	fi

distclean-local:
	rm -rf catch