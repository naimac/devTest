##
## Author: Mickaël BLET
##

#------------------------------------------------------------------------------
# common
#------------------------------------------------------------------------------

# choose your compilation mode at 'make' call
#	modes: (debug, release, lib_debug, lib_release, test)
#	default value: debug
MODE					=	debug

# define version of module
#	default value: 0.0.0
VERSION					=	1.0.0

# name of your binary
#	default value: (name of Makefile current directory)
BINARY_NAME				=

# name of your library
#	default value: (name of Makefile current directory)
LIBRARY_NAME			=

#------------------------------------------------------------------------------
# directories
#------------------------------------------------------------------------------

# destination path of your binaries (not forget the last '/')
#	default value: bin/
BINARY_DIRECTORY		=	../../bin/

# destination path of your libraries (not forget the last '/')
#	default value: lib/
LIBRARY_DIRECTORY		=	../../lib/

# source path (not forget the last '/')
#	default value: src/
SOURCE_DIRECTORY		=	./src/

# source test path (not forget the last '/')
#	default value: test/
TEST_DIRECTORY			=	./test/

# include path (not forget the last '/')
#	default value: include/
INCLUDE_DIRECTORY		=	./include/

# object path (not forget the last '/')
#	default value: obj/
OBJECT_DIRECTORY		=	./obj/

#------------------------------------------------------------------------------
# compilation
#------------------------------------------------------------------------------

# extention of source file
#	default value: .c
SOURCE_EXTENTION		=	.cpp

# exclude source for binary
BINARY_EXCLUDE_SOURCE	=	

# exclude source for library
LIBRARY_EXCLUDE_SOURCE	=	main.cpp

# exclude source for test
TEST_EXCLUDE_SOURCE		=

# compilation line:
#	$(COMPILER) $(FLAGS) ... $(OPTIONS)

DEBUG_COMPILER			=	$(CXX)
RELEASE_COMPILER		=	$(CXX)
TEST_COMPILER			=	$(CXX)

DEBUG_FLAGS				=	-std=c++11 -Wall -Wextra -ggdb3
RELEASE_FLAGS			=	-std=c++11 -Wall -Wextra -Werror -O2
TEST_FLAGS				=	-std=c++11 -Wall -Wextra -ggdb3

DEBUG_OPTIONS			=	-DVERSION=\"$(VERSION)\" \
							-I$(INCLUDE_DIRECTORY) -I../../common/include/ \
							-L$(LIBRARY_DIRECTORY) \
							-lprotobuf -lproto-debug \
							-lnetconfServer-debug \
							-lnetconf2 -lyang \
							-lpthread # lpthread toujours en dernier
RELEASE_OPTIONS			=	-DVERSION=\"$(VERSION)\" \
							-I$(INCLUDE_DIRECTORY) -I../../common/include/ \
							-L$(LIBRARY_DIRECTORY) \
							-lprotobuf -lproto-release \
							-lnetconfServer-release \
							-lnetconf2 -lyang \
							-lpthread #lpthread toujours en dernier
TEST_OPTIONS			=	-DVERSION=\"$(VERSION)\"  \
							-I$(INCLUDE_DIRECTORY) -I../../common/include/ \
							-L$(LIBRARY_DIRECTORY) \
							-l$(LIBRARY_NAME)-debug \
							-lnetconf2 -lyang \
							-lgtest -lgtest_main -lgmock -lpthread -lprotobuf -lproto-debug

DEBUG_DEPENDENCIES		=	$(LIBRARY_DIRECTORY)libproto-debug.a \
							$(LIBRARY_DIRECTORY)libnetconfServer-debug.a

RELEASE_DEPENDENCIES	=	$(LIBRARY_DIRECTORY)libproto-release.a \
							$(LIBRARY_DIRECTORY)libnetconfServer-release.a 

TEST_DEPENDENCIES		=	$(LIBRARY_DIRECTORY)lib$(LIBRARY_NAME)-debug.a $(LIBRARY_DIRECTORY)libproto-debug.a #path_to_-lib_toto.a

include ../../module.mk

#Library dependence 
#lib_toto.a: 
# $(MAKE) lib_debug -C ../toto/

$(LIBRARY_DIRECTORY)libproto-debug.a:
	$(MAKE) -C ../../common/proto

$(LIBRARY_DIRECTORY)libnetconfServer-debug.a:
	$(MAKE) MODE=debug common -C ../../

$(LIBRARY_DIRECTORY)libnetconfClient-debug.a:
	$(MAKE) MODE=debug common -C ../../

$(LIBRARY_DIRECTORY)libnetconfServer-release.a:
	$(MAKE) MODE=release common -C ../../

$(LIBRARY_DIRECTORY)libnetconfClient-release.a:
	$(MAKE) MODE=release common -C ../../

exe_test:	test
	$(foreach bin,$(BINARIES_TEST),$(bin) || exit;)

PHONY:
