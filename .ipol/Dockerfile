FROM registry.ipol.im/ipol:v1-py3.9

RUN mkdir -p /workdir/src
RUN mkdir -p /workdir/bin
RUN mkdir -p /workdir/exec

WORKDIR /workdir/src
COPY . .
RUN cmake . && make -j && mv random_mask /workdir/bin/ 
RUN cd src_random_mask && make -j && mv Inpainting /workdir/bin/ 

ENV bin /workdir/bin/
COPY .ipol/run.sh /workdir/bin

WORKDIR /workdir/exec
