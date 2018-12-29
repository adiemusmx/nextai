include ../build/configuration.mk

all:
	$(MAKE) -C ../base
	$(MAKE) -C ../render_system
	$(MAKE) -C ../trinity
	$(MAKE) -C ../app
	$(CXX) $(LIBS_DIRS) $(LDFLAGS) -o app

clean:
	$(MAKE) clean -C ../base
	$(MAKE) clean -C ../render_system
	$(MAKE) clean -C ../trinity
	$(MAKE) clean -C ../app
	rm -f ./app
