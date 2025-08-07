.PHONY : install update ref gz
install: doc ref gz
	$(MAKE) update
update :
	sudo apt update
	sudo apt install -uy `cat apt.Debian` $(APT)
ref    : $(REF)
gz     : $(GZ)
