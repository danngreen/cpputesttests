#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = dgtests

#--- Inputs ----#
CPPUTEST_HOME = cpputest
CPP_PLATFORM = Gcc
PROJECT_HOME_DIR = .

SRC_DIRS = \
	src/util\
	src/LedDriver \

TEST_SRC_DIRS = \
	.\
	mocks\
	tests/LedDriver\
	tests/util\
	tests\

	
INCLUDE_DIRS =\
  .\
  $(CPPUTEST_HOME)/include\
  include/\
  include/IO\
  mocks\
  include/util\
  include/LedDriver\

MOCKS_SRC_DIRS = \
	mocks\

# Figure out how to ask if gcc7 vs clang, gcc7 only right now
# CPPUTEST_WARNINGFLAGS += -Wno-unknown-warning-option
# CPPUTEST_WARNINGFLAGS += -Wno-covered-switch-default
# CPPUTEST_WARNINGFLAGS += -Wno-reserved-id-macro
# CPPUTEST_WARNINGFLAGS += -Wno-keyword-macro
# CPPUTEST_WARNINGFLAGS += -Wno-documentation
# CPPUTEST_WARNINGFLAGS += -Wno-missing-noreturn

CPPUTEST_WARNINGFLAGS += -Wall 
CPPUTEST_WARNINGFLAGS += -Werror
CPPUTEST_WARNINGFLAGS += -Wswitch-default
CPPUTEST_WARNINGFLAGS += -Wno-format-nonliteral
CPPUTEST_WARNINGFLAGS += -Wno-sign-conversion 
CPPUTEST_WARNINGFLAGS += -Wno-pedantic 
CPPUTEST_WARNINGFLAGS += -Wno-shadow
CPPUTEST_WARNINGFLAGS += -Wno-missing-field-initializers
CPPUTEST_WARNINGFLAGS += -Wno-unused-parameter
CPPUTEST_CFLAGS += -Wall
CPPUTEST_CFLAGS += -Wstrict-prototypes
CPPUTEST_CFLAGS += -pedantic
CPPUTEST_CFLAGS += -Wno-missing-prototypes

#LD_LIBRARIES = -lpthread

include $(CPPUTEST_HOME)/build/MakefileWorker.mk

.PHONY: cpputest
cpputest: cpputest/lib/libCppUTest.a

cpputest/lib/libCppUTest.a:
	cd cpputest; autoreconf . -i && ./configure && make tdd
