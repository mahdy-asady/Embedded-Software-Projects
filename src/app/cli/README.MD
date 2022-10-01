# Command Line Interface Using Uart Communication
So I have to create a cli to communicatite board using uart for managing GPIO pins.
I decided to add another functionality to it! I added timer!
Note that for this project I only used STM32 hardware and it not ported to avr yet!

## Hardware Requirements:
1. STM32 Development Board (I used a board based on STM32F107VC)
2. STM32 Debugger & Programmer (ST-LINK or J-Link)
3. USB to Serial Adapter. (I used FT232 based board)

## Running steps:
1. **Planning**:
    I thought that it is good to have a modular project structure, so anytime it needed to add any new feature, costs be acceptable.
    Initial modules I considered:
    1. User Interaction module **CliInterface**.(I know that its a redundant word usage!)
    2. Command Interpreting module **CommandInterpreter**.
    3. GPIO interaction module **GPIOModule**.
    4. Timer interaction module **TimerModule**.
2. **CLI Usage**:
   So, after all. turn everything on. you will see a welcome message on Serial cim. window. type help all available commands will be listed.
   commands are separated by dot between sections. for example to turn gpio PortD Pin5 on just type gpio.on.d.5(ofcourse you have to set it as output pin using gpio.output.d.5 before commiting that command).
   I will complete help section so when you type help.Command the help of that command will bring up.

**Preview**: (Click for Video!)

https://user-images.githubusercontent.com/60986124/193429232-c5154ca9-df38-4d1f-a7b4-4330e1528cf2.mp4

