BLACK_LIST = RemoteSystemsTempFiles
SUBDIRS = $(shell ls -d */)

all:
	for dir in $(SUBDIRS) ; do \
		make -C  $$dir ; \
	done

clean:
	rm -rf $(BLACK_LIST)
	for dir in $(SUBDIRS) ; do \
		make -C  $$dir clean; \
	done
