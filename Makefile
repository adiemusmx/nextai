all:
	$(MAKE) -C ./trinity
	$(MAKE) -C ./app
	cp ./app/app.exe ./app.exe -f

clean:
	$(MAKE) clean -C ./trinity
	$(MAKE) clean -C ./app
	rm -f ./app.exe

install : all
	./app.exe