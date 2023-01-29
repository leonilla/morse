# morse
A UNIX-style command line utility to encode and decode messages using morse code.

Implemented features include:
- String encoding and decoding from command line using UNIX-style options and arguments.
- Text file encoding and decoding from command line using UNIX-style options and arguments.
- Prompt-based user friendly menu.
- Interactive mode that keeps the application open for ongoing encoding and decoding.

## Morse code
Morse code is a method used in telecommunication to encode text characters as standardized, variable-length sequences of two different signal durations, called *dots* and *dashes*, represented by **.** and **-** respectively.   

Characters within a word are separated by blank spaces, and words are separated by **/**.

International Morse code encodes the **26 basic Latin letters A-Z** (with no distinction between upper and lower case letters), the **Arabic numerals** (0-9), and a **set of punctuation signs**. 

## Dependencies and Requirements
Compilation requirements are minimal:
- A C compiler
- make 

## Installation instructions
1. Clone the repository from GitHub. Alternatively, download the code as a ZIP archive and extract its contents.
2. Change into the directory containing the code.
3. Run **make**

## Usage instructions
The application can be run with or without command line parameters.

### Interactive mode (no command line parameters)
Start the application by simply running **./morse**.

A menu containing the available options will be displayed. Simply tip in the desired option and press the "Enter" key.

Respond to the on-screen prompts by tipping in the requested information and pressing "Enter" again.

For instance, if you are holding a conversation-like message exchange, you could:
1. Start the application by running **./morse**.
2. Tip 'i' and press "Enter" to start the interactive mode.
3. When you see the "Message:" prompt, tip in your input and press "Enter".
* If you input a message that contains only a series of spaces, '-', '/' and '.',  it will be assumed to be a morse-encoded message. It will be decoded, and the decoded message will be displayed.
* If you input a message containing characters A-Z (both upper- and lowercase), numbers 0-9 and/or punctuation symbols, the message will be encoded and the corresponding morse-encoded message will be displayed.

   In this mode, each message you input will be processed and the corresponding output will be shown, followed by a prompt for a new message. This way, you can encode the first message of your conversation, decode the message you receive as a reply, encode your reply and so on and so forth.

4. Once your message exchange is over, you can exit this mode by typing **exit()** and pressing "Enter".


### UNIX-Style mode (run with command line parameters)
You can use command line parameters to have the application start, complete a specific task, and close upon completion.

#### Processing strings

The syntax for decoding or encoding a string is

   ```morse [MODE] [\"QUOTED STRING\"]```

For example, to encode the string "String to encode"

   ```morse -E "String to encode"``` or ```morse --encode "String to encode"```

To decode the string "... - .-. .. -. --." 

   ```morse -D "... - .-. .. -. --."``` or ```morse --decode "... - .-. .. -. --."```

#### Processing text files

The syntax for decoding or encoding a file is

   ```morse [MODE] [INPUTFLAG] [FILENAME] [OUTPUTFLAG] [FILENAME]```

So, to decode the contents of file *input.file* onto *output.file*:

   ```morse -D -I <path/to/input.file> -O <path/to/output.file>``` or ```morse --decode -I <path/to/input.file> -O <path/to/output.file>```

To encode the contents of file *input.file* onto *output.file*:

   ```morse -E -I <path/to/input.file> -O <path/to/output.file>``` or ```morse --encode -I <path/to/input.file> -O <path/to/output.file>```

This help page can be displayed in the command line by running 

   ```"morse -H"``` or ```"morse --help"```


## License
This project is licensed under the GNU GPLv3 license. Feel free to use, distribute and modify this project as you see fit, but please remember to disclose its source.