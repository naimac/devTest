
from registry.gitlab.sepro-group.com/integration/i586_linux:16233 AS lua_builder
COPY tc /app/tc
COPY bp /app/bp
RUN mkdir -p /app/install/lib/i386-linux-gnu
RUN mkdir -p /app/install/usr/include/
COPY k2ctrl /app/k2ctrl
RUN cp bp/external/*.h /app/install/usr/include/
RUN cp bp/lib/libBPApi.so /app/install/lib/i386-linux-gnu/libBPApi.so.2 && cd /app/install/lib/i386-linux-gnu/ && ln -s  libBPApi.so.2 libBPApi.so
RUN cp tc/external/*.h /app/install/usr/include/
RUN mkdir -p /app/install/usr/include/TcClient && cp tc/external/TcClient/*.h /app/install/usr/include/TcClient
RUN cp tc/lib/i386/libTcClient.so /app/install/lib/i386-linux-gnu/libTcClient.so.0 && cd /app/install/lib/i386-linux-gnu/ && ln -s  libTcClient.so.0 libTcClient.so
RUN cp k2ctrl/external/*.h /app/install/usr/include/
RUN cp k2ctrl/lib/libK2Ctrl.so /app/install/lib/i386-linux-gnu/libK2Ctrl.so

FROM registry.gitlab.sepro-group.com/integration/i586_linux:16233
RUN apt-get update && apt-get install -y --no-install-recommends \
	libbison-dev:i386 \
        libreadline6:i386 \
	libfl-dev:i386 bison flex \
	lua5.2-dev:i386 \
	valgrind:i386 \
	uuid-dev:i386 \
	libuuid1:i386 \
	gdbserver \
	&& rm -rf /var/lib/apt/lists/*

COPY --from=lua_builder /app/install /
