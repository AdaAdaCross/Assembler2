FROM ubuntu
COPY lab3.cpp .
RUN apt-get update
RUN apt-get -y install g++
RUN g++ -o lab3 lab3.cpp
CMD ./lab3
