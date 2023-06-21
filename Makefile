SUBDIRS := $(wildcard */*)

all: $(SUBDIRS)
$(SUBDIRS):
	@echo ">>>>>>>>>>>>> SUBDIRS $@"
	$(MAKE) -C $@
	@echo "\n"

clean:
	for sub in $(SUBDIRS) ; do \
		$(MAKE) -C $$sub clean; \
	done

.PHONY: all $(SUBDIRS)