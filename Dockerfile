# replace 'templatebot' with the name of your bot in the paths

FROM brainboxdotcc/dpp:latest

WORKDIR /usr/src/templatebot

COPY . .

WORKDIR /usr/src/templatebot/build

RUN cmake ..
RUN make -j$(nproc)

ENTRYPOINT [ "/usr/src/templatebot/build/templatebot" ]
