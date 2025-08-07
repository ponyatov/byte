.PHONY: install update
install: doc ref gz
	$(MAKE) update
update:
	sudo apt update
	sudo apt install -uy `cat apt.Debian`
ref: $(REF)
gz:  $(GZ)
