all :
	$(MAKE) -C ./trinity/build
	$(MAKE) -C ./app/build

clean:
	$(MAKE) clean -C ./trinity/build
	$(MAKE) clean -C ./app/build
	rm -f ./app.exe

install : all
	./app.exe