# templatebot

CMake template for a simple D++ bot. This template assumes that D++ is already installed systemwide.

## Compilation

    mkdir build
    cd build
    cmake ..
    make -j

## Running the template bot

Create a config.json in the directory above the build directory:

    { "token": "your bot token here" }

Start the bot:

    cd build
    ./templatebot

## Extending the bot

You can add as many header files and .cpp files into the src and include folders as you wish. All .cpp files in the src directory will be linked together into the bot's executable.

## Renaming the bot

To rename the bot, search and replace "templatebot" in the `CMakeLists.txt` with your new bots name and then rename the templatebot folder in include. Rerun `cmake ..` from the `build` directory and rebuild.

# templatebot
