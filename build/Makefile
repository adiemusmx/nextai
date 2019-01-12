include ../build/configuration.mk

all:
	$(MAKE) -C ../base
	$(MAKE) -C ../render_system
	$(MAKE) -C ../trinity
	$(MAKE) -C ../app
	cp -f ../app/lib/app ./exe/app

clean:
	$(MAKE) clean -C ../base
	$(MAKE) clean -C ../render_system
	$(MAKE) clean -C ../trinity
	$(MAKE) clean -C ../app
	rm -f ./app
