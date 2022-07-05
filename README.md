# keyboard-layout-skip
The small CLI utility that skips one or few keyboard layouts on Windows.
In while loop utility checks if current keyboard layout is in list and then it skips it.
For example: you have Russian, English and Japanese keyboard layouts.
You don't need the English layout but you can't remove it (because you want to keep the English language).
So you can use this utility in order to skip the English layout when you press SHIFT+ALT.
# Installation
### Build Requirement
In order to install you need:
* git [optional]
* cmake [optional]
* C++ compiler with at least C++11 standart.
## Build
Open cmd somewhere.
```
git clone https://github.com/Tykveg/keyboard-layout-skip.git
```
Or just download the source code and unpack somewhere.
```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
Your executable named `keyboard-layout-skip.exe` will be located in `keyboard-layout-skip/build/Release/keyboard-layout-skip.exe` so you can move it anywhere.
# Usage
With the same folder where **keyboard-layout-skip.exe** is located, you can create **config.txt** and **skips.txt** (see about them below).
To use this utility just launch **keyboard-layout-skip.exe** or open it with cmd.
 - keyboard-layout-skip.exe
 - config.txt
 - skips.txt
## Warning!
In order to work correctly, the console should be minimized all the time.
If the console is not minimized, the utility won't detect your keyboard layout correctly.
That's why the console will minimize automatically.
You can maximize the console windows to read some info and minimize it back though.
## config.txt
Configure the utility.
### Line format:
`var=value`
### Parameters:
* `delay=[int]` <- delay in ms between each layout checks. Default: 50.
More parameters coming soon (maybe).
### config.txt example:
```
// Writing comment
delay=49
```
## skips.txt
Keyboard layouts that would be skipped.
### Line format:
`hex_id`
### Default:
`0x04090409`
(so the utility skips en_US by default)
### skips.txt example (skipping en_US keyboard, pick one of the lines (except the comment obviously)):
```
// Writing comment
0x04090409
04090409
4090409
```
Each time you open the utility, you will see you keyboard layout list with the same order as in windows, so that's where you can find those hex IDs. Or you can reference [this table (Windows 10/11)](https://docs.microsoft.com/en-us/windows-hardware/manufacture/desktop/windows-language-pack-default-values?view=windows-10#keyboard-identifiers), but with extra numerals.
# Other info
Feel free to write about bugs/issues/questions/requests in `Issues`. I'm a beginner that's why I might have done something wrong. Thank you!
# Plans
I don't really plan to add some heavy features there and I want to keep this utility small and specific (specific to skip keyboard layouts).
But I do have plans to create a utility with GUI that switches different keyboard layouts with a different shortcuts (so it will be easier to organize your keyboard layouts if you have a lot of them).
And I also want to include some features from this small project.