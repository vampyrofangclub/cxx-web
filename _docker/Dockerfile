FROM ubuntu:22.04
RUN apt-get update
RUN apt-get install -y curl xz-utils
RUN apt-get install -y lsb-release wget software-properties-common gnupg
RUN bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"
RUN curl -SL https://nodejs.org/dist/v20.10.0/node-v20.10.0-linux-x64.tar.xz | tar -xJC .
RUN echo 'export PATH=/node-v20.10.0-linux-x64/bin:$PATH' >> ~/.bashrc
CMD [ "/bin/bash" ]