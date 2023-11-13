TARGET      = bfi
SRC        := src/bfi.c

PREFIX     ?= /usr/local
INSTALL     = install -Dm755
RM         ?= rm -f
PKG_CONFIG ?= pkg-config

COMPILER      ?= g++
CFLAGS     += -Wall 
#IFLAGS      = --pkg gio-2.0
LFLAGS      = `$(PKG_CONFIG) --libs glib-2.0 gio-2.0`

all: $(TARGET)

$(TARGET): $(SRC)
	$(COMPILER) $(IFLAGS) $(SRC) -o $(TARGET)

install: $(TARGET)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	$(INSTALL) $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

clean:
	$(RM) ./bfi
