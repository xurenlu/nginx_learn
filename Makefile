
default:	build

clean:
	rm -rf Makefile objs

build:
	$(MAKE) -f objs/Makefile
	$(MAKE) -f objs/Makefile manpage

install:
	$(MAKE) -f objs/Makefile install

upgrade:
	./object_echo-nginx-module/sbin/nginx -t

	kill -USR2 `cat ./object_echo-nginx-module/logs/nginx.pid`
	sleep 1
	test -f ./object_echo-nginx-module/logs/nginx.pid.oldbin

	kill -QUIT `cat ./object_echo-nginx-module/logs/nginx.pid.oldbin`
