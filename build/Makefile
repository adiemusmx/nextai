all:
	$(MAKE) -C ../base
	$(MAKE) -C ../render_system
	$(MAKE) -C ../trinity
	$(MAKE) -C ../app
	cp ./app/app.exe ./app.exe -f

clean:
	$(MAKE) clean -C ../base
	$(MAKE) clean -C ../render_system
	$(MAKE) clean -C ../trinity
	$(MAKE) clean -C ../app
	rm -f ./app.exe

install : clean all
	./app.exe